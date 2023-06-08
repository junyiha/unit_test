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

#include <atomic>
#include "ParseFrame.hpp"
#include "ServiceLogic.hpp"
#include "opencv2/opencv.hpp"


class ProcessPicture
{

public:
    bool Process(std::string &in);
    bool Process(std::string &image, std::string &json_string);

private:
    void DrawBox();

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

private:
    std::atomic<bool> m_draw_flag {false};
    cv::Mat m_img;

private:
    ServiceLogic m_sl;
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

    m_img = image;
    // 定义边框的位置和大小
    int x = 100;
    int y = 100;
    int width = 200;
    int height = 150;

    // 在图像上绘制边框
    // cv::rectangle(image, cv::Point(x, y), cv::Point(x + width, y + height), cv::Scalar(0, 255, 0), 2);
    if (m_draw_flag.load())
    {
        for (auto &point : m_point_arr)
        {
            cv::rectangle(image, cv::Point(point.first.first, point.first.second), cv::Point(point.second.first, point.second.second), cv::Scalar(0, 255, 0), 2);
        }
    }
    m_draw_flag.store(false);

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
                        int ret {ServiceLogic::RET_ERR};
                        int event {ServiceLogic::EVENT_ERROR};
                        Logic_t l;

                        l.label = box.label;
                        l.score = box.score;
                        l.box.x1 = box.x1;
                        l.box.x2 = box.x2;
                        l.box.y1 = box.y1;
                        l.box.y2 = box.y2;
                        LogicTime_t lt;
                        lt.hour = 16;
                        lt.minute = 43;
                        lt.second = 0;
                        ret = m_sl.SetLimitBeginTime(lt);
                        if (ret == ServiceLogic::RET_OK)
                        {
                            lt.hour = 22;
                            lt.minute = 45;
                            ret = m_sl.SetLimitEndTime(lt);
                            if (ret == ServiceLogic::RET_OK)
                            {
                                m_sl.ConfigThreshold(50);
                                // Point p1(495, 68);
                                // Point p2(1206, 41);
                                // Point p3(1116, 580);
                                // Point p4(401, 580);
                                // std::vector<Point> region {p1, p2, p3, p4};
                                // ret = m_sl.SetDetectionRegion(region);
                                if (ret == ServiceLogic::RET_OK)
                                {
                                    ret = m_sl.Process(l, event);
                                    Process(image);
                                    if (ret == ServiceLogic::RET_OK && event != ServiceLogic::EVENT_ERROR)
                                    {
                                        m_point1 = std::make_pair(box.x1, box.y1);

                                        m_point2 = std::make_pair(box.x2, box.y2);
                                        
                                        m_point = std::make_pair(m_point1, m_point2);
                                        m_point_arr.push_back(m_point);

                                        DrawBox();
                                        std::cerr << "an alarm is generated, the event id: " << event << std::endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

inline void ProcessPicture::DrawBox()
{
    // for (auto &point : m_point_arr)
    // {
    //     cv::rectangle(m_img, cv::Point(point.first.first, point.first.second), cv::Point(point.second.first, point.second.second), cv::Scalar(0, 255, 0), 2);
    // }
    m_draw_flag.store(true);
}