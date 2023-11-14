/**
 * @file test_stl.cc
 * @author your name (you@domain.com)
 * @brief 测试stl多线程访问问题
 * @version 0.1
 * @date 2023-06-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <queue>
#include <thread>
#include <unistd.h>

std::queue<int> queue;

void Call_A()
{
    int a;

    while (true)
    {
        a = queue.front();
        std::cerr << "a: " << a << std::endl;
    }
}

void Call_B()
{
    int b;

    while(true)
    {
        b = queue.front();
        std::cerr << "b: " << b << std::endl;
    }
}

int main()
{
    queue.push(10);
    queue.push(20);
    queue.push(30);

    std::thread a_p = std::thread{Call_A};
    std::thread b_p = std::thread{Call_B};

    sleep(100);   

    return 0;
}