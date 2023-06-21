#include <iostream>
#include <string>

// 从路径中提取文件名
std::string extractFilename(const std::string& path) {
    size_t lastSlash = path.find_last_of('/');
    if (lastSlash != std::string::npos) {
        return path.substr(lastSlash + 1);
    }
    return path;
}

// 从路径中提取路径部分
std::string extractPath(const std::string& path) {
    size_t lastSlash = path.find_last_of('/');
    if (lastSlash != std::string::npos) {
        return path.substr(0, lastSlash);
    }
    return "";
}

// 从路径中提取文件名
void ExtractFileName(std::string in, std::string &out)
{
    std::size_t last_slash = in.find_last_of('/');
    if (last_slash != std::string::npos)
    {
        out = in.substr(last_slash + 1);
        return;
    }

    out = in;
}

// 从路径中提取路径部分
void ExtractPath(std::string in, std::string &out)
{
    std::size_t last_slash = in.find_last_of('/');
    if (last_slash != std::string::npos)
    {
        out = in.substr(0, last_slash);
        return;
    }

    out.clear();
}

int main() {
    std::string filePath = "/home/user/Documents/example.txt";

    // 提取文件名
    std::string filename {};
    ExtractFileName(filePath, filename);
    std::cout << "文件名: " << filename << std::endl;

    // 提取路径
    std::string path {};
    ExtractPath(filePath, path);
    std::cout << "路径: " << path << std::endl;

    return 0;
}
