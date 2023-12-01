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

int test_asio(Message& message)
{
    LOG(INFO) << "test asio begin..." << "\n";
    asio::io_context io;

    asio::steady_timer t(io, asio::chrono::seconds(5));

    t.wait();

    LOG(INFO) << "hello world" << "\n";
    LOG(INFO) << "test asio end..." << "\n";

    return 0;
}