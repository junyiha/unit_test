/*
 * Copyright (c) XYZ Robotics Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: yongqi <frank.lee@xyzrobotics.ai>, 2023/02/08
 */

#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <cstdint>

#include "xyz_sensor_sdk/api_export.h"
#include "xyz_sensor_sdk/common_types.h"
#include "xyz_sensor_sdk/param.h"
#include "xyz_sensor_sdk/image.h"

namespace xyz::sensor {

/**
 * @brief This `xyz::sensor::Status` class is generally used to gracefully handle errors.
 */
class XYZ_SENSOR_API Sensor {
 public:
  /**
   * Type alias for a color frame, representing an color image with 3 channels (red, green, blue).
   */
  using ColorFrame = Image<char, 3>;

  /**
   * Type alias for a depth frame, representing a depth image with a single channel for depth
   * values.
   */
  using DepthFrame = Image<float, 1>;

  /**
   * Type alias for a point cloud frame, representing an image with 3 channels (x, y, z
   * coordinates).
   */
  using PointXYZFrame = Image<float, 3>;

  /**
   * Type alias for a normal frame, representing an image with a single channel for surface normals.
   */
  using NormalFrame = Image<char, 1>;

  /**
   * Type alias for an infrared frame, representing an image with a single channel for gray data.
   */
  using IRFrame = Image<char, 1>;

  /**
   * @brief Enumerates the connected XYZ devices and populates the provided vector with sensor
   * information.
   *
   * This static function retrieves information about the connected sensors and fills the provided
   * vector with SensorInfo objects, each containing details about a connected sensor.
   *
   * @param[out] sensors A vector to store the information of connected sensors.
   * @return Status code indicating the success or failure of the enumeration process.
   */
  static Status EnumerateConnectedSensors(std::vector<SensorInfo> &sensors);

  /**
   * @brief Checks if a sensor specified by the provided SensorInfo is accessible.
   *
   * This static function verifies whether a camera device, described by the given SensorInfo, is
   * accessible and can be connected.
   *
   * @param[in] info The SensorInfo object describing the sensor to check.
   * @return `true` if the sensor is accessible, `false` otherwise.
   */
  static bool IsSensorAccessible(const SensorInfo &info);

  /**
   * @brief Sets the IP configuration for a specified sensor.
   *
   * This static function allows setting the IP configuration (IP address, subnet mask, and gateway)
   * for a camera specified by the provided SensorInfo.
   *
   * @param[in] info The SensorInfo object describing the sensor to configure.
   * @param[in] ip The new IP address to set for the sensor.
   * @param[in] mask The subnet mask for the IP address.
   * @param[in] gateway The gateway IP address.
   * @return Status code indicating the success or failure of the configuration process.
   */
  static Status SetSensorIp(const SensorInfo &info, uint32_t ip, uint32_t mask, uint32_t gateway);

  /**
   * Constructor
   */
  Sensor() = default;

  /**
   * Destructor
   */
  ~Sensor();

  /**
   * No copy
   */
  Sensor(const Sensor &) = delete;

  /**
   * No copy
   */
  Sensor &operator=(const Sensor &) = delete;

  /**
   * @brief Opens a connection to the camera specified by the provided SensorInfo.
   *
   * This function attempts to establish a connection to the camera described by the given
   * SensorInfo. The connection process involves initializing communication channels and setting up
   * the camera for data acquisition.
   *
   * @param[in] info The SensorInfo object describing the sensor to connect to.
   * @param[in] timeout_ms The maximum time, in milliseconds, to wait for the connection to be
   * established. If not specified, a default timeout of 10,000 milliseconds (10 seconds) is used.
   * @return Status code indicating the success or failure of the connection process.
   */
  Status Open(const SensorInfo &info, int timeout_ms = 10000);

  /**
   * Opens a connection to a camera with the specified ID address and waits for up to the specified
   * timeout duration for the connection to be established.
   * @param[in] id The ID of the camera to be connected to.
   * @param[in] timeout_ms The maximum time, in milliseconds, to wait for the connection to be
   * established. If not specified, a default timeout of 10,000 milliseconds (10 seconds) is used.
   * @return Status code indicating the success or failure of the connection process.
   */
  Status OpenById(const std::string &id, int timeout_ms = 10000);

