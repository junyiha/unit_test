/**
 * @file TargetPool.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 
#ifndef TARGET_POOL_HPP
#define TARGET_POOL_HPP

#include <deque>
#include <vector>
#include <map>
#include <string>
#include <mutex>

using Target_t = std::pair<int, std::vector<double>>;

class TargetPool
{
private:
    std::mutex m_mutex;
    std::deque<Target_t> m_pool;
    int m_max;

public:
    TargetPool(int max = 100)
    {
        m_max = max;
    }
    TargetPool(const TargetPool& other)
    {
        m_pool = other.m_pool;
        m_max = other.m_max;
    }
    ~TargetPool()
    {

    }

public:
    void GetPool(std::deque<Target_t>& out)
    {
        out = m_pool;
    }

    void Push(Target_t target)
    {
        if (m_pool.size() >= m_max)
        {
            Delete();
        }
        m_pool.push_back(target);

        Sort();
    }

    int Pop(Target_t &out)
    {
        if (m_pool.empty())
        {
            return 0;
        }
        m_mutex.lock();

        out = m_pool.front();

        m_mutex.unlock();

        Delete();

        Sort();

        return 1;
    }

    // 删除队头
    void Delete()
    {
        m_mutex.lock();

        m_pool.pop_front();

        m_mutex.unlock();

        return;
    }

private:
    void Sort()
    {
        std::sort(m_pool.begin(), m_pool.end(), TargetPool::Compare);

        return;
    }

private:
    static bool Compare(const Target_t& a, const Target_t& b)
    {
        return a.second[0] > b.second[0];
    }
};

namespace TargetPoolV2 
{
    class SpacePoint_t
    {
    public:
        double x;
        double y;
        double z;

    public:
        SpacePoint_t()
        {
            x = 0.0;
            y = 0.0;
            z = 0.0;
        }
        SpacePoint_t(double in_x, double in_y, double in_z)
        {
            x = in_x;
            y = in_y;
            z = in_z;
        }
        SpacePoint_t(const SpacePoint_t& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        ~SpacePoint_t()
        {

        }

        SpacePoint_t& operator=(const SpacePoint_t& other)
        {
            if (this != &other)
            {
                x = other.x;
                y = other.y;
                z = other.z;
            }

            return *this;
        }
    };

    class TargetArea_t
    {
    public:
        SpacePoint_t left_back_point;
        SpacePoint_t right_back_point;
        SpacePoint_t right_front_point;
        SpacePoint_t left_front_point;
    
    public:
        TargetArea_t()
        {
            
        }
        TargetArea_t(SpacePoint_t in_left_back_point, SpacePoint_t in_right_back_point, SpacePoint_t in_left_front_point, SpacePoint_t in_right_front_point)
        {
            left_back_point = in_left_back_point;
            right_back_point = in_right_back_point;
            right_front_point = in_right_front_point;
            left_front_point = in_left_front_point;
        }
        TargetArea_t(const TargetArea_t& other)
        {
            left_back_point = other.left_back_point;
            right_back_point = other.right_back_point;
            right_front_point = other.right_front_point;
            left_front_point = other.left_front_point;
        }
        ~TargetArea_t()
        {
            
        }

        TargetArea_t& operator=(const TargetArea_t& other)
        {
            if (this != &other)
            {
                left_back_point = other.left_back_point;
                right_back_point = other.right_back_point;
                right_front_point = other.right_front_point;
                left_front_point = other.left_front_point;
            }

            return *this;
        }
    };

    struct TargetMeta_t 
    {
        int index;
        long double timestamp;
        std::string timestamp_str;
    };
    using Target_t = std::pair<TargetMeta_t, std::vector<double>>;

    class TargetPool
    {
    private:
        std::mutex m_mutex;
        std::deque<Target_t> m_pool;
        int m_max;
        TargetArea_t m_area;

    public:
        TargetPool(int max = 100)
        {
            m_max = max;
        }
        TargetPool(const TargetPool& other)
        {
            m_pool = other.m_pool;
            m_max = other.m_max;
        }
        ~TargetPool()
        {

        }

    public:
        void SetTargetArea(TargetArea_t in)
        {
            m_area = in;

            return;
        }
        
        void GetPool(std::deque<Target_t>& out)
        {
            out = m_pool;

            return;
        }

        void Push(Target_t target)
        {
            if (m_pool.size() >= m_max)
            {
                Delete();
            }
            m_pool.push_back(target);

            Sort();
            Area();

            return;
        }

        int Pop(Target_t &out)
        {
            if (m_pool.empty())
            {
                return 0;
            }
            m_mutex.lock();

            out = m_pool.front();

            m_mutex.unlock();

            Delete();

            Sort();
            Area();

            return 1;
        }

        // 删除队头
        void Delete()
        {
            m_mutex.lock();

            m_pool.pop_front();

            m_mutex.unlock();

            return;
        }

    private:
        void Sort()
        {
            std::sort(m_pool.begin(), m_pool.end(), TargetPool::Compare);

            return;
        }

        // 区域设置
        void Area()
        {
            for (auto it = m_pool.begin(); it != m_pool.end();)
            {
                if (!IsInArea(*it))
                {
                    m_pool.erase(it);
                }
                else 
                {
                    ++it;
                }
            }


            return;
        }

        bool IsInArea(Target_t target)
        {
            LOG(INFO) << "x: " << target.second.at(0) << ", y: " << target.second.at(1) << ", z: " << target.second.at(2) << "\n";
            return (target.second.at(0) >= m_area.left_back_point.x && target.second.at(0) >= m_area.right_back_point.x && 
                    target.second.at(0) <= m_area.left_front_point.x && target.second.at(0) <= m_area.right_front_point.x && 
                    target.second.at(1) <= m_area.left_back_point.y && target.second.at(1) <= m_area.left_front_point.y &&
                    target.second.at(1) >= m_area.right_back_point.y && target.second.at(1) >= m_area.right_front_point.y && 
                    target.second.at(2) >= 0 && target.second.at(2) <= 0.1 );
        }

    private:
        static bool Compare(const Target_t& a, const Target_t& b)
        {
            return a.second[0] > b.second[0];
        }
    };    
}

#endif // TARGET_POOL_HPP
