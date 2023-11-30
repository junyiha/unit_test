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
        return a.second[0] < b.second[0];
    }
};

#endif // TARGET_POOL_HPP