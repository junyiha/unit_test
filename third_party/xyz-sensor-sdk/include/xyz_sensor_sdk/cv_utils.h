/*
 * Copyright (c) XYZ Robotics Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: wengu003 <wen.gu@xyzrobotics.com>, 2023/07/06
 */

#pragma once

#include "xyz_sensor_sdk/sensor.h"

#include <opencv2/opencv.hpp>

namespace xyz::sensor {

inline cv::Mat to_cv_mat(const Sensor::ColorFrame& frame) {
  return cv::Mat(frame.height, frame.width, CV_8UC3, frame.ptr).clone();
}

inline cv::Mat to_cv_mat(const Sensor::DepthFrame& frame) {
  return cv::Mat(frame.height, frame.width, CV_32FC1, frame.ptr).clone();
}

inline cv::Mat to_cv_mat(const Sensor::PointXYZFrame& frame) {
  return cv::Mat(frame.height, frame.width, CV_32FC3, frame.ptr).clone();
}

}  // namespace xyz::sensor