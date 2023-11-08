cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)
project(xyz_sensor_sdk_example)

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
  message(STATUS "Has a parent scope.")
  set(xyz_sensor_sdk_LIBRARIES xyz_sensor_sdk)
else()
  message(STATUS "Doesn't have a parent scope.")
  set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
  set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  set(CMAKE_CXX_STANDARD 17)
  find_package(xyz_sensor_sdk REQUIRED)
  include_directories(${xyz_sensor_sdk_INCLUDE_DIRS})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(capture capture.cpp)
target_link_libraries(capture ${xyz_sensor_sdk_LIBRARIES})

add_executable(common_api common_api.cpp)
target_link_libraries(common_api ${xyz_sensor_sdk_LIBRARIES})
