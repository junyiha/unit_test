/**
 * @file test_opencv.cc
 * @author your name (you@domain.com)
 * @brief 读取图片数据，画框，显示
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "opencv2/opencv.hpp"

void Help()
{
    std::string help_info {R"(
        help information

        --draw-static-image

    )"};

    std::cerr << help_info << std::endl;
}

// 读取文件内容到内存
std::vector<char> ReadFileToMemory(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return {};
    }

    // 获取文件大小
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // 分配内存缓冲区
    std::vector<char> buffer(fileSize);

    // 读取文件内容到缓冲区
    if (!file.read(buffer.data(), fileSize)) {
        std::cerr << "Failed to read file: " << filename << std::endl;
        return {};
    }

    return buffer;
}

int ProcessPic(cv::Mat &image)
{
    if (image.empty()) {
        std::cout << "无法加载图像文件" << std::endl;
        return -1;
    }

    // 定义边框的位置和大小
    int x = 100;
    int y = 100;
    int width = 200;
    int height = 150;

    // 在图像上绘制边框
    // cv::rectangle(image, cv::Point(x, y), cv::Point(x + width, y + height), cv::Scalar(0, 255, 0), 2);

    // 创建窗口
    cv::namedWindow("Image", cv::WINDOW_NORMAL);

    // 显示带有边框的图像
    cv::imshow("Image", image);

    // 等待按键事件
    cv::waitKey(0);

    // 关闭窗口
    cv::destroyWindow("Image");

    return 0;
}

int show()
{
    // 读取图片
    // cv::Mat image = cv::imread("input_pic.jpg");
    cv::Mat image = cv::imread("./wQMc1-frame-4792.jpg");
    ProcessPic(image);
}

int old_version ()
{
    std::string file {"frame.jpg"};
    int height {1920};
    int width {1080};
    std::vector<char> pic_data;

    pic_data = ReadFileToMemory(file);
    if (pic_data.empty())
    {
        std::cerr << "Failed to read data of :" << file << std::endl;
        return -1;
    }
    cv::Mat image = cv::Mat( width, height, CV_8UC3, pic_data.data());
    ProcessPic(image);
    // show();

    return 0;
}

std::string tmp_img {"path/to/aaa-frame-6137.jpg"};

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
*/


int draw_static_image()
{
    /* 检测区域 */
    int x1 = 265;
    int y1 = 300;
    int x2 = 700;
    int y2 = 900;

    /* 告警框信息 */
    // int x1 = 720;
    // int y1 = 231;
    // int x2 = 773;
    // int y2 = 308;
    std::string window_name {"tmp"};
    cv::Mat img;
    img = cv::imread(tmp_img);

    cv::rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);

    /* 告警框信息1 */
    x1 = 720;
    y1 = 231;
    x2 = 773;
    y2 = 308;
    cv::rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);

    /* 告警框信息2 */
    x1 = 341;
    y1 = 329;
    x2 = 483;
    y2 = 732;
    cv::rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);

    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    cv::imshow(window_name, img);
    cv::waitKey(0);

    return 0;
}

int failed_read_image()
{
    std::string file_name {"origin-frame-1.jpg"};

    int height {1920};
    int width {1080};
    std::vector<char> pic_data;

    pic_data = ReadFileToMemory(file_name);
    if (pic_data.empty())
    {
        std::cerr << "Failed to read data of :" << file_name << std::endl;
        return -1;
    }
    cv::Mat image = cv::Mat( width, height, CV_8UC3, pic_data.data());
    cv::namedWindow(file_name, cv::WINDOW_NORMAL);
    cv::imshow(file_name, image);
    cv::waitKey(0);

    return 0;
}

int test_scalar()
{
    // 创建一个红色的 Scalar 对象
    cv::Scalar redColor(0, 0, 255);

    // 创建一个白色的 Scalar 对象
    cv::Scalar whiteColor(255, 255, 255);

    // 输出 Scalar 对象的分量值
    std::cout << "Red Color: " << redColor[0] << ", " << redColor[1] << ", " << redColor[2] << std::endl;

    // 创建一个像素值为 (100, 150, 200) 的 Scalar 对象
    cv::Scalar pixelValue(100, 150, 200);

    return 0;
}

int test_point()
{
    // 创建一个点对象
    cv::Point pt1(10, 20);

    // 访问点的坐标
    int x = pt1.x;
    int y = pt1.y;

    // 输出点的坐标
    std::cout << "Point coordinates: (" << x << ", " << y << ")" << std::endl;

    // 创建另一个点对象
    cv::Point pt2(5, 8);

    // 使用复制构造函数创建新点对象
    cv::Point pt3 = pt2;

    return 0;
}

