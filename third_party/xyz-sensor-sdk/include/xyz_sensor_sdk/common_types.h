/*
 * Copyright (c) XYZ Robotics Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: yongqi <frank.lee@xyzrobotics.ai>, 2023/02/08
 */

#ifndef COMMON_TYPES
#define COMMON_TYPES
#include <string>
#include <vector>

namespace xyz::sensor {

/**
 * @brief This `xyz::sensor::Status` class is generally used to gracefully handle errors.
 */
class Status final {
 public:
  enum StatusCode : int {
    // common code
    kOk = 0,
    kCancellled = -1,
    kUnknown = -2,
    kInvalidArgument = -3,
    kDeadlineExceeded = -4,
    kNotFound = -5,
    kAlreadyExists = -6,
    kPermissionDenied = -7,
    kResourceExhausted = -8,
    kFailedPrecondition = -9,
    kAborted = -10,
    kOutOfRange = -11,
    kUnimplemented = -12,
    kInternal = -13,
    kUnavailable = -14,
    kDataLoss = -15,
    kUnauthenticated = -16,
    kDoNotUseReservedForFutureExpansionUseDefaultInSwitchInstead = -20
    // sensor code
    // @TODO(yongqi): add sensor specific code
  };

  Status() = default;

  Status(StatusCode code, const std::string& message) : code_(code), message_(message) {}

  Status(int code, const std::string& message)
      : code_(static_cast<StatusCode>(code)), message_(message) {}

  [[nodiscard]] bool ok() const { return code_ == StatusCode::kOk; }

  StatusCode code() const { return code_; }

  std::string message() const { return message_; }

 private:
  StatusCode code_{StatusCode::kOk};
  std::string message_;
};

class SensorInfo {
 public:
  std::string model;
  std::string id;
  std::string ip_address;
  std::string mac;
};

class SensorIntrinsic {
 public:
  unsigned width;
  unsigned height;
  /// [fx, 0, cx; 0, fy, cy; 0, 0, 1]
  std::vector<double> camera_matrix;
  /// Distortion model for all camera except fish-eye cam.
  /// the ful-length (14) distorion coefficients are :
  /// (k1,k2,p1,p2[,k3[,k4,k5,k6[,s1,s2,s3,s4[,τx,τy]]]]), where k_n counts
  /// for radial distortion, p for tangential distortion, s for prisim
  /// disortion and t for trapezoidal distortion. The array for storing
  /// coefficients must be size of 0, 4, 5, 8, 12 and 14
  std::vector<double> distortion;
};

}  // namespace xyz::sensor

#endif
