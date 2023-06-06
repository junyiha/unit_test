#include <iostream>
#include <fstream>
#include <sys/stat.h>

std::uintmax_t getFileSize(const std::string& filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) {
        // 获取文件信息失败
        return 0;
    }
    return st.st_size;
}

int main() {
    // std::string filename = "example.txt"; // 文件名
    std::string filename = "test.log"; // 文件名

    std::uintmax_t fileSize = getFileSize(filename);

    std::cout << "文件大小: " << fileSize << " 字节" << std::endl;

    return 0;
}
