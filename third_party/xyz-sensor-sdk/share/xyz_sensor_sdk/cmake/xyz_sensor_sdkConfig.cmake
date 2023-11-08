include(CMakeFindDependencyMacro)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

find_path(xyz_sensor_sdk_INCLUDE_DIRS NAMES xyz_sensor_sdk HINTS ${CMAKE_CURRENT_LIST_DIR}/../../../include)
find_library(xyz_sensor_sdk_LIBRARIES NAMES xyz_sensor_sdk HINTS ${CMAKE_CURRENT_LIST_DIR}/../../../lib)
