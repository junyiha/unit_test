#include <iostream>
#include <vector>

// 定义点的数据结构
struct Point {
    double x;
    double y;

    Point(double x_, double y_) : x(x_), y(y_) {}
};

// 射线法判断点是否在区域内
bool isPointInRegion(const Point& point, const std::vector<Point>& region) {
    int count = 0;
    int n = region.size();

    for (int i = 0; i < n; ++i) {
        const Point& p1 = region[i];
        const Point& p2 = region[(i + 1) % n];

        if ((p1.y > point.y) != (p2.y > point.y) &&
            point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x) {
            ++count;
        }
    }

    return count % 2 == 1;
}

int main() {
    // 定义区域的顶点坐标
    std::vector<Point> region;
    // region.push_back(Point(50, 50));
    // region.push_back(Point(200, 50));
    // region.push_back(Point(200, 200));
    // region.push_back(Point(50, 200));


    region.push_back(Point(9, 7));
    region.push_back(Point(9, 1037));
    region.push_back(Point(1836, 1038));
    region.push_back(Point(1836, 7));

    // 定义要判断的点的坐标
    // Point point(100, 100);
    // Point point(716, 238);
    // Point point(716, 71);
    // Point point(762, 309);
    Point point(762, 238);

    // 判断点是否在区域内
    bool isInRegion = isPointInRegion(point, region);

    if (isInRegion) {
        std::cout << "点在区域内" << std::endl;
    } else {
        std::cout << "点在区域外" << std::endl;
    }

    return 0;
}
