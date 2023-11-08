/*
 * Copyright (c) XYZ Robotics Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: Gongzhe Su <gongzhe.su@xyzrobotics.com>, 2023/02/10
 */

#ifndef PARAM
#define PARAM

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <cstdint>
#include <map>

#include "xyz_sensor_sdk/api_export.h"
#include "xyz_sensor_sdk/common_types.h"

namespace xyz::sensor {

enum class ParamType {
  Base,         //!< Base param
  Integer,      //!< Integer param
  Float,        //!< Float param
  IBoolean,     //!< Boolean param
  String,       //!< String param
  Enumeration,  //!< Enumeration param
  Command,      //!< Command param
};

//! visibility of a node
enum class Visibility {
  Beginner = 0,   //!< Always visible
  Expert = 1,     //!< Visible for experts or Gurus
  Guru = 2,       //!< Visible for Gurus
  Invisible = 3,  //!< Not Visible
};

enum class AccessMode {
  NI,  //!< Not implemented
  NA,  //!< Not available
  WO,  //!< Write Only
  RO,  //!< Read Only
  RW,  //!< Read and Write
};

class XYZ_SENSOR_API ParamNode {
 public:
  using Ptr = std::shared_ptr<ParamNode>;

  struct NodeInfo {
    ParamType type = ParamType::Base;
    AccessMode mode = AccessMode::RW;
    Visibility visibility = Visibility::Beginner;
    std::string name;
    std::string description;
    std::string category;
    std::string tooltip;
  };

  virtual ParamType GetParamType() const { return info_.type; }
  virtual AccessMode GetAccessMode() const { return info_.mode; }
  virtual Visibility GetVisibility() const { return info_.visibility; }
  virtual std::string GetName() const { return info_.name; }
  virtual std::string GetDescription() const { return info_.description; }
  virtual std::string GetCategory() const { return info_.category; }
  virtual std::string GetToolTip() const { return info_.tooltip; }

 protected:
  NodeInfo info_;
};

class XYZ_SENSOR_API IntegerParam : public ParamNode {
 public:
  virtual Status SetValue(int64_t v) = 0;
  virtual int64_t GetValue() = 0;
  virtual int64_t GetMin() = 0;
  virtual int64_t GetMax() = 0;
  virtual int64_t GetInc() = 0;
  virtual std::string GetUnit() = 0;
};

class XYZ_SENSOR_API FloatParam : public ParamNode {
 public:
  virtual Status SetValue(double Value) = 0;
  virtual double GetValue() = 0;
  virtual double GetMin() = 0;
  virtual double GetMax() = 0;
  virtual double GetInc() = 0;
  virtual double GetDecimals() = 0;
  virtual std::string GetUnit() = 0;
};

class XYZ_SENSOR_API BooleanParam : public ParamNode {
 public:
  virtual Status SetValue(bool Value) = 0;
  virtual bool GetValue() = 0;
};

class XYZ_SENSOR_API EnumerationParam : public ParamNode {
 public:
  virtual Status SetValue(const std::string &Symbolic) = 0;
  virtual Status SetValue(int64_t Entry) = 0;
  virtual std::pair<int64_t, std::string> GetValue() = 0;
  virtual std::map<int64_t, std::string> GetEnumLists() = 0;
};

class XYZ_SENSOR_API StringParam : public ParamNode {
 public:
  virtual Status SetValue(const std::string &Value) = 0;
  virtual std::string GetValue() = 0;
};

class XYZ_SENSOR_API CommandParam : public ParamNode {
 public:
  virtual Status Execute() = 0;
  virtual bool IsDone() = 0;
};

}  // namespace xyz::sensor

#endif
