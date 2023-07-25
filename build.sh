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
          test_magic )

opencv_header_path="/mnt/remote/190-mnt/zhangjunyi/Documents/OpenCV/4.5.2/install/include/opencv4/"
opencv_library_path="/mnt/remote/190-mnt/zhangjunyi/Documents/OpenCV/4.5.2/install/lib/"

for file in "${file_arr[@]}"
do
    f="${file}.exe"
    # if [[ -e ${f} ]]; then
    #     echo "Exist file: " ${f} ", and delete it"
    #     rm ${f}
    # fi

    if [[ -e ${f} ]]; then
        echo "Exist file: " ${f} ", and continue"
        continue
    fi

    if [[ ${file} == "shm_open_unlink" ]]; then
        g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -lrt
        continue
    fi

    if [[ ${file} == "test_thread" ]]; then
        g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -lpthread
        continue
    fi

    if [[ ${file} == "test_video_stream" ]]; then
        g++ -g -std=c++11 "${file}.cc" "mongoose.c" "ParseFrame.cc" -o ${f} -I./ -lpthread -lrt -I${opencv_header_path} -L${opencv_library_path} -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lpthread
        continue
    fi

    if [[ ${file} == "test_pic_server" ]]; then
        g++ -g -std=c++11 "${file}.cc" "ParseFrame.cc" -o ${f} -I./ -lrt -lpthread -I${opencv_header_path} -L${opencv_library_path} -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lpthread
        continue
    fi

    if [[ ${file} == "test_opencv" ]]; then
        g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -I${opencv_header_path} -L${opencv_library_path} -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lpthread
        continue
    fi

    if [[ ${file} == "test_opencv_get_position" ]]; then
        g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -I${opencv_header_path} -L${opencv_library_path} -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lpthread
        continue
    fi

    if [[ ${file} == "test_static_file"  ||
          ${file} == "test_mongoose_client" ||
          ${file} == "test_mongoose_server" ]]; then
        g++ -g -std=c++11 "${file}.cc" "mongoose.c" -o ${f} -I./
        continue
    fi

    if [[ ${file} == "test_stl" ]]; then
        g++ -g -std=c++11 "${file}.cc"  -o ${f} -I./ -lpthread
        continue
    fi

    if [[ ${file} == "test_perf" ]]; then
        # g++ -g -std=c++11 "${file}.cc" "hash_table.c"  -o ${f} -I./ -lpthread
        continue
    fi

    if [[ ${file} == "test_sqlpp11" ]]; then
        g++ -g -std=c++11 "${file}.cc" -o ${f} -I ./ -I./sqlite3/include/ -L./sqlite3/lib/ -lsqlite3
        continue
    fi

    if [[ ${file} == "test_asan" ]]; then
        g++ -fsanitize=address -g "${file}.cc" -o ${f} -I.
        continue
    fi

    if [[ ${file} == "test_sqlite_orm" ]]; then
        g++ -g "${file}.cc"  -o ${f} -I. -I./sqlite3/include/ -L./sqlite3/lib/ -lsqlite3
        continue
    fi

    if [[ ${file} == "test_eigen" ]]; then
        g++ -g "${file}.cc"  -o ${f} -I. -I./eigen3/
        continue
    fi

    if [[ ${file} == "test_magic" ]]; then
        g++ -g "${file}.cc"  -o ${f} -I. -lmagic
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