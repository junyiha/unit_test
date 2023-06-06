/**
 * @file ParseFrame.hpp
 * @author your name (you@domain.com)
 * @brief 提供对vca输出的结构化数据进行处理，转化为内部数据结构
 * @version 0.1
 * @date 2023-06-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include <string>
#include <vector>
#include <iostream>
#include "json.hpp"

struct FrameDetectorBox_t
{
    long index;
    std::string index2;
    long label;
    long number;
    int score;
    int x1;
    int x2;
    int y1;
    int y2;
};

struct FrameDetector_t 
{
    std::string id;
    std::vector<struct FrameDetectorBox_t> box_arr;
};

struct NextProtocol_t 
{
    int seqnum;
    std::string param;
};

struct Frame_t 
{
    long monotonic;
    long real_time;
    std::string task;
    std::string version;
    NextProtocol_t next_protocol;

    int height;
    int width;
    long index;
    long number;
    std::vector<struct FrameDetector_t> detector_arr;
};

bool ParseFrame(std::string &in, struct Frame_t &out);