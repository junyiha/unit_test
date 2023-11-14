#include "XYZCamera.hpp"

XYZCamera::XYZCamera()
{
    sensor_ptr = std::make_unique<xyz::sensor::Sensor>();
    m_config_file = "/data/home/user/workspace/unit_test/data/xyz_camera/xyz_camera_settings.json";
}

XYZCamera::~XYZCamera()
{
}

bool XYZCamera::Open()
{
    auto status = xyz::sensor::Sensor::EnumerateConnectedSensors(sensor_list);
    if (!status.ok())
    {
        std::cout << status.message() << std::endl;
        return false;
    }
    std::cout << "found " << sensor_list.size() << " connected sensors:" << std::endl;
    for (const auto &info : sensor_list)
    {
        std::cout << info.id << ", " << info.model << ", " << info.ip_address << std::endl;
    }
    status = sensor_ptr->Open(sensor_list[0]);
    if (!status.ok())
    {
        std::cout << status.message() << std::endl;
        return false;
    }
    status = sensor_ptr->LoadSettingsFromFile(m_config_file);
    if (!status.ok())
    {
        std::cout << status.message() << std::endl;
        return false;
    }

    return true;
}

bool XYZCamera::Close()
{
    sensor_ptr->Close();
    
    return true;
}

bool XYZCamera::Start()
{
    auto status = sensor_ptr->Capture();
    if (!status.ok())
    {
        return false;
    }

    return true;
}

bool XYZCamera::Stop()
{
    return true;
}

bool XYZCamera::SaveColorFrame(std::string path)
{
    xyz::sensor::Sensor::ColorFrame color_frame;
    auto status = sensor_ptr->GetColorFrame(color_frame);
    if (!status.ok())
    {
        std::cerr << "Failed to get color frame from sensor pointer" << std::endl;
        return false;
    }
    cv::Mat color_img(color_frame.height, color_frame.width, CV_8UC3, color_frame.ptr);
    
    return cv::imwrite(path, color_img);
}

bool XYZCamera::Debug()
{
    auto status = sensor_ptr->SaveSettingsToFile("/data/home/user/workspace/unit_test/data/xyz_camera/xyz_camera_settings.json");
    if (!status.ok())
    {
        return false;
    }

    return true;
}

bool XYZCamera::GetColorImage(cv::Mat &out)
{
    xyz::sensor::Sensor::ColorFrame color_frame;
    auto status = sensor_ptr->GetColorFrame(color_frame);
    if (!status.ok())
    {
        std::cerr << "Failed to get color frame from sensor pointer" << std::endl;
        return false;
    }
    cv::Mat color_img(color_frame.height, color_frame.width, CV_8UC3, color_frame.ptr);

    out = color_img.clone();

    return true;
}

bool XYZCamera::GetDepthImage()
{
    xyz::sensor::Sensor::DepthFrame depth_frame;
    auto status = sensor_ptr->GetDepthFrame(depth_frame);
    if (!status.ok())
    {
        std::cerr << "Failed to get depth frame from sensor pointer" << std::endl;
        return false;
    }
    float *data_ptr = depth_frame.data.get();
    for (int i = 0; i < depth_frame.size(); i++)
    {
        std::cerr << "index: "<< i << ", data: " << data_ptr[i] << std::endl;
    }

    return true;
}

bool XYZCamera::GetPointCloudFrame()
{
    xyz::sensor::Sensor::PointXYZFrame point_frame;
    auto status = sensor_ptr->GetPointXYZFrame(point_frame);
    if (!status.ok())
    {
        std::cerr << "Failed to get point cloud frame from sensor pointer" << std::endl;
        return false;
    }
    float *data_ptr = point_frame.data.get();
    for (int i = 0; i < point_frame.size(); i++)
    {
        std::cerr << "index: "<< i << ", data: " << data_ptr[i] << std::endl;
    }

    return true;
}