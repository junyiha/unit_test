/**
 * @file protocol.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 
#include <vector>
#include <string>

class Message
{
public:
    std::string first_layer;
    std::string second_layer;
    std::string third_layer;
    std::vector<std::string> message_pool;

public:
    Message()
    {
        first_layer = "";
        second_layer = "";
        third_layer = "";
        message_pool.resize(0);
    }
    Message(const Message& other)
    {
        first_layer = other.first_layer;
        second_layer = other.second_layer;
        third_layer = other.third_layer;
        message_pool = other.message_pool;
    }
    ~Message()
    {
        first_layer = "";
        second_layer = "";
        third_layer = "";
        message_pool.clear();
    }

public:
    Message& operator=(const Message& other)
    {
        if (this != &other)
        {
            first_layer = other.first_layer;
            second_layer = other.second_layer;
            third_layer = other.third_layer;
            message_pool = other.message_pool;
        }

        return *this;
    }
};

class DetectorModel
{
public:
    std::string name;
    std::vector<std::string> file;
    std::string type;

public:
    DetectorModel()
    {
        name = "";
        file.clear();
        type = "";
    }
    DetectorModel(const DetectorModel& other)
    {
        name = other.name;
        file = other.file;
        type = other.type;
    }
    ~DetectorModel()
    {
        name = "";
        file.clear();
        type = "";
    }

    DetectorModel& operator=(const DetectorModel& other)
    {
        if (this != &other)
        {
            name = other.name;
            file = other.file;
            type = other.type;
        }

        return *this;
    }
};

class DetectorConfig
{
public:
    int detector_type;
    int detector_gap;
    int detector_fps;
    double detector_thresholds;
    int tracker_type;
    int trace_case;
    DetectorModel detector_model;

public:
    DetectorConfig()
    {
        detector_type = 0;
        detector_gap = 0;
        detector_fps = 0;
        detector_thresholds = 0;
        tracker_type = 0;
        trace_case = 0;
    }
    DetectorConfig(const DetectorConfig& other)
    {
        detector_type = other.detector_type;
        detector_gap = other.detector_gap;
        detector_fps = other.detector_fps;
        detector_thresholds = other.detector_thresholds;
        tracker_type = other.tracker_type;
        trace_case = other.trace_case;
        detector_model = other.detector_model;
    }
    ~DetectorConfig()
    {
        detector_type = 0;
        detector_gap = 0;
        detector_fps = 0;
        detector_thresholds = 0;
        tracker_type = 0;
        trace_case = 0;
    }
    DetectorConfig& operator=(const DetectorConfig& other)
    {
        if (this != &other)
        {
            detector_type = other.detector_type;
            detector_gap = other.detector_gap;
            detector_fps = other.detector_fps;
            detector_thresholds = other.detector_thresholds;
            tracker_type = other.tracker_type;
            trace_case = other.trace_case;
            detector_model = other.detector_model;
        }

        return *this;
    }
};