/**
 * @file test_hashmap.cc
 * @author your name (you@domain.com)
 * @brief 哈希表的单元测试
 * @version 0.1
 * @date 2023-09-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>

static void Help()
{
    std::string help_info = R"(

        test_hashmap.exe  哈希表单元测试

        -h, --help   输出帮助信息

    )";

    std::cerr << help_info << std::endl;
}

int test_hashmap_1()
{
    // 创建一个哈希表
    std::unordered_map<std::string, int> hashMap;

    // 插入键值对
    hashMap["Alice"] = 25;
    hashMap["Bob"] = 30;

    // 查找键的值
    if (hashMap.find("Alice") != hashMap.end())
    {
        std::cout << "Alice's age is " << hashMap["Alice"] << std::endl;
    }
    else
    {
        std::cout << "Alice not found in the map." << std::endl;
    }

    // 删除键值对
    hashMap.erase("Bob");

    // 遍历哈希表
    for (const auto &pair : hashMap)
    {
        std::cout << pair.first << "'s age is " << pair.second << std::endl;
    }

    return 0;
}

int test_hashmap_cmd()
{
    std::string cmd {"test-hashmap-1"};
    std::unordered_map<std::string, std::function<int()>> cmd_map;
    cmd_map["test-hashmap-1"] = test_hashmap_1;

    auto res = cmd_map.find("test-hashmap-1");
    if (res != cmd_map.end())
    {
        std::cerr << "找到对应的函数" << std::endl;
        res->second();
        return 0;
    }
    else
    {
        std::cerr << "没有找到对应的函数" << std::endl;
        return -1;
    }
}

// class Robot
// {
// private:
//     std::unordered_map<std::string, std::function<int(Robot *)>> cmd_map;

// private:
//     int MoveJoint()
//     {
//         std::cerr << "in Robot class, move joint" << std::endl;
//         return 0;
//     }
// public:
//     int test_hashmap_class_cmd()
//     {
//         std::string cmd {"move_joint"};
//         Robot r;
//         cmd_map["move_joint"] = MoveJoint;

//         auto res = cmd_map.find("move_joint");
//         if (res != cmd_map.end())
//         {
//             std::cerr << "find the command" << std::endl;
//             res->second(this);
//             return 0;
//         }
//         else
//         {
//             std::cerr << "not found" << std::endl;
//             return -1;
//         }
//     }
// };


int main(int argc, char *argv[])
{
    std::string arg;
    for (int row{1}; row < argc; row++)
    {
        arg = argv[row];
        if (arg == "--help" || arg == "-h")
        {
            Help();
        }
        else if (arg == "--test-hashmap-1")
        {
            test_hashmap_1();
        }
        else if (arg == "--test-hashmap-cmd")
        {
            test_hashmap_cmd();
        }
        else if (arg == "--test-hashmap-class-cmd")
        {
            std::cerr << "未实现" << std::endl;
        }
        else
        {
            Help();
        }
    }

    return 0;
}