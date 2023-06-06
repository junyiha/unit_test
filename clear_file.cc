#include <fstream>
#include <iostream>

int main() {
    std::string filename = "example.txt"; // 文件名

    // 创建输出文件流对象并打开文件
    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        // 清空文件内容
        outputFile.close();

        // 输出清空文件成功的消息
        std::cout << "文件已成功清空" << std::endl;
    } else {
        // 输出无法打开文件的消息
        std::cout << "无法打开文件" << std::endl;
    }

    return 0;
}
