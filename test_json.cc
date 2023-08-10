/**
 * @file test_json.cc
 * @author your name (you@domain.com)
 * @brief JSON字符串
 * @version 0.1
 * @date 2023-08-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string>
#include <iostream>
#include "json.hpp"

int main()
{
    std::string point_str {R"({"CartInfo":[5.630188835235163e-05,-0.19249999742802357,0.6714999963324777,1.5707963199010575,-3.1414488428910943,9.587379973829968e-05],"JointInfo":[4.7936899621426287e-05,0.0,0.00014381069886427886,0.0,4.7936899621426287e-05,0.0],"STATUS":"SUCCESS"})"};

    std::string str {R"({"code":0,"data":null,"message":"{\"CartInfo\":[5.630188835235163e-05,-0.19249999742802357,0.6714999963324777,1.5707963199010575,-3.1414488428910943,9.587379973829968e-05],\"JointInfo\":[4.7936899621426287e-05,0.0,0.00014381069886427886,0.0,4.7936899621426287e-05,0.0],\"STATUS\":\"SUCCESS\"}"})"};

    std::cerr << "point_str: " << point_str << "\n"
              << "str: " << str << "\n"
              << std::endl;

    nlohmann::json reply_data;
    nlohmann::json parsed_data;

    reply_data["code"] = 0;
    try
    {
        parsed_data = nlohmann::json::parse(point_str);
    }
    catch (nlohmann::json::parse_error &e)
    {
        std::cerr << "error info: " << e.what() << std::endl;
        return -1;
    }
    reply_data["message"] = parsed_data;
    reply_data["data"];

    std::cerr << "reply data: " << reply_data.dump() << std::endl;

    return 0;
}