#include <iostream>
#include <fstream>
#include <vector>

// 读取文件内容到内存
std::vector<char> ReadFileToMemory(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return {};
    }
    
    // 获取文件大小
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // 分配内存缓冲区
    std::vector<char> buffer(fileSize);
    
    // 读取文件内容到缓冲区
    if (!file.read(buffer.data(), fileSize)) {
        std::cerr << "Failed to read file: " << filename << std::endl;
        return {};
    }
    
    return buffer;
}

// 将内存内容保存为新文件
bool SaveMemoryToFile(const std::vector<char>& data, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    
    if (!file) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return false;
    }
    
    // 将内存内容写入文件
    if (!file.write(data.data(), data.size())) {
        std::cerr << "Failed to write file: " << filename << std::endl;
        return false;
    }
    
    return true;
}

int main() {
    std::string inputFile = "input_pic.jpg";
    std::string outputFile = "output_pic.jpg";
    
    // 读取文件到内存
    std::vector<char> fileData = ReadFileToMemory(inputFile);
    
    if (fileData.empty()) {
        std::cerr << "Failed to read file: " << inputFile << std::endl;
        return 1;
    }
    
    // 将内存内容保存为新文件
    if (!SaveMemoryToFile(fileData, outputFile)) {
        std::cerr << "Failed to save file: " << outputFile << std::endl;
        return 1;
    }
    
    std::cout << "File saved successfully: " << outputFile << std::endl;
    
    return 0;
}
