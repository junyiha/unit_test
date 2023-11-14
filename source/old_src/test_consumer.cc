#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <iostream>

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

int WriteConsumerIdx(int shm_fd, std::size_t in)
{
    int ret {-1};
    std::vector<char> num_data(20, ' ');
    std::string num_string {};

    num_string = std::to_string(in);
    for (int col {0}; col < num_string.size(); col++)
    {
        num_data[col] = num_string[col];
    }

    ret = write(shm_fd, num_data.data(), num_data.size());
    if (ret == -1 || ret == 0)
    {
        std::cerr << "Failed to write data to shared memory file" << std::endl;
        return -1;
    }

    return 0;
}

int ReadConsumerIdx(int shm_fd, std::size_t &out)
{
    int ret {-1};
    std::string num_string;
    std::vector<char> consumer_data(20);

    ret = lseek(shm_fd, 0, SEEK_SET);
    if (ret == -1)
    {
        std::cerr << "Reset file director pointer to file begin" << std::endl;
        return -1;
    }

    ret = read(shm_fd, consumer_data.data(), consumer_data.size());
    if (ret == -1 || ret == 0)
    {
        std::cerr << "Failed to read data or empty data from consumer file" << std::endl;
        return -1;
    }
    

    for (auto &it : consumer_data)
    {
        num_string += it;
    }
    out = std::stoi(num_string);

    return 0;
}

int main()
{
    int ret {-1};
    int shm_fd {-1};
    std::size_t file_size {20};
    std::vector<char> pic_data;
    std::string mjpeg_file {"aaa-frame-1.jpg"};
    std::string consumer_file {"aaa-consumer.idx"};

    shm_fd = shm_open(consumer_file.c_str(), O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        std::cerr << "Failed to create shared memory file" << std::endl;
        return -1;
    }
    std::size_t idx {};
    std::cerr << "input consumer index: " << std::endl;
    std::cin >> idx;
    ret = WriteConsumerIdx(shm_fd, idx);
    if (ret == 0)
    {
        std::cerr << "Success to write index : " << idx << " to consumer index file" << std::endl;
    }

    ret = ReadConsumerIdx(shm_fd, idx);
    if (ret == 0)
    {
        std::cerr << "Success to read data from consumer file, consumer index: " << idx << std::endl;
    }

    close(shm_fd);

    return 0;
}