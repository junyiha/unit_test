cmake_minimum_required(VERSION 3.0)

project(UnitTest)

add_compile_options(-std=c++11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "Debug")

set( executables 
     test_string 
     test_bit
     get_file_size
     clear_file
     test_logger
     create_directory
     share_memory
     test_ftok
     read_share_mem
     read_write_file
     shm_open_unlink
     test_mmap
     read_shm_open
     test_tcgetattr
     test_pipe
     parse_mjpeg
     test_parse_mjpeg
     test_consumer
     test_ascii
     test_consumer_index
     test_pic_server
     test_remove
     test_thread
     test_parse_frame
     test_video_stream
     test_opencv
     test_std_system
     test_opencv_get_position
     test_point_in_region
     test_point_in_region_v2
     test_cb
     test_generate_id
     test_vca_tool
     test_pgrep
     test_kill
     test_friend
     test_callback
     test_polymorphism
     test_extract_path
     test_static_file
     test_parse_time
     test_queue
     test_stl
     test_mongoose_client
     test_mongoose_server
     test_http_lib
     test_time
     test_alert_time
     test_service_logic
     test_nlohmann_json
     test_tmp
     test_sqlpp11
     test_map
     test_file
     test_function_time
     test_asan
     test_get_meminfo
     test_get_diskinfo
     test_cnt_mjpeg
     test_remove_dir
     test_vector
    #  test_sqlite_orm
     test_eigen
    #  test_magic
     test_save_status
     test_json
    #  test_ty
     test_lambda
     test_math
     test_base
     test_opengl
    #  test_pcl
     test_httplib_server
     test_hashmap
     test_api_process
     test_api_v2
     test_nvr
     test_sqlite3
    )

# set(opencv_header_path "/mnt/remote/190-mnt/zhangjunyi/workspace/vca_dir/master/video_process/3party/GENERAL/x86_64-linux-gnu/gcc-9/include/opencv4/")
# set(opencv_library_path "/mnt/remote/190-mnt/zhangjunyi/workspace/vca_dir/master/video_process/3party/GENERAL/x86_64-linux-gnu/gcc-9/lib/")

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_SOURCE_DIR}/source/
                    ${CMAKE_SOURCE_DIR}/third_party/
                    # ${opencv_header_path}
                    ${CMAKE_SOURCE_DIR}/third_party/opencv4/include/opencv4/
                    ${CMAKE_SOURCE_DIR}/third_party/eigen3/
                    ${CMAKE_SOURCE_DIR}/third_party/Mongoose/
                    ${CMAKE_SOURCE_DIR}/third_party/Httplib/
                    # ${CMAKE_SOURCE_DIR}third_party//ty_lib/
                    # /usr/local/TY_sdk/include/
                    ${CMAKE_SOURCE_DIR}/third_party/ty_lib/include
                    ${CMAKE_SOURCE_DIR}/third_party/ty_lib/common
                    # /mnt/remote/190-mnt/zhangjunyi/workspace/vca_dir/master/video_process/3party/GENERAL/x86_64-linux-gnu/gcc-9/include/pcl-1.12/
                    ${CMAKE_SOURCE_DIR}/third_party/sqlite3/include/)   

link_directories(${CMAKE_SOURCE_DIR}/third_party/opencv4/lib/
                 ${opencv_library_path}
                 ${CMAKE_SOURCE_DIR}/third_party/sqlite3/lib/
                #  /usr/local/TY_sdk/lib/linux/lib_x64/
                 ${CMAKE_SOURCE_DIR}/third_party/ty_lib/lib/linux/lib_x64
                 /usr/local/lib/)

foreach(executable ${executables})

    # message("the value of executable is :${executable}.cc")

    add_executable(${executable} ${CMAKE_SOURCE_DIR}/source/${executable}.cc ${CMAKE_SOURCE_DIR}/source/ParseFrame.cc ${CMAKE_SOURCE_DIR}/third_party/Mongoose/mongoose.c)
    target_link_libraries(${executable} 
                          rt
                          pthread
                          opencv_core
                          opencv_imgcodecs
                          opencv_highgui
                          opencv_imgproc
                          opencv_videoio
                          sqlite3
                        #   magic
                          tycam
                        #   pcl_common
                        #   pcl_io
                        #   pcl_visualization
                        #   pcl_filters
                        #   boost_system
                          )
endforeach()