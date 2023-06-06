#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main() 
{
    key_t key = ftok("path/to/my/directory/share_memory", 1);
    key_t key2 = ftok("path/to/my/directory/share_memory", 1);
    
    if (key == -1) {
        perror("ftok");
        return 1;
    }
    if (key2 == -1) {
        perror("ftok");
        return 1;
    }

    printf("Generated key: %d\n", key);
    printf("Generated key: %d\n", key2);
    
    return 0;
}