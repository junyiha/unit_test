/**
 * @file test_nlohmann_json.cc
 * @author your name (you@domain.com)
 * @brief nlohmann::json 测试
 * @version 0.1
 * @date 2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include "json.hpp"

int main()
{
    nlohmann::json data;

    data["code"] = 0;
    data["area"];
    std::cerr << "str: " << data.dump() << std::endl;
    
    return 0;
}