/**
 * @file protocol.h
 * @author your name (you@domain.com)
 * @brief 对外统一的数据结构
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 
#ifndef AICONTRIB_ROBOT_PROTOCOL_H
#define AICONTRIB_ROBOT_PROTOCOL_H

#include <vector>
#include <mutex>

namespace aicontrib
{
    namespace Robot
    {
        using RobotCart_t = std::vector<double>;
        using RobotJoint_t = std::vector<double>;
        using RobotFlange_t = std::vector<double>;

        class RobotConfig
        {
        public:
            std::string ip;
            size_t port;
        
        public:
            RobotConfig()
            {
                ip = "0.0.0.0";
                port = 9999;
            }
            RobotConfig(const RobotConfig& other)
            {
                ip = other.ip;
                port = other.port;
            }
            ~RobotConfig()
            {
                ip.clear();
                port = 0;
            }

        public:
            RobotConfig& operator=(const RobotConfig& other)
            {
                if (this != &other)
                {
                    ip = other.ip;
                    port = other.port;
                }

                return *this;
            }
        };

        class RobotPlanning
        {
        public:
            bool f_stopping;
            std::size_t last_added_task_id;
            std::size_t last_ran_task_id;
            std::string operation_command;
            double speed_ratio;
            std::size_t step_count;
            double target_speed_ratio;
            std::size_t task_id;
            std::string task_type;

        public:
            RobotPlanning()
            {
                f_stopping = false;
                last_added_task_id = 0;
                last_ran_task_id = 0;
                operation_command = "";
                speed_ratio = 0;
                step_count = 0;
                target_speed_ratio = 0;
                task_id = 0;
                task_type = "";
            }
            RobotPlanning(const RobotPlanning& other)
            {
                f_stopping = other.f_stopping;
                last_added_task_id = other.last_added_task_id;
                last_ran_task_id = other.last_ran_task_id;
                operation_command = other.operation_command;
                speed_ratio = other.speed_ratio;
                step_count = other.step_count;
                target_speed_ratio = other.target_speed_ratio;
                task_id = other.task_id;
                task_type = other.task_type;
            }
            ~RobotPlanning()
            {
                f_stopping = false;
                last_added_task_id = 0;
                last_ran_task_id = 0;
                operation_command = "";
                speed_ratio = 0;
                step_count = 0;
                target_speed_ratio = 0;
                task_id = 0;
                task_type = "";
            }
        
        public:
            RobotPlanning& operator=(const RobotPlanning& other)
            {
                if (this != &other)
                {
                    f_stopping = other.f_stopping;
                    last_added_task_id = other.last_added_task_id;
                    last_ran_task_id = other.last_ran_task_id;
                    operation_command = other.operation_command;
                    speed_ratio = other.speed_ratio;
                    step_count = other.step_count;
                    target_speed_ratio = other.target_speed_ratio;
                    task_id = other.task_id;
                    task_type = other.task_type;
                }

                return *this;
            }
        };

        class RobotResult
        {
        public:
            std::string status;
            std::string message;

        public:
            RobotResult()
            {
                status = "";
                message = "";
            }
            RobotResult(const RobotResult& other)
            {
                status = other.status;
                message = other.message;
            }
            ~RobotResult()
            {
                status = "";
                message = "";
            }
        
        public:
            RobotResult& operator=(const RobotResult& other)
            {
                if (this != &other)
                {
                    status = other.status;
                    message = other.message;
                }

                return *this;
            }

            int IsOk()
            {
                if (status.empty())
                {
                    return -1;
                }

                if (status == "success")
                {
                    return 1;
                }
                else 
                {
                    return 0;
                }
            }
        };

        class RobotStatus
        {
        public:
            RobotCart_t cart;
            RobotJoint_t joint;
            RobotFlange_t flange;
            std::string mode;
            bool running;
            int64_t time;
            RobotPlanning robot_planning;
        
        public:
            RobotStatus()
            {
                cart.resize(6);
                joint.resize(6);
                flange.resize(6);
                mode = "";
                running = false;
                time = -1;
            }
            RobotStatus(const RobotStatus& other)
            {
                cart = other.cart;
                joint = other.joint;
                flange = other.flange;
                mode = other.mode;
                running = other.running;
                time = other.time;
                robot_planning = other.robot_planning;
            }
            ~RobotStatus()
            {
                cart.clear();
                joint.clear();
                flange.clear();
                mode = "";
                running = false;
                time = -1;
            }

        public:
            RobotStatus& operator=(const RobotStatus &other) 
            {
                if (this != &other) // 避免自我赋值
                {
                    cart = other.cart;
                    joint = other.joint;
                    flange = other.flange;
                    mode = other.mode;
                    running = other.running;
                    time = other.time;
                    robot_planning = other.robot_planning;
                }

                return *this;
            }
        };

        class RobotTool
        {
        public:
            int index;                          // 正整数,区分不同末端工具的唯一标识
            double mass;                        // 质量
            bool default_tool;                  // 是否为默认工具
            std::string name;                   // 名字
            std::vector<double> position;       // 偏移量 x,y,z,rx,ry,rz
            std::vector<double> center_of_mass; // 质心
            std::vector<double> inertia;        // 转动惯量 Ixx,Ixy,Ixz,Iyz,Iyy,Iyz,Izx,Izy,Izz
        
        public:
            RobotTool()
            {
                index = -1;
                mass = 0.0;
                default_tool = false;
                name = "";
                position.resize(0);
                center_of_mass.resize(0);
                inertia.resize(0);
            }
            RobotTool(const RobotTool& other)
            {
                index = other.index;
                mass = other.mass;
                default_tool = other.default_tool;
                name = other.name;
                position = other.position;
                center_of_mass = other.center_of_mass;
                inertia = other.inertia;
            }
            ~RobotTool()
            {
                index = -1;
                mass = 0.0;
                default_tool = false;
                name = "";
                position.clear();
                center_of_mass.clear();
                inertia.clear();
            }

        public:
            RobotTool& operator=(const RobotTool& other)
            {
                if (this != &other)
                {
                    index = other.index;
                    mass = other.mass;
                    default_tool = other.default_tool;
                    name = other.name;
                    position = other.position;
                    center_of_mass = other.center_of_mass;
                    inertia = other.inertia;
                }

                return *this;
            }
        };

        class RobotToolArray
        {
        public:
            std::vector<RobotTool> robot_tool_arr;
        
        public:
            void push_back(RobotTool in)
            {
                robot_tool_arr.push_back(in);
            }
        
        public:
            RobotToolArray()
            {
                robot_tool_arr.resize(0);
            }
            RobotToolArray(const RobotToolArray& other)
            {
                robot_tool_arr = other.robot_tool_arr;
            }
            ~RobotToolArray()
            {
                robot_tool_arr.clear();
            }
        
        public:
            RobotToolArray& operator=(const RobotToolArray& other)
            {
                if (this != &other)
                {
                    robot_tool_arr = other.robot_tool_arr;
                }

                return *this;
            }
        };

        class RobotCartVelocity
        {
        public:
            double trans_vel;       // 平移速度 m/s
            double trans_acc;       // 平移加速度
            double trans_jerk;      // 平移加速度的导数
            double rot_vel;         // 旋转速度 rad/s
            double rot_acc;         // 旋转加速度
            double rot_jerk;        // 旋转加速度的导数
        
        public:
            RobotCartVelocity()
            {
                trans_vel = 0.0;
                trans_acc = 0.0;
                trans_jerk = 0.0;
                rot_vel = 0.0;
                rot_acc = 0.0;
                rot_jerk = 0.0;
            }
            RobotCartVelocity(const RobotCartVelocity& other)
            {
                trans_vel = other.trans_vel;
                trans_acc = other.trans_acc;
                trans_jerk = other.trans_jerk;
                rot_vel = other.rot_vel;
                rot_acc = other.rot_acc;
                rot_jerk = other.rot_jerk;
            }
            ~RobotCartVelocity()
            {
                trans_vel = 0.0;
                trans_acc = 0.0;
                trans_jerk = 0.0;
                rot_vel = 0.0;
                rot_acc = 0.0;
                rot_jerk = 0.0;
            }
        
        public:
            RobotCartVelocity& operator=(const RobotCartVelocity& other)
            {
                if (this != &other)
                {
                    trans_vel = other.trans_vel;
                    trans_acc = other.trans_acc;
                    trans_jerk = other.trans_jerk;
                    rot_vel = other.rot_vel;
                    rot_acc = other.rot_acc;
                    rot_jerk = other.rot_jerk;
                }

                return *this;
            }
        };

        class RobotJointVelocity
        {
        public:
            std::vector<double> joint_vel;      // 关节1-6的速度
            std::vector<double> joint_acc;      // 关节1-6的加速度
            std::vector<double> joint_jerk;     // 关节1-6的加速度的导数
        
        public:
            RobotJointVelocity()
            {
                joint_vel.resize(6);
                joint_acc.resize(6);
                joint_jerk.resize(6);
            }
            RobotJointVelocity(const RobotJointVelocity& other)
            {
                joint_vel = other.joint_vel;
                joint_acc = other.joint_acc;
                joint_jerk = other.joint_jerk;
            }
            ~RobotJointVelocity()
            {
                joint_vel.clear();
                joint_acc.clear();
                joint_jerk.clear();
            }
        
        public:
            RobotJointVelocity& operator=(const RobotJointVelocity& other)
            {
                if (this != &other)
                {
                    joint_vel = other.joint_vel;
                    joint_acc = other.joint_acc;
                    joint_jerk = other.joint_jerk;
                }

                return *this;
            }
        };

        class RobotMove
        {
        public:
            std::string space;                      // 运动空间,值为: joint(关节空间) | cartBase(世界坐标系) | cartTcp(末端工具坐标系)
            double cart_velocity;                   // 笛卡尔空间下平移速度 (m/s) 
            double rot_velocity;                    // 笛卡尔空间下旋转速度 (rad/s)  
                                                    // 注:如果不确定运动的主分量是平移还是旋转,可同时设置cart_velocity和rot_velocity,以确保这两个速度限制均不被超过.
            double speed_percent;                   // 速度百分比,50 即 50%  
                                                    // 注: 使用cart_velocity/rot_velocity时,不能使用speedpercent.   
            std::vector<double> target_position;    // 在笛卡尔空间下为x,y,z,rx,ry,rz | 在关节空间下为J1,J2,J3,J4,J5,J6

        public:
            RobotMove()
            {
                space = "";  // cartTcp 相对末端坐标系移动 | cartBase 相对基底坐标系移动 | joint 相对关节空间移动
                cart_velocity = 0.0;
                rot_velocity = 0.0;
                speed_percent = 0.0;
                target_position.resize(6);
            }
            RobotMove(const RobotMove& other)
            {
                space = other.space;
                cart_velocity = other.cart_velocity;
                rot_velocity = other.rot_velocity;
                speed_percent = other.speed_percent;
                target_position = other.target_position;                
            }
            ~RobotMove()
            {
                space = "";
                cart_velocity = 0.0;
                rot_velocity = 0.0;
                speed_percent = 0.0;
                target_position.resize(6);
            }

        public:
            RobotMove& operator=(const RobotMove& other)
            {
                if (this != &other)
                {
                    space = other.space;
                    cart_velocity = other.cart_velocity;
                    rot_velocity = other.rot_velocity;
                    speed_percent = other.speed_percent;
                    target_position = other.target_position;                
                }

                return *this;
            }
        };

        class RobotTeachPoint
        {
        public:
            int index;                  // 正整数,示教点的唯一标识
            std::string point_name;     // 示教点的名字
            RobotJoint_t joint;         // 关节空间下的关节角,单位为弧度
            RobotCart_t cart;           // 笛卡尔空间下的位姿,位置单位为米,姿态为弧度,轴角形式
        
        public:
            RobotTeachPoint()
            {
                index = 0;
                point_name = "";
                joint.resize(6);
                cart.resize(6);
            }
            RobotTeachPoint(const RobotTeachPoint& other)
            {
                index = other.index;
                point_name = other.point_name;
                joint = other.joint;
                cart = other.cart;
            }
            ~RobotTeachPoint()
            {
                index = 0;
                point_name = "";
                joint.resize(6);
                cart.resize(6);
            }

        public:
            RobotTeachPoint& operator=(const RobotTeachPoint& other)
            {
                if (this != &other)
                {
                    index = other.index;
                    point_name = other.point_name;
                    joint = other.joint;
                    cart = other.cart;
                }

                return *this;
            }
        };

        class RobotToolCenter
        {
        public:
            double err;
            std::vector<double> tool_center_point;
        
        public:
            RobotToolCenter()
            {
                err = 0.0;
                tool_center_point.resize(3);
            }
            RobotToolCenter(const RobotToolCenter& other)
            {
                err = other.err;
                tool_center_point = other.tool_center_point;
            }
            ~RobotToolCenter()
            {
                err = 0.0;
                tool_center_point.resize(3);
            }
        
        public:
            RobotToolCenter& operator=(const RobotToolCenter& other)
            {
                if (this != &other)
                {
                    err = other.err;
                    tool_center_point = other.tool_center_point;
                }

                return *this;
            }
        };
    }  // namespace Robot
}  // namespace aicontrib

#endif  // AICONTRIB_ROBOT_PROTOCOL_H