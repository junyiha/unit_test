/**
 * @file test_cb.cc
 * @author your name (you@domain.com)
 * @brief 测试回调函数
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <unistd.h>
#include <iostream>

static std::size_t cnt {0};
using pc_cb = void (*)(void *);

void VirtualPictureServer (void *arg)
{
    while (true)
    {
        cnt++;
        sleep(2);
        std::cerr << "cnt: "<< cnt << ", generate a image" << std::endl;
    }
}

void Test(pc_cb cb)
{
    cb(nullptr);
}

int main() 
{

    pc_cb cb = VirtualPictureServer;
    Test(cb);

    return 0;
}