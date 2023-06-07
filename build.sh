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
          test_video_stream )

for file in "${file_arr[@]}"
do 
    f="${file}.exe"
    if [[ -e ${f} ]]; then 
        echo "Exist file: " ${f} ", and delete it"
        rm ${f}
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
        g++ -g -std=c++11 "${file}.cc" "mongoose.c" -o ${f} -I./ -lpthread -lrt
        continue
    fi

    if [[ ${file} == "test_pic_server" ]]; then 
        g++ -g -std=c++11 "${file}.cc" "ParseFrame.cc" -o ${f} -I./ -lrt -lpthread
        continue
    fi

    g++ -g -std=c++11 "${file}.cc" -o ${f} -I./ -lrt
done 