#include <stdio.h>

int main() {
    const char *filename = "/dev/shm/aaa-consumer.idx";

    if (remove(filename) == 0) {
        printf("文件删除成功\n");
    } else {
        printf("文件删除失败\n");
    }

    return 0;
}
