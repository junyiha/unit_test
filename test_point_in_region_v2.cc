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

// 判断矩形框是否在区域内
bool isRectangleInRegion(const std::vector<Point>& rectangle, const std::vector<Point>& region) {
    for (const Point& point : rectangle) {
        if (!isPointInRegion(point, region)) {
            return false;
        }
    }

    return true;
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

    // 定义矩形框的顶点坐标
    std::vector<Point> rectangle;
    rectangle.push_back(Point(716, 238));
    rectangle.push_back(Point(716, 71));
    rectangle.push_back(Point(762, 309));
    rectangle.push_back(Point(762, 238));

    // 判断矩形框是否在区域内
    bool isInsideRegion = isRectangleInRegion(rectangle, region);

    if (isInsideRegion) {
        std::cout << "矩形框完全在区域内" << std::endl;
    } else {
        std::cout << "矩形框不完全在区域内" << std::endl;
    }

    return 0;
}
