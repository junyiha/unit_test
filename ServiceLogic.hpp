/**
 * @file ServiceLogic.hpp
 * @author your name (you@domain.com)
 * @brief 算力节点
 * @version 0.1
 * @date 2023-06-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include "BaseServiceLogic.hpp"

class ServiceLogic final : public BaseServiceLogic
{
public:
    int SetDetectionRegion(std::vector<Point> &in) override;
    int ConfigThreshold(int threshold) override;
    void GetThreshold(int &out) override;
    int Process(Logic_t &l, int &event) override;
    void InitLimitTime() override;
    void InitLimitArea() override;
    int SetLimitBeginTime(LogicTime_t &in) override;
    int SetLimitEndTime(LogicTime_t &in) override;
    int GetEventNameFromID(int in_event, std::string &out_event_name) override;

private:
    void DetectPerson(Logic_t &l, int &event) override;
    void DetectFire(Logic_t &l, int &event) override;
    void DetectSmoke(Logic_t &l, int &event) override;
    void DetectHelmet(Logic_t &l, int &event) override;
    void DetectReflectClothing(Logic_t &l, int &event) override;

private:
    void GetCurrentTime(LogicTime_t &lt) override;
    int CheckAlarmTime() override;
    bool isInsidePolygon(const Point& point, const std::vector<Point>& region) override;
    bool isRectangleInsidePolygon(const std::vector<Point>& rectangle, const std::vector<Point>& region) override;
    int CheckAlarmArea() override;

public:
    ServiceLogic();
    ~ServiceLogic() = default;

private:
    int m_threshold {60};

private:
    std::vector<Point> m_region;
    struct Logic_t m_l {};
    std::pair<LogicTime_t, LogicTime_t> m_time_limit;
    AlertTimeMap_t m_alert_time_map {};
};

inline ServiceLogic::ServiceLogic()
{
    InitLimitTime();
    InitLimitArea();
}

inline int ServiceLogic::SetDetectionRegion(std::vector<Point> &in)
{
    if (in.size() < 3)
        return RET_ERR;
    
    m_region = in;

    return RET_OK;
}

inline int ServiceLogic::ConfigThreshold(int threshold)
{
    if (threshold <= 0)
        return RET_ERR;
    
    m_threshold = threshold;

    return RET_OK;
}

inline void ServiceLogic::GetThreshold(int &out)
{
    out = m_threshold;
}

inline int ServiceLogic::Process(Logic_t &l, int &event)
{
    if (l.label == LABEL_FULL_BODY)
    {
        DetectPerson(l, event);
    }
    else if (l.label == LABEL_WEAR_HELMET)
    {
        DetectHelmet(l, event);
    }
    else if (l.label == LABEL_UNWEAR_HELMET)
    {

    }
    else if (l.label == LABEL_WEAR_REFLECTIVE_CLOTHING)
    {
        DetectReflectClothing(l, event);
    }
    else if (l.label == LABEL_UNWEAR_REFLECTIVE_CLOTHING)
    {

    }
    else if (l.label == LABEL_SMOKE)
    {
        DetectSmoke(l, event);
    }
    else if (l.label == LABEL_FIRE)
    {
        DetectFire(l, event);
    }
    else 
    {
        std::cerr << "Invalid label" << std::endl;
        return RET_ERR;
    }

    return RET_OK;
}

inline void ServiceLogic::InitLimitTime()
{
    LogicTime_t lt_begin;
    LogicTime_t lt_end;

    lt_begin.hour = 0;
    lt_begin.minute = 0;
    lt_begin.second = 0;

    lt_end.hour = 23;
    lt_end.minute = 59;
    lt_end.second = 59;

    m_time_limit = std::make_pair(lt_begin, lt_end);
}

inline void ServiceLogic::InitLimitArea()
{
    m_region = 
    {
        {0, 0},
        {1920, 0},
        {1920, 1080},
        {0, 1080}
    };
}

inline void ServiceLogic::DetectPerson(Logic_t &l, int &event)
{
    int ret {RET_ERR};
    event = EVENT_ERROR;

    if (l.score >= m_threshold)
    {
        ret = CheckAlarmTime();
        if ( ret == RET_OK)
        {
            m_l = l;
            ret = CheckAlarmArea();
            if (ret == RET_OK)
            {
                event = EVENT_AREA_INVASION;
            }
        }
    }
}

inline void ServiceLogic::DetectFire(Logic_t &l, int &event)
{
    int ret {RET_ERR};
    event = EVENT_ERROR;

    if (l.score >= m_threshold)
    {
        ret = CheckAlarmTime();
        if (ret == RET_OK)
        {
            m_l = l;
            ret = CheckAlarmArea();
            if (ret == RET_OK)
            {
                event = EVENT_FIRE;
            }
        }
    }
}

inline void ServiceLogic::DetectSmoke(Logic_t &l, int &event)
{
    int ret {RET_ERR};
    event = EVENT_ERROR;

    if (l.score >= m_threshold)
    {
        ret = CheckAlarmTime();
        if (ret == RET_OK)
        {
            m_l = l;
            ret = CheckAlarmArea();
            if (ret == RET_OK)
            {
                event = EVENT_SMOKE;
            }
        }
    }
}

inline void ServiceLogic::DetectHelmet(Logic_t &l, int &event)
{
    int ret {RET_ERR};
    event = EVENT_ERROR;

    if (l.score >= m_threshold)
    {
        ret = CheckAlarmTime();
        if (ret == RET_OK)
        {
            m_l = l;
            ret = CheckAlarmArea();
            if (ret == RET_OK)
            {
                event = EVENT_WEAR_HELMET;
            }
        }
    }
}

inline void ServiceLogic::DetectReflectClothing(Logic_t &l, int &event)
{
    int ret {RET_ERR};
    event = EVENT_ERROR;

    if (l.score >= m_threshold)
    {
        ret = CheckAlarmTime();
        if (ret == RET_OK)
        {
            m_l = l;
            ret = CheckAlarmArea();
            if (ret == RET_OK)
            {
                event = EVENT_WEAR_REFLECTIVE_CLOTHING;
            }
        }
    }
}

inline void ServiceLogic::GetCurrentTime(LogicTime_t &lt)
{
    std::time_t current_time = std::time(nullptr);
    std::tm *local_time = std::localtime(&current_time);
    assert(local_time != nullptr);
    
    lt.hour = local_time->tm_hour;
    lt.minute = local_time->tm_min;
    lt.second = local_time->tm_sec;
}

inline int ServiceLogic::SetLimitBeginTime(LogicTime_t &in)
{
    if (in.hour < 0 || in.hour >= 24)
        return RET_ERR;
    
    if (in.minute < 0 || in.minute >= 60)
        return RET_ERR;
    
    if (in.second < 0 || in.second >= 60)
        return RET_ERR;
    
    if (in.hour > m_time_limit.second.hour)
        return RET_ERR;
    
    /*小时相同，分钟不可大于结束时间点的*/
    if (in.hour == m_time_limit.second.hour)
        if (in.minute > m_time_limit.second.minute)
            return RET_ERR;
    
    /*小时相同，分钟相同，秒不可大于结束时间点的*/
    if (in.hour == m_time_limit.second.hour)
        if (in.minute == m_time_limit.second.minute)
            if (in.second > m_time_limit.second.second)
                return RET_ERR;
    
    m_time_limit.first = in;

    return RET_OK;
}

