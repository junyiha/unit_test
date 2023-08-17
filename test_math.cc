/**
 * @file test_math.cc
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */

extern "C"
{
    #include <stdio.h>
    #include <math.h>
}

#include <string>
#include <iostream>

void Help()
{
    std::string help_info {R"(
        help information

        --test-ceil
    )"};

    std::cerr << help_info << std::endl;
}

int test_ceil()
{
    double num = 12.34;
    double result = ceil(num);

    printf("Original Number: %.2f\n", num);
    printf("Ceil Value: %.2f\n", result);

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg;
    for (int col{1}; col < argc; col++)
    {
        arg = argv[col];
        if (arg == "--test-ceil")
        {
            test_ceil();
        }
        else
        {
            Help();
        }
    }
}