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
        }

        return *this;
    }

    void GenerateHashId()
    {
        std::hash<std::string> hasher;

        hash_id = std::to_string(hasher(meta.product + meta.vendor));
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