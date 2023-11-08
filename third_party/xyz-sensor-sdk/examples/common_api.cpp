#include <iostream>
#include <memory>

#include "xyz_sensor_sdk/sensor.h"

using namespace xyz::sensor;

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cout << "usage: common_api " << std::endl;
    std::cout << "or " << std::endl;
    std::cout << "common_api /path/to/camera_config.json";
    return 0;
  }
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
  if (sensor_list.empty() || sensor_list[0].model.find("XYZ-ST") == std::string::npos) {
    std::cout << "no XYZ camera found" << std::endl;
    return 0;
  }
  auto sensor_ptr = std::make_unique<Sensor>();
  status = sensor_ptr->Open(sensor_list[0]);
  if (!status.ok()) {
    std::cout << status.message() << std::endl;
    return status.code();
  }

  if (argc == 2) {
    std::string config_path = argv[1];
    status = sensor_ptr->LoadSettingsFromFile(config_path);
    if (!status.ok()) {
      std::cout << status.message() << std::endl;
      return status.code();
    }
  }

  status = sensor_ptr->Capture();
  if (!status.ok()) {
    std::cout << status.message() << std::endl;
    return status.code();
  }
  if (status.ok()) {
    Sensor::ColorFrame color_frame;
    sensor_ptr->GetColorFrame(color_frame);
    Sensor::DepthFrame depth_frame;
    sensor_ptr->GetDepthFrame(depth_frame);
    Sensor::PointXYZFrame point_cloud;
    sensor_ptr->GetPointXYZFrame(point_cloud);
  }
  std::string save_path = "camera.json";
  sensor_ptr->SaveSettingsToFile(save_path);
  sensor_ptr->Close();
  std::cout << "done" << std::endl;
}
