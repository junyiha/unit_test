/**
 * @file test_parse_time.cc
 * @author your name (you@domain.com)
 * @brief 解析时间
 * @version 0.1
 * @date 2023-06-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>
#include <sstream>

bool GetYearMonthDay(std::string in, std::string &year, std::string &month, std::string &day)
{
    std::istringstream iss(in);
    std::getline(iss, year, '-');
    std::getline(iss, month, '-');
    std::getline(iss, day, ' ');

    return true;
}

int main() {
    std::string str = "2023-6-21 10:15:2";
    std::istringstream iss(str);
    std::string year, month, day;

    // // 提取年月日
    // std::getline(iss, year, '-');
    // std::getline(iss, month, '-');
    // std::getline(iss, day, ' ');

    if (GetYearMonthDay(str, year, month, day))
        std::cout << "提取的年月日为：" << year << "-" << month << "-" << day << std::endl;

    return 0;
}
