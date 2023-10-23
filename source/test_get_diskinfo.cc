/**
 * @file test_get_diskinfo.cc
 * @author your name (you@domain.com)
 * @brief 获取磁盘信息
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <sys/statvfs.h>
#include <string>

void Help()
{
    std::string help_info {R"(
        test_get_diskinfo.exe  获取磁盘信息

        -h, --help  输出帮助信息
        -o, --old-version  第一次测试
    )"};
    std::cerr << help_info << std::endl;
}

int old_version() {
    struct statvfs fs_info;
    if (statvfs("/userdata/static/", &fs_info) == 0) {
        unsigned long total_space = fs_info.f_frsize * fs_info.f_blocks;
        unsigned long available_space = fs_info.f_frsize * fs_info.f_bavail;

        std::cout << "Total Space: " << total_space << " bytes" << std::endl;
        std::cout << "Available Space: " << available_space << " bytes" << std::endl;
    } else {
        std::cerr << "Failed to get filesystem information." << std::endl;
    }

    return 0;
}

int GetDiskInfo(std::string path)
{
    int ret {};
    struct statvfs fs_info;

    ret = statvfs(path.c_str(), &fs_info);
    if (ret == -1)
    {
        std::cerr << "Failed to execute statvfs() function" << std::endl;
        return -1;
    }

    std::size_t total_space = fs_info.f_frsize * fs_info.f_blocks / 1024 / 1024;
    std::size_t free_space = fs_info.f_frsize * fs_info.f_bfree / 1024 / 1024;

    std::cerr << "total space: " << total_space << " MB" << std::endl;
    std::cerr << "free space: " << free_space << " MB" << std::endl;

    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>

int df_disk() {
    FILE* pipe = popen("df -h", "r");
    if (pipe) {
        char buffer[128];
        std::string result;
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
        pclose(pipe);

        // 解析所需的磁盘信息
        // ...

        std::cout << result << std::endl;
    }

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
        else if (arg == "--get-diskinfo")
        {
            GetDiskInfo(argv[col + 1]);
        }
        else if (arg == "--df-diskinfo")
        {
            df_disk();
        }
        else 
        {
            Help();
        }
    }
}