  /**
   * Opens a connection to a sensor with the specified IP address and waits for up to the specified
   * timeout duration for the connection to be established.
   * @param[in] ip The IP address of the camera to be connected to.
   * @param[in] timeout_ms The maximum time, in milliseconds, to wait for the connection to be
   * established. If not specified, a default timeout of 10,000 milliseconds (10 seconds) is used.
   * @return Status code indicating the success or failure of the connection process.
   */
  Status OpenByIp(const std::string &ip, int timeout_ms = 10000);

  /**
   * Closes the connection to the camera.
   */
  void Close();

  /**
   * @brief Initiates the data capture process from the opened sensor.
   *
   * This function starts the process of capturing data from the previously opened sensor. The
   * capture process gets data frames from camera, and waits for up to the specified timeout
   * duration for the capture to complete.
   *
   * @param[in] timeout_ms The maximum time, in milliseconds, to wait for the capture process to
   * complete. If not specified, a default timeout of 10,000 milliseconds (10 seconds) is used.
   * @return Status code indicating the success or failure of the capture process.
   */
  Status Capture(int timeout_ms = 10000);

  /**
   * @brief Retrieves the latest color frame captured by the sensor.
   * @param[out] color_frame A ColorFrame object to store the acquired color frame data.
   * @return Status code indicating the success or failure of retrieving the color frame.
   */
  Status GetColorFrame(ColorFrame &color_frame);

  /**
   * @brief Retrieves the latest depth frame captured by the sensor.
   * @param[out] depth_frame A DepthFrame object to store the acquired depth frame data.
   * @return Status code indicating the success or failure of retrieving the depth frame.
   */
  Status GetDepthFrame(DepthFrame &depth_frame);

  /**
   * @brief Retrieves the latest left ir frame captured by the sensor(Only for XYZ-ST camera).
   * @param[out] left_frame A IRFrame object to store the acquired left ir frame data.
   * @return Status code indicating the success or failure of retrieving the left ir frame.
   */
  Status GetLeftFrame(IRFrame &left_frame);

  /**
   * @brief Retrieves the latest right ir frame captured by the sensor(Only for XYZ-ST camera).
   * @param[out] right_frame A IRFrame object to store the acquired right ir frame data.
   * @return Status code indicating the success or failure of retrieving the right ir frame.
   */
  Status GetRightFrame(IRFrame &right_frame);

  /**
   * Retrieves the latest point cloud frame captured by the sensor, represented as a PointXYZFrame
   * object.
   * @param[out] point_xyz_frame A reference to a PointXYZFrame object to hold the retrieved frame
   * data.
   * @return Status code indicating the success or failure of retrieving the point frame.
   */
  Status GetPointXYZFrame(PointXYZFrame &point_xyz_frame);

  /**
   * Retrieves the latest normal point cloud frame captured by the sensor, represented as a
   * PointXYZFrame object.
   * @param[out] normal_frame A reference to a PointXYZFrame object to hold the retrieved frame
   * data.
   * @return Status code indicating the success or failure of retrieving the normal point frame.
   */
  Status GetNormalFrame(NormalFrame &normal_frame);

  /**
   * Retrieves information about the connected sensor, such as its type and capabilities.
   * @param[out] info A reference to a SensorInfo object to hold the retrieved information. info:
   * {id, model_name, ip}
   * @return Status code indicating the success or failure of getting sensor info.
   */
  Status GetSensorInfo(SensorInfo &info) const;

  /**
   * Retrieves intrinsic calibration parameters for the connected sensor.
   * @param[out] intr A reference to a SensorIntrinsic object to hold the retrieved calibration
   * parameters.
   * @return Status code indicating the success or failure of getting sensor intrinsic.
   */
  Status GetSensorIntrinsic(SensorIntrinsic &intr) const;

  /**
   * Saves the current sensor settings to a file with the specified filename.
   * @param[in] filename The name of the file to save the settings to.
   * @return Status code indicating the success or failure of saving setting.
   */
  Status SaveSettingsToFile(const std::string &filename) const;

  /**
   * Loads sensor settings from a file with the specified filename.
   * @param[in] filename The name of the file to load the settings from.
   * @return Status code indicating the success or failure of loading setting.
   */
  Status LoadSettingsFromFile(const std::string &filename);

