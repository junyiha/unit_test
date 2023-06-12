/**
 * @file test_video_stream.cc
 * @author your name (you@domain.com)
 * @brief 
 * 
 * http://192.169.4.16:8200/api/video1
 * 
 * @version 0.1
 * @date 2023-06-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include "mongoose.h"
#include "PictureServer.hpp"
#include "ProcessFrame.hpp"

PictureServer ps;
std::string prefix {"aaa"};

std::string fire_prefix {"fire"};

static void CreateHeader(std::string &out)
{
    out =  "Content-Type: application/json\r\n";
    out += "Connection: keep-alive\r\n";
    out += "Server: mnc.exe\r\n";
    out += "Cache-control: no-cache, max-age=0, must-revalidate\r\n";
    out += "Access-Control-Allow-Origin: *\r\n";
    out += "Access-Control-Allow-Methods: *\r\n";
}

static bool ProcessHttpMsg(struct mg_http_message *hm)
{
    std::string query_string;

    if (hm->query.ptr == nullptr)
        return false;

    query_string = hm->query.ptr;
    query_string = query_string.substr(0, hm->query.len);
    std::size_t p = query_string.find('=');
    std::string key = query_string.substr(0, p);
    std::string value = query_string.substr(p+1);

    if (key.compare("play") == 0)
    {
        if (value.compare("1") == 0)
            return true;
    }

    return false;
}


static void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{
    if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        if (mg_http_match_uri(hm, "/api/video1"))
        {
            if (ProcessHttpMsg(hm))
            {
                c->data[0] = 'S';
                mg_printf(
                    c, "%s",
                    "HTTP/1.0 200 OK\r\n"
                    "Cache-Control: no-cache\r\n"
                    "Pragma: no-cache\r\nExpires: Thu, 01 Dec 1994 16:00:00 GMT\r\n"
                    "Content-Type: multipart/x-mixed-replace; boundary=--foo\r\n\r\n");
            }
            else 
            {
                c->data[0] = ' ';
                std::string header_string;
                CreateHeader(header_string);
                mg_http_reply(c, 200, header_string.c_str(), "close");
            }
        }
        else 
        {
            struct mg_http_serve_opts opts = {.root_dir = "web_root"};
            mg_http_serve_dir(c, static_cast<mg_http_message *>(ev_data), &opts);

        }
    }

    (void) fn_data;
}

/**
 * @brief 通过发送由文件名“files”数组指定的MJPEG帧来模拟图像流
 * 
 * @param mgr 
 */
static void broadcast_mjpeg_frame(struct mg_mgr *mgr) 
{
    std::vector<std::string> file_arr = 
    {
        "path/to/aaa-frame-6123.jpg",  
        "path/to/aaa-frame-6408.jpg",  
        "path/to/aaa-frame-6457.jpg"
    };

    const char *files[] = 
    {
        "path/to/aaa-frame-6123.jpg",
        "path/to/aaa-frame-6128.jpg",
        "path/to/aaa-frame-6132.jpg",
        "path/to/aaa-frame-6137.jpg",
        "path/to/aaa-frame-6141.jpg",
        "path/to/aaa-frame-6144.jpg",
        "path/to/aaa-frame-6146.jpg"
    };

    size_t nfiles = sizeof(files) / sizeof(files[0]);
    static size_t i;  // i 静态变量 调用一次broadcast_mjpeg_frame() 函数，递增一次，用于指向下一张mjpeg图片
    const char *path = files[i++ % nfiles];
    std::string file_path = file_arr[i++ % file_arr.size()];
    size_t size = 0;
    // char *data = mg_file_read(&mg_fs_posix, path, &size);  // Read next file
    char *data = mg_file_read(&mg_fs_posix, file_path.c_str(), &size);  // Read next file
    struct mg_connection *c;
    std::vector<char> pic_data;
    ParseMjpeg::Mjpeg_t m;
    ps.GetMjpegData(m);
    ps.GetOriginPicData(pic_data);
    for (c = mgr->conns; c != nullptr; c = c->next)
    {
        if (c->data[0] != 'S') 
            continue;
        
        // if (data == nullptr || size == 0)
        //     continue;

        // if (pic_data.empty())
        //     continue;

        if (m.origin_pic_data.empty())
            continue;

        mg_printf(c,
                    "--foo\r\nContent-Type: image/jpeg\r\n"
                    "Content-Length: %lu\r\n\r\n",
                    (unsigned long) size);
        // mg_send(c, data, size);
        // mg_send(c, pic_data.data(), pic_data.size());
        mg_send(c, m.origin_pic_data.data(), m.origin_pic_data.size());
        mg_send(c, "\r\n", 2);
    }

    free(data);
}

static void timer_callback(void *arg) 
{
    broadcast_mjpeg_frame(static_cast<mg_mgr *>(arg));
}

int server ()
{
    struct mg_mgr mgr;

    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://0.0.0.0:8200", cb, nullptr);
    mg_timer_add(&mgr, 500, MG_TIMER_REPEAT, timer_callback, &mgr);

    while (true)
    {
        mg_mgr_poll(&mgr, 50);
    }

    return 0;
}


int main ()
{
    std::size_t cnt {0};

    prefix = "cxsLw";
    // ps.SetPrefix(prefix);
    // ps.SetPrefix(fire_prefix);
    // ps.Init();
    // std::thread ps_thread {&PictureServer::Process, &ps};
    // if (ps_thread.joinable())
    //     ps_thread.join();
    std::shared_ptr<PictureServer> ps_ptr = std::make_shared<PictureServer>();
    ps_ptr->SetPrefix(prefix);
    ps_ptr->Init();
    std::thread ps_shared_thread {&PictureServer::Process, ps_ptr};

    std::thread t {server};

    while (true)
    {
        std::cerr << "sleep 1 second, cnt: " << cnt << std::endl;
        sleep(1);
        cnt++;
    }
}