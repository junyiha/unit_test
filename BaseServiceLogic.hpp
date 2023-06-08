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
    virtual int ConfigDetectionArea(struct Box_t &b) {}
    virtual int ConfigThreshold(int threshold) {}
    virtual int Process(struct Logic_t &l, int &event) {}

protected:
    virtual void DetectPerson(struct Logic_t &l, int &event) {}

public:
    BaseServiceLogic() = default;
    virtual ~BaseServiceLogic() = default;

};