/**
 * @file business.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "entry.hpp"
#include "TargetPool.hpp"

static int generate_target(TargetPool &out)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> x_dis(-40, 40);
    std::uniform_real_distribution<> y_dis(0, 40);
    std::uniform_real_distribution<> z_dis(0, 10);
    std::uniform_real_distribution<> rx_dis(-3.14, 3.14);
    std::uniform_real_distribution<> ry_dis(-3.14, 3.14);
    std::uniform_real_distribution<> rz_dis(-3.14, 3.14);

    for (int i = 0; i < 10; ++i)
    {
        LOG(INFO) << "x: " << x_dis(gen) << ", "
                  << "y: " << y_dis(gen) << ", "
                  << "z: " << z_dis(gen) << ", "
                  << "rx: " << rx_dis(gen) << ", "
                  << "ry: " << ry_dis(gen) << ", "
                  << "rz: " << rz_dis(gen) << "\n";
        Target_t target;
        target.first = i;
        target.second = {x_dis(gen), y_dis(gen), z_dis(gen), rx_dis(gen), ry_dis(gen), rz_dis(gen)};
        out.Push(target);
    }

    return 1;
}

int test_business()
{
    LOG(INFO) << "hello" << "\n";
    Target_t target;
    TargetPool target_pool;

    generate_target(target_pool);

    while (true)
    {
        std::deque<Target_t> pool;
        target_pool.GetPool(pool);
        LOG(INFO) << "Original target pool: " << "\n";
        for (const auto &it : pool)
        {
            LOG(INFO) << it.second[0] << ", "
                      << it.second[1] << ", "
                      << it.second[2] << ", "
                      << it.second[3] << ", "
                      << it.second[4] << ", "
                      << it.second[5] << "\n";
        }
        int res = target_pool.Pop(target);
        if (res != 1)
        {
            LOG(WARNING) << "target pool is empty" << "\n";
            break;
        }
        LOG(INFO) << "cart info: " << "\n"
                  << "index: " << target.first << "\n"
                  << target.second[0] << ", "
                  << target.second[1] << ", "
                  << target.second[2] << ", "
                  << target.second[3] << ", "
                  << target.second[4] << ", "
                  << target.second[5] << "\n";
    }

    return 1;
}