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
          test_callback )

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

    g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -lrt
done 