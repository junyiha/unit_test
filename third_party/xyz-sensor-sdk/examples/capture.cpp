#include <iostream>
#include <memory>
#include "xyz_sensor_sdk/sensor.h"

using namespace xyz::sensor;

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
      Sensor::DepthFrame depth_frame;
      sensor_ptr->GetDepthFrame(depth_frame);
      Sensor::PointXYZFrame point_cloud;
      sensor_ptr->GetPointXYZFrame(point_cloud);
    }
  }
  return 0;
}
