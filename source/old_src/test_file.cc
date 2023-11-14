/**
 * @file test_file.cc
 * @author your name (you@domain.com)
 * @brief 文件相关的单元测试
 * @version 0.1
 * @date 2023-06-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <fstream>
#include <string>

extern "C"
{
    #include <dirent.h>
}

void Help()
{
    std::string info = R"(
        ./test_file  文件相关操作的单元测试

        --help

    )";

    std::cerr << info << std::endl;
}

bool fileExists(const std::string &filename)
{
    std::ifstream file;

    file.open(filename);
    return file.good();
}

int test_file_exists()
{
    std::string filename = "/userdata/static/origin_pictures/Q4H0v/";
    if (fileExists(filename))
    {
        std::cout << "File exists." << std::endl;
    }
    else
    {
        std::cout << "File does not exist." << std::endl;
    }

    return 0;
}

int test_read_directory_files()
{
    std::string dir_path = "/home/user/zjy-190/Documents/VCR/自动标定算法/标定源数据/2023.11.10/images";
    DIR *dir = opendir(dir_path.c_str());
    if (dir == NULL)
    {
        return -1;
    }
    struct dirent *dir_data = readdir(dir);
    if (dir_data == NULL)
    {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "--help")
        {
            Help();
        }
        else if (arg == "--test-file-exists")
        {
            test_file_exists();
        }
        else if (arg == "--test-read-directory-files")
        {
            test_read_directory_files();
        }
        else 
        {
            Help();
        }
    }

    return 0;
}