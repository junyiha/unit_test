/**
 * @file test_http_lib.cc
 * @author your name (you@domain.com)
 * @brief 测试httplib第三方库
 * @version 0.1
 * @date 2023-06-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <map>
#include <string>
#include "httplib.h"

static void Help()
{
    std::string help_info {
R"(
    -h, --help        输出帮助信息
    --check-licence   查看授权信息
    --update-licence  更新授权码
    --list-task       查勘人任务列表
    --start-task      启动任务
    --delete-task     删除任务
    --stop-task       停止任务
    --status-task     查看任务状态
    --update-task     更新任务
)"
    };

    std::cerr << help_info << std::endl;
}


int main(int argc, char *argv[])
{
    httplib::Client cli("http://192.169.4.16:8989");

    httplib::Params params =
    {
        {"cmd", "201"} // 查看许可证信息
    };

    httplib::Params licence_params =
    {
        {"cmd", "202"},
        {"licence", "HFWYU4MP-NEW6GQLD-HFWYU4MK-PFWYU4MK-6PWQUJEB-MDWWU4MK-PFXUSS53-7F8WU4QK-PFWYU4MK-PFXZ24K6-2FXYUMGK"}
    };

    httplib::Params list_task_params =
    {
        {"cmd", "1"}
    };

    httplib::Params start_task_params =
    {
        {"cmd", "2"},
        {"id", "aaa"},
        {"detector-conf-inline", ""},
        {"detector-conf", "@--detector-models@/data/models/PERSON/DETECT.conf@xxx@yyy@"},
        {"input-video-name", "rtsp://192.169.4.16/test_personcount.mp4"},
        {"output-type", "5"}
    };

    httplib::Params delete_task_params =
    {
        {"cmd", "4"},
        {"id", "aaa"}
    };

    httplib::Params stop_task_params =
    {
        {"cmd", "3"},
        {"id", "aaa"}
    };

    httplib::Params status_task_params =
    {
        {"cmd", "6"},
        {"id", "aaa"}
    };

    httplib::Params update_task_params =
    {
        {"cmd", "5"},
        {"id", "aaa"},
        {"input-video-name", "rtsp://admin:a1234567@192.169.7.123:554"}
    };

    std::string arg {};
    for (int col {1}; col < argc; ++col)
    {
        arg = argv[col];
        if (arg == "-h" || arg == "--help")
        {
            std::cerr << "Help message" << std::endl;
            Help();
            return 0;
        }
        else if (arg == "--check-licence")
        {
            auto res = cli.Post("/api", params);
            if (res.error() == httplib::Error::Success)
            {
                std::cerr << "Success to get response information" << std::endl;
                std::cerr << res->body << std::endl;
            }
        }
        else if (arg == "--update-licence")
        {
            auto res = cli.Post("/api", licence_params);
            if (res.error() == httplib::Error::Success)
            {
                std::cerr << "Success to get response information" << std::endl;
                std::cerr << res->body << std::endl;
            }
        }
        else if (arg == "--list-task")
        {
            auto res = cli.Post("/api", list_task_params);
            if (res.error() == httplib::Error::Success)
            {
                std::cerr << "Success to get response information" << std::endl;
                std::cerr << res->body << std::endl;
            }
        }
        else if (arg == "--start-task")
        {
            auto res = cli.Post("/api", start_task_params);
            if (res.error() == httplib::Error::Success)
            {
                std::cerr << "Success to get response information" << std::endl;
                std::cerr << res->body << std::endl;
            }
        }
        else if (arg == "--delete-task")
        {
            auto res = cli.Post("/api", delete_task_params);
            if (res.error() == httplib::Error::Success)
            {
                std::cerr << "Success to get response information" << std::endl;
                std::cerr << res->body << std::endl;
            }
        }
        else if (arg == "--stop-task")
        {
            auto res = cli.Post("/api", stop_task_params);
            if (res.error() == httplib::Error::Success)
            {
                std::cerr << "Success to get response information" << std::endl;
                std::cerr << res->body << std::endl;
            }
        }
        else if (arg == "--status-task")
        {
            auto res = cli.Post("/api", status_task_params);
            if (res.error() == httplib::Error::Success)
            {
                std::cerr << "Success to get response information" << std::endl;
                std::cerr << res->body << std::endl;
            }
        }
        else if (arg == "--update-task")
        {
            auto res = cli.Post("/api", update_task_params);
            if (res.error() == httplib::Error::Success)
            {
                std::cerr << "Success to get response information" << std::endl;
                std::cerr << res->body << std::endl;
            }
        }
        else if (arg == "--post-json")
        {
            std::string msg {R"({"hello":"world"})"};

            auto res = cli.Post("/api", msg, "application/json");
            if (res.error() == httplib::Error::Success)
            {
                std::cerr << "Success to get response information" << std::endl;
                std::cerr << res->body << std::endl;
            }
        }
        else
        {
            std::cerr << "Unknown option: " << arg << std::endl;
            return -1;
        }
    }

    // auto res = cli.Post("/api", "cmd=201", "application/x-www-form-urlencoded");

    // if (res.error() == httplib::Error::Success)
    // {
    //     std::cerr << "Success to get response information" << std::endl;
    //     std::cerr << res->body << std::endl;
    // }

    return 0;
}