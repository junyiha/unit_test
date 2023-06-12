#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

pid_t findProcessIdByName(const char* processName) 
{
    char command[256];
    sprintf(command, "pgrep -f %s", processName);
    FILE* fp = popen(command, "r");
    if (fp != nullptr) {
        char buffer[16];
        if (fgets(buffer, sizeof(buffer), fp)) {
            pclose(fp);
            return atoi(buffer);
        }
        pclose(fp);
    }
    return -1;
}

int main () 
{
    std::string program_name {"/home/user/zjy-190/workspace/video_process/build/vca.exe"};

    pid_t p; 
    p = findProcessIdByName(program_name.c_str());
    std::cerr << "Program : " << program_name << ", pid: " << p << std::endl;

    return 0;
}
