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
#include "httplib.h"

class VcaTool 
{
public:
    using EnumRET_t = enum 
    {
        RET_ERR = -1,
        RET_OK = 0
    };

    using EnumVCACommand_t = enum 
    {
        VCA_LIST_TASK = 1,           // 1：任务列表
        VCA_START_TASK = 2,          // 2：启动任务
        VCA_STOP_TASK = 3,           // 3：停止任务
        VCA_DELETE_TASK = 4,         // 4：删除任务
        VCA_UPDATE_TASK = 5,         // 5：更新任务
        VCA_STATUS_TASK = 6,         // 6：任务状态
        VCA_SET_DOWN_PROTOCOL = 7,   // 7：设置下层协议
        VCA_DEVICE_INFO = 101,       // 101：设备信息
        VCA_LICENCE_INFO = 201,      // 201：许可证信息
        VCA_UPDATE_LICENCE = 202,    // 202：更新许可证
        VCA_GET_MACHINE_CODE = 203,  // 203：获取机器码
        VCA_LIST_SLAVE = 301         // 301：从站列表
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
    struct ReplyCommon_t 
    {
        std::size_t monotonic;
        std::size_t realtime;
        std::string version;
        int vca_errno;
    };

    struct ReplyListTask_t 
    {
        ReplyCommon_t vca_common;  // 出错码(整型)。0：成功，3：空的
        std::vector<std::string> id_arr;
    };

    using ReplyStartTask_t = ReplyCommon_t;  // 出错码(整型)。0：成功，9：ID不存在，13：未授权，17：ID已存在，24：试用版最多启动两个任务

    using StartTaskParam_t = Command_t;  // 启动任务需要的参数结构体

    using ReplyStopTask_t = ReplyCommon_t;  // 出错码(整型)。0：成功，3：ID不存在

    using ReplyDeleteTask_t = ReplyCommon_t;  // 出错码(整型)。0：成功，3：ID不存在，16：运行中

    using ReplyUpdateTask_t = ReplyCommon_t;  // 出错码(整型)。0：成功，3：ID不存在

    struct ReplyTaskDetector_t 
    {
        std::string detector_id;
        std::vector<std::pair<std::string, std::string>> detector_status;  // Ok/Failed/Unknown(未加载或无输入)
    };

    struct ReplyStatusTask_t 
    {
        ReplyCommon_t vca_common;  // 出错码(整型)。0：成功，3：ID不存在
        std::vector<ReplyTaskDetector_t> detector_arr;
        std::pair<std::string, int> input;  // Ok/Failed/Unknown(未启用)
        std::pair<std::string, int> output;  // Ok/Unknown(无输入或未启用)
    };

    using ReplySetDownProtocol_t = ReplyCommon_t;  // 出错码(整型)。0：成功，3：ID不存在

    struct ReplyDeviceInfo_t 
    {
        ReplyCommon_t vca_common;  // 出错码(整型)。0：成功
        std::string product;
        std::string vendor;
        int socket;
    };

    struct ReplyLicenceInfo_t 
    {
        ReplyCommon_t vca_common;  // 出错码(整型)。0：成功，1：不支持的操作
        std::size_t duration;
        int nodes;
        int type;  // 类型(整型)。0：正式版，128：试用版
    };

    using ReplyUpdateLicence_t = ReplyCommon_t;  // 出错码(整型)。0：成功，1：不支持的操作，22：未生效、已过期、不适用，93：运行模式不匹配

    struct ReplyGetMachineCode 
    {
        ReplyCommon_t vca_common;  // 出错码(整型)。0：成功，1：不支持的操作
        std::string machine_code;
    };

    struct ReplyListSlave_t 
    {
        ReplyCommon_t vca_common;  // 出错码(整型)。0：成功，1：不支持的操作，3：空的
        std::string id;  // 节点ID(字符串)
        int granted;  // 是否授权(整型)。1：未授权，2：已授权
        int ctime;  // 上线时间(秒，整型)。自然时间
        int atime;  // 活动时间(秒，整型)。自然时间
        std::string remote_addr;  // 远程地址(字符串)。
    };

public:
    virtual bool ParseFrameString(std::string &in, Frame_t &out);
    int SendCommand(Command_t &in);
    bool StartVcaTask(pid_t &out);
    bool KillVcaTask();

public:
    int LicenceInfo(ReplyLicenceInfo_t &out);
    int UpdateLicence(std::string licence, ReplyUpdateLicence_t &out);
    int ListTask(ReplyListTask_t &out);
    int StartTask(StartTaskParam_t in, ReplyStartTask_t &out);

private:
    pid_t findProcessIdByName(const char* processName);

public:
    VcaTool() = default;
    virtual ~VcaTool() = default;

private:
    std::string m_vca_listen {"http://127.0.0.1:17008"};
    std::string m_vca_api {"/api"};

private:
    std::string m_json_string {};
    pid_t m_vca_pid;
    std::string m_program_name {"vca.exe"};
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

    std::cerr << "\nVcaTool: " << "the command of sended vca: " << cmd << std::endl;

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

inline int VcaTool::LicenceInfo(ReplyLicenceInfo_t &out)
{
    nlohmann::json parsed_data;
    httplib::Client client(m_vca_listen);
    httplib::Params licence_info_params = 
    {
        {"cmd", std::to_string(VCA_LICENCE_INFO)}
    };

    auto ret = client.Post(m_vca_api, licence_info_params);
    if (ret.error() != httplib::Error::Success)
    {
        return RET_ERR;
    }

    try 
    {
        parsed_data = nlohmann::json::parse(ret->body);
        out.vca_common.monotonic = parsed_data["monotonic"];
        out.vca_common.realtime = parsed_data["realtime"];
        out.vca_common.version = parsed_data["version"];
        out.vca_common.vca_errno = parsed_data["errno"];
        if (parsed_data["duration"].is_null())
        {
            out.duration = 0;
            out.nodes = 0;
            out.type = 0;
        }
        else 
        {
            out.duration = parsed_data["duration"];
            out.nodes = parsed_data["nodes"];
            out.type = parsed_data["type"];
        }
    }
    catch(nlohmann::json::parse_error &e)
    {
        std::cerr << "VcaTool: " << "Error information: " << e.what() << std::endl;
        return RET_ERR;
    }
    catch (nlohmann::json::type_error &e)
    {
        std::cerr << "VcaTool: " << "Error information: " << e.what() << std::endl;
        return RET_ERR;
    }

    return RET_OK;
}

inline int VcaTool::UpdateLicence(std::string licence, ReplyUpdateLicence_t &out)
{
    nlohmann::json parsed_data;
    httplib::Client client(m_vca_listen);
    httplib::Params update_licence_params = 
    {
        {"cmd", std::to_string(VCA_UPDATE_LICENCE)},
        {"licence", licence}
    };

    auto ret = client.Post(m_vca_api, update_licence_params);
    if (ret.error() != httplib::Error::Success)
    {
        return RET_ERR;
    }

    try 
    {
        parsed_data = nlohmann::json::parse(ret->body);
        out.monotonic = parsed_data["monotonic"];
        out.realtime = parsed_data["realtime"];
        out.version = parsed_data["version"];
        out.vca_errno = parsed_data["errno"];
    }
    catch(nlohmann::json::parse_error &e)
    {
        std::cerr << "VcaTool: " << "Error information: " << e.what() << std::endl;
        return RET_ERR;
    }
    catch (nlohmann::json::type_error &e)
    {
        std::cerr << "VcaTool: " << "Error information: " << e.what() << std::endl;
        return RET_ERR;
    }

    return RET_OK;
}

inline int VcaTool::ListTask(ReplyListTask_t &out)
{
    nlohmann::json parsed_data;
    httplib::Client client(m_vca_listen);
    httplib::Params list_task_params = 
    {
        {"cmd", std::to_string(VCA_LIST_TASK)}
    };

    auto ret = client.Post(m_vca_api, list_task_params);
    if (ret.error() != httplib::Error::Success)
    {
        return RET_ERR;
    }

    try 
    {
        parsed_data = nlohmann::json::parse(ret->body);
        out.vca_common.monotonic = parsed_data["monotonic"];
        out.vca_common.realtime = parsed_data["realtime"];
        out.vca_common.version = parsed_data["version"];
        out.vca_common.vca_errno = parsed_data["errno"];
        if (out.vca_common.vca_errno == 0 && parsed_data["ids"].is_array())
        {
            for (auto &it : parsed_data["ids"])
            {
                out.id_arr.push_back(it);
            }
        }
        else 
        {
            std::cerr << "VcaTool: Empty task list or Error json string : " << ret->body << std::endl;
            return RET_ERR;
        }
    }
    catch(nlohmann::json::parse_error &e)
    {
        std::cerr << "VcaTool: " << "Error information: " << e.what() << std::endl;
        return RET_ERR;
    }
    catch (nlohmann::json::type_error &e)
    {
        std::cerr << "VcaTool: " << "Error information: " << e.what() << std::endl;
        return RET_ERR;
    }

    return RET_OK;
}

inline int VcaTool::StartTask(StartTaskParam_t in, ReplyStartTask_t &out)
{
    nlohmann::json parsed_data;
    httplib::Client client(m_vca_listen);
    httplib::Params start_task_params = 
    {
        {"cmd", std::to_string(VCA_START_TASK)},
        {"id", in.id},
        {"detector-conf-inline", ""},
        {"detector-conf", in.detector_conf},
        {"input-video-name", in.input_video_name},
        {"output-type", std::to_string(in.output_type)}
    };

    auto ret = client.Post(m_vca_api, start_task_params);
    if (ret.error() != httplib::Error::Success)
    {
        return RET_ERR;
    }
    try 
    {
        parsed_data = nlohmann::json::parse(ret->body);
        out.monotonic = parsed_data["monotonic"];
        out.realtime = parsed_data["realtime"];
        out.version = parsed_data["version"];
        out.vca_errno = parsed_data["errno"];
    }
    catch(nlohmann::json::parse_error &e)
    {
        std::cerr << "VcaTool: " << "Error information: " << e.what() << std::endl;
        return RET_ERR;
    }
    catch (nlohmann::json::type_error &e)
    {
        std::cerr << "VcaTool: " << "Error information: " << e.what() << std::endl;
        return RET_ERR;
    }

    return RET_OK;
}