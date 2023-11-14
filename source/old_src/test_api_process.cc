/**
 * @file test_api_process.cc
 * @author your name (you@domain.com)
 * @brief 服务器处理api单元测试
 * @version 0.1
 * @date 2023-09-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>

class Sucker
{
public:
    void Process(std::string in, std::string &out);
};

void Sucker::Process(std::string in, std::string &out)
{

}

class Jaw
{

};


class BeijingRobot
{

};

class CobRobot
{

};


class TYCamera01
{

};

class TYCamera02
{

};

class GHDetector01
{

};

class GHDetector02
{

};

class Devices
{
private:
    enum class DeviceClass : unsigned int
    {
        TOOL = 1,
        ROBOT = 2,
        CAMERA = 3,
        DETECTOR = 4
    };
    std::map<DeviceClass, std::string> m_cmds =
    {
        {DeviceClass::TOOL, "/api/tool"},
        {DeviceClass::ROBOT, "/api/robot"},
        {DeviceClass::CAMERA, "/api/camera"},
        {DeviceClass::DETECTOR, "/api/detector"}
    };
    enum class ToolClass : unsigned int
    {
        OPEN = 1,
        START = 2,
        STOP = 3
    };
    std::map<ToolClass, std::string> m_tool_cmds =
    {
        {ToolClass::OPEN, "/api/tool/sucker/open"},
        {ToolClass::START, "/api/tool/sucker/start"},
        {ToolClass::STOP, "/api/tool/sucker/stop"}
    };
public:
    struct Cmd_t
    {
        std::string request_method;
        std::string device_class;
        std::string device_id;
        std::string device_function;
    };

    using DeviceMap_t = std::map<std::string, void *>;
    std::unordered_map<std::string, DeviceMap_t> m_abstract_device_map;
public:
    Devices();
    virtual ~Devices();

public:
    void Process(std::string in, std::string &out);

private:
    void ToolProcess(std::string in, std::string &out);
    void RobotProcess(std::string in, std::string &out);
    void CameraProcess(std::string in, std::string &out);
    void DetectorProcess(std::string in, std::string &out);
    void UnknownProcess(std::string in, std::string &out);

    void ToolOpen(std::string in, std::string &out);
    void ToolStart(std::string in, std::string &out);
    void ToolStop(std::string in, std::string &out);
};

Devices::Devices()
{
    DeviceMap_t tool_map;
    DeviceMap_t camera_map;
    DeviceMap_t robot_map;
    DeviceMap_t detector_map;

    tool_map["sucker"] = new Sucker();
    tool_map["jaw"] = new Jaw();

    camera_map["ty_camera_01"] = new TYCamera01();
    camera_map["ty_camera_02"] = new TYCamera02();

    robot_map["beijing_robot"] = new BeijingRobot();
    robot_map["cob_robot"] = new CobRobot();

    detector_map["GH_Detector_01"] = new GHDetector01();
    detector_map["GH_Detector_02"] = new GHDetector02();

    m_abstract_device_map["tool"] = tool_map;
    m_abstract_device_map["camera"] = camera_map;
    m_abstract_device_map["robot"] = robot_map;
    m_abstract_device_map["detector"] = detector_map;
}

Devices::~Devices()
{
    for (auto &it : m_abstract_device_map)
    {
        for (auto &i : it.second)
        {
            if (i.second != NULL)
            {
                // delete i.second;
                // i.second = NULL;
            }
        }
    }
}

void Devices::Process(std::string in, std::string &out)
{
    std::vector<std::string> cmd_list;
    size_t start_pos = 0;
    for (int row = 0; row < in.size(); ++row)
    {
        if (in[row] == '/')
        {
            std::string tmp = in.substr(start_pos, row - start_pos);
            cmd_list.push_back(tmp);
            start_pos = row + 1;
        }
    }
    Cmd_t cmd;
    cmd.request_method = cmd_list[0];
    cmd.device_class = cmd_list[1];
    cmd.device_id = cmd_list[2];
    cmd.device_function = cmd_list[3];

    for (auto &it : m_abstract_device_map)
    {
        if (cmd.device_class == it.first)
        {
            for (auto &i : it.second)
            {
                if (cmd.device_id == i.first)
                {

                }
            }
        }
    }

    if (in.substr(0, m_cmds[DeviceClass::TOOL].length()) == m_cmds[DeviceClass::TOOL])
    {
        ToolProcess(in, out);
    }
    else if (in.substr(0, m_cmds[DeviceClass::ROBOT].length()) == m_cmds[DeviceClass::ROBOT])
    {
        RobotProcess(in, out);
    }
    else if (in.substr(0, m_cmds[DeviceClass::CAMERA].length()) == m_cmds[DeviceClass::CAMERA])
    {
        CameraProcess(in, out);
    }
    else if (in.substr(0, m_cmds[DeviceClass::DETECTOR].length()) == m_cmds[DeviceClass::DETECTOR])
    {
        DetectorProcess(in, out);
    }
    else
    {
        UnknownProcess(in, out);
    }
}

void Devices::ToolProcess(std::string in, std::string &out)
{
    if (in.substr(0, m_tool_cmds[ToolClass::OPEN].length()) == m_tool_cmds[ToolClass::OPEN])
    {
        ToolOpen(in, out);
    }
    else if (in.substr(0, m_tool_cmds[ToolClass::START].length()) == m_tool_cmds[ToolClass::START])
    {
        ToolStart(in, out);
    }
    else if (in.substr(0, m_tool_cmds[ToolClass::STOP].length()) == m_tool_cmds[ToolClass::STOP])
    {
        ToolStop(in, out);
    }
    else
    {
        out = "unknown sucker operate";
    }
}

void Devices::RobotProcess(std::string in, std::string &out)
{
    out = "process Robot";
}

void Devices::CameraProcess(std::string in, std::string &out)
{
    out = "process Camera";
}

void Devices::DetectorProcess(std::string in, std::string &out)
{
    out = "process Detector";
}

void Devices::UnknownProcess(std::string in, std::string &out)
{
    out = "process Unknown";
}

void Devices::ToolOpen(std::string in, std::string &out)
{
    out = "open sucker tool";
}

void Devices::ToolStart(std::string in, std::string &out)
{
    out = "start sucker tool";
}

void Devices::ToolStop(std::string in, std::string &out)
{
    out = "stop sucker tool";
}

static void Help()
{
    std::string help_info = R"(
        test_api_process.exe  服务器API分发单元测试

        api list
            /api/tool
            /api/robot
            /api/camera
            /api/detector
    )";

    std::cerr << help_info << std::endl;
}

int test_process_api(char *in)
{
    Devices dev;
    std::string out;

    dev.Process(std::string(in), out);
    std::cerr << out << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg;
    for (int row{1}; row < argc; row++)
    {
        arg = argv[row];
        if (arg == "-h")
        {
            Help();
        }
        else if (arg == "--test-process-api")
        {
            test_process_api(argv[row + 1]);
            break;
        }
        else
        {
            Help();
        }
    }
}