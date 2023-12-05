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

int target_pool_business()
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

int test_target_pool_area()
{
    // x: -0.186795, y: -0.436419, z: 0.0515753
    // -0.186795, -0.436419, 0.0515753
    TargetPoolV2::SpacePoint_t left_back_point(-0.5, -0.2, 0);
    TargetPoolV2::SpacePoint_t left_front_point(0, -0.2, 0);
    TargetPoolV2::SpacePoint_t right_back_point(-0.5, -0.7, 0);
    TargetPoolV2::SpacePoint_t right_front_point(0, -0.7, 0);

    TargetPoolV2::TargetArea_t target_area(left_back_point, right_back_point, left_front_point, right_front_point);

    TargetPoolV2::TargetPool target_pool;
    TargetPoolV2::Target_t target;

    target_pool.SetTargetArea(target_area);
    target.first.index = 1;
    target.second = {-0.186795, -0.436419, 0.0515753, 12, 23, 45};
    target_pool.Push(target);

    TargetPoolV2::Target_t tmp;
    int res = target_pool.Pop(tmp);
    if (res != 1)
    {
        LOG(WARNING) << "no target data" << "\n";
        return 0;
    }

    LOG(INFO) << "x: " << tmp.second.at(0) << ", y: " << tmp.second.at(1) << ", z: " << tmp.second.at(2) << "\n";
    return 1;
}

int test_business(Message& message)
{
    LOG(INFO) << "test business begin..." << "\n";

    std::map<std::string, std::function<int()>> cmd_map = {
        {"target-pool-business", target_pool_business},
        {"test-target-pool-area", test_target_pool_area}
    };
    std::string cmd = message.message_pool[2];
    auto it = cmd_map.find(cmd);
    if (it != cmd_map.end())
    {
        it->second();
        return 1;
    }
    LOG(ERROR) << "invalid command: " << cmd << "\n";
    LOG(INFO) << "test business end..." << "\n";

    return 0;
}