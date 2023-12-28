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

#include <map>
#include <vector>
#include <string>
#include "robot_protocol.hpp"

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
    std::string hash_id;

public:
    DetectorConfig()
    {
        detector_type = 0;
        detector_gap = 0;
        detector_fps = 0;
        detector_thresholds = 0;
        tracker_type = 0;
        trace_case = 0;
        hash_id = "";
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
        hash_id = other.hash_id;
    }
    ~DetectorConfig()
    {
        detector_type = 0;
        detector_gap = 0;
        detector_fps = 0;
        detector_thresholds = 0;
        tracker_type = 0;
        trace_case = 0;
        hash_id = "";
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
            hash_id = other.hash_id;
        }

        return *this;
    }

    void GenerateHashId()
    {
        std::hash<std::string> hasher;

        hash_id = std::to_string(hasher(detector_model.name + detector_model.type));
    }    
};

class RoboticArmConfig
{
public:
    struct Meta_t 
    {
        std::string product;
        std::string vendor;
    };
    struct Address_t
    {
        std::string ip;
        size_t port;
    };

    std::string hash_id;
    Meta_t meta;
    Address_t address;
    aicontrib::Robot::RobotToolArray robot_tool_array;

public:
    RoboticArmConfig()
    {
        hash_id = "";
        meta.product = "";
        meta.vendor = "";
        address.ip = "";
        address.port = 0;
    }
    RoboticArmConfig(const RoboticArmConfig& other)
    {
        hash_id = other.hash_id;
        meta = other.meta;
        address = other.address;
        robot_tool_array = other.robot_tool_array;
    }
    ~RoboticArmConfig()
    {
        hash_id = "";
        meta.product = "";
        meta.vendor = "";
        address.ip = "";
        address.port = 0;
    }

    RoboticArmConfig& operator=(const RoboticArmConfig& other)
    {
        if (this != &other)
        {
            hash_id = other.hash_id;
            meta = other.meta;
            address = other.address;
            robot_tool_array = other.robot_tool_array;
        }

        return *this;
    }

    void GenerateHashId()
    {
        std::hash<std::string> hasher;

        hash_id = std::to_string(hasher(meta.product + meta.vendor + address.ip + std::to_string(address.port)));
    }
};

class EndToolConfig
{
public:
    struct Meta_t 
    {
        std::string product;
        std::string vendor;
        Meta_t()
        {
            product = "";
            vendor = "";
        }
    };
    struct Address_t
    {
        std::string path;
        std::string ip;
        size_t port;
        Address_t()
        {
            ip = "";
            port = 0;
            path = "";
        }
    };
    struct Config_t
    {
        int slave_id;
        size_t baudrate;
        int bits;
        int parity;
        int stop;
        Config_t()
        {
            slave_id = 0;
            baudrate = 0;
            bits = 0;
            parity = 0;
            stop = 0;
        }
    };

    std::string hash_id;
    Meta_t meta;
    Address_t address;
    Config_t config;

public:
    EndToolConfig()
    {
        hash_id = "";
    }
    EndToolConfig(const EndToolConfig& other)
    {
        hash_id = other.hash_id;
        meta = other.meta;
        address = other.address;
        config = other.config;
    }
    ~EndToolConfig()
    {

    }

    EndToolConfig& operator=(const EndToolConfig& other)
    {
        if (this != &other)
        {
            hash_id = other.hash_id;
            meta = other.meta;
            address = other.address;
            config = other.config;
        }

        return *this;
    }

    void GenerateHashId()
    {
        std::hash<std::string> hasher;

        hash_id = std::to_string(hasher(meta.product + meta.vendor + address.path + std::to_string(config.slave_id) + std::to_string(config.baudrate)));
    }
};

class CameraConfig
{
public:
    struct Meta_t 
    {
        std::string product;
        std::string vendor;
        std::string brief;
        Meta_t()
        {
            product = "";
            vendor = "";
            brief = "";
        }
    };
    struct Address_t
    {
        std::string id;
        std::string path;
        std::string ip;
        size_t port;
        Address_t()
        {
            id = "";
            ip = "";
            port = 0;
            path = "";
        }
    };
    struct Config_t
    {
        int mode;
        int slave_id;
        size_t baudrate;
        int bits;
        int parity;
        int stop;
        Config_t()
        {
            mode = 0;
            slave_id = 0;
            baudrate = 0;
            bits = 0;
            parity = 0;
            stop = 0;
        }
    };

