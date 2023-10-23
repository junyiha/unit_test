/**
 * @file test_bind.cc
 * @author your name (you@domain.com)
 * @brief 测试函数绑定
 * @version 0.1
 * @date 2023-09-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>

static void Help()
{
    std::string help_info = R"(
        test_bind.exe  绑定函数的单元测试

        -h  输出帮助信息
    )";

    std::cerr << help_info << std::endl;
}

class Tool
{
public:
    void Process(std::string in, std::string &out);

};

void Tool::Process(std::string in, std::string &out)
{

}

class Device
{
public:
    std::unordered_map<std::string, std::function<void(std::string, std::string)>> m_cmds;

private:
    Tool *m_tool;
};

Device::Device()
{
    m_tool = new Tool();
    // m_cmds["tool"] = std::bind(&Tool::Process, m_tool, std::string in, std::string in);
}

Device::~Device()
{

}


int main(int argc, char *argv)
{
    std::string arg;
    for (int row = 1; row < argc; row++)
    {
        arg = argv[row];
        if (arg == "-h")
        {
            Help();
        }
        else
        {
            Help();
        }
    }
}