#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>

struct SharedData 
{
    int value;
    char message[256];
};

int main() 
{
    key_t key = ftok("/tmp/memfile", 1);
    int shmId = shmget(key, sizeof(SharedData), IPC_CREAT | 0666);
    SharedData* sharedData = static_cast<SharedData*>(shmat(shmId, nullptr, 0));
    
    // 写入共享内存数据
    sharedData->value = 42;
    std::strcpy(sharedData->message, "Hello, shared memory!");
    std::cerr << "shmid: " << shmId << std::endl;
    std::cerr << "size of SharedData: " << sizeof(SharedData) << std::endl;
    sleep(10);
    
    // 从共享内存中读取数据
    std::cout << "Value: " << sharedData->value << std::endl;
    std::cout << "Message: " << sharedData->message << std::endl;
    
    shmdt(sharedData);
    shmctl(shmId, IPC_RMID, nullptr);
    
    return 0;
}
