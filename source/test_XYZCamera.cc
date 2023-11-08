/**
 * @file test_XYZCamera.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <unistd.h>
#include "XYZCamera.hpp"
#include "httplib.h"

// std::string server_addr = "http://192.169.0.152:28001";
std::string server_addr = "http://192.169.0.116:28001";

void Help()
{
    std::string info = R"(
        test_XYZCamera 

        --help
    )";

    std::cerr << info << std::endl;
}   

bool GetRobotStatus(std::string &out)
{
    httplib::Client client(server_addr);
    auto res = client.Get("/api/robots/cob/getPoint");
    if (res.error() != httplib::Error::Success)
    {
        return false;    
    }
    out = res->body;

    return true;
}

bool SaveXYZCameraFrame()
{
    std::string path = "/data/home/user/workspace/unit_test/data/xyz_camera/";
    XYZCamera xyz_camera;

    assert(xyz_camera.Open());
    assert(xyz_camera.Start());
    for (int i = 0; i < 10; i++)
    {
        std::string file = path;
        file += std::to_string(i);
        file += ".jpg";
        xyz_camera.SaveColorFrame(file);
        sleep(1);
    }
    xyz_camera.Close();

    return 0;
}

void CycleGetData()
{
    std::string path = "/data/home/user/workspace/unit_test/data/xyz_camera/";
    XYZCamera xyz_camera;

    assert(xyz_camera.Open());
    assert(xyz_camera.Start());

    std::string cmd;
    while (true)
    {
        cv::Mat tmp;
        xyz_camera.GetColorImage(tmp);
        cv::imwrite("/home/user/job/unit_test/data/xyz_camera/tmp.jpg", tmp);

        std::cerr << "input command(input q to quit | input c to continue)>>> " << std::endl;
        std::cin >> cmd;
        if (cmd == "q" || cmd == "quit")
        {
            std::cerr << "quit..." << std::endl;
            break;
        }
        else if (cmd == "c")
        {
            continue;
        }
        // 保存RGB图
        std::string img_file = path;
        time_t current_time = std::time(nullptr);
        img_file += std::to_string(current_time);
        img_file += ".jpg";
        assert(xyz_camera.SaveColorFrame(img_file));

        // 保存机械臂位姿数据
        std::string robot_status;
        assert(GetRobotStatus(robot_status));
        std::string status_file = path;
        status_file += std::to_string(current_time);
        status_file += ".json";
        std::ofstream file(status_file, std::ios::out);
        file.write(robot_status.c_str(), robot_status.size());
        file.close();
    }
    
    xyz_camera.Close();
}

void test_debug()
{
    XYZCamera xyz_camera;

    assert(xyz_camera.Open());
    assert(xyz_camera.Debug());

    xyz_camera.Close();
}

void test_point_cloud()
{
    XYZCamera xyz_camera;

    assert(xyz_camera.Open());
    assert(xyz_camera.Start());
    assert(xyz_camera.GetPointCloudFrame());

    xyz_camera.Close();
}

void test_depth_image()
{
    XYZCamera xyz_camera;

    assert(xyz_camera.Open());
    assert(xyz_camera.Start());
    assert(xyz_camera.GetDepthImage());

    xyz_camera.Close();
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "--test-get-robot-status")
        {
            std::string output;
            GetRobotStatus(output);
            std::cerr << output << std::endl;
        }
        else if (arg == "--test-depth-image")
        {
            test_depth_image();
        }
        else if (arg == "--test-point-cloud")
        {
            test_point_cloud();
        }
        else if (arg == "--test-debug")
        {
            test_debug();
        }
        else if (arg == "--test-save-xyz-camera-frame")
        {
            SaveXYZCameraFrame();
        }
        else if (arg == "--help")
        {
            Help();
        }
        else if (arg == "--cycle-get-data")
        {
            CycleGetData();
        }
        else 
        {
            std::cerr << "error input argument, try --help to get more information" << std::endl;
        }
    }

    return 0;
}