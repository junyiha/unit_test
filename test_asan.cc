/**
 * @file test_asan.cc
 * @author your name (you@domain.com)
 * @brief 测试asan 工具
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int* buffer = (int*)malloc(sizeof(int) * 10);
    buffer[10] = 42; // 内存越界访问

    free(buffer);
    return 0;
}
