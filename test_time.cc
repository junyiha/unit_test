/**
 * @file test_time.cc
 * @author your name (you@domain.com)
 * @brief 测试时间相关函数
 * @version 0.1
 * @date 2023-06-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <ctime>
#include <chrono>
#include <sstream>

struct Time_t 
{
    std::string time_string;
    int year;
    int month;
    int day;
    int hour {0};
    int minute {0};
    int second {0};
    std::size_t timestamp;
    public:
        void ConvertTime()
        {
            std::tm timeinfo = {};
            timeinfo.tm_year = year - 1900; // 年份需要减去1900
            timeinfo.tm_mon = month - 1; // 月份需要减去1
            timeinfo.tm_mday = day;
            timeinfo.tm_hour = hour;
            timeinfo.tm_min = minute;
            timeinfo.tm_sec = second;

            timestamp = std::mktime(&timeinfo);
        }
        bool ConvertYearMonthDay()
        {
            if (time_string.empty())
                return false;

            std::string year_str;
            std::string month_str;
            std::string day_str;
            std::istringstream iss(time_string);
            std::getline(iss, year_str, '-');
            std::getline(iss, month_str, '-');
            std::getline(iss, day_str, ' ');
            year = std::stoi(year_str);
            month = std::stoi(month_str);
            day = std::stoi(day_str);

            return true;
        }
};

int get_time ()
{

    std::time_t current_time = std::time(nullptr);
    std::cerr << "Current timestamp: " << current_time << std::endl;

    return 0;
}


int convert_time()
{
    // 定义日期时间
    int year = 2023;
    int month = 7;
    int day = 27;

    // 构造时间点
    std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::from_time_t(0);
    timePoint += std::chrono::hours(24 * 365 * (year - 1970)); // 年
    timePoint += std::chrono::hours(24 * 30 * (month - 1)); // 月
    timePoint += std::chrono::hours(24 * (day - 1)); // 日

    // 转换为秒数
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(timePoint.time_since_epoch()).count();

    std::cout << "Seconds since epoch: " << seconds << std::endl;

    return 0;
}

std::time_t getTimestamp(int year, int month, int day, int hour, int minute, int second)
{
    std::tm timeinfo = {};
    timeinfo.tm_year = year - 1900; // 年份需要减去1900
    timeinfo.tm_mon = month - 1; // 月份需要减去1
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = minute;
    timeinfo.tm_sec = second;

    std::time_t timestamp = std::mktime(&timeinfo);
    return timestamp;
}

bool GetYearMonthDay(std::string in, std::string &year, std::string &month, std::string &day)
{
    if (in.empty())
        return false;
    
    std::istringstream iss(in);
    std::getline(iss, year, '-');
    std::getline(iss, month, '-');
    std::getline(iss, day, ' ');

    return true;
}

int main()
{
    Time_t t;
    t.year = 2023;
    t.month = 6;
    t.day = 27;
    t.hour = 11;
    t.minute = 0;
    t.second = 0;

    std::string str {"2023-05-23"};
    std::string year;
    std::string month;
    std::string day;
    GetYearMonthDay(str, year, month, day);
    std::cerr << "year: " << year << std::endl;
    std::cerr << "month: " << month << std::endl;
    std::cerr << "day: " << day << std::endl;
    Time_t tmp;
    tmp.time_string = str;
    tmp.ConvertYearMonthDay();
    // tmp.time_string = str;
    // tmp.year = std::stoi(year);
    // tmp.month = std::stoi(month);
    // tmp.day = std::stoi(day);
    std::cerr << "tmp.year: " << tmp.year << std::endl;
    std::cerr << "tmp.month: " << tmp.month << std::endl;
    std::cerr << "tmp.day: " << tmp.day << std::endl;

    t.ConvertTime();
    std::cerr << "Time_t:: timestamp: " << t.timestamp << std::endl;
    convert_time();
    auto tt = getTimestamp(t.year, t.month, t.day, t.hour, t.minute, t.second);
    std::cerr << "getTimestamp: " << tt << std::endl;

    return 0;
}