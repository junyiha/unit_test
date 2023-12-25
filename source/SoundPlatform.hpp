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
#include "nlohmann/json.hpp"

class SoundPlatform
{
private:
    std::string m_addr;
    std::string m_sn;
    
public:
    SoundPlatform() = delete;
    SoundPlatform(std::string sn, std::string addr) : m_sn(sn), m_addr(addr)
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
        data["params"]["tid"] = "123";
        data["params"]["vol"] = vol;
        item_data["name"] = name;
        item_data["uri"] = uri;
        data["params"]["urls"].push_back(item_data);

        std::cerr << data.dump() << "\n";

        auto res = cli.Post("/", data.dump(), "Content-Type: application/json");
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
        auto res = cli.Post("/", data.dump(), "Content-Type: application/json");
        if (res.error() == httplib::Error::Success)
        {
            return 1;
        }

        return 0;
    }

    int List(std::vector<std::string>& list)
    {
        httplib::Client cli(m_addr);
        nlohmann::json data;

        data["sn"] = m_sn;
        data["type"] = "req";
        data["name"] = "songs_queue_list";
        auto res = cli.Post("/", data.dump(), "Content-Type: application/json");
        if (res.error() == httplib::Error::Success)
        {
            return 1;
        }
        
        nlohmann::json parsed_data;
        try
        {
            parsed_data = nlohmann::json::parse(res->body);
            for (auto& it : parsed_data["params"]["songs_queue"])
            {
                list.push_back(std::string(it));
            }
        }
        catch (nlohmann::json::parse_error& e)
        {
            std::cerr << "parse error, data: " << res->body << std::endl;
            return 0;
        }
        catch (nlohmann::json::type_error& e)
        {
            std::cerr << "type error, data: " << res->body << std::endl;
            return 0;
        }

        return 1;
    }
};