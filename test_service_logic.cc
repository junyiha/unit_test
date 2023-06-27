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

/**
 * @brief 测试告警时间间隔
 * 
 * @return int 
 */
int test_alert_time()
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

std::string tmp_img {"/tmp/mnc/wQMc1-frame-4792.jpg"};

/**
    ++++++++++++++++++
    cnt: 1
    x: 265
    y: 351
    ++++++++++++++++++

    ++++++++++++++++++
    cnt: 2
    x: 538
    y: 326
    ++++++++++++++++++

    ++++++++++++++++++
    cnt: 3
    x: 721
    y: 780
    ++++++++++++++++++

    ++++++++++++++++++
    cnt: 4
    x: 160
    y: 912
    ++++++++++++++++++
*/

int x1 = 265;
int y1 = 351;
int x2 = 160;
int y2 = 912;

int main()
{

}