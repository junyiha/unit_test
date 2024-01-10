/**
 * @file TaskParser.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once 

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <random>

#include "old_src/json.hpp"  // nlohmann/json

//////////////////////////////////////////////////////////////////////////////////////

enum class TaskKeyWord : unsigned int
{
    INVALID = 1,
    START,
    STOP,
    MOVE_LINE,
    MOVE_JOINT,
    CATCH,
    RELEASE,
    PAUSE,
    SLEEP,
    ERROR_NUM,
    TIMER,
    COUNTER,
    WHILE,
    IF
};

extern std::map<std::string, TaskKeyWord> TaskKeyWordMap;

struct TaskArgument_t 
{
    std::string id;
    double speed_percent;
    double cart_vel;
    double rot_vel;
    std::vector<double> target;
    int sleep;
    size_t counter;
    size_t condition_value;
    std::string condition_operator;
};

struct TaskVariant_t
{
    size_t m_counter {0};
    int m_error_number {0};
    std::chrono::steady_clock::time_point m_timer;
    TaskKeyWord key_word;
    TaskKeyWord condition_key_word;
    TaskArgument_t argument;
    std::vector<TaskVariant_t> task_variant_arr;
    std::vector<TaskVariant_t> true_variant_arr;
    std::vector<TaskVariant_t> false_variant_arr;

    std::map<TaskKeyWord, std::function<int(TaskVariant_t)>> TaskKeyWordOperatorMap;
};

extern std::map<TaskKeyWord, std::function<int(TaskVariant_t)>> TaskKeyWordOperatorMap;

//////////////////////////////////////////////////////////////////////////////////////

// declare there, define other
int operator_move_joint(TaskVariant_t task_variant);
int operator_move_line(TaskVariant_t task_variant);
int operator_catch(TaskVariant_t task_variant);
int operator_release(TaskVariant_t task_variant);
int operator_sleep(TaskVariant_t task_variant);
int operator_while(TaskVariant_t task_variant);
int operator_if(TaskVariant_t task_variant);

//////////////////////////////////////////////////////////////////////////////////////

class TaskParser 
{
private:
    size_t m_counter{0};
    int m_error_number{0};
    std::chrono::steady_clock::time_point m_timer;
    std::vector<TaskVariant_t> m_task_variant_arr;
    std::map<std::string, TaskVariant_t> m_task_map;

public:
    std::map<std::string, TaskKeyWord> TaskKeyWordMap = {
        {"start", TaskKeyWord::START},
        {"stop", TaskKeyWord::STOP},
        {"move_line", TaskKeyWord::MOVE_LINE},
        {"move_joint", TaskKeyWord::MOVE_JOINT},
        {"catch", TaskKeyWord::CATCH},
        {"release", TaskKeyWord::RELEASE},
        {"pause", TaskKeyWord::PAUSE},
        {"sleep", TaskKeyWord::SLEEP},
        {"error_num", TaskKeyWord::ERROR_NUM},
        {"timer", TaskKeyWord::TIMER},
        {"counter", TaskKeyWord::COUNTER},
        {"while", TaskKeyWord::WHILE},
        {"if", TaskKeyWord::IF}
    };

    std::map<TaskKeyWord, std::function<int(TaskVariant_t)>> TaskKeyWordOperatorMap = 
    {
        {TaskKeyWord::MOVE_JOINT, operator_move_joint},
        {TaskKeyWord::MOVE_LINE, operator_move_line},
        {TaskKeyWord::CATCH, operator_catch},
        {TaskKeyWord::RELEASE, operator_release},
        {TaskKeyWord::SLEEP, operator_sleep},
        {TaskKeyWord::WHILE, operator_while},
        {TaskKeyWord::IF, operator_if}
    };

public:
    TaskParser()
    {

    }
    ~TaskParser()
    {

    }

public:
    int ParseFromFile(std::string task_file, std::string& task_id)
    {
        nlohmann::json parse_data;
        std::ifstream file(task_file, std::ios::in);

        if (!file.is_open())
        {
            std::cerr << "invalid task file : " << task_file << "\n";
            return 0;
        }
        try 
        {
            file >> parse_data;
            file.close();
        }
        catch (nlohmann::json::parse_error& e)
        {
            std::cerr << "parse error, config file path: " << task_file << "\n";
            file.close();
            return 0;
        }
        catch (nlohmann::json::type_error& e)
        {
            std::cerr << "type error, config file path: " << task_file << "\n";
            file.close();
            return 0;
        }

        // 检查start和stop
        nlohmann::json task_data = parse_data["task_id"];

        auto first_data = task_data.front();
        auto last_data = task_data.back();
        if (first_data["key_word"] != "start" || last_data["key_word"] != "stop")
        {
            std::cerr << "invalid task\n";
            return 0;
        }

        TaskVariant_t task_variant;
        for (auto& item : task_data)
        {
            TaskVariant_t sub_task_variant;
            ParseTask(item, sub_task_variant);
            sub_task_variant.TaskKeyWordOperatorMap = TaskKeyWordOperatorMap;
            task_variant.task_variant_arr.push_back(sub_task_variant);
            std::cerr << "key word: " << item["key_word"] << "\n"
                      << "id: " << sub_task_variant.argument.id << "\n";
        }
        task_variant.TaskKeyWordOperatorMap = TaskKeyWordOperatorMap;
        task_id = generate_id();
        m_task_map[task_id] = task_variant;

        return 1;
    }

    int Execute(std::string task_id)
    {
        auto it = m_task_map.find(task_id);
        if (it == m_task_map.end())
        {
            std::cerr << "invalid task id: " << task_id << "\n";
            return 0;
        }

        for (auto& it : it->second.task_variant_arr)
        {
            auto tmp_it = it.TaskKeyWordOperatorMap.find(it.key_word);
            if (tmp_it == it.TaskKeyWordOperatorMap.end())
            {
                continue;
            }
            int res = tmp_it->second(it);
            if (res != 1)
            {
                std::cerr << "fail\n";
                continue;
            }
            std::cerr << "success\n";
        }

        return 1;
    }

private:
    void ParseCondition(const nlohmann::json item_data, TaskVariant_t& out)
    {
        switch (TaskKeyWordMap[item_data["condition_key_word"]])
        {
            case TaskKeyWord::COUNTER:
            {
                out.condition_key_word = TaskKeyWord::COUNTER;
                out.argument.condition_operator = item_data["condition_operator"];
                out.argument.condition_value = std::stoi(std::string(item_data["condition_value"]));
                break;
            }
            case TaskKeyWord::TIMER:
            {

                break;
            }
            case TaskKeyWord::ERROR_NUM:
            {

                break;
            }
            default:
            {

            }
        }
    }

    void ParseTask(const nlohmann::json task_data, TaskVariant_t& out)
    {
        switch (TaskKeyWordMap[task_data["key_word"]])
        {
            case TaskKeyWord::MOVE_LINE:
            {
                out.key_word = TaskKeyWord::MOVE_LINE;
                out.argument.id = task_data["argument_id"];
                out.argument.cart_vel = task_data["argument_cart_vel"];
                out.argument.rot_vel = task_data["argument_rot_vel"];
                out.argument.target = task_data["argument_target"].get<std::vector<double>>();

                break;
            }
            case TaskKeyWord::MOVE_JOINT:
            {
                out.key_word = TaskKeyWord::MOVE_JOINT;
                out.argument.id = task_data["argument_id"];
                out.argument.speed_percent = task_data["argument_speedpercent"];
                out.argument.target = task_data["argument_target"].get<std::vector<double>>();

                break;
            }
            case TaskKeyWord::CATCH:
            {
                out.key_word = TaskKeyWord::CATCH;
                out.argument.id = task_data["argument_id"];

                break;
            }
            case TaskKeyWord::RELEASE:
            {
                out.key_word = TaskKeyWord::RELEASE;
                out.argument.id = task_data["argument_id"];

                break;
            }
            case TaskKeyWord::PAUSE:
            {
                out.key_word = TaskKeyWord::PAUSE;
                out.argument.id = task_data["argument_id"];

                break;
            }
            case TaskKeyWord::SLEEP:
            {
                out.key_word = TaskKeyWord::SLEEP;
                out.argument.sleep = task_data["argument_sleep"];

                break;
            }
            case TaskKeyWord::ERROR_NUM:
            {
                out.key_word = TaskKeyWord::ERROR_NUM;
                out.argument.id = " ";

                break;
            }
            case TaskKeyWord::TIMER:
            {
                out.key_word = TaskKeyWord::TIMER;
                out.argument.id = " ";

                break;
            }
            case TaskKeyWord::COUNTER:
            {
                out.key_word = TaskKeyWord::COUNTER;
                out.argument.id = " ";

                break;
            }
            case TaskKeyWord::WHILE:
            {
                out.key_word = TaskKeyWord::WHILE;
                out.argument.id = " ";
                ParseCondition(task_data, out);
                for (auto& sub_data : task_data["process"])
                {
                    TaskVariant_t sub_task_variant;
                    ParseTask(sub_data, sub_task_variant);
                    out.task_variant_arr.push_back(sub_task_variant);
                }

                break;
            }
            case TaskKeyWord::IF:
            {
                out.key_word = TaskKeyWord::IF;
                out.argument.id = " ";
                ParseCondition(task_data, out);
                for (auto& sub_data : task_data["true_process"])
                {
                    TaskVariant_t sub_task_variant;
                    ParseTask(sub_data, sub_task_variant);
                    out.true_variant_arr.push_back(sub_task_variant);
                }
                for (auto& sub_data : task_data["false_process"])
                {
                    TaskVariant_t sub_task_variant;
                    ParseTask(sub_data, sub_task_variant);
                    out.false_variant_arr.push_back(sub_task_variant);
                }

                break;
            }
            default:
            {
                std::cerr << "invalid key word: " << task_data["key_word"] << "\n";
                out.key_word = TaskKeyWord::INVALID;
                out.argument.id = " ";
                break;
            }
        }
    }

    std::string generate_id()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> ds(1, 9);

        std::string random_id;
        for (int i = 1; i < 10; i++)
        {
            int random_num = ds(gen);
            random_id = random_id + std::to_string(random_num);
        }

        return random_id;
    }
};

//////////////////////////////////////////////////////////////////////////////////////