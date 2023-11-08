#include "XYZCamera.hpp"

XYZCamera::XYZCamera()
{
    sensor_ptr = std::make_unique<xyz::sensor::Sensor>();
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

    return true;
}

bool XYZCamera::Close()
{
    sensor_ptr->Close();
    
    return true;
}

bool XYZCamera::Start()
{
    auto status = sensor_ptr->Open(sensor_list[0]);
    if (!status.ok())
    {
        std::cout << status.message() << std::endl;
        return false;
    }
    status = sensor_ptr->Capture();
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