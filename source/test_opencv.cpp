/**
 * @file test_opencv.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "entry.hpp"

#include "opencv4/opencv2/opencv.hpp"

int test_opencv_imencode(Message& message)
{
    std::string img_path = "/data/home/user/workspace/unit_test/data/img-2.jpg";
    std::string save_img_path = "/data/home/user/workspace/unit_test/data/save-img-2.jpg";
    std::string save_img_string = "/data/home/user/workspace/unit_test/data/save-string-img-2.txt";

    cv::Mat img = cv::imread(img_path);
    if (img.empty())
    {
        LOG(ERROR) << "invalid image path: " << img_path << "\n";
        return 0;
    }

    std::vector<uchar> buffer;
    std::vector<int> params;

    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(95);

    bool success = cv::imencode(".jpg", img, buffer, params);

    if (success)
    {
        std::ofstream file;

        file.open(save_img_path, std::ios::out | std::ios::binary);

        if (!file.is_open())
        {
            LOG(ERROR) << "invalid save path: " << save_img_path << "\n";
            return 0;
        }

        file.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
        if (file)
        {   
            LOG(INFO) << "write image successfully\n";
            std::string tmp_str = base64_encode(buffer.data(), buffer.size());
            char* tmp_data_ptr = base64_encode(buffer.data(), buffer.size());
            std::ofstream tmp_file(save_img_string, std::ios::out);
            if (!tmp_file.is_open())
            {
                LOG(ERROR) << "invalid save string path: " << save_img_string << "\n";
            }
            else 
            {
                // tmp_file.write(tmp_str.c_str(), tmp_str.length());
                tmp_file.write(tmp_data_ptr, sizeof(tmp_data_ptr));
                if (tmp_file)
                {   
                    LOG(INFO) << "write image base64 string successfully\n";
                    if (tmp_data_ptr)
                    {
                        free(tmp_data_ptr);
                        tmp_data_ptr = nullptr;
                    }
                    return 1;
                }
                else 
                {
                    LOG(ERROR) << "write image base64 string failed \n";
                    if (tmp_data_ptr)
                    {
                        free(tmp_data_ptr);
                        tmp_data_ptr = nullptr;
                    }
                    return 0;
                }
            }
            return 1;
        }
        else 
        {
            LOG(ERROR) << "write image failed\n";
            return 0;
        }
    }   
    else 
    {
        LOG(ERROR) << "imencode failed\n";
        return 0;
    }
}

int test_opencv(Message& message)
{
    LOG(INFO) << "----test opencv begin----\n";

    std::map<std::string, std::function<int(Message&)>>cmd_map = {
        {"test-opencv-imencode", test_opencv_imencode}
    };

    std::string cmd = message.message_pool.at(2);
    auto it = cmd_map.find(cmd);
    if (it != cmd_map.end())
    {
        it->second(message);
        return 1;
    }
    else 
    {
        LOG(ERROR) << "invalid command: " << cmd << std::endl;
    }

    LOG(INFO) << "----test opencv end----\n";

    return 1;
}