#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main()
{
    std::string shm_name {"/my_shared_memory"};
    std::size_t shm_size = 4096;

    int shm_fd = shm_open(shm_name.c_str(), O_RDWR, 0666);
    if (shm_fd == -1)
    {
        std::cerr << "Failed to create shared memory" << std::endl;
        return -1;
    }

    void *shm_ptr = mmap(nullptr, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        std::cerr << "Failed to map shared memory" << std::endl;
        shm_unlink(shm_name.c_str());
        return -1;
    }

    std::cerr << "size of shared memory : " << sizeof(*(reinterpret_cast<char*>(shm_ptr))) << std::endl;
    std::cerr << "data of shared memory : " << static_cast<char *>(shm_ptr) << std::endl;

    if (munmap(shm_ptr, shm_size) == -1)
        std::cerr << "Failed to unmap shared memory" << std::endl;

    close(shm_fd);

    // if (shm_unlink(shm_name.c_str()) == -1)
    //     std::cerr << "Failed to unlink shared memory" << std::endl;

    return 0;
}