/**
 * @file test_asio.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "entry.hpp"
#include "asio.hpp"

int asio_timer_hello()
{
    asio::io_context io;

    asio::steady_timer t(io, asio::chrono::seconds(5));

    t.wait();

    LOG(INFO) << "hello world" << "\n";
    LOG(INFO) << "test asio end..." << "\n";

    return 1;
}

int test_asio(Message& message)
{
    LOG(INFO) << "test asio begin..." << "\n";

    std::map<std::string, std::function<int()>> cmd_map = {
        {"asio-timer-hello", asio_timer_hello}
    };

    std::string cmd = message.message_pool[2];

    auto it = cmd_map.find(cmd);
    if (it != cmd_map.end())
    {
        it->second();
        return 1;
    }

    LOG(ERROR) << "invalid command: " << cmd << "\n";
    LOG(INFO) << "test asio end..." << "\n";

    return 0;
}
