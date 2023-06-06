#include <iostream>
#include <sys/stat.h>

bool createDirectory(const std::string& path) 
{
    // 检查路径是否存在
    struct stat info;
    if (stat(path.c_str(), &info) != 0) 
    {
        // 路径不存在，创建目录
        if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0) 
        {
            std::cout << "Created directory: " << path << std::endl;
            return true;
        } 
        else 
        {
            std::cerr << "Failed to create directory: " << path << std::endl;
            return false;
        }
    } 
    else if (info.st_mode & S_IFDIR) 
    {
        // 路径已存在且为目录
        std::cout << "Directory already exists: " << path << std::endl;
        return true;
    } 
    else 
    {
        // 路径已存在但不是目录
        std::cerr << "Path already exists but not a directory: " << path << std::endl;
        return false;
    }
}

bool createDirectoriesRecursive(const std::string& path) 
{
    size_t pos = 0;
    std::string subPath;
    
    while ((pos = path.find_first_of("/\\", pos + 1)) != std::string::npos) 
    {
        subPath = path.substr(0, pos);
        if (!createDirectory(subPath)) 
        {
            return false;
        }
    }
    
    return createDirectory(path);
}

int main() {
    std::string path = "path/to/my/directory";
    if (createDirectoriesRecursive(path)) 
    {
        std::cout << "All directories created successfully!" << std::endl;
    } 
    else 
    {
        std::cerr << "Failed to create directories." << std::endl;
    }
    
    return 0;
}
