/**
 * @file test_thread.cc、
 * @author your name (you@domain.com)
 * @brief 线程的单元测试
 * @version 0.1
 * @date 2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>   
#include <atomic>
#include <sched.h>
#include <csignal>

class Request 
{
public:
    void SetId(int id)
    {
        m_id = id;
    }

    void Process()
    {
        std::cerr << "Processing request id: " << m_id << std::endl;
    }

private:
    int m_id;
};

void Help()
{
    std::string help_info {
        R"(
            Help information:
            -h, --help  打印帮助信息

        )"
    };

    std::cerr << help_info << std::endl;
}

std::atomic<bool> m_flag{false};

void signalHandler(int signal)
{
    std::cerr << "Received signal : " << signal << std::endl;
    m_flag.store(true);
}

void DeadLoop()
{
    std::size_t cnt {0};
    while (true)
    {
        if (m_flag.load())
        {
            std::cerr << "receive exited signal" << std::endl;
            sleep(1);
            break;
        }

        std::cerr << "\n cnt: " << cnt << "dead loop\n" << std::endl;
        sleep(1);
        cnt++;
    }
}

int test_1()
{
    Request q;
    std::thread t {&Request::Process, &q};

    t.join();

    return 0;
}

int RenameThread()
{
    std::thread tmp(DeadLoop);
    std::string thread_name {"dead_loop"};
    pthread_setname_np(tmp.native_handle(), thread_name.c_str());
    tmp.detach();
    while(!m_flag.load())
    {
        sched_yield();
    }
    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg {};
    std::signal(SIGINT, signalHandler);
    for (int col {1}; col < argc; ++col)
    {
        arg = argv[col];
        if (arg == "-h" || arg == "--help")
        {
            Help();
            return 0;
        }
        else if (arg == "--rename-thread")
        {
            RenameThread();
        }
    }
}