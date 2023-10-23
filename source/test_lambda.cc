/**
 * @file test_lambda.cc
 * @author your name (you@domain.com)
 * @brief lambda unit test
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */

extern "C"
{
    #include <unistd.h>  // sleep()
}
#include <iostream>
#include <thread>

int main()
{
    std::string str{"hahahahah"};
    std::string str2{"aaaaa"};
    int x {999};
    auto lambda = [&](int in)
    {
        int index {0};
        while (true)
        {
            if (index > 10)
                break;
            std::cerr << "index: " << index << "\n"
                      << "hello world" << "\n"
                      << str << "\n"
                      << str2 << "\n"
                      << in << "\n"
                      << std::endl;
            sleep(1);
            index++;
        }
    };
    std::thread tmp;
    tmp = std::thread(lambda, x);
    // t.join();
    if (tmp.joinable())
    {
        tmp.join();
    }
    return 0;
}