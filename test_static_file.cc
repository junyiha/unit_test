/**
 * @file test_static_file.cc
 * @author your name (you@domain.com)
 * @brief 测试Mongoose的静态文件托管功能
 * @version 0.1
 * @date 2023-06-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "mongoose.h"
#include <string>

static std::string listen_url {"0.0.0.0:9999"};
static std::string root_dir {"/mnt/remote/190-mnt/zhangjunyi/Documents/工地盒子业务逻辑-rk平台/前端静态文件/20230620/dist"};
static std::string ssi_pattern {"#.html"};

static void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{
    if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *http_msg = static_cast<struct mg_http_message *>(ev_data);
        struct mg_http_serve_opts opts {};
        opts.root_dir = root_dir.c_str();
        // opts.ssi_pattern = ssi_pattern.c_str();
        mg_http_serve_dir(c, http_msg, &opts);
    }
}

int main ()
{
    struct mg_mgr mgr;
    struct mg_connection *c {nullptr};

    mg_mgr_init(&mgr);
    c = mg_http_listen(&mgr, listen_url.c_str(), cb, &mgr);
    if (!c)
        return -1;
    while (true)
    {
        mg_mgr_poll(&mgr, 1000);
    }

    return 0;
}