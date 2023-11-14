/**
 * @file test_auto_calibration.cc
 * @author your name (you@domain.com)
 * @brief 自动标定算法的单元测试
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <string>
#include <vector>

#include "opencv2/opencv.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/core/eigen.hpp"

#define DATA_SIZE 20

struct Position_t
{
    double x;
    double y;
    double z;
};

struct Rotation_t
{
    double rx;
    double ry;
    double rz;
};

int main()
{
    int window_size = 11;
    cv::Size board_size(11, 8);
    std::vector<std::string> image_path_arr(DATA_SIZE);
    std::vector<Position_t> robot_position_arr(DATA_SIZE);
    std::vector<Rotation_t> robot_rotation_arr(DATA_SIZE);

    std::vector<std::vector<cv::Point2f>> point_two_dimensional_arr;
    for (auto &it : image_path_arr)
    {
        std::vector<cv::Point2f> point_one_dimensional_arr;
        cv::Mat img = cv::imread(it);
        bool tmp = cv::findChessboardCorners(img, board_size, point_one_dimensional_arr, cv::CALIB_CB_EXHAUSTIVE | cv::CALIB_CB_ACCURACY | cv::CALIB_CB_NORMALIZE_IMAGE);
        if (!tmp)
        {
            std::clog << "Error message: failed to get board data" << std::endl;
            return -1;
        }
        cv::Mat img_gray;
        cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
        cv::cornerSubPix(img_gray, point_one_dimensional_arr, cv::Size(window_size, window_size), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 100, 0.0001));
        
        point_two_dimensional_arr.push_back(point_one_dimensional_arr);
    }

    /**************************************************************8*/
    cv::Mat camera_parameter = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat camera_undistort_parameter;
}