    std::string hash_id;
    Meta_t meta;
    Address_t address;
    Config_t config;

public:
    CameraConfig()
    {
        hash_id = "";
    }
    CameraConfig(const CameraConfig& other)
    {
        hash_id = other.hash_id;
        meta = other.meta;
        address = other.address;
        config = other.config;
    }
    ~CameraConfig()
    {

    }

    CameraConfig& operator=(const CameraConfig& other)
    {
        if (this != &other)
        {
            hash_id = other.hash_id;
            meta = other.meta;
            address = other.address;
            config = other.config;
        }

        return *this;
    }

    void GenerateHashId()
    {
        std::hash<std::string> hasher;

        hash_id = std::to_string(hasher(meta.product + meta.vendor + meta.brief +address.id + std::to_string(config.mode)));
    }
};

using VisionAlgorithmConfig = DetectorConfig;

class TaskAlgorithmConfig
{
public:
    struct Meta_t 
    {
        std::string product;
        std::string vendor;
        std::string brief;
        Meta_t()
        {
            product = "";
            vendor = "";
            brief = "";
        }
    };
    struct Address_t
    {
        std::string id;
        std::string path;
        std::string ip;
        size_t port;
        Address_t()
        {
            id = "";
            ip = "";
            port = 0;
            path = "";
        }
    };
    struct Config_t
    {
        int mode;
        int slave_id;
        size_t baudrate;
        int bits;
        int parity;
        int stop;
        Config_t()
        {
            mode = 0;
            slave_id = 0;
            baudrate = 0;
            bits = 0;
            parity = 0;
            stop = 0;
        }
    };

    std::string hash_id;
    Meta_t meta;
    Address_t address;
    Config_t config;
    RoboticArmConfig robotic_arm_config;
    EndToolConfig end_tool_config;
    CameraConfig camera_config;
    VisionAlgorithmConfig vision_algorithm_config;

public:
    TaskAlgorithmConfig()
    {
        hash_id = "";
    }
    TaskAlgorithmConfig(const TaskAlgorithmConfig& other)
    {
        hash_id = other.hash_id;
        meta = other.meta;
        address = other.address;
        config = other.config;
        robotic_arm_config = other.robotic_arm_config;
        end_tool_config = other.end_tool_config;
        camera_config = other.camera_config;
        vision_algorithm_config = other.vision_algorithm_config;
    }
    ~TaskAlgorithmConfig()
    {

    }

    TaskAlgorithmConfig& operator=(const TaskAlgorithmConfig& other)
    {
        if (this != &other)
        {
            hash_id = other.hash_id;
            meta = other.meta;
            address = other.address;
            config = other.config;
            robotic_arm_config = other.robotic_arm_config;
            end_tool_config = other.end_tool_config;
            camera_config = other.camera_config;
            vision_algorithm_config = other.vision_algorithm_config;
        }

        return *this;
    }

    void GenerateHashId()
    {
        std::hash<std::string> hasher;

        hash_id = std::to_string(hasher(meta.brief));
    }
};

class InitConfig
{
public:
    int max_size;
    std::string vision_algorithm;
    std::string robotic_arm;
    std::string end_tool;
    std::string camera;
    std::string task_algorithm;

public:
    InitConfig()
    {
        max_size = 0;
        vision_algorithm = "";
        robotic_arm = "";
        end_tool = "";
        camera = "";
        task_algorithm = "";
    }
    InitConfig(const InitConfig& other)
    {   
        max_size = other.max_size;
        vision_algorithm = other.vision_algorithm;
        robotic_arm = other.robotic_arm;
        end_tool = other.end_tool;
        camera = other.camera;
        task_algorithm = other.task_algorithm;
    }
    ~InitConfig()
    {
        max_size = 0;
        vision_algorithm = "";
        robotic_arm = "";
        end_tool = "";
        camera = "";
        task_algorithm = "";  
    }

    InitConfig& operator=(const InitConfig& other)
    {
        if (this != std::addressof(other))
        {
            max_size = other.max_size;
            vision_algorithm = other.vision_algorithm;
            robotic_arm = other.robotic_arm;
            end_tool = other.end_tool;
            camera = other.camera;
            task_algorithm = other.task_algorithm;
        }

        return *this;
    }
};  

