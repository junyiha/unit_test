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
    virtual int ConfigDetectionArea(struct Box_t &b) override;
    virtual int ConfigThreshold(int threshold) override;
    virtual int Process(struct Logic_t &l, int &event) override;

public:
    virtual void DetectPerson(struct Logic_t &l, int &event) override;

public:
    ServiceLogic() = default;
    virtual ~ServiceLogic() = default;

private:
    int m_threshold {60};

private:
    struct Box_t m_b {};
    struct Logic_t m_l {};
};

inline int ServiceLogic::ConfigDetectionArea(struct Box_t &b)
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

inline int ServiceLogic::Process(struct Logic_t &l, int &event)
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

inline void ServiceLogic::DetectPerson(struct Logic_t &l, int &event)
{
    event = EVENT_ERROR;
    
    if (l.score >= m_threshold)
        event = EVENT_AREA_INVASION;
}