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

PictureServer ps;
std::string prefix {"aaa"};

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
        "path/to/aaa-frame-6175.jpg",  
        "path/to/aaa-frame-6221.jpg",  
        "path/to/aaa-frame-6270.jpg",  
        "path/to/aaa-frame-6313.jpg",  
        "path/to/aaa-frame-6363.jpg",  
        "path/to/aaa-frame-6412.jpg",  
        "path/to/aaa-frame-6462.jpg",
        "path/to/aaa-frame-6128.jpg",  
        "path/to/aaa-frame-6179.jpg",  
        "path/to/aaa-frame-6223.jpg",  
        "path/to/aaa-frame-6274.jpg",  
        "path/to/aaa-frame-6316.jpg",  
        "path/to/aaa-frame-6367.jpg",  
        "path/to/aaa-frame-6416.jpg",  
        "path/to/aaa-frame-6466.jpg",
        "path/to/aaa-frame-6132.jpg",  
        "path/to/aaa-frame-6181.jpg",  
        "path/to/aaa-frame-6227.jpg",  
        "path/to/aaa-frame-6278.jpg",  
        "path/to/aaa-frame-6317.jpg",  
        "path/to/aaa-frame-6370.jpg",  
        "path/to/aaa-frame-6420.jpg",  
        "path/to/aaa-frame-6471.jpg",
        "path/to/aaa-frame-6137.jpg",  
        "path/to/aaa-frame-6184.jpg",  
        "path/to/aaa-frame-6230.jpg",  
        "path/to/aaa-frame-6282.jpg",  
        "path/to/aaa-frame-6320.jpg",  
        "path/to/aaa-frame-6371.jpg",  
        "path/to/aaa-frame-6424.jpg",  
        "path/to/aaa-frame-6475.jpg",
        "path/to/aaa-frame-6141.jpg",  
        "path/to/aaa-frame-6188.jpg",  
        "path/to/aaa-frame-6232.jpg",  
        "path/to/aaa-frame-6286.jpg",  
        "path/to/aaa-frame-6324.jpg",  
        "path/to/aaa-frame-6375.jpg",  
        "path/to/aaa-frame-6429.jpg",  
        "path/to/aaa-frame-6477.jpg",
        "path/to/aaa-frame-6144.jpg",  
        "path/to/aaa-frame-6192.jpg",  
        "path/to/aaa-frame-6236.jpg",  
        "path/to/aaa-frame-6290.jpg",  
        "path/to/aaa-frame-6329.jpg",  
        "path/to/aaa-frame-6378.jpg",  
        "path/to/aaa-frame-6146.jpg",  
        "path/to/aaa-frame-6196.jpg",  
        "path/to/aaa-frame-6240.jpg",  
        "path/to/aaa-frame-6291.jpg",  
        "path/to/aaa-frame-6333.jpg",  
        "path/to/aaa-frame-6379.jpg",  
        "path/to/aaa-frame-6147.jpg",  
        "path/to/aaa-frame-6200.jpg",  
        "path/to/aaa-frame-6244.jpg",  
        "path/to/aaa-frame-6294.jpg",  
        "path/to/aaa-frame-6338.jpg",  
        "path/to/aaa-frame-6383.jpg",  
        "path/to/aaa-frame-6441.jpg",
        "path/to/aaa-frame-6150.jpg",  
        "path/to/aaa-frame-6201.jpg",  
        "path/to/aaa-frame-6249.jpg",  
        "path/to/aaa-frame-6299.jpg",  
        "path/to/aaa-frame-6342.jpg",  
        "path/to/aaa-frame-6388.jpg",  
        "path/to/aaa-frame-6445.jpg",
        "path/to/aaa-frame-6154.jpg",  
        "path/to/aaa-frame-6205.jpg",  
        "path/to/aaa-frame-6253.jpg",  
        "path/to/aaa-frame-6303.jpg",  
        "path/to/aaa-frame-6346.jpg",  
        "path/to/aaa-frame-6391.jpg",  
        "path/to/aaa-frame-6446.jpg",
        "path/to/aaa-frame-6159.jpg",  
        "path/to/aaa-frame-6208.jpg",  
        "path/to/aaa-frame-6257.jpg",  
        "path/to/aaa-frame-6305.jpg",  
        "path/to/aaa-frame-6350.jpg",  
        "path/to/aaa-frame-6396.jpg",  
        "path/to/aaa-frame-6447.jpg",
        "path/to/aaa-frame-6163.jpg",  
        "path/to/aaa-frame-6210.jpg",  
        "path/to/aaa-frame-6261.jpg",  
        "path/to/aaa-frame-6307.jpg",  
        "path/to/aaa-frame-6354.jpg",  
        "path/to/aaa-frame-6400.jpg",  
        "path/to/aaa-frame-6449.jpg",
        "path/to/aaa-frame-6167.jpg",  
        "path/to/aaa-frame-6214.jpg",  
        "path/to/aaa-frame-6264.jpg",  
        "path/to/aaa-frame-6308.jpg",  
        "path/to/aaa-frame-6356.jpg",  
        "path/to/aaa-frame-6404.jpg",  
        "path/to/aaa-frame-6453.jpg",
        "path/to/aaa-frame-6171.jpg",  
        "path/to/aaa-frame-6218.jpg",  
        "path/to/aaa-frame-6266.jpg",  
        "path/to/aaa-frame-6312.jpg",  
        "path/to/aaa-frame-6359.jpg",  
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
    ps.GetOriginPicData(pic_data);
    for (c = mgr->conns; c != nullptr; c = c->next)
    {
        if (c->data[0] != 'S') 
            continue;
        
        if (data == nullptr || size == 0)
            continue;

        if (pic_data.empty())
            continue;

        mg_printf(c,
                    "--foo\r\nContent-Type: image/jpeg\r\n"
                    "Content-Length: %lu\r\n\r\n",
                    (unsigned long) size);
        // mg_send(c, data, size);
        mg_send(c, pic_data.data(), pic_data.size());
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

    ps.SetPrefix(prefix);
    ps.Init();
    std::thread ps_thread {&PictureServer::Process, &ps};

    std::thread t {server};

    while (true)
    {
        std::cerr << "sleep 1 second, cnt: " << cnt << std::endl;
        sleep(1);
        cnt++;
    }
}