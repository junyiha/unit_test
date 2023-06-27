/**
 * @file test_time.cc
 * @author your name (you@domain.com)
 * @brief 测试时间相关函数
 * @version 0.1
 * @date 2023-06-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <ctime>

int main ()
{

    std::time_t current_time = std::time(nullptr);
    std::cerr << "Current timestamp: " << current_time << std::endl;

    return 0;
}