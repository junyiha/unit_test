/**
 * @file test_nvr.cc
 * @author your name (you@domain.com)
 * @brief 测试nvr
 * @version 0.1
 * @date 2023-10-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "NvrTool.hpp"

static void Help()
{
    std::string info = R"(

        --help
        
        --list
        --create
        --delete
    )";

    std::cerr << info << std::endl;
}

NvrTool nvr;

int List()
{
    bool res = nvr.List();
    if (!res)
    {
        std::cerr << "failed to lsit" << std::endl;
    }
    else 
    {
        std::cerr << "succes" << std::endl;
    }

    return 0;
}

int Create()
{
    NvrTool::NvrCommand_t cmd;
    cmd.input_fmt = "rtsp";
    cmd.input_uri = "rtsp://admin:a1234567@192.169.7.123:554";
    cmd.input_timeout = 30;
    cmd.input_retry = 15;
    cmd.input_xspeed = 1.0;
    cmd.record_name = "123";
    cmd.record_count = 20;
    cmd.record_duration = 10;
    cmd.publish_fmt = "flv";
    cmd.publish_uri = "rtmp://192.169.4.16:1935/live/123";
    bool res = nvr.Create(cmd);
    if (!res)
    {
        std::cerr << "failed to lsit" << std::endl;
    }
    else 
    {
        std::cerr << "succes" << std::endl;
    }

    return 0;
}

int Delete()
{
    bool res = nvr.Delete();
    if (!res)
    {
        std::cerr << "failed to lsit" << std::endl;
    }
    else 
    {
        std::cerr << "succes" << std::endl;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg;
    for (int i = 1; i < argc; i++)
    {
        arg = argv[i];
        if (arg == "--list")
        {
            List();
        }
        else if (arg == "--create")
        {
            Create();
        }
        else if (arg == "--delete")
        {
            Delete();
        }
        else 
        {
            Help();
        }
    }

    return 0;
}