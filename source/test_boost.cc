/**
 * @file test_boost.cc
 * @author your name (you@domain.com)
 * @brief boost 单元测试
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include <iostream>
#include "boost/shared_ptr.hpp"

int main()
{
    boost::shared_ptr<int> shared_int(new int(42));

    std::clog << "Shared pointer value: " << *shared_int << std::endl;
    std::clog << "Reference count: " << shared_int.use_count() << std::endl;

    // shared_int 在离开作用域时会自动释放内存
    return 0;
}