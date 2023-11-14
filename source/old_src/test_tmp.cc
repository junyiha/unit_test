/**
 * @file test_tmp.cc
 * @author your name (you@domain.com)
 * @brief 临时单元测试
 * @version 0.1
 * @date 2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <vector>

struct Point 
{
    int x;
    int y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point &in) const 
    {
        if (x == in.x && y == in.y)
            return true;
        else 
            return false;
    }
};

int main ()
{
    std::vector<Point> m_region;
        m_region = 
        {
            {0, 0},
            {1920, 0},
            {1920, 1080},
            {0, 1080}
        };

    std::vector<Point> m_region_2;
        m_region_2 = 
        {
            {0, 0},
            {1920, 0},
            {1920, 1080},
            {0, 1080}
        };
    
    if (m_region == m_region_2)
    {
        std::cerr << "m_region == m_region_2" << std::endl;
    }
    else 
    {
        std::cerr << "m_region != m_region_2" << std::endl;
    }

    return 0;
}