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
    NvrTool();
    virtual ~NvrTool();

public:
    bool List();

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
    std::cerr << "response data: \n" << res->body << std::endl;

    return true;
}