/**
 * @file test_libuv.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "entry.hpp"

extern "C"
{
    #include "uv.h"
}

int test_libuv_hello(Message& message)
{
    uv_loop_t *loop = static_cast<uv_loop_t *>(malloc(sizeof(uv_loop_t)));
    uv_loop_init(loop);

    printf("Now quitting.\n");
    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);

    return 1;
}

void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
    if (nread > 0) {
        printf("Received data: %.*s\n", (int)nread, buf->base);
    } else if (nread < 0) {
        if (nread != UV_EOF) {
            fprintf(stderr, "Read error: %s\n", uv_strerror(nread));
        }
        uv_close((uv_handle_t *)client, NULL);
    }

    free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "Error on new connection: %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(uv_default_loop(), client);

    if (uv_accept(server, (uv_stream_t *)client) == 0) {
        // Handle the client connection
        // Implement logic to handle HTTP requests here
        LOG(INFO) << "a connect in" << "\n";
        uv_read_start((uv_stream_t*)client, (uv_alloc_cb)uv_buf_init, on_read);
    } else {
        uv_close((uv_handle_t *)client, NULL);
    }
}

int test_libuv_http_server(Message& message)
{
    uv_loop_t *loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 8000, &addr);

    uv_tcp_bind(&server, (const sockaddr*)&addr, 0);
    int result = uv_listen((uv_stream_t*)&server, SOMAXCONN, on_new_connection);
    if (result)
    {
        LOG(ERROR) << "Error on listening: \n" << uv_strerror(result) << "\n";
        return 0;
    }

    uv_run(loop, UV_RUN_DEFAULT);

    return 1;
}

int test_libuv(Message& message)
{
    LOG(INFO) << "----test network begin----\n";

    std::map<std::string, std::function<int(Message&)>>cmd_map = {
        {"test-libuv-hello", test_libuv_hello},
        {"test-libuv-http-server", test_libuv_http_server}
    };

    std::string cmd = message.message_pool.at(2);
    auto it = cmd_map.find(cmd);
    if (it != cmd_map.end())
    {
        it->second(message);
        return 1;
    }
    else 
    {
        LOG(ERROR) << "invalid command: " << cmd << std::endl;
    }

    LOG(INFO) << "----test network end----\n";

    return 1;
}