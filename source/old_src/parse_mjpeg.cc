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

int CharToInt(std::vector<char> &in, std::size_t &out)
{
    std::string tmp_str {};
    for (auto &it : in)
    {
        tmp_str += static_cast<char>(it);
    }
    out = std::stoi(tmp_str);
    return 0;
}

int main()
{
    std::vector<char> raw_data(20);
    std::vector<char> thumb_data(20);
    std::vector<char> json_data(20);
    std::size_t raw_data_size {};
    std::size_t thumb_data_size {};
    std::size_t json_data_size {};

    std::string inputFile = "aaa-frame-1.jpg";
    std::string outputFile = "frame.jpg";
    std::string output_json_file = "frame_data.json";

    // 读取文件到内存
    std::vector<char> fileData = ReadFileToMemory(inputFile);
    if (fileData.empty()) {
        std::cerr << "Failed to read file: " << inputFile << std::endl;
        return -1;
    }
    for (int col {0}; col < 20; col++)
    {
        raw_data[col] = fileData[fileData.size() - 60 + col];
        thumb_data[col] = fileData[fileData.size() - 40 + col];
        json_data[col] = fileData[fileData.size() - 20 + col];
    }

    CharToInt(raw_data, raw_data_size);
    CharToInt(thumb_data, thumb_data_size);
    CharToInt(json_data, json_data_size);

    std::cerr << "raw picture data size: " << raw_data_size << std::endl;
    std::cerr << "thumb picture data size: " << thumb_data_size << std::endl;
    std::cerr << "json data size: " << json_data_size << std::endl;

    std::vector<char> raw_pic;
    std::vector<char> json_file;
    for (std::size_t col {0}; col < raw_data_size; col++)
    {
        raw_pic.push_back(fileData.at(col));
    }
    if (SaveMemoryToFile(raw_pic, outputFile))
    {
        std::cerr << "Success to save frame picture" << std::endl;
    }
    for (std::size_t col {raw_data_size + thumb_data_size}; col < fileData.size() - 60; col++)
    {
        json_file.push_back(fileData.at(col));
    }
    if (SaveMemoryToFile(json_file, output_json_file))
    {
        std::cerr << "Success to save json data to file" << std::endl;
    }

    return 0;
}