class NetworkMessage
{
public:
    std::string method;
    std::map<std::string, std::string> request_headers;
    std::string path;
    std::vector<std::string> path_array;
    std::string body;
    std::string response;
    std::string response_type;

public:
    NetworkMessage()
    {

    }
    NetworkMessage(const NetworkMessage& other)
    {
        method = other.method;
        request_headers = other.request_headers;
        path = other.path;
        path_array = other.path_array;
        body = other.body;
        response = other.response;
        response_type = other.response_type;
    }
    ~NetworkMessage()
    {
        
    }

    NetworkMessage& operator=(const NetworkMessage& other)
    {
        if (this != &other)
        {
            method = other.method;
            request_headers = other.request_headers;
            path = other.path;
            path_array = other.path_array;
            body = other.body;
            response = other.response;
            response_type = other.response_type;
        }

        return *this;
    }

public:
    void ExtractPathArgument()
    {
        ExtractFields(path, path_array);
    }

private:
    void ExtractFields(const std::string& path, std::vector<std::string>& fields)
    {
        size_t pos = path.find('/');

        if (pos != std::string::npos)
        {
            std::string field = path.substr(0, pos);
            fields.push_back(field);

            ExtractFields(path.substr(pos + 1), fields);
        }
        else 
        {
            fields.push_back(path);
        }
    }
};

class Robot 
{
public:
    virtual const char* Product() = 0;
};

class Cob final : public Robot
{
public:
    const char* Product() override 
    {
        return "I'm Cob robot!!!";
    }
};

class Dob final : public Robot
{
public:
    const char* Product() override
    {
        return "I'm Dob robot!!!";
    }
};

class Eob final : public Robot 
{
public:
    const char* Product() override
    {
        return "I'm Eob robot!!!";
    }
};

class SIMRobot3kg final : public Robot
{
public:
    const char* Product() override
    {
        return "I'm SIMRobot 3kg!!!";
    }
};

class SIMRobot10kg final : public Robot
{
public:
    const char* Product() override
    {
        return "I'm SIMRobot 10kg!!!";
    }
};

enum class RobotList : unsigned int 
{
    COB = 1,
    DOB = 2,
    EOB = 3
};

class Tool 
{
public:
    virtual const char* Product() = 0;
};

class Sucker final : public Tool 
{
public:
    const char* Product() override
    {
        return "I'm the sucker tool!!!";
    }
};

class Jaw final : public Tool
{
public:
    const char* Product() override
    {
        return "I'm the jaw tool!!!";
    };
};

enum class ToolList : unsigned int 
{
    SUCKER = 1,
    JAW = 2
};

template <typename TID, typename T>
class ObjectPool
{
public:
    using Object_t = std::pair<TID, T*>;

private:
    std::vector<Object_t> m_pool;
    unsigned int m_size;

public:
    ObjectPool() = delete;
    ObjectPool(unsigned int max_size) : m_size(max_size)
    {

    }
    virtual ~ObjectPool()
    {
        Clear();                                                                                
    }

public:
    int Push(Object_t object)
    {
        m_pool.push_back(object);

        return 1;
    }

    int Pop(TID object_id, Object_t& target)
    {
        auto it = std::find_if(m_pool.begin(), m_pool.end(), [=](Object_t object){
            return object.first == object_id;
        });

        if (it != m_pool.end())
        {
            target = *it;
            return 1;
        }

        return 0;
    }

    int GetObjectRef(TID object_id, Object_t& object_ref)
    {
        auto it = std::find_if(m_pool.begin(), m_pool.end(), [=](Object_t object){
            return object.first == object_id;
        });

        if (it != m_pool.end())
        {
            object_ref = *it;
            return 1;
        }

        return 0;
    }

    void Delete(TID object_id)
    {
        auto it = std::find_if(m_pool.begin(), m_pool.end(), [=](Object_t object){
            return object.first == object_id;
        });

        if (it != m_pool.end())
        {
            if (it->second != nullptr)
            {
                delete it->second;
                it->second = nullptr;
            }
            m_pool.erase(it);
            m_pool.shrink_to_fit();
        }
    }

    void Clear()
    {
        for (Object_t object : m_pool)
        {
            if (object.second != nullptr)
            {
                delete object.second;
                object.second = nullptr;
            }
        }
        m_pool.clear();
    }
};