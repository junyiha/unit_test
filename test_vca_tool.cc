/**
 * @file test_vca_tool.cc
 * @author your name (you@domain.com)
 * @brief 测试VcaTool类
 * @version 0.1
 * @date 2023-06-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "VcaTool.hpp"
#include <unistd.h>

int main(int argv, char *argc[])
{
    int ret {VcaTool::RET_ERR};
    pid_t p;
    bool result {false};
    VcaTool vt;
    VcaTool::Command_t c;
    std::string cmd {};

    if (argv <= 1)
    {
        std::cerr << "command: start | kill | cmd" << std::endl;
        return -1;
    }

    cmd = argc[1];
    std::cerr << "cmd " << cmd << std::endl;

    if (cmd.compare("start") == 0)
    {
        result = vt.StartVcaTask(p);
        if (result)
            std::cerr << "Success to start a task on vca, and it's pid : " << p << std::endl;
    }
    else if (cmd.compare("kill") == 0)
    {
        result = vt.KillVcaTask();
        if (result)
            std::cerr << "Success to kill vca task" << std::endl;
    }
    else if (cmd.compare("cmd") == 0)
    {
        c.path = "/home/user/zjy-190/workspace/video_process/build/vca.exe";
        /**
         * @brief 
         * 
         * 2 : 启动
         * 3 : 暂停
         * 
         */
        // c.cmd = 2; 
        c.cmd = 3; 
        c.daemon_mode = true;
        c.detector_conf_inline = true;
        c.detector_conf = "@--detector-models@/data/models/PERSON/DETECT.conf@xxxx@yyyy@";
        c.service_mode = 0;
        c.id = "cxsLw";
        c.output_type = 5;
        c.input_video_name = "rtsp://admin:a1234567@192.169.7.123:554";
        
        ret = vt.SendCommand(c);
        if (ret == VcaTool::RET_OK)
        {
            std::cerr << "Success to send command" << std::endl;
        }
    }
    else 
    {
        std::cerr << "invalid input command: " << cmd << std::endl;
    }

    return 0;
}