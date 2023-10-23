/**
 * @file test_vector.cc
 * @author your name (you@domain.com)
 * @brief 测试vector相关特性
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <vector>
#include <string>

void Help()
{
    std::string  help_info {R"(
        test_vector.exe  测试vector相关特性

        -h, --help   输出帮助信息

    )"};

    std::cerr << help_info << std::endl;
}

void TestVector()
{
    int max {5};
    std::vector<int> id_arr {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> tmp_arr {};

    if (id_arr.size() > max)
    {
        for (int col {max}; col < id_arr.size(); col++)
        {
            tmp_arr.push_back(id_arr.at(col));
        }
    }

    std::cerr << "\nid array: " << std::endl;
    for (auto &id : id_arr)
    {
        std::cerr << "id: " << id << std::endl;
    }

    std::cerr << "\ntmp id array : " << std::endl;
    for (auto &id : tmp_arr)
    {
        std::cerr << "tmp id: " << id << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::string arg {};
    for (int col {1}; col < argc; ++col)
    {
        arg = argv[col];
        if (arg == "-h")
        {
            Help();
        }
        else if (arg == "--test-vector")
        {
            TestVector();
        }
        else 
        {
            Help();
        }
    }
}