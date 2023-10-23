/**
 * @file test_nlohmann_json.cc
 * @author your name (you@domain.com)
 * @brief nlohmann::json 测试
 * @version 0.1
 * @date 2023-06-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <fstream>
#include "json.hpp"

void Help()
{
    std::string help_info {R"(
        test_nlohmann_json.exe  测试json工具：nlohmann

        -h, --help  输出帮助信息
        -o, --old-version  使用第一版单元测试
    )"};

    std::cerr << help_info << std::endl;
}

int old_version()
{
    nlohmann::json data;

    data["code"] = 0;
    data["area"];
    std::cerr << "str: " << data.dump() << std::endl;

    return 0;
}

int parse_file()
{
    nlohmann::json parsed_data;
    std::string kms_file {"/userdata/static/json/kms.json"};

    std::ifstream file;
    file.open(kms_file);
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file: " << kms_file << std::endl;
        return -1;
    }

    file >> parsed_data;
    std::string licence {};
    try
    {
        licence = parsed_data["licence"];
    }
    catch (nlohmann::json::type_error &e)
    {
        std::cerr << "json type error, error information: " << e.what() << std::endl;
        return -1;
    }

    std::cerr << "licence : " << licence << std::endl;

    return 0;
}

int test_array()
{
    nlohmann::json reply_data;
    nlohmann::json arr_data;

    for (int col {0}; col < 7; ++col)
    {
        reply_data.push_back(col);
        // reply_data[std::to_string(col)] = col;
    }

    std::cerr << reply_data.dump() << std::endl;


    std::cerr << "+++++++++++++++++++++++++++" << std::endl;
    arr_data["list"] = reply_data;
    std::cerr << arr_data.dump() << std::endl;

    return 0;
}

int test_array_2()
{
    nlohmann::json reply_data;

    double joint_value[6] = {0, 1, 2, 3, 4, 5};

    nlohmann::json arr_data(joint_value);

    reply_data["array"] = arr_data;

    reply_data["arr"] = nlohmann::json(joint_value);

    std::cerr << reply_data.dump() << std::endl;
}

int main(int argc, char *argv[])
{
    std::string arg {};
    for (int col {1}; col < argc; ++col)
    {
        arg = argv[col];
        if (arg == "-h" || arg == "--help")
        {
            Help();
        }
        else if (arg == "-o" || arg == "--old-version")
        {
            old_version();
        }
        else if (arg == "--parse-file")
        {
            parse_file();
        }
        else if (arg == "--test-array")
        {
            test_array();
        }
        else if (arg == "--test-array-2")
        {
            test_array_2();
        }
        else
        {
            Help();
        }
    }

    return 0;
}