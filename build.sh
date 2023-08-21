#! /bin/bash

file_arr=(get_file_size
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
          test_perf
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
          test_sqlite_orm
          test_eigen
          test_magic
          test_save_status
          test_bit
          test_json
          test_ty
          test_lambda
          test_math
          test_base
          test_opengl
          test_pcl )

opencv_header_path="/mnt/remote/190-mnt/zhangjunyi/Documents/OpenCV/4.5.2/install/include/opencv4/"
opencv_library_path="/mnt/remote/190-mnt/zhangjunyi/Documents/OpenCV/4.5.2/install/lib/"

# CXX_FLAGS="g++ -g -std=c++11"
CXX_FLAGS="g++ -g -std=c++14"

for file in "${file_arr[@]}"
do
    f="./bin/${file}.exe"
    # if [[ -e ${f} ]]; then
    #     echo "Exist file: " ${f} ", and delete it"
    #     rm ${f}
    # fi

    if [[ -e ${f} ]]; then
        echo "Exist file: " ${f} ", and continue"
        continue
    elif [[ ${file} == "shm_open_unlink" ]]; then
        g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -lrt
        continue
    elif [[ ${file} == "test_thread" ]]; then
        g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -lpthread
        continue
    elif [[ ${file} == "test_video_stream" ]]; then
        g++ -g -std=c++11 "${file}.cc" "mongoose.c" "ParseFrame.cc" -o ${f} -I./ -lpthread -lrt -I${opencv_header_path} -L${opencv_library_path} -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lpthread
        continue
    elif [[ ${file} == "test_pic_server" ]]; then
        g++ -g -std=c++11 "${file}.cc" "ParseFrame.cc" -o ${f} -I./ -lrt -lpthread -I${opencv_header_path} -L${opencv_library_path} -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lpthread
        continue
    elif [[ ${file} == "test_opencv" ]]; then
        g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -I${opencv_header_path} -L${opencv_library_path} -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lpthread
        continue
    elif [[ ${file} == "test_opencv_get_position" ]]; then
        g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -I${opencv_header_path} -L${opencv_library_path} -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lpthread
        continue
    elif [[ ${file} == "test_static_file"  ||
          ${file} == "test_mongoose_client" ||
          ${file} == "test_mongoose_server" ]]; then
        g++ -g -std=c++11 "${file}.cc" "mongoose.c" -o ${f} -I./
        continue
    elif [[ ${file} == "test_stl" ]]; then
        g++ -g -std=c++11 "${file}.cc"  -o ${f} -I./ -lpthread
        continue
    elif [[ ${file} == "test_perf" ]]; then
        # g++ -g -std=c++11 "${file}.cc" "hash_table.c"  -o ${f} -I./ -lpthread
        continue
    elif [[ ${file} == "test_sqlpp11" ]]; then
        g++ -g -std=c++11 "${file}.cc" -o ${f} -I ./ -I./sqlite3/include/ -L./sqlite3/lib/ -lsqlite3
        continue
    elif [[ ${file} == "test_asan" ]]; then
        g++ -fsanitize=address -g "${file}.cc" -o ${f} -I.
        continue
    elif [[ ${file} == "test_sqlite_orm" ]]; then
        g++ -g "${file}.cc"  -o ${f} -I. -I./sqlite3/include/ -L./sqlite3/lib/ -lsqlite3
        continue
    elif [[ ${file} == "test_eigen" ]]; then
        g++ -g "${file}.cc"  -o ${f} -I. -I./eigen3/
        continue
    elif [[ ${file} == "test_magic" ]]; then
        g++ -g "${file}.cc"  -o ${f} -I. -lmagic
        continue
    elif [[ ${file} == "test_ty" ]]; then
        ${CXX_FLAGS} "${file}.cc" "./ty_lib/MatViewer.cpp" "./ty_lib/DepthInpainter.cpp" "./ty_lib/ImageSpeckleFilter.cpp" -o ${f} -I./ty_lib/ -I/usr/local/TY_sdk/include/ -L/usr/local/TY_sdk/lib/linux/lib_x64/  -I/usr/local/include/opencv4/ -L/usr/local/lib/ -ltycam -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_photo -lpthread
        continue
    elif [[ ${file} == "test_lambda" ]]; then
        ${CXX_FLAGS} "${file}.cc" -o ${f} -I. -lpthread
        continue
    elif [[ ${file} == "test_pcl" ]]; then
        ${CXX_FLAGS} "${file}.cc" -o ${f} -I./eigen3/ -I/usr/local/include/vtk-7.1/ -I/usr/local/include/pcl-1.12/ -L/usr/local/lib/ -lvtkCommonCore-7.1 -lvtksys-7.1 -lvtkCommonColor-7.1 -lpcl_common -lpcl_io -lpcl_visualization -lpcl_filters -lpthread
        continue
    fi

    g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -lrt
done

function CopyVideoPlayFiles()
{
    cp /mnt/remote/190-mnt/zhangjunyi/workspace/manager_node_cpp/include/BaseIndex.hpp .
    cp /mnt/remote/190-mnt/zhangjunyi/workspace/manager_node_cpp/include/ConsumerIndex.hpp .
    cp /mnt/remote/190-mnt/zhangjunyi/workspace/manager_node_cpp/include/ProducerIndex.hpp .
    cp /mnt/remote/190-mnt/zhangjunyi/workspace/manager_node_cpp/include/ParseMjpeg.hpp .
    cp /mnt/remote/190-mnt/zhangjunyi/workspace/manager_node_cpp/include/PictureServer.hpp .
    cp /mnt/remote/190-mnt/zhangjunyi/workspace/manager_node_cpp/include/VcaTool.hpp .
}