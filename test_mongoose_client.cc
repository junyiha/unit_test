/**
 * @file test_mongoose_client.cc
 * @author your name (you@domain.com)
 * @brief 测试Mongoose客户端
 * @version 0.1
 * @date 2023-06-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include "mongoose.h"

static std::string url {"http://127.0.0.1:8989"};
static const char *s_post_data = nullptr;      // POST data

struct Client_t 
{
    bool result;
    std::string msg;
};

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{
    if (ev == MG_EV_OPEN)
    {
        std::cerr << "HTTP connection is open" << std::endl;
    }
    else if (ev == MG_EV_POLL)
    {

    }
    else if (ev == MG_EV_CONNECT)
    {
        /**
         * @brief 在这里发送请求数据
         * 
         */
        std::cerr << "HTTP connection is connected" << std::endl;
        struct mg_str host = mg_url_host(url.c_str());
        mg_printf(c,
                "%s %s HTTP/1.0\r\n"
                "Host: %.*s\r\n"
                "Content-Type: octet-stream\r\n"
                "Content-Length: %d\r\n"
                "\r\n",
                s_post_data ? "POST" : "GET", mg_url_uri(url.c_str()), (int) host.len,
                host.ptr, 0);
        mg_send(c, "hello world", strlen("hello world"));
    }
    else if (ev == MG_EV_HTTP_MSG)
    {
        std::cerr << "receive http message data" << std::endl;
        struct mg_http_message *http_msg = static_cast<struct mg_http_message *>(ev_data);
        Client_t *c_msg = static_cast<Client_t *>(fn_data);
        c_msg->msg = http_msg->body.ptr;
        c_msg->msg = c_msg->msg.substr(0, http_msg->body.len);
        c_msg->result = true;
    }
    else if (ev == MG_EV_ERROR)
    {
        std::cerr << "generate some error information" << std::endl;
        Client_t *c_msg = static_cast<Client_t *>(fn_data);
        c_msg->result = true;
    }
}

int main()
{
    struct mg_mgr mgr;              // Event manager
    Client_t c_msg {false, ""};
    mg_mgr_init(&mgr);
    mg_http_connect(&mgr, url.c_str(), fn, &c_msg);
    while (!c_msg.result)
    {
        mg_mgr_poll(&mgr, 50);
    }
    std::cerr << "c_msg.msg: " << c_msg.msg << std::endl;
    mg_mgr_free(&mgr);

    return 0;
}