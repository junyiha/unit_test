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
    y: 300
    ++++++++++++++++++

    ++++++++++++++++++
    cnt: 2
    x: 700
    y: 300
    ++++++++++++++++++

    ++++++++++++++++++
    cnt: 3
    x: 700
    y: 900
    ++++++++++++++++++

    ++++++++++++++++++
    cnt: 4
    x: 265
    y: 900
    ++++++++++++++++++

    // 检测区域： 小会议室门口与白板中间
    int x1 = 265;
    int y1 = 300;
    int x2 = 700;
    int y2 = 900;

    // 告警框信息：前端对面
    l.score = 80;
    l.label = 10001;
    l.box.x1 = 720;
    l.box.y1 = 231;
    l.box.x2 = 773;
    l.box.y2 = 308;

    // 告警框信息2：小会议室门口
    l.score = 96;
    l.label = 10001;
    l.box.x1 = 341;
    l.box.y1 = 329;
    l.box.x2 = 483;
    l.box.y2 = 732;
*/


int main()
{
    // l.score = 80;
    // l.label = 10001;
    // l.box.x1 = 720;
    // l.box.y1 = 231;
    // l.box.x2 = 773;
    // l.box.y2 = 308;

    l.score = 96;
    l.label = 10001;
    l.box.x1 = 341;
    l.box.y1 = 329;
    l.box.x2 = 483;
    l.box.y2 = 732;

    int event {0};
    int cnt {0};
    int alert_time {};
    int ret {ServiceLogic::RET_ERR};
    service_logic.GetAlertTime(alert_time);
    std::cerr << "default alert time: " << alert_time << std::endl;
    std::string event_string {};
    ServiceLogic::Point p1(265, 300);
    ServiceLogic::Point p2(700, 300);
    ServiceLogic::Point p3(700, 900);
    ServiceLogic::Point p4(265, 900);
    std::vector<ServiceLogic::Point> point_arr;
    service_logic.GetDetectionRegion(point_arr);
    std::cerr << "Default detection region: " << std::endl;
    for (int col {0}; col < point_arr.size(); ++col)
    {
        std::cerr << "\n++++++++++++++++++++++++++++++" <<std::endl;
        std::cerr << "x" << col << ": " << point_arr[col].x << std::endl;
        std::cerr << "y" << col << ": " << point_arr[col].y << std::endl;
        std::cerr << "++++++++++++++++++++++++++++++\n" <<std::endl;
    }
    point_arr.clear();
    point_arr.push_back(p1);
    point_arr.push_back(p2);
    point_arr.push_back(p3);
    point_arr.push_back(p4);
    ret = service_logic.SetDetectionRegion(point_arr);
    service_logic.GetDetectionRegion(point_arr);
    std::cerr << "Set detection region: " << std::endl;
    for (int col {0}; col < point_arr.size(); ++col)
    {
        std::cerr << "\n++++++++++++++++++++++++++++++" <<std::endl;
        std::cerr << "x" << col << ": " << point_arr[col].x << std::endl;
        std::cerr << "y" << col << ": " << point_arr[col].y << std::endl;
        std::cerr << "++++++++++++++++++++++++++++++\n" <<std::endl;
    }
    if (ret == ServiceLogic::RET_ERR)
    {
        std::cerr << "Error input detection region" << std::endl;
        return -1;
    }
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
}