/**
 * @file test_get_meminfo.cc
 * @author your name (you@domain.com)
 * @brief 测试获取系统内存信息
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <sys/sysinfo.h>
#include <iostream>
#include <string>

void Help()
{
    std::string help_info {R"(
        test_get_meminfo.exe  获取系统内存信息

        -h, --help   获取帮助信息
        -o, --old-version  第一次单元测试
    )"};
    std::cerr << help_info << std::endl;
}

int old_version() {
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != -1) {
        long long total_memory = sys_info.totalram * sys_info.mem_unit;
        long long free_memory = sys_info.freeram * sys_info.mem_unit;
        long long used_memory = total_memory - free_memory;
        
        std::cout << "Total Memory: " << total_memory << " bytes" << std::endl;
        std::cout << "Free Memory: " << free_memory << " bytes" << std::endl;
        std::cout << "Used Memory: " << used_memory << " bytes" << std::endl;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "Total Memory: " << total_memory / 1024 << " m" << std::endl;
        std::cout << "Free Memory: " << free_memory / 1024 << " m" << std::endl;
        std::cout << "Used Memory: " << used_memory / 1024 << " m" << std::endl;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "Total Memory: " << total_memory / 1024 / 1024 << " G" << std::endl;
        std::cout << "Free Memory: " << free_memory / 1024 / 1024 << " G" << std::endl;
        std::cout << "Used Memory: " << used_memory / 1024 / 1024 << " G" << std::endl;
    } else {
        std::cerr << "Failed to retrieve system memory information." << std::endl;
    }

    return 0;
}

int GetMemInfo()
{
    int ret;
    struct sysinfo sys_info {};

    ret = sysinfo(&sys_info);
    if (ret == -1)
    {
        std::cerr << "Failed to get system information" << std::endl;
        return -1;
    }

    std::size_t total_memory = sys_info.totalram / 1024 / 1024;
    std::size_t free_memory = sys_info.freeram / 1024 / 1024;
    std::size_t used_memory = total_memory - free_memory / 1024 / 1024;

    std::cerr << "total memory: " << total_memory << " MB" << std::endl;
    std::cerr << "free memory: " << free_memory << " MB" << std::endl;
    std::cerr << "used memory: " << used_memory << " MB" << std::endl;
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
        else if (arg == "-o" || arg == "--old-version")
        {
            old_version();
        }
        else if (arg == "--get-meminfo")
        {
            GetMemInfo();
        }
        else 
        {
            Help();
        }
    }

    return 0;
}