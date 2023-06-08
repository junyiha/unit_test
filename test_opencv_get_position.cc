#include <opencv2/opencv.hpp>
#include <iostream>

// 鼠标点击事件的回调函数
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Point* p = static_cast<cv::Point*>(userdata);
        p->x = x;
        p->y = y;
        std::cerr << "\n++++++++++++++++++" << std::endl;
        std::cerr << "x: " << x << std::endl;
        std::cerr << "y: " << y << std::endl;
        std::cerr << "++++++++++++++++++\n" << std::endl;
    }
}

int main() {
    cv::Mat image = cv::imread("path/to/aaa-frame-6249.jpg");

    // 创建窗口并显示图像
    cv::namedWindow("Image");
    cv::imshow("Image", image);

    // 定义点的坐标
    cv::Point point;

    // 设置鼠标回调函数，并传递点的坐标作为用户数据
    cv::setMouseCallback("Image", onMouse, &point);

    // 等待鼠标点击
    cv::waitKey(0);

    // 输出点击点的坐标
    std::cout << "Clicked point coordinates: (" << point.x << ", " << point.y << ")" << std::endl;

    cv::destroyAllWindows();

    return 0;
}
