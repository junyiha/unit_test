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
    virtual int ConfigDetectionArea(Box_t &b) override;
    virtual int ConfigThreshold(int threshold) override;
    virtual int Process(Logic_t &l, int &event) override;
    virtual void InitLimitTime() override;
    virtual int SetLimitBeginTime(LogicTime_t &in) override;
    virtual int SetLimitEndTime(LogicTime_t &in) override;

public:
    virtual void DetectPerson(Logic_t &l, int &event) override;
    virtual void GetCurrentTime(LogicTime_t &lt) override;
    virtual int CheckAlarmTime() override;

public:
    ServiceLogic();
    virtual ~ServiceLogic() = default;

private:
    int m_threshold {60};

private:
    struct Box_t m_b {};
    struct Logic_t m_l {};
    std::pair<LogicTime_t, LogicTime_t> m_time_limit;
};

inline ServiceLogic::ServiceLogic()
{
    InitLimitTime();
}

inline int ServiceLogic::ConfigDetectionArea(Box_t &b)
{
    if (b.x1 < 0 || b.x2 < 0 || b.y1 < 0 || b.y2 < 0)
        return RET_ERR;
    
    m_b = b;
    
    return RET_OK;
}

inline int ServiceLogic::ConfigThreshold(int threshold)
{
    if (threshold <= 0)
        return RET_ERR;
    
    m_threshold = threshold;

    return RET_OK;
}

inline int ServiceLogic::Process(Logic_t &l, int &event)
{
    if (l.label == LABEL_FULL_BODY)
    {
        DetectPerson(l, event);
    }
    else if (l.label == LABEL_WEAR_HELMET)
    {

    }
    else if (l.label == LABEL_UNWEAR_HELMET)
    {

    }
    else if (l.label == LABEL_WEAR_REFLECTIVE_CLOTHING)
    {

    }
    else if (l.label == LABEL_UNWEAR_REFLECTIVE_CLOTHING)
    {

    }
    else if (l.label == LABEL_SMOKE)
    {

    }
    else if (l.label == LABEL_FIRE)
    {

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

inline void ServiceLogic::DetectPerson(Logic_t &l, int &event)
{
    int ret {RET_ERR};
    event = EVENT_ERROR;

    if (l.score >= m_threshold)
    {
        ret = CheckAlarmTime();
        if ( ret == RET_OK)
        {
            event = EVENT_AREA_INVASION;
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