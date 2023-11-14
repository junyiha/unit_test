/**
 * @file test_function_time.cc
 * @author your name (you@domain.com)
 * @brief 测试函数运行时间
 * @version 0.1
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>
#include <chrono>

void Help()
{
    std::string help_info {
        R"(
            test_function_time.exe

            -h, --help  打印帮助信息
            --x86-time  高精度计时
            --arm-time  低精度计时
        )"
    };

    std::cerr << help_info << std::endl;
}

// 要测试运行时间的函数
void myFunction()
{
    // 在这里添加你的函数逻辑
    for (int i = 0; i < 1000000; ++i)
    {
        // 执行一些操作
    }
}

int x86_time()
{
    // 获取当前时间点
    auto startTime = std::chrono::high_resolution_clock::now();

    // 调用要测试的函数
    myFunction();

    // 获取当前时间点
    auto endTime = std::chrono::high_resolution_clock::now();

    // 计算时间差
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // 输出结果
    std::cout << "函数运行时间： " << duration.count() << " 毫秒" << std::endl;

    return 0;
}

int arm_time()
{
    // 获取当前时间点
    auto startTime = std::chrono::steady_clock::now();

    // 调用要测试的函数
    myFunction();

    // 获取当前时间点
    auto endTime = std::chrono::steady_clock::now();

    // 计算时间差
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // 输出结果
    std::cout << "函数运行时间： " << duration.count() << " 毫秒" << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg {};
    for (int col {1}; col < argc; ++col)
    {
        arg = argv[col];
        if (arg == "-h" || arg == "--help")
        {
            Help();
        }
        else if (arg == "--x86-time")
        {  
            x86_time();
        }
        else if (arg == "--arm-time")
        {
            arm_time();
        }
        else 
        {
            Help();
        }
    }

    return 0;
}