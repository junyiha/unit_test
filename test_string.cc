/**
 * @file test_string.cc
 * @author your name (you@domain.com)
 * @brief 字符串单元测试
 * @version 0.1
 * @date 2023-09-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <string>
#include <iostream>
#include <vector>

static void Help()
{
    std::string help_info = R"(
        test_string.exe  字符串的单元测试

        -h  输出帮助信息
    )";

    std::cerr << help_info << std::endl;
}

int test_split_api(std::string in)
{
    std::cerr << "source string: " << in << std::endl;
    std::vector<std::string> result;
    size_t startPos = 0;

    for (size_t i = 0; i < in.length(); ++i)
    {
        if (in[i] == '/')
        {
            std::string subStr = in.substr(startPos, i - startPos);
            result.push_back(subStr);
            startPos = i + 1;
        }
    }

    /**处理最后一个字符串*/
    if (startPos < in.length())
    {
        std::string subStr = in.substr(startPos);
        result.push_back(subStr);
    }

    std::cerr << "/*********************/" << std::endl;
    for (auto &it : result)
    {
        std::cerr << it << std::endl;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    std::string arg;
    for (int row {1}; row < argc; row++)
    {
        arg = argv[row];
        if (arg == "-h")
        {
            Help();
        }
        else if (arg == "--test-split-api")
        {
            test_split_api(std::string(argv[row + 1]));
            break;
        }
        else
        {
            Help();
        }
    }
}