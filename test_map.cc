/**
 * @file test_map.cc
 * @author your name (you@domain.com)
 * @brief 测试std::map
 * @version 0.1
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

std::map<std::string, std::string> tmp_map = 
{
    {"one", "1"},
    {"hello", "world"},
    {"test", "测试"}
};

int main()
{
    for (auto &it : tmp_map)
    {
        std::cerr << "it.first: " << it.first << std::endl;
        std::cerr << "it.second: " << it.second << std::endl;
    }
    std::cerr << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    for (auto it = tmp_map.begin(); it != tmp_map.end(); it++)
    {
        if (it->first == "hello")
        {
            it = tmp_map.erase(it);
        }
    }

    for (auto &it : tmp_map)
    {
        std::cerr << "it.first: " << it.first << std::endl;
        std::cerr << "it.second: " << it.second << std::endl;
    }
    std::cerr << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    return 0;
}