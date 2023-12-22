/**
 * @file SoundPlatform.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include <string>

#include "httplib.h"
#include "old_src/json.hpp"

class SoundPlatform
{
private:
    std::string m_addr;
    std::string m_sn;
    
public:
    SoundPlatform()
    {

    }
    ~SoundPlatform()
    {
        
    }

public:
    int Append(size_t vol, std::string name, std::string uri)
    {
        httplib::Client cli(m_addr);
        nlohmann::json data;
        nlohmann::json item_data;

        data["sn"] = m_sn;
        data["type"] = "req";
        data["name"] = "songs_queue_append";
        data["tid"] = "123";
        data["vol"] = vol;
        item_data["name"] = name;
        item_data["uri"] = uri;
        data["params"]["urls"].push_back(item_data);

        auto res = cli.Post("", data.dump(), "Content-Type: application/json");
        if (res.error() == httplib::Error::Success)
        {
            return 1;
        }

        return 0;
    }

    int Clear()
    {
        httplib::Client cli(m_addr);
        nlohmann::json data;

        data["sn"] = m_sn;
        data["type"] = "req";
        data["name"] = "songs_queue_clear";

        auto res = cli.Post("", data.dump(), "Content-Type: application/json");
        if (res.error() == httplib::Error::Success)
        {
            return 1;
        }

        return 0;
    }
};