/**
 * @file test_save_status.cc
 * @author your name (you@domain.com)
 * @brief 保存机械臂当前状态信息的单元测试
 * @version 0.1
 * @date 2023-07-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>
#include <sys/stat.h>

static void Help()
{
    std::string help_info {R"(
help information

-h  output help information
    )"};

    std::cerr << help_info << std::endl;
}

bool createDirectory(const std::string& path) {
    // 检查路径是否存在
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        // 路径不存在，创建目录
        if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0) {
            std::cout << "Created directory: " << path << std::endl;
            return true;
        } else {
            std::cerr << "Failed to create directory: " << path << std::endl;
            return false;
        }
    } else if (info.st_mode & S_IFDIR) {
        // 路径已存在且为目录
        std::cout << "Directory already exists: " << path << std::endl;
        return true;
    } else {
        // 路径已存在但不是目录
        std::cerr << "Path already exists but not a directory: " << path << std::endl;
        return false;
    }
}

bool createDirectoriesRecursive(const std::string& path) {
    size_t pos = 0;
    std::string subPath;

    while ((pos = path.find_first_of("/\\", pos + 1)) != std::string::npos) {
        subPath = path.substr(0, pos);
        if (!createDirectory(subPath)) {
            return false;
        }
    }

    return createDirectory(path);
}

using RET_t = enum
{
    RET_ERR = -1,
    RET_OK = 0
};

std::string data_dir {"/tmp/robot/"};

void GetCurTimeName(std::string &out)
{
    std::time_t current_time;

    current_time = std::time(nullptr);
    auto local_time = std::localtime(&current_time);
    out = std::to_string((local_time->tm_year + 1900)) + "-";
    out += std::to_string(local_time->tm_mon + 1) + "-";
    out += std::to_string(local_time->tm_mday) + "-";
    out += std::to_string(local_time->tm_hour) + "-";
    out += std::to_string(local_time->tm_min) + "-";
    out += std::to_string(local_time->tm_sec);
}

int test_save_status_v1()
{
    std::cerr << "save status version 1" << std::endl;

    bool result {false};
    std::string file_name {};
    std::ofstream file;

    result = createDirectoriesRecursive(data_dir);
    if (!result)
    {
        std::cerr << "failed to create direcory: " << data_dir << std::endl;
        return RET_ERR;
    }

    GetCurTimeName(file_name);
    std::string tmp = data_dir + file_name + ".txt";
    file.open(tmp, std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "failed to open file: " << data_dir + file_name << std::endl;
        return RET_ERR;
    }

    std::vector<double> joint_arr {
        0.1313,
        0.02410,
        0.140254821,
        0.3413,
        0.7294792,
        0.1379173
    };

    for (auto &it : joint_arr)
    {
        file << it;
        file << "\n";
    }

    std::cerr << "success" << std::endl;
    file.close();
    return 0;
}

int main(int argc, char **argv)
{
    std::string arg {};
    for (int col{1}; col < argc; ++col)
    {
        arg = argv[col];
        if (arg == "-h")
        {
            Help();
        }
        else if (arg == "--test-save-status-v1")
        {
            test_save_status_v1();
        }
        else
        {
            Help();
        }
    }
}