/**
 * @file NvrTool.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-16
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

class NvrTool
{
public:
    struct NvrCommand_t 
    {
        std::string input_fmt;
        std::string input_uri;
        int input_timeout;
        int input_retry;
        float input_xspeed;
        std::string record_name;
        int record_count;
        int record_duration;
        std::string publish_fmt;
        std::string publish_uri;
    };

    struct NvrResponse_t 
    {
        long monotonic;
        int real_time;
        std::string version;
        int error_code;
    };

public:
    NvrTool();
    virtual ~NvrTool();

public:
    bool List();
    bool Create();
    bool Create(NvrCommand_t in);
    bool Delete();

private:
    bool ParseResponseMessage(std::string in, NvrResponse_t &out);

private:
    std::string m_addr;
    std::string m_api;
};

inline NvrTool::NvrTool()
{
    m_addr = "http://127.0.0.1:37008";
    m_api = "/api";
}

inline NvrTool::~NvrTool()
{
    
}

inline bool NvrTool::List()
{
    httplib::Client client(m_addr);
    httplib::Params data = 
    {
        {"cmd", "2"}
    };

    auto res = client.Post(m_api, data);
    if (res.error() != httplib::Error::Success)
    {
        return false;
    }
    NvrResponse_t nvr_response;
    bool tmp = ParseResponseMessage(res->body, nvr_response);
    if (!tmp)
    {
        return false;
    }
    switch (nvr_response.error_code)
    {
        case 0:
            std::cerr << "成功" << std::endl;
            break;
        case 3:
            std::cerr << "空的任务列表" << std::endl;
            break;
        default:
            std::cerr << "无效的错误码" << std::endl;
    }
    std::cerr << "response data: \n" << res->body << std::endl;

    return true;
}

inline bool NvrTool::Create()
{
    httplib::Client client(m_addr);
    httplib::Params data = 
    {
        {"cmd", "3"},
        {"input-fmt", "rtsp"},
        {"input-uri", "rtsp://admin:a1234567@192.169.7.123:554"},
        {"input-timeout", "30"},
        {"input-retry", "15"},
        {"input-xspeed", "1.0"},
        {"record-name", "123"},
        {"record-count", "20"},
        {"record-duration", "10"},
        {"publish-fmt", "flv"},
        {"publish-uri", "rtmp://192.169.4.16:1935/live/123"}
    };

    auto res = client.Post(m_api, data);
    if (res.error() != httplib::Error::Success)
    {
        return false;
    }
    NvrResponse_t nvr_response;
    bool tmp = ParseResponseMessage(res->body, nvr_response);
    if (!tmp)
    {
        return false;
    }
    switch (nvr_response.error_code)
    {
        case 0:
            std::cerr << "成功" << std::endl;
            break;
        case 17:
            std::cerr << "任务已存在" << std::endl;
            break;
        case 22:
            std::cerr << "参数错误" << std::endl;
            break;
        default:
            std::cerr << "无效错误码" << std::endl;
    }
    std::cerr << "response data: \n" << res->body << std::endl;

    return true;
}

inline bool NvrTool::Create(NvrCommand_t in)
{
    httplib::Client client(m_addr);
    httplib::Params data = 
    {
        {"cmd", "3"},
        {"input-fmt", in.input_fmt},
        {"input-uri", in.input_uri},
        {"input-timeout", std::to_string(in.input_timeout)},
        {"input-retry", std::to_string(in.input_retry)},
        {"input-xspeed", std::to_string(in.input_xspeed)},
        {"record-name", in.record_name},
        {"record-count", std::to_string(in.record_count)},
        {"record-duration", std::to_string(in.record_duration)},
        {"publish-fmt", in.publish_fmt},
        {"publish-uri", in.publish_uri}
    };

    auto res = client.Post(m_api, data);
    if (res.error() != httplib::Error::Success)
    {
        return false;
    }
    NvrResponse_t nvr_response;
    bool tmp = ParseResponseMessage(res->body, nvr_response);
    if (!tmp)
    {
        return false;
    }
    switch (nvr_response.error_code)
    {
        case 0:
            std::cerr << "成功" << std::endl;
            break;
        case 17:
            std::cerr << "任务已存在" << std::endl;
            break;
        case 22:
            std::cerr << "参数错误" << std::endl;
            break;
        default:
            std::cerr << "无效错误码" << std::endl;
    }
    std::cerr << "response data: \n" << res->body << std::endl;

    return true;
}

inline bool NvrTool::Delete()
{
    httplib::Client client(m_addr);
    httplib::Params data = 
    {
        {"cmd", "4"},
        {"input-uri", "rtsp://admin:a1234567@192.169.7.123:554"}
    };

    auto res = client.Post(m_api, data);
    if (res.error() != httplib::Error::Success)
    {
        return false;
    }
    NvrResponse_t nvr_response;
    bool tmp = ParseResponseMessage(res->body, nvr_response);
    if (!tmp)
    {
        return false;
    }
    switch (nvr_response.error_code)
    {
        case 0:
            std::cerr << "成功" << std::endl;
            break;
        case 2:
            std::cerr << "任务不存在" << std::endl;
            break;
        case 22:
            std::cerr << "参数错误" << std::endl;
            break;
        default:
            std::cerr << "无效错误码" << std::endl;
    }
    std::cerr << "response data: \n" << res->body << std::endl;

    return true;
}

inline bool NvrTool::ParseResponseMessage(std::string in, NvrResponse_t &out)
{
    nlohmann::json parse_data;

    try 
    {
        parse_data = nlohmann::json::parse(in);
        out.monotonic = parse_data["monotonic"];
        out.real_time = parse_data["realtime"];
        out.version = parse_data["version"];
        out.error_code = parse_data["errno"];
    }
    catch (nlohmann::json::parse_error &e)
    {
        std::cerr << "解析JSON数据失败: " << e.what() << std::endl;
        return false;
    }
    catch (nlohmann::json::type_error &e)
    {
        std::cerr << "处理JSON数据失败: " << e.what() << std::endl;
        return false;
    }

    return true;
}