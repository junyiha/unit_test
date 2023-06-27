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

static void Help()
{
    std::string help_info =
    {
        R"(
            -h, --help  打印帮助信息
            --list-task  查看任务列表
            --start-task  启动任务
            --check-licence 查看授权信息
            --update-licence 更新授权码
        )"
    };
    std::cerr << help_info << std::endl;
}

int old_version(int argv, char *argc[])
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

int main(int argc, char *argv[])
{
    VcaTool vca_tool;
    std::string arg {};
    int ret {VcaTool::RET_ERR};
    for (int col {1}; col < argc; ++col)
    {
        arg = argv[col];
        if (arg == "-h" || arg == "--help")
        {
            Help();
            return 0;
        }
        else if (arg == "--list-task")
        {
            VcaTool::ReplyListTask_t vca_list_task;
            ret = vca_tool.ListTask(vca_list_task);
            if (ret == VcaTool::RET_OK)
            {
                std::cerr << "Success to list task" << std::endl;
                for (auto &it : vca_list_task.id_arr)
                {
                    std::cerr << "id: " << it << std::endl;
                }
            }
        }
        else if (arg == "--start-task")
        {
            VcaTool::ReplyStartTask_t reply_start_task;
            VcaTool::StartTaskParam_t in;
            in.detector_conf = "@--detector-models@/data/models/PERSON/DETECT.conf@xxxx@yyyy@";
            in.input_video_name = "rtsp://192.169.4.16/test_fire_smoke.mp4";
            in.output_type = 5;
            in.id = "aaa";
            ret = vca_tool.StartTask(in, reply_start_task);
            if (ret == VcaTool::RET_OK && reply_start_task.vca_errno == 0)
            {
                std::cerr << "Success to list task" << std::endl;
            }
        }
        else if (arg == "--check-licence")
        {
            VcaTool::ReplyLicenceInfo_t reply_licence_info;
            ret = vca_tool.LicenceInfo(reply_licence_info);
            if (ret == VcaTool::RET_OK && reply_licence_info.vca_common.vca_errno == 0)
            {
                std::cerr << "Success to list licence" << std::endl;
                std::cerr << "duration: " << reply_licence_info.duration << std::endl;
                std::cerr << "nodes: " << reply_licence_info.nodes << std::endl;
                std::cerr << "type: " << reply_licence_info.type << std::endl;
            }
        }
        else if (arg == "--update-licence")
        {
            VcaTool::ReplyUpdateLicence_t reply_update_licence;
            std::string licence {"HFWYU4MP-NEW6GQLD-HFWYU4MK-PFWYU4MK-6PWQUJEB-MDWWU4MK-PFXUSS53-7F8WU4QK-PFWYU4MK-PFXZ24K6-2FXYUMGK"};
            ret = vca_tool.UpdateLicence(licence, reply_update_licence);
            if (ret == VcaTool::RET_OK && reply_update_licence.vca_errno == 0)
            {
                std::cerr << "Success to update licence" << std::endl;
            }
        }
        else if (arg == "--stop-task")
        {
            VcaTool::ReplyStopTask_t reply_stop_task;
            ret = vca_tool.StopTask("aaa", reply_stop_task);
            if (ret == VcaTool::RET_OK && reply_stop_task.vca_errno == 0)
            {
                std::cerr << "Success to stop task: " << "aaa" << std::endl;
            }
        }
        else if (arg == "--delete-task")
        {
            VcaTool::ReplyDeleteTask_t reply_delete_task;
            ret = vca_tool.DeleteTask("aaa", reply_delete_task);
            if (ret == VcaTool::RET_OK && reply_delete_task.vca_errno == 0)
            {
                std::cerr << "Success to delete task: aaa" << std::endl;
            }
        }
        else if (arg == "--status-task")
        {
            VcaTool::ReplyStatusTask_t reply_status_task;
            ret = vca_tool.StatusTask("aaa", reply_status_task);
            if (ret == VcaTool::RET_OK && reply_status_task.vca_common.vca_errno == 0)
            {
                std::cerr << "Success to status task: aaa" << std::endl;
                for (auto &detector : reply_status_task.detector_arr)
                {
                    std::cerr << detector.detector_id << std::endl;
                    std::cerr << detector.status_string << std::endl;
                }
            }
        }
        else if (arg == "--device-info")
        {
            VcaTool::ReplyDeviceInfo_t reply_device_info;
            ret = vca_tool.DeviceInfo(reply_device_info);
            if (ret == VcaTool::RET_OK && reply_device_info.vca_common.vca_errno == 0)
            {
                std::cerr << "Success to query device information" << std::endl;
                std::cerr << "product: " << reply_device_info.product << std::endl;
                std::cerr << "socket: " << reply_device_info.socket << std::endl;
                std::cerr << "vendor: " << reply_device_info.vendor << std::endl;
            }
        }
        else if (arg == "--get-machince-code")
        {
            VcaTool::ReplyGetMachineCode reply_get_machine_code;
            ret = vca_tool.GetMachineCode(reply_get_machine_code);
            if (ret == VcaTool::RET_OK && reply_get_machine_code.vca_common.vca_errno == 0)
            {
                std::cerr << "Success to get machine code" << std::endl;
                std::cerr << "Machine code: " << reply_get_machine_code.machine_code << std::endl;
            }
        }
        else if (arg == "--list-slave")
        {
            VcaTool::ReplyListSlave_t reply_list_slave;
            ret = vca_tool.ListSlave(reply_list_slave);
            if (ret == VcaTool::RET_OK && reply_list_slave.vca_common.vca_errno == 0)
            {
                std::cerr << "Success to list slaves" << std::endl;
                for (auto &node : reply_list_slave.node_arr)
                {
                    std::cerr << "id: " << node.id << std::endl;
                    std::cerr << "granted: " << node.granted << std::endl;
                    std::cerr << "ctime: " << node.ctime << std::endl;
                    std::cerr << "atime: " << node.atime << std::endl;
                    std::cerr << "remote_addr: " << node.remote_addr << std::endl;
                }
            }
        }
        else if (arg == "--yolov5-fire")
        {
            VcaTool::ReplyStartTask_t reply_start_task;
            VcaTool::StartTaskParam_t in;
            in.detector_conf = "@--detector-models@/workspace/fastApiProject/static/models/FIRE/DETECT.conf@xxx@yyy@";
            in.input_video_name = "/workspace/video2/fire.mp4";
            in.output_type = 0;
            in.id = "aaa";
            ret = vca_tool.StartTask(in, reply_start_task);
            if (ret == VcaTool::RET_OK && reply_start_task.vca_errno == 0)
            {
                std::cerr << "Success to list task" << std::endl;
            }
        }
    }
}