int test_RotatedRect()
{
    cv::Point2f center(100, 100);
    cv::Size2f size(100, 50);
    float angle = 30.0;

    // 创建一个旋转矩形对象
    cv::RotatedRect rotatedRect(center, size, angle);

    // 访问旋转矩形的属性
    cv::Point2f rectCenter = rotatedRect.center;
    cv::Size2f rectSize = rotatedRect.size;
    float rectAngle = rotatedRect.angle;

    // 输出旋转矩形的属性
    std::cout << "Center: (" << rectCenter.x << ", " << rectCenter.y << ")" << std::endl;
    std::cout << "Size: " << rectSize.width << " x " << rectSize.height << std::endl;
    std::cout << "Angle: " << rectAngle << " degrees" << std::endl;

    cv::Scalar redColor(0, 0, 255);
    cv::Mat image(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));
    std::vector<cv::Point2f> point(4);
    rotatedRect.points(point.data());
    cv::line(image, point[0], point[1], redColor, 3);
    cv::line(image, point[1], point[2], redColor, 3);
    cv::line(image, point[2], point[3], redColor, 3);
    cv::line(image, point[3], point[0], redColor, 3);
    cv::imshow("RotatedRect", image);
    cv::waitKey(0);

    return 0;
}

int test_point2f()
{
    // 创建一个点对象
    cv::Point2f pt1(10.5, 20.3);

    // 访问点的坐标
    float x = pt1.x;
    float y = pt1.y;

    // 输出点的坐标
    std::cout << "Point coordinates: (" << x << ", " << y << ")" << std::endl;

    // 创建另一个点对象
    cv::Point2f pt2(5.2, 8.7);

    // 使用复制构造函数创建新点对象
    cv::Point2f pt3 = pt2;

    return 0;
}

int test_size()
{
    // 创建一个尺寸对象
    cv::Size size1(640, 480);

    // 访问尺寸的宽度和高度
    int width = size1.width;
    int height = size1.height;

    // 输出尺寸的宽度和高度
    std::cout << "Size: " << width << " x " << height << std::endl;

    // 创建另一个尺寸对象
    cv::Size size2(320, 240);

    // 使用复制构造函数创建新尺寸对象
    cv::Size size3 = size2;

    return 0;
}

int test_line()
{
    // 创建一个黑色图像
    cv::Mat image(300, 400, CV_8UC3, cv::Scalar(0, 0, 0));

    // 定义起点和终点坐标
    cv::Point pt1(50, 100);
    cv::Point pt2(350, 200);

    // 绘制直线
    cv::line(image, pt1, pt2, cv::Scalar(0, 0, 255), 2);

    // 显示绘制的图像
    cv::imshow("Line Example", image);
    cv::waitKey(0);

    return 0;
}

int test_rect()
{
    // 创建一个矩形对象
    cv::Rect rect1(100, 50, 200, 150);

    // 访问矩形的属性
    int x = rect1.x;
    int y = rect1.y;
    int width = rect1.width;
    int height = rect1.height;

    // 输出矩形的属性
    std::cout << "Rectangle: x=" << x << ", y=" << y << ", width=" << width << ", height=" << height << std::endl;

    // 创建另一个矩形对象
    cv::Rect rect2(50, 30, 100, 80);

    // 使用复制构造函数创建新矩形对象
    cv::Rect rect3 = rect2;

    return 0;
}

int test_rectangle()
{
    // 创建一个空白图像
    cv::Mat image(300, 400, CV_8UC3, cv::Scalar(255, 255, 255));

    // 绘制矩形
    cv::Rect rect(50, 50, 200, 150);
    cv::Scalar color(0, 0, 255);  // 红色
    int thickness = 2;
    int lineType = cv::LINE_8;
    int shift = 0;
    cv::rectangle(image, rect, color, thickness, lineType, shift);

    // 显示图像
    cv::imshow("Image", image);
    cv::waitKey(0);

    return 0;
}

int test_circle()
{
    // 创建一个黑色图像
    cv::Mat image(300, 400, CV_8UC3, cv::Scalar(0, 0, 0));

    // 定义圆心坐标和半径
    cv::Point center(200, 150);
    int radius = 50;

    // 绘制圆
    cv::circle(image, center, radius, cv::Scalar(0, 0, 255), 2);

    // 显示绘制的图像
    cv::imshow("Circle Example", image);
    cv::waitKey(0);

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg;
    for (int col{1}; col < argc; col++)
    {
        arg = argv[col];
        if (arg == "--draw-static-image")
        {
            draw_static_image();
        }
        else if (arg == "--test-scalar")
        {
            test_scalar();
        }
        else if (arg == "--test-point")
        {
            test_point();
        }
        else if (arg == "--test-rotated-rect")
        {
            test_RotatedRect();
        }
        else if (arg == "--test-point-2f")
        {
            test_point2f();
        }
        else if (arg == "--test-size")
        {
            test_size();
        }
        else if (arg == "--test-line")
        {
            test_line();
        }
        else if (arg == "--test-rect")
        {
            test_rect();
        }
        else if (arg == "--test-rectangle")
        {
            test_rectangle();
        }
        else if (arg == "--test-circle")
        {
            test_circle();
        }
        else
        {
            Help();
        }
    }

    std::cerr << "--end--" << std::endl;

    return 0;
}