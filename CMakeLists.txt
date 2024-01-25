cmake_minimum_required(VERSION 3.0)

project(UnitTest)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-pg)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "Debug")

add_definitions(-DBOOST_LOG_DYN_LINK=1)
add_definitions(-DLOG_V2=1)
# 生产环境
add_definitions(-DPRODUCT_ENV=1)

# 开发环境
# add_definitions(-DDEVELOP_ENV=1)

set( executables 
     test_anything
    )

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_SOURCE_DIR}/source/
                    ${CMAKE_SOURCE_DIR}/third_party/xyz-sensor-sdk/include/
                    ${CMAKE_SOURCE_DIR}/third_party/boost/include/
                    ${CMAKE_SOURCE_DIR}/third_party/
                    ${CMAKE_SOURCE_DIR}/third_party/asio/
                    ${CMAKE_SOURCE_DIR}/third_party/glog/include/
                    ${CMAKE_SOURCE_DIR}/third_party/opencv4/include/opencv4/
                    ${CMAKE_SOURCE_DIR}/third_party/eigen3/
                    ${CMAKE_SOURCE_DIR}/third_party/Mongoose/
                    ${CMAKE_SOURCE_DIR}/third_party/Httplib/
                    ${CMAKE_SOURCE_DIR}/third_party/ty_lib/include
                    ${CMAKE_SOURCE_DIR}/third_party/ty_lib/common
                    ${CMAKE_SOURCE_DIR}/third_party/sqlite3/include/
                    ${CMAKE_SOURCE_DIR}/third_party/libuv/include/)   

link_directories(${CMAKE_SOURCE_DIR}/third_party/opencv4/lib/
                 ${opencv_library_path}
                 ${CMAKE_SOURCE_DIR}/third_party/xyz-sensor-sdk/lib/
                 ${CMAKE_SOURCE_DIR}/third_party/boost/lib/
                 ${CMAKE_SOURCE_DIR}/third_party/sqlite3/lib/
                 ${CMAKE_SOURCE_DIR}/third_party/glog/lib/
                 ${CMAKE_SOURCE_DIR}/third_party/ty_lib/lib/linux/lib_x64
                 /usr/local/lib/
                 ${CMAKE_SOURCE_DIR}/third_party/libuv/lib/)

find_package(gflags REQUIRED)

if (gflags_FOUND)
  message("gflags found. Include dirs: ${gflags_INCLUDE_DIRS}")
  message("gflags libraries: ${gflags_LIBRARIES}")
else ()
  message(FATAL_ERROR "gflags not found.")
endif ()

aux_source_directory(${CMAKE_SOURCE_DIR}/source/ src_file_array)

foreach(executable ${executables})
    add_executable(${executable} 
                   ${src_file_array}
                   ${CMAKE_SOURCE_DIR}/source/old_src/XYZCamera.cpp 
                   ${CMAKE_SOURCE_DIR}/source/old_src/ParseFrame.cc 
                   ${CMAKE_SOURCE_DIR}/third_party/Mongoose/mongoose.c
                   )
    target_link_libraries(${executable} 
                          rt
                          pthread
                          opencv_core
                          opencv_imgcodecs
                          opencv_highgui
                          opencv_imgproc
                          opencv_videoio
                          sqlite3
                          tycam
                          boost_log_setup
                          boost_log
                          boost_thread
                          glog
                          xyz_sensor_sdk
                          MVGigEVisionSDK
                          MvCameraControl
                          ssl
                          crypto
                          uv
                          ${GFLAGS_LIBRARIES}
                          )
endforeach()
