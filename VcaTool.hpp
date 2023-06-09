/**
 * @file VcaTool.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include "json.hpp"

class VcaTool 
{
public:
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

public:
    virtual bool ParseFrameString(std::string &in, Frame_t &out);

public:
    VcaTool() = default;
    virtual ~VcaTool() = default;

private:
    std::string m_json_string {};

};

inline bool VcaTool::ParseFrameString(std::string &in, Frame_t &out)
{
    FrameDetector_t fd;
    FrameDetectorBox_t fdb;
    nlohmann::json parsed_data;

    try 
    {
        parsed_data = nlohmann::json::parse(in);
        out.monotonic = parsed_data["monotonic"];
        out.real_time = parsed_data["realtime"];
        out.task = parsed_data["task"];
        out.version = parsed_data["version"];
        out.next_protocol.seqnum = parsed_data["next_protocol"]["seqnum"];
        out.next_protocol.param = parsed_data["next_protocol"]["param"];
        out.height = parsed_data["frame"]["height"];
        out.width = parsed_data["frame"]["width"];
        out.index = parsed_data["frame"]["index"];
        out.number = parsed_data["frame"]["index"];
        if (parsed_data["frame"]["detector"].is_array())
        {
            for (auto &item_data : parsed_data["frame"]["detector"])
            {
                fd.id = item_data["id"];
                if (item_data["boxs"].is_array())
                {
                    for (auto &it : item_data["boxs"])
                    {
                        fdb.index = it["index"];
                        fdb.index2 = it["index2"];
                        fdb.label = it["label"];
                        fdb.number = it["number"];
                        fdb.score = it["score"];
                        fdb.x1 = it["x1"];
                        fdb.x2 = it["x2"];
                        fdb.y1 = it["y1"];
                        fdb.y2 = it["y2"];
                        fd.box_arr.push_back(fdb);
                    }
                }  // 遍历键为 boxs 的值
                out.detector_arr.push_back(fd);
            }  // 遍历键为 detector 的值
        }
    }
    catch (nlohmann::json::parse_error &e)
    {
        std::cerr << "Failed to parse frame string, the error information: " << e.what() << std::endl;
        return false;
    }
    catch (nlohmann::json::type_error &e)
    {
        std::cerr << "Failed to process json data, the error information: "<< e.what() << std::endl;
        return false;
    }

    return true;
}