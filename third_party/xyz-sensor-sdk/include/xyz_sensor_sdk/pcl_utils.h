/*
 * Copyright (c) XYZ Robotics Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: yongqi <frank.lee@xyzrobotics.ai>, 2023/05/12
 */

#pragma once

#include "xyz_sensor_sdk/sensor.h"
#include <pcl/point_types.h>
#include <opencv2/opencv.hpp>

namespace xyz::sensor {

inline void to_pcl(const Sensor::PointXYZFrame& point_xyz_frame,
                   pcl::PointCloud<pcl::PointXYZRGB>& cloud) {
  cloud.resize(point_xyz_frame.size());
  cloud.height = point_xyz_frame.height;
  cloud.width = point_xyz_frame.width;
  cloud.is_dense = false;
#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < point_xyz_frame.size(); i++) {
    int v = i / point_xyz_frame.width;
    int u = i % point_xyz_frame.width;
    cloud[i].x = point_xyz_frame(v, u, 0);
    cloud[i].y = point_xyz_frame(v, u, 1);
    cloud[i].z = point_xyz_frame(v, u, 2);
  }
}

inline void to_pcl(const Sensor::PointXYZFrame& point_xyz_frame,
                   const Sensor::ColorFrame& color_frame,
                   pcl::PointCloud<pcl::PointXYZRGB>& cloud) {
  cloud.resize(point_xyz_frame.size());
  cloud.height = point_xyz_frame.height;
  cloud.width = point_xyz_frame.width;
  cloud.is_dense = false;
#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < point_xyz_frame.size(); i++) {
    int v = i / point_xyz_frame.width;
    int u = i % point_xyz_frame.width;
    cloud[i].x = point_xyz_frame(v, u, 0);
    cloud[i].y = point_xyz_frame(v, u, 1);
    cloud[i].z = point_xyz_frame(v, u, 2);
    cloud[i].r = color_frame(v, u, 0);
    cloud[i].g = color_frame(v, u, 1);
    cloud[i].b = color_frame(v, u, 2);
  }
}

inline void to_pcl(const cv::Mat& point_xyz_frame, pcl::PointCloud<pcl::PointXYZRGB>& cloud) {
  auto size = point_xyz_frame.rows * point_xyz_frame.cols;
  cloud.resize(size);
  cloud.height = point_xyz_frame.rows;
  cloud.width = point_xyz_frame.cols;
  cloud.is_dense = false;
#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < size; i++) {
    int v = i / point_xyz_frame.cols;
    int u = i % point_xyz_frame.cols;
    auto& xyz = point_xyz_frame.at<cv::Vec3f>(v, u);
    cloud[i].x = xyz[0];
    cloud[i].y = xyz[1];
    cloud[i].z = xyz[2];
  }
}

inline void to_pcl(const cv::Mat& point_xyz_frame, const cv::Mat& color_frame,
                   pcl::PointCloud<pcl::PointXYZRGB>& cloud) {
  auto size = point_xyz_frame.rows * point_xyz_frame.cols;
  cloud.resize(size);
  cloud.height = point_xyz_frame.rows;
  cloud.width = point_xyz_frame.cols;
  cloud.is_dense = false;
#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < size; i++) {
    int v = i / point_xyz_frame.cols;
    int u = i % point_xyz_frame.cols;
    auto& xyz = point_xyz_frame.at<cv::Vec3f>(v, u);
    cloud[i].x = xyz[0];
    cloud[i].y = xyz[1];
    cloud[i].z = xyz[2];
    auto& rgb = color_frame.at<cv::Vec3b>(v, u);
    cloud[i].r = rgb[0];
    cloud[i].g = rgb[1];
    cloud[i].b = rgb[2];
  }
}

}  // namespace xyz::sensor
