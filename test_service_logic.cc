/**
 * @file test_service_logic.cc
 * @author your name (you@domain.com)
 * @brief 测试rk平台的业务层
 * @version 0.1
 * @date 2023-06-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <unistd.h>
#include "ServiceLogic.hpp"

ServiceLogic::Logic_t l;

ServiceLogic service_logic;

int main()
{
    l.score = 80;
    l.label = 10001;
    l.box.x1 = 720;
    l.box.y1 = 231;
    l.box.x2 = 773;
    l.box.y2 = 308;

    int event {0};
    int cnt {0};
    int alert_time {};
    service_logic.GetAlertTime(alert_time);
    std::cerr << "default alert time: " << alert_time << std::endl;
    std::string event_string {};
    while (true)
    {
        if (cnt > 10)
            break;
        service_logic.Process(l, event);
        service_logic.GetEventNameFromID(event, event_string);
        std::cerr << "cnt: " << cnt << "event: " << event_string << std::endl;
        sleep(1);
        cnt++;
    }
    std::cerr << "set the alert time to :" << std::endl;
    std::cin >> alert_time;
    service_logic.SetAlertTime(alert_time);
    cnt = 0;
    while (true)
    {
        if (cnt > 10)
            break;
        service_logic.Process(l, event);
        service_logic.GetEventNameFromID(event, event_string);
        std::cerr << "cnt: " << cnt << "event: " << event_string << std::endl;
        sleep(1);
        cnt++;
    }

    return 0;
}