#include <unistd.h>
#include <signal.h>
#include <iostream>

int main() {
    pid_t pid = 13509;  // 要杀死的进程的PID

    // 发送SIGKILL信号来终止指定的进程
    if (kill(pid, SIGKILL) == 0) {
        std::cout << "进程已成功终止" << std::endl;
    } else {
        std::cerr << "无法终止进程" << std::endl;
    }

    return 0;
}
