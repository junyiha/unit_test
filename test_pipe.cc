#include <iostream>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        std::cerr << "Failed to create pipe" << std::endl;
        return 1;
    }

    int writeEnd = pipefd[1]; // 写入端
    const char* data = "Hello, pipe!";

    ssize_t bytesWritten = write(writeEnd, data, strlen(data));
    if (bytesWritten == -1) {
        std::cerr << "Failed to write to pipe" << std::endl;
        return 1;
    }

    close(pipefd[0]);  // 关闭读取端
    close(pipefd[1]);  // 关闭写入端

    std::cout << "Data written to pipe" << std::endl;

    return 0;
}
