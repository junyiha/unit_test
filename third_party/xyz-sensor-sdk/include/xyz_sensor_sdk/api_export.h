/*
 * Copyright (c) XYZ Robotics Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Author: haikuan <haikuan.du@xyzrobotics.ai>, 2022/08/18
 */

#pragma once

#if (defined _WIN32 && defined _dll)
#ifdef XYZ_SENSOR_API_EXPORT
#define XYZ_SENSOR_API __declspec(dllexport)
#else
#define XYZ_SENSOR_API __declspec(dllimport)
#endif
#else
#define XYZ_SENSOR_API
#endif
