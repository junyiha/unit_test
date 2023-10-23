#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>

struct SharedData 
{
    int value;
    char message[256];
};

int read_v1()
{
    struct shmid_ds shm_info;
    int shm_id {};

    std::cerr << "input shm_id value: " << std::endl;
    std::cin >> shm_id;


    int result = shmctl(shm_id, IPC_STAT, &shm_info);
    if (result == -1)
    {
        std::cerr << "Failed in shmctl function" << std::endl;
        return -1;
    }

    std::cerr << "size of shared memory segment: " << shm_info.shm_segsz << std::endl;
    std::cerr << "owner's user ID: " << shm_info.shm_perm.uid << std::endl;
    std::cerr << "Last attach time: " << shm_info.shm_atime << std::endl;


    return 0;
}

int read_v2()
{
    key_t key = ftok("/tmp/memfile", 1);
    int shm_id = shmget(key, sizeof(SharedData), IPC_EXCL | 0666);
    struct shmid_ds shm_info;

    int result = shmctl(shm_id, IPC_STAT, &shm_info);
    if (result == -1)
    {
        std::cerr << "Failed in shmctl function" << std::endl;
        return -1;
    }

    std::cerr << "size of shared memory segment: " << shm_info.shm_segsz << std::endl;
    std::cerr << "owner's user ID: " << shm_info.shm_perm.uid << std::endl;
    std::cerr << "Last attach time: " << shm_info.shm_atime << std::endl;

    SharedData *shared_data = static_cast<SharedData*>(shmat(shm_id, nullptr, 0));

    std::cerr << "Value: " << shared_data->value << std::endl;
    std::cerr << "Message: " << shared_data->message << std::endl;

    shmdt(shared_data);

    return 0;
}

int main()
{
    read_v2();
}