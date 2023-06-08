/**
 * @file BaseServiceLogic.hpp
 * @author your name (you@domain.com)
 * @brief 业务逻辑基类
 * @version 0.1
 * @date 2023-06-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include <iostream>
#include <ctime>
#include <cassert>

struct Box_t 
{
    int x1;
    int y1;
    int x2;
    int y2;
};

struct Logic_t 
{
    int label;
    int score;
    Box_t box;
};

struct LogicTime_t 
{
    int hour;
    int minute;
    int second;
};

struct Point {
    int x;
    int y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}
};

class BaseServiceLogic
{
public:
    using EnumRET_t = enum 
    {
        RET_ERR = -1,
        RET_OK = 0
    };

    using EnumLabel_t = enum 
    {
        LABEL_FULL_BODY = 10001,
        LABEL_HALF_BODY = 10002,
        LABEL_HEADER_SHOULDER = 10003,
        LABEL_HEADER = 10004,
        LABEL_FACE = 10005,

        LABEL_WEAR_HELMET = 10204,
        LABEL_UNWEAR_HELMET = 10208,

        LABEL_WEAR_REFLECTIVE_CLOTHING = 10206,
        LABEL_UNWEAR_REFLECTIVE_CLOTHING = 10210,

        LABEL_SMOKE = 30001,
        LABEL_FIRE = 30002

    };

    using EnumEvent_t = enum 
    {
        EVENT_ERROR = -1,

        EVENT_AREA_INVASION = 10018,

        EVENT_WEAR_HELMET = 20005,
        EVENT_UNWEAR_HELMET = 20006,

        EVENT_WEAR_REFLECTIVE_CLOTHING = 20009,
        EVENT_UNWEAR_REFLECTIVE_CLOTHING = 20010,

        EVENT_SMOKE = 30001,
        EVENT_FIRE = 30002
    };

public:
    virtual int ConfigDetectionArea(Box_t &b) {}
    virtual int SetDetectionRegion(std::vector<Point> &in) {}
    virtual int ConfigThreshold(int threshold) {}
    virtual int Process(Logic_t &l, int &event) {}
    virtual void InitLimitTime() {}
    virtual void InitLimitArea() {}
    virtual int SetLimitBeginTime(LogicTime_t &in) {}
    virtual int SetLimitEndTime(LogicTime_t &in) {}

protected:
    virtual void DetectPerson(Logic_t &l, int &event) {}
    virtual void GetCurrentTime(LogicTime_t &lt) {}
    virtual int CheckAlarmTime() {}
    virtual bool isInsidePolygon(const Point& point, const std::vector<Point>& region) {}
    virtual bool isRectangleInsidePolygon(const std::vector<Point>& rectangle, const std::vector<Point>& region) {}
    virtual int CheckAlarmArea() {}

public:
    BaseServiceLogic() = default;
    virtual ~BaseServiceLogic() = default;

};