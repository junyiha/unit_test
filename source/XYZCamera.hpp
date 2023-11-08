/**
 * @file XyzCamera.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <memory>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "xyz_sensor_sdk/sensor.h"

class XYZCamera
{

public:
    XYZCamera();
    virtual ~XYZCamera();

    bool Open();
    bool Close();
    bool Start();
    bool Stop();
    bool SaveColorFrame(std::string path);
    bool Debug();
    bool GetColorImage(cv::Mat &out);
    bool GetPointCloudFrame();
    bool GetDepthImage();

private:
    std::vector<xyz::sensor::SensorInfo> sensor_list;
    std::unique_ptr<xyz::sensor::Sensor> sensor_ptr;
    std::string m_config_file;
};