  /**
   * @brief Retrieves a vector of available option keys for the sensor.
   *
   * This function retrieves a vector of strings representing the available option keys that can be
   * used to query and manipulate various sensor options. These keys are used to access specific
   * parameters and settings associated with the sensor.
   *
   * @return A vector of strings containing available option keys.
   */
  std::vector<std::string> GetOptionKeys();

  /**
   * @brief Retrieves a specific option parameter node using its key name.
   *
   * This function allows retrieving detailed information about a specific sensor option parameter
   * identified by its unique key. The returned ParamNode object contains metadata and configuration
   * information for the specified option, such as its data type, access mode, and description...
   *
   * @param[in] key The unique key name identifying the option parameter to retrieve.
   * @param[out] ptr A shared pointer to a ParamNode object that will be populated with information
   about the option.

   * @return Status code indicating the success or failure of retrieving the option parameter's
   information.
   */
  Status GetOption(const std::string &key, xyz::sensor::ParamNode::Ptr &ptr) const;

  /**
   * Set an integer value for camera
   * @param[in] name The name of the parameter to set
   * @param[in] value The integer value to set
   * @return OK if successful, otherwise an error code
   */
  Status SetInteger(const std::string &name, int64_t value);

  /**
   * Get an integer value for camera
   * @param[in] name The name of the parameter to set
   * @param[out] value The integer value to get
   * @param[out] vmin Optional pointer to the minimum allowed value
   * @param[out] vmax Optional pointer to the maximum allowed value
   * @param[out] vinc Optional pointer to the increment step value
   * @return OK if successful, otherwise an error code
   */
  Status GetInteger(const std::string &name, int64_t &value, int64_t *vmin = nullptr,
                    int64_t *vmax = nullptr, int64_t *vinc = nullptr);

  /**
   * Set a double float value for camera
   * @param[in] name The name of the parameter to set
   * @param[in] value The double value to set
   * @return OK if successful, otherwise an error code
   */
  Status SetFloat(const std::string &name, double value);

  /**
   * Get a double float value for camera
   * @param[in] name The name of the parameter to set
   * @param[out] value The double float value to get
   * @param[out] vmin Optional pointer to the minimum allowed value
   * @param[out] vmax Optional pointer to the maximum allowed value
   * @param[out] vinc Optional pointer to the increment step value
   * @return OK if successful, otherwise an error code
   */
  Status GetFloat(const std::string &name, double &value, double *vmin = nullptr,
                  double *vmax = nullptr, double *vinc = nullptr);

  /**
   * Set a boolean value for camera
   * @param[in] name The name of the parameter to set
   * @param[in] value The boolean value to set
   * @return OK if successful, otherwise an error code
   */
  Status SetBoolean(const std::string &name, bool value);

  /**
   * Get the boolean value for the specified parameter name
   * @param[in] name The name of the parameter to set
   * @param[out] value The bool value to get
   * @return The boolean value of the specified parameter
   */
  Status GetBoolean(const std::string &name, bool &value);

  /**
   * Set a enum value for camera
   * @param[in] name The name of the parameter to set
   * @param[in] value The double value to set
   * @return OK if successful, otherwise an error code
   */
  Status SetEnum(const std::string &name, const std::string &value);

  /**
   * Get the enum value for the specified parameter name
   * @param[in] name The name of the parameter to get
   * @param[out] value The enum value to get
   * @param[out] list Optional pointer to a vector of strings representing the allowed enum values
   * @return The enum value of the specified parameter
   */
  Status GetEnum(const std::string &name, std::string &value,
                 std::vector<std::string> *list = nullptr);

  /**
   * Set a string value for camera
   * @param[in] name The name of the parameter to set
   * @param[in] value The double value to set
   * @return OK if successful, otherwise an error code
   */
  Status SetString(const std::string &name, const std::string &value);

  /**
   * Get the string value for the specified parameter name
   * @param[in] name The name of the parameter to get
   * @param[out] value The string value of the parameter to get
   * @return OK if successful, otherwise an error code
   */
  Status GetString(const std::string &name, std::string &value);

  Status CallCommand(const std::string &name);

 private:
  void *impl_;
};

}  // namespace xyz::sensor
