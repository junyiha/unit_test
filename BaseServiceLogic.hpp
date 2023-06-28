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
#include <vector>
#include <cassert>
#include <map>  


class BaseServiceLogic
{
public:
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

    struct Point 
    {
        int x;
        int y;

        Point() {}
        Point(int x, int y) : x(x), y(y) {}
    };

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

        EVENT_AREA_INVASION = 10018,               // 区域入侵

        EVENT_WEAR_HELMET = 20005,                 // 戴安全帽
        EVENT_UNWEAR_HELMET = 20006,               // 未戴安全帽

        EVENT_WEAR_REFLECTIVE_CLOTHING = 20009,    // 穿反光衣
        EVENT_UNWEAR_REFLECTIVE_CLOTHING = 20010,  // 未穿反光衣

        EVENT_SMOKE = 30001,                       // 烟
        EVENT_FIRE = 30002                         // 火
    };

    struct TimeInfo_t 
    {
        std::size_t last_alert_time;

    };

    using AlertTimeMap_t = std::map<EnumEvent_t, TimeInfo_t>;

protected:
    std::map<EnumEvent_t, std::string> m_event_map = 
    {
        {EVENT_ERROR, "未知事件"},
        {EVENT_AREA_INVASION, "区域入侵"},
        {EVENT_WEAR_HELMET, "戴安全帽"},
        {EVENT_UNWEAR_HELMET, "未戴安全帽"},
        {EVENT_WEAR_REFLECTIVE_CLOTHING, "穿反光衣"},
        {EVENT_UNWEAR_REFLECTIVE_CLOTHING, "未穿反光衣"},
        {EVENT_SMOKE, "烟"},
        {EVENT_FIRE, "火"}
    };

public:
    virtual void GetDetectionRegion(std::vector<Point> &out) {}
    virtual int SetDetectionRegion(std::vector<Point> &in) {}
    virtual int ConfigThreshold(int threshold) {}
    virtual void GetThreshold(int &out) {}
    /**
     * @brief 
     * 
     * @param [in] l 
     * @param [out] event 
     * @return int 
     */
    virtual int Process(Logic_t &l, int &event) {}
    virtual void InitLimitTime() {}
    virtual void InitLimitArea() {}
    virtual int SetLimitBeginTime(LogicTime_t &in) {}
    virtual int SetLimitEndTime(LogicTime_t &in) {}
    virtual int GetEventNameFromID(int in_event, std::string &out_event_name) {}
    virtual int GetAlertTime(int &out) {}
    virtual int SetAlertTime(int in) {}

protected:
    virtual void DetectPerson(Logic_t &l, int &event) {}
    virtual void DetectFire(Logic_t &l, int &event) {}
    virtual void DetectSmoke(Logic_t &l, int &event) {}
    virtual void DetectHelmet(Logic_t &l, int &event) {}
    virtual void DetectReflectClothing(Logic_t &l, int &event) {}
protected:
    virtual void GetCurrentTime(LogicTime_t &lt) {}
    virtual int CheckAlarmTime() {}
    virtual bool isInsidePolygon(const Point& point, const std::vector<Point>& region) {}
    virtual bool isRectangleInsidePolygon(const std::vector<Point>& rectangle, const std::vector<Point>& region) {}
    virtual int CheckAlarmArea() {}
    virtual int CheckAlertTime(int event) {};

public:
    BaseServiceLogic() = default;
    virtual ~BaseServiceLogic() = default;
};