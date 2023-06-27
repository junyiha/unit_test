/**
 * @file test_alert_time.cc
 * @author your name (you@domain.com)
 * @brief 测试告警时间间隔的业务实现
 * @version 0.1
 * @date 2023-06-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

const int ALERT_INTERVAL_SECONDS = 3;  // 告警时间间隔为60秒
std::time_t lastAlertTime = 0;  // 上次告警时间的初始值为0

void processRequest()
{
    // 模拟请求处理过程
    bool hasError = true;  // 假设出现异常情况

    if (hasError)
    {
        std::time_t currentTime = std::time(nullptr);  // 获取当前时间
        if (currentTime - lastAlertTime > ALERT_INTERVAL_SECONDS)
        {
            // 满足告警条件，进行告警操作
            std::cerr << "time: " << std::time(nullptr) << std::endl;
            std::cout << "Alert: An error occurred!" << std::endl;

            // 更新上次告警时间为当前时间
            lastAlertTime = currentTime;
        }
    }
}

int main()
{
    while (true)
    {
        processRequest();

        // 暂停一段时间
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
