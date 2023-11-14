#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
    const char* shm_name = "/my_shared_memory";
    const int shm_size = 4096;

    // 创建共享内存对象
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to create shared memory" << std::endl;
        return 1;
    }

    // 调整共享内存对象的大小
    if (ftruncate(shm_fd, shm_size) == -1) {
        std::cerr << "Failed to resize shared memory" << std::endl;
        shm_unlink(shm_name); // 删除共享内存对象
        return 1;
    }

    // 将共享内存对象映射到进程的地址空间
    void* shm_ptr = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        std::cerr << "Failed to map shared memory" << std::endl;
        shm_unlink(shm_name); // 删除共享内存对象
        return 1;
    }

    // 写入数据到共享内存
    std::size_t cnt {0};
    std::size_t size {0};
    std::string message;
    while (true)
    {
        if (cnt > 10)
            break;
        message = "cnt: " + std::to_string(cnt);
        message += " Hello, shared memory!";
        std::memcpy(shm_ptr, message.c_str(), message.size() + 1);
        sleep(1);    
        cnt++;
    }

    // 从共享内存中读取数据并输出
    std::cout << "Shared memory content: " << static_cast<char*>(shm_ptr) << std::endl;

    // 解除映射
    if (munmap(shm_ptr, shm_size) == -1) {
        std::cerr << "Failed to unmap shared memory" << std::endl;
    }

    // 关闭共享内存对象
    close(shm_fd);

    // 删除共享内存对象
    if (shm_unlink(shm_name) == -1) {
        std::cerr << "Failed to unlink shared memory" << std::endl;
    }

    return 0;
}
