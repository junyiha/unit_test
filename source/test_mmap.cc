#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <vector>

int main() {
    const char* filename = "example.txt";
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1) {
        std::cerr << "Failed to get file size" << std::endl;
        close(fd);
        return 1;
    }

    off_t file_size = file_stat.st_size;

    void* addr = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        std::cerr << "Failed to map file to memory" << std::endl;
        close(fd);
        return 1;
    }

    // 在 addr 指向的内存区域中可以直接访问文件的内容
    std::vector<char> str(file_size);
    std::strcpy(str.data(),static_cast<const char *>(addr));
    std::cerr << "str: " << str.data() << std::endl;

    munmap(addr, file_size);
    close(fd);

    std::cout << "File mapped to memory successfully" << std::endl;

    return 0;
}