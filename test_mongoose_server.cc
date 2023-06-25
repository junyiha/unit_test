/**
 * @file test_mongoose_server.cc
 * @author your name (you@domain.com)
 * @brief 测试Mongoose服务器
 * @version 0.1
 * @date 2023-06-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "mongoose.h"
#include <unistd.h>

static std::string url {"0.0.0.0:8989"};
static std::string m_http_header;
static std::string file {"/tmp/mnc/92I2J-frame-31.jpg"};

// 读取文件内容到内存
std::vector<char> ReadFileToMemory(const std::string& filename) 
{
    std::ifstream file(filename, std::ios::binary);
    
    if (!file) 
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return {};
    }
    
    // 获取文件大小
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // 分配内存缓冲区
    std::vector<char> buffer(fileSize);
    
    // 读取文件内容到缓冲区
    if (!file.read(buffer.data(), fileSize)) 
    {
        std::cerr << "Failed to read file: " << filename << std::endl;
        return {};
    }
    
    return buffer;
}

static void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{
    if (ev == MG_EV_HTTP_MSG)   
    {
        struct mg_http_message *http_msg = static_cast<struct mg_http_message *>(ev_data);
        std::cerr << "Receive http message, and it's data is :" << std::endl;
        std::string body = http_msg->body.ptr;
        body = body.substr(0, http_msg->body.len);
        std::cerr << "body: " << body << std::endl;

        std::vector<char> buffer = ReadFileToMemory(file);

        mg_printf(c, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding:chunked\r\n\r\n");
        mg_http_write_chunk(c, buffer.data(), buffer.size());
        mg_http_write_chunk(c, "", 0);
        // mg_printf(c, "Content-Length: %ld\r\n\r\n", buffer.size());
        // mg_send(c, buffer.data(), buffer.size());
        // mg_send(c, "\r\n", 2);
        // mg_http_reply(c, 200, m_http_header.c_str(), "success");
    }
}

int main()
{
    struct mg_mgr mgr;
    struct mg_connection *c {nullptr};
    // m_http_header =  "Content-Type: application/json\r\n";
    m_http_header =  "Content-Type: image/jpeg\r\n";
    m_http_header += "Connection: keep-alive\r\n";
    m_http_header += "Server: mnc.exe\r\n";
    m_http_header += "Cache-control: no-cache, max-age=0, must-revalidate\r\n";
    m_http_header += "Access-Control-Allow-Origin: *\r\n";
    m_http_header += "Access-Control-Allow-Methods: *\r\n";
    mg_mgr_init(&mgr);
    c = mg_http_listen(&mgr, url.c_str(), cb, nullptr);
    if (!c)
    {
        std::cerr << "Failed to listen url: " << url << std::endl;
        return -1;
    }
    while (true)
    {
        mg_mgr_poll(&mgr, 1000);
    }
    
    return 0;
}