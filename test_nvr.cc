/**
 * @file test_nvr.cc
 * @author your name (you@domain.com)
 * @brief 测试nvr
 * @version 0.1
 * @date 2023-10-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "NvrTool.hpp"

int main()
{
    NvrTool nvr;
    bool res = nvr.List();
    if (!res)
    {
        std::cerr << "failed to lsit" << std::endl;
    }
    else 
    {
        std::cerr << "succes" << std::endl;
    }

    return 0;
}