/**
 * @file ThreadPool.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <vector>
#include <queue>

class ThreadPool
{
private:
    bool should_terminate = false;
    std::mutex queue_mutex;
    std::condition_variable mutex_condition;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;

private:
    void ThreadLoop()
    {
        while (true)
        {
            std::function<void()> job;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                mutex_condition.wait(lock, [this] {
                    return !jobs.empty() || should_terminate;
                });
                if (should_terminate)
                {
                    return;
                }
                job = jobs.front();
                jobs.pop();
            }

            job();
        }
    }

public:
    void Start()
    {
        const uint32_t num_threads = std::thread::hardware_concurrency();
        for (uint32_t ii = 0; ii < num_threads; ++ii)
        {
            threads.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
        }
    }
    void QueueJob(const std::function<void()>& job)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            jobs.push(job);
        }

        mutex_condition.notify_one();
    }
    void Stop()
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            should_terminate = true;
        }
        mutex_condition.notify_all();
        for (std::thread& active_thread : threads)
        {
            active_thread.join();
        }
        threads.clear();
    }
    bool Busy()
    {
        bool poolbusy;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            poolbusy = !jobs.empty();
        }

        return poolbusy;
    }
};