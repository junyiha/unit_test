#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    int fd = STDIN_FILENO; // 标准输入设备文件描述符

    struct termios term;
    if (tcgetattr(fd, &term) == -1) {
        perror("tcgetattr");
        return 1;
    }

    // 打印终端设备的属性
    printf("Input flags: %x\n", term.c_iflag);
    printf("Output flags: %x\n", term.c_oflag);
    printf("Control flags: %x\n", term.c_cflag);
    printf("Local flags: %x\n", term.c_lflag);

    return 0;
}