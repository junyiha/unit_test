/**
 * @file test_file.cc
 * @author your name (you@domain.com)
 * @brief 文件相关的单元测试
 * @version 0.1
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <fstream>

bool fileExists(const std::string& filename) {
    std::ifstream file;

    file.open(filename);
    return file.good();
}

int main() {
    std::string filename = "/dev/shm/9afU4-producer.idx";
    if (fileExists(filename)) {
        std::cout << "File exists." << std::endl;
    } else {
        std::cout << "File does not exist." << std::endl;
    }

    return 0;
}
