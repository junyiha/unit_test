//
// Created by liangsy on 23-7-10.
//
#ifndef HAND_EYE_CV_UTILS_H
#define HAND_EYE_CV_UTILS_H

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "Eigen/Core"
#include <Eigen/Geometry>
#include "boost/filesystem.hpp"
#include <boost/program_options.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

bool readStringList(const std::string& filename, std::vector<std::string>& l);

bool compareFilesWithoutExt(std::string& a, std::string& b);

void retrieveFilesInDir(boost::filesystem::path& input_p, std::vector<std::string >& out, bool sort_output);

void readPoseFromCSV(const std::string& input_path, cv::Mat& out_mat, char delim);

bool isRotatedMatrix(cv::Mat& R);

cv::Mat eulerAngleToRotateMatrix(const cv::Mat& eulerAngle, const std::string& seq, bool is_rad);

void Transform2Rt(cv::Mat& HomoMtr, cv::Mat& R, cv::Mat& T);

cv::Mat R_t2Transform(const cv::Mat& R,const cv::Mat& T);

#endif //HAND_EYE_CV_UTILS_H
