/**
 * @file test_opencv.cc
 * @author your name (you@domain.com)
 * @brief 读取图片数据，画框，显示
 * @version 0.1
 * @date 2023-06-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "opencv2/opencv.hpp"

// 读取文件内容到内存
std::vector<char> ReadFileToMemory(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return {};
    }
    
    // 获取文件大小
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // 分配内存缓冲区
    std::vector<char> buffer(fileSize);
    
    // 读取文件内容到缓冲区
    if (!file.read(buffer.data(), fileSize)) {
        std::cerr << "Failed to read file: " << filename << std::endl;
        return {};
    }
    
    return buffer;
}

int ProcessPic(cv::Mat &image)
{
    if (image.empty()) {
        std::cout << "无法加载图像文件" << std::endl;
        return -1;
    }

    // 定义边框的位置和大小
    int x = 100;
    int y = 100;
    int width = 200;
    int height = 150;

    // 在图像上绘制边框
    // cv::rectangle(image, cv::Point(x, y), cv::Point(x + width, y + height), cv::Scalar(0, 255, 0), 2);

    // 创建窗口
    cv::namedWindow("Image", cv::WINDOW_NORMAL);

    // 显示带有边框的图像
    cv::imshow("Image", image);

    // 等待按键事件
    cv::waitKey(0);

    // 关闭窗口
    cv::destroyWindow("Image");

    return 0;
}

int show() 
{
    // 读取图片
    // cv::Mat image = cv::imread("input_pic.jpg");
    cv::Mat image = cv::imread("./wQMc1-frame-4792.jpg");
    ProcessPic(image);
}

int old_version ()
{
    std::string file {"frame.jpg"};
    int height {1920};
    int width {1080};
    std::vector<char> pic_data;

    pic_data = ReadFileToMemory(file);
    if (pic_data.empty())
    {
        std::cerr << "Failed to read data of :" << file << std::endl;
        return -1;
    }
    cv::Mat image = cv::Mat( width, height, CV_8UC3, pic_data.data());
    ProcessPic(image);
    // show();

    return 0;
}

std::string tmp_img {"./wQMc1-frame-4792.jpg"};

/**
    ++++++++++++++++++
    cnt: 1
    x: 265
    y: 300
    ++++++++++++++++++

    ++++++++++++++++++
    cnt: 2
    x: 700
    y: 300
    ++++++++++++++++++

    ++++++++++++++++++
    cnt: 3
    x: 700
    y: 900
    ++++++++++++++++++

    ++++++++++++++++++
    cnt: 4
    x: 265
    y: 900
    ++++++++++++++++++
*/


int draw_static_image()
{
    /* 检测区域 */
    int x1 = 265;
    int y1 = 300;
    int x2 = 700;
    int y2 = 900;

    /* 告警框信息 */
    // int x1 = 720;
    // int y1 = 231;
    // int x2 = 773;
    // int y2 = 308;
    std::string window_name {"tmp"};
    cv::Mat img;
    img = cv::imread(tmp_img);

    cv::rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);

    /* 告警框信息1 */
    x1 = 720;
    y1 = 231;
    x2 = 773;
    y2 = 308;
    cv::rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);

    /* 告警框信息2 */
    x1 = 341;
    y1 = 329;
    x2 = 483;
    y2 = 732;
    cv::rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);

    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    cv::imshow(window_name, img);
    cv::waitKey(0);

    return 0;
}

int failed_read_image()
{
    std::string file_name {"origin-frame-1.jpg"};

    int height {1920};
    int width {1080};
    std::vector<char> pic_data;

    pic_data = ReadFileToMemory(file_name);
    if (pic_data.empty())
    {
        std::cerr << "Failed to read data of :" << file_name << std::endl;
        return -1;
    }
    cv::Mat image = cv::Mat( width, height, CV_8UC3, pic_data.data());
    cv::namedWindow(file_name, cv::WINDOW_NORMAL);
    cv::imshow(file_name, image);
    cv::waitKey(0);

    return 0;
}

int main()
{
    draw_static_image();

    return 0;
}