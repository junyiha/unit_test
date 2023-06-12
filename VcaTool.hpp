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
#include <signal.h>
#include "json.hpp"

class VcaTool 
{
public:
    using EnumRET_t = enum 
    {
        RET_ERR = -1,
        RET_OK = 0
    };

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
    struct Command_t 
    {
        std::string path;
        int cmd;
        int service_mode;
        bool daemon_mode;
        std::string id;
        bool detector_conf_inline;
        std::string detector_conf;
        std::string input_video_name;
        int output_type;
    };

public:
    virtual bool ParseFrameString(std::string &in, Frame_t &out);
    int SendCommand(Command_t &in);
    bool StartVcaTask(pid_t &out);
    bool KillVcaTask();

private:
    pid_t findProcessIdByName(const char* processName);

public:
    VcaTool() = default;
    virtual ~VcaTool() = default;

private:
    std::string m_json_string {};
    pid_t m_vca_pid;
    std::string m_program_name {"/home/user/zjy-190/workspace/video_process/build/vca.exe"};
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

inline int VcaTool::SendCommand(Command_t &in)
{
    int ret {RET_ERR};
    std::string cmd {};

    cmd = in.path;
    cmd += " --cmd " + std::to_string(in.cmd) + " ";
    if (in.daemon_mode)
        cmd += " --daemon ";
    cmd += " --service-mode " + std::to_string(in.service_mode) + " ";
    cmd += " --id " + in.id + " ";
    if (in.detector_conf_inline)
    {
        cmd += " --detector-conf-inline --detector-conf " + in.detector_conf + " ";
    }
    else 
    {
        return RET_ERR;
    }
    cmd += " --input-video-name " + in.input_video_name + " ";
    cmd += " --output-type " + std::to_string(in.output_type) + " ";

    ret = std::system(cmd.c_str());
    if (ret == RET_OK)
    {
        m_vca_pid = findProcessIdByName(in.path.c_str());
        if (m_vca_pid != RET_ERR)
            return RET_OK;
    }

    return RET_ERR;
}

inline bool VcaTool::StartVcaTask(pid_t &out)
{
    int ret {-1};
    std::string program_name {"/home/user/zjy-190/workspace/video_process/build/vca.exe"};
    std::string start_vca_cmd {};

    start_vca_cmd = program_name + " --daemon --service-mode 0 --id aaa --detector-conf-inline --detector-conf @--detector-models@/data/models/PERSON/DETECT.conf@xxxx@yyyy@ --input-video-name rtsp://admin:a1234567@192.169.7.123:554  --output-type 5";

    ret = std::system(start_vca_cmd.c_str());
    if (ret == 0)
    {
        out = findProcessIdByName(program_name.c_str());
        if (out != -1)
        {
            m_vca_pid = out;
            return true;
        }
    }

    return false;
}

inline pid_t VcaTool::findProcessIdByName(const char* processName) 
{
    char command[256];
    sprintf(command, "pgrep -f %s", processName);
    FILE* fp = popen(command, "r");
    if (fp != nullptr) {
        char buffer[16];
        if (fgets(buffer, sizeof(buffer), fp)) {
            pclose(fp);
            return atoi(buffer);
        }
        pclose(fp);
    }
    
    return -1;
}

inline bool VcaTool::KillVcaTask()
{
    int ret {RET_ERR};

    m_vca_pid = findProcessIdByName(m_program_name.c_str());

    ret = kill(m_vca_pid, SIGKILL);
    if (ret == RET_OK)
        return true;

    return false;
}