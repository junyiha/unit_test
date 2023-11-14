/**
 * @file test_xyz.cc
 * @author your name (you@domain.com)
 * @brief 星源哲相机
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

using namespace xyz::sensor;

std::string color_file = "/data/home/user/workspace/unit_test/data/auto_calibrate/xyz/color.jpg";
std::string depth_file = "/data/home/user/workspace/unit_test/data/auto_calibrate/xyz/depth.jpg";

int main(int argc, char *argv[]) {
  std::vector<SensorInfo> sensor_list;
  auto status = Sensor::EnumerateConnectedSensors(sensor_list);
  if (!status.ok()) {
    std::cout << status.message() << std::endl;
    return status.code();
  }
  std::cout << "found " << sensor_list.size() << " connected sensors:" << std::endl;
  for (const auto &info : sensor_list) {
    std::cout << info.id << ", " << info.model << ", " << info.ip_address << std::endl;
  }
  if (!sensor_list.empty()) {
    std::cout << "try to capture image using first connected sensor." << std::endl;
    auto sensor_ptr = std::make_unique<Sensor>();
    auto status = sensor_ptr->Open(sensor_list[0]);
    if (!status.ok()) {
      std::cout << status.message() << std::endl;
      return status.code();
    }
    status = sensor_ptr->Capture();
    if (status.ok()) {
      Sensor::ColorFrame color_frame;
      sensor_ptr->GetColorFrame(color_frame);
      cv::Mat color(color_frame.height, color_frame.width, CV_8UC3, color_frame.ptr);
      cv::imwrite(color_file, color);

      Sensor::DepthFrame depth_frame;
      sensor_ptr->GetDepthFrame(depth_frame);
      cv::Mat depth(depth_frame.height, depth_frame.width, CV_32F, depth_frame.ptr);
      cv::imwrite(depth_file, depth);

      Sensor::PointXYZFrame point_cloud;
      sensor_ptr->GetPointXYZFrame(point_cloud);
    }
  }
  return 0;
}
