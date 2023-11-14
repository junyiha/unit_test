/**
 * @file test_api_v2.cc
 * @author your name (you@domain.com)
 * @brief 处理api的单元测试
 * @version 0.1
 * @date 2023-09-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <map>

static void Help()
{
    std::string info;

    std::cerr << info << std::endl;
}

struct Command_t
{
    std::string cmd;
};

struct ServerMessage_t
{
    std::string request_type;
    std::string device_type;
    std::string command_type;
};

class Robot
{
private:
    enum cmd
    {
        MOVE_JOINT,
        MOVE_LINE
    };

public:
    Robot();
    virtual ~Robot();

public:
    void Process(std::string in, std::string &out);

private:
    void MoveJoint();
    void MoveLine();
    void Unknown();

private:
    std::map<std::string, enum cmd> m_map;
};

Robot::Robot()
{
    m_map["moveJoint"] = MOVE_JOINT;
    m_map["moveLine"] = MOVE_LINE;
}

Robot::~Robot()
{

}

void Robot::Process(std::string in, std::string &out)
{
    auto it = m_map.find(in);
    if (it == m_map.end())
    {
        Unknown();
        return;
    }
    switch (it->second)
    {
        case MOVE_JOINT:
            MoveJoint();
            break;
        case MOVE_LINE:
            MoveLine();
            break;
        default:
            Unknown();
    }
}

void Robot::MoveJoint()
{
    std::cerr << "---move joint---" << std::endl;
}

void Robot::MoveLine()
{
    std::cerr << "---move line---" << std::endl;
}

void Robot::Unknown()
{
    std::cerr << "---unkown command---" << std::endl;
}

class Device
{
private:
    enum cmd
    {
        ROBOT,
        CAMERA
    };

    enum class RequestType : unsigned int
    {
        API = 1
    };

    enum class DeviceType : unsigned int
    {
        ROBOT = 1,
        CAMERA = 2
    };

    enum class RobotCommand : unsigned int
    {
        MOVE_JOINT = 1,
        MOVE_LINE = 2
    };

public:
    Device();
    virtual ~Device();

public:
    void Process(std::string in, std::string &out);
    void Process(struct ServerMessage_t in, std::string &out);

private:
    void ProcessRequestType(struct ServerMessage_t in, std::string &out);
    void ProcessDeviceType(struct ServerMessage_t in, std::string &out);
    void RobotProcess(std::string in, std::string &out);
    void CameraProcess(std::string in, std::string &out);
    void Unknown();

private:
    Robot m_robot;
    std::map<std::string, enum cmd> m_map;
    std::map<std::string, DeviceType> m_device_map;
};

Device::Device()
{
    m_map["robot"] = ROBOT;
    m_map["camera"] = CAMERA;

    m_device_map["robot"] = DeviceType::ROBOT;
    m_device_map["camera"] = DeviceType::CAMERA;
}

Device::~Device()
{

}

void Device::Process(std::string in, std::string &out)
{
    auto it = m_map.find(in);
    if (it == m_map.end())
    {
        Unknown();
        return;
    }

    switch (it->second)
    {
        case ROBOT:
            RobotProcess(in, out);
            break;
        case CAMERA:
            CameraProcess(in, out);
            break;
        default:
            Unknown();
    }
}

void Device::Process(struct ServerMessage_t in, std::string &out)
{
    ProcessDeviceType(in, out);
}

void Device::ProcessRequestType(struct ServerMessage_t in, std::string &out)
{
    
}

void Device::ProcessDeviceType(struct ServerMessage_t in, std::string &out)
{
    auto it = m_device_map.find(in.device_type);
    if (it == m_device_map.end())
    {
        return ;
    }
    switch(it->second)
    {
        case DeviceType::ROBOT:
            std::cerr << "device is robot" << std::endl;
            break;
        case DeviceType::CAMERA:
            std::cerr << "device is camera" << std::endl;
            break;
        default:
            std::cerr << "unknown device" << std::endl;
    }
}


void Device::RobotProcess(std::string in, std::string &out)
{
    std::cerr << "robot" << std::endl;
}

void Device::CameraProcess(std::string in, std::string &out)
{
    std::cerr << "camera" << std::endl;
}

void Device::Unknown()
{
    std::cerr << "unknown device cmd" << std::endl;
}

int test_robot(std::string cmd)
{
    Robot robot;
    std::string out;

    robot.Process(cmd, out);

    return 0;
}

int test_device(std::string cmd)
{
    Device m_device;
    std::string out;
    ServerMessage_t sm;
    sm.request_type = "api";
    sm.device_type = "robot";
    sm.command_type = "moveJoint";

    m_device.Process(sm, out);

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg;
    for (int i = 1; i < argc; i++)
    {
        arg = argv[i];
        if (arg == "--help")
        {
            Help();
        }
        else if (arg == "--test-device")
        {
            i++;
            test_device(argv[i]);
        }
        else if (arg == "--test-robot")
        {
            i++;
            test_robot(argv[i]);
        }
        else 
        {
            std::cerr << "unknown command: " << arg << std::endl;
        }
    }

    return 0;
} 