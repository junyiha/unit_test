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

void Devices::Process(std::string in, std::string &out)
{
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