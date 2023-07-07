/**
 * @file test_remove.cc
 * @author your name (you@domain.com)
 * @brief 测试文件删除
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>

void Help()
{
    std::string help_info {R"(
        test_remove.exe  删除文件单元测试

        -h, --help  输出帮助信息
        -o  第一次单元测试
        --remove-file  删除文件
    )"};

    std::cerr << help_info << std::endl;
}

int old() {
    const char *filename = "/dev/shm/aaa-consumer.idx";

    if (remove(filename) == 0) {
        printf("文件删除成功\n");
    } else {
        printf("文件删除失败\n");
    }

    return 0;
}

#include <cstdio>

int RemoveFile()
{
    int ret {-1};
    std::string file {"path/origin_pictures/2.jpg"};

    ret = std::remove(file.c_str());
    if (ret != 0)
    {
        std::cerr << "Failed to remove file: " << file << std::endl;
        return -1;
    }

    return 0;
}

int RemoveDirectory()
{
    int ret {-1};
    std::string dir {"/userdata/static/origin_pictures/Q4H0v"};

    ret = rmdir(dir.c_str());
    if (ret != 0)
    {
        std::cerr << "Failed to remove directory: " << dir << std::endl;
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg {};
    
    for (int col {1}; col < argc; col++)
    {
        arg = argv[col];
        if (arg == "-h" || arg == "--help")
        {
            Help();
        }
        else if (arg == "-o")
        {
            old();
        }
        else if (arg == "--remove-file")
        {
            RemoveFile();
        }
        else if (arg == "--remove-dir")
        {
            RemoveDirectory();
        }
        else 
        {
            Help();
        }
    }
}