inline int ServiceLogic::SetLimitEndTime(LogicTime_t &in)
{
    if (in.hour < 0 || in.hour >= 24)
        return RET_ERR;
    
    if (in.minute < 0 || in.minute >= 60)
        return RET_ERR;
    
    if (in.second < 0 || in.second >= 60)
        return RET_ERR;
    
    if (in.hour < m_time_limit.first.hour)
        return RET_ERR;
    
    /*小时相同，分钟不可小于开始时间点的*/
    if (in.hour == m_time_limit.first.hour)
        if (in.minute < m_time_limit.first.minute)
            return RET_ERR;
    
    /*小时相同，分钟相同，秒不可小于开始时间点的*/
    if (in.hour == m_time_limit.first.hour)
        if (in.minute == m_time_limit.first.minute)
            if (in.second < m_time_limit.first.second)
                return RET_ERR;
    
    m_time_limit.second = in;

    return RET_OK;
}

inline int ServiceLogic::GetEventNameFromID(int in_event, std::string &out_event_name)
{
    auto it = m_event_map.find(static_cast<EnumEvent_t>(in_event));
    if (it != m_event_map.end())
    {
        out_event_name = it->second;
        return RET_OK;
    }

    out_event_name.clear();
    return RET_ERR;
}

inline int ServiceLogic::CheckAlarmTime()
{
    int ret {RET_ERR};
    int begin_second {RET_ERR};
    int end_second {RET_ERR};
    int current_second {RET_ERR};
    LogicTime_t current_time;

    GetCurrentTime(current_time);

    /*直接都换成秒，不就可以了*/
    begin_second = (m_time_limit.first.hour * 60 * 60) + (m_time_limit.first.minute * 60) + (m_time_limit.first.second);
    end_second = (m_time_limit.second.hour * 60 * 60) + (m_time_limit.second.minute * 60) + (m_time_limit.second.second);
    current_second = (current_time.hour * 60 * 60) + (current_time.minute * 60) + (current_time.second);

    if (current_second > begin_second && current_second < end_second)
        return RET_OK;

    return RET_ERR;
}

inline bool ServiceLogic::isInsidePolygon(const Point& point, const std::vector<Point>& region)
{
    int count = 0;
    int n = region.size();

    for (int i = 0; i < n; ++i) 
    {
        const Point& p1 = region[i];
        const Point& p2 = region[(i + 1) % n];

        if ((p1.y > point.y) != (p2.y > point.y) &&
            point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x) 
        {
            ++count;
        }
    }

    return count % 2 == 1;
}

inline bool ServiceLogic::isRectangleInsidePolygon(const std::vector<Point>& rectangle, const std::vector<Point>& region)
{
    for (const Point& point : rectangle) 
    {
        if (!isInsidePolygon(point, region)) 
        {
            return false;
        }
    }

    return true;
}

inline int ServiceLogic::CheckAlarmArea()
{
    std::vector<Point> rectangle = 
    {
        {m_l.box.x1, m_l.box.y1},
        {m_l.box.x1, m_l.box.y2 - m_l.box.y1},
        {m_l.box.x2, m_l.box.y2},
        {m_l.box.x2, m_l.box.y1}
    };

    if (isRectangleInsidePolygon(rectangle, m_region))
    {
        return RET_OK;
    }
    else 
    {
        return RET_ERR;
    }
}