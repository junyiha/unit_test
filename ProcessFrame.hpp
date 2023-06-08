/**
 * @file ProcessFrame.hpp
 * @author your name (you@domain.com)
 * @brief 使用OpenCV处理图片数据
 * @version 0.1
 * @date 2023-06-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include "ParseFrame.hpp"
#include "opencv2/opencv.hpp"


class ProcessPicture
{

public:
    bool Process(std::string &in);
    bool Process(std::string &image, std::string &json_string);

public:
    ProcessPicture() = default;
    virtual ~ProcessPicture() = default;

private:
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;
    std::pair<int, int> m_point1;
    std::pair<int, int> m_point2;
    std::pair<std::pair<int, int>, std::pair<int, int>> m_point;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> m_point_arr;
};

inline bool ProcessPicture::Process(std::string &in)
{
    std::string full_name;

    full_name = "/dev/shm/" + in;
    cv::Mat image = cv::imread(full_name);
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
    for (auto &point : m_point_arr)
    {
        cv::rectangle(image, cv::Point(point.first.first, point.first.second), cv::Point(point.second.first, point.second.second), cv::Scalar(0, 255, 0), 2);
    }

    // 创建窗口
    cv::namedWindow("Image", cv::WINDOW_NORMAL);

    // 显示带有边框的图像
    cv::imshow("Image", image);

    // 等待按键事件
    cv::waitKey(10);

    // 关闭窗口
    // cv::destroyWindow("Image");

    return 0;
}

inline bool ProcessPicture::Process(std::string &image, std::string &json_string)
{
    bool result {false};
    Frame_t f;

    result = ParseFrame(json_string, f);
    if (result)
    {
        if (!f.detector_arr.empty())
        {
            for (auto &detector : f.detector_arr)
            {
                if (!detector.box_arr.empty())
                {
                    m_point_arr.clear();
                    for (auto &box : detector.box_arr)
                    {
                        m_x1 = box.x1;
                        m_y1 = box.y1;
                        m_x2 = box.y2;
                        m_y2 = box.y2;
                        m_point1.first = box.x1;
                        m_point1.second = box.y1;
                        m_point2.first = box.x2;
                        m_point2.second = box.y2;
                        m_point.first = m_point1;
                        m_point.second = m_point2;
                        m_point_arr.push_back(m_point);
                        Process(image);
                    }
                }
            }
        }
    }
}