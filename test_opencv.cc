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
    std::string help_info{R"(
        help information

        --draw-static-image

    )"};

    std::cerr << help_info << std::endl;
}

// 读取文件内容到内存
std::vector<char> ReadFileToMemory(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);

    if (!file)
    {
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
    if (!file.read(buffer.data(), fileSize))
    {
        std::cerr << "Failed to read file: " << filename << std::endl;
        return {};
    }

    return buffer;
}

int ProcessPic(cv::Mat &image)
{
    if (image.empty())
    {
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

    return 0;
}

int old_version()
{
    std::string file{"frame.jpg"};
    int height{1920};
    int width{1080};
    std::vector<char> pic_data;

    pic_data = ReadFileToMemory(file);
    if (pic_data.empty())
    {
        std::cerr << "Failed to read data of :" << file << std::endl;
        return -1;
    }
    cv::Mat image = cv::Mat(width, height, CV_8UC3, pic_data.data());
    ProcessPic(image);
    // show();

    return 0;
}

std::string tmp_img{"path/to/aaa-frame-6137.jpg"};

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
    std::string window_name{"tmp"};
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
    std::string file_name{"origin-frame-1.jpg"};

    int height{1920};
    int width{1080};
    std::vector<char> pic_data;

    pic_data = ReadFileToMemory(file_name);
    if (pic_data.empty())
    {
        std::cerr << "Failed to read data of :" << file_name << std::endl;
        return -1;
    }
    cv::Mat image = cv::Mat(width, height, CV_8UC3, pic_data.data());
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
    cv::Scalar color(0, 0, 255); // 红色
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

int test_opencv_at()
{
    std::string img_path = "path/to/aaa-frame-6253.jpg";

    cv::Mat image = cv::imread(img_path);

    if (!image.empty())
    {
        int row = 100;
        int col = 150;

        cv::Vec3b pixel = image.at<cv::Vec3b>(row, col);

        uchar blue = pixel[0];
        uchar green = pixel[1];
        uchar red = pixel[2];

        std::cout << "Pixel at (" << col << ", " << row << "): "
                  << "B: " << int(blue) << " G: " << int(green) << " R: " << int(red) << std::endl;
    }
    return 0;
}

int test_opencv_polygon()
{
    std::vector<cv::Point> contour = {cv::Point(50, 50), cv::Point(200, 50), cv::Point(200, 200), cv::Point(50, 200)};
    cv::Point2f point(100, 100);

    double distance = cv::pointPolygonTest(contour, point, true);

    if (distance > 0)
    {
        std::cout << "Point is inside the polygon." << std::endl;
    }
    else if (distance == 0)
    {
        std::cout << "Point is on the polygon boundary." << std::endl;
    }
    else
    {
        std::cout << "Point is outside the polygon." << std::endl;
    }
    return 0;
}

int test_opencv_ptr()
{
    std::string depth_img_path = "data/depth-img-73.jpg";

    cv::Mat depth_image = cv::imread(depth_img_path, cv::IMREAD_ANYDEPTH);

    // if (!depth_image.empty() && depth_image.depth() == CV_16U)
    if (!depth_image.empty())
    {
        int row = 100;

        uint16_t *ptr = depth_image.ptr<uint16_t>(row);

        for (int col = 0; col < depth_image.cols; ++col)
        {
            uint16_t depth_value = ptr[col];
            std::cerr << "depth value: " << depth_value << std::endl;
        }
    }
    return 0;
}

int test_opencv_fillpoly()
{
    // cv::Mat image(300, 300, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat image = cv::Mat::zeros(cv::Size(1280, 760), CV_8UC3);

    std::vector<cv::Point> polygon;
    polygon.push_back(cv::Point(50, 50));
    polygon.push_back(cv::Point(150, 50));
    polygon.push_back(cv::Point(150, 150));
    polygon.push_back(cv::Point(50, 150));

    std::vector<std::vector<cv::Point>> polygons;
    polygons.push_back(polygon);

    cv::fillPoly(image, polygons, cv::Scalar(125, 125, 125));

    cv::imshow("Filled Image", image);
    cv::waitKey(0);
    return 0;
}

int test_opencv_rotatedRect_points()
{
    cv::Point2f points[4]; // 存储顶点坐标的数组
    cv::RotatedRect rotatedRect(cv::Point2f(100, 100), cv::Size2f(200, 100), 30); // 创建一个旋转矩形

    rotatedRect.points(points); // 获取旋转矩形的顶点坐标

    for (int i = 0; i < 4; ++i) {
        std::cout << "Point " << i + 1 << ": (" << points[i].x << ", " << points[i].y << ")" << std::endl;
    }

    return 0;
}

int test_opencv_video2picture()
{
    std::string video_file;
    cv::VideoCapture cap;
    cv::Mat frame;
    int frame_index = 1;

    video_file = "data/opencv/aod_video_01.mp4";
    cap.open(video_file);
    if (!cap.isOpened())
    {
        std::cerr << "failed to open video file: " << video_file << std::endl;
        return -1;
    }
    while (cap.read(frame))
    {
        std::string output_file_name = "data/opencv/image/frame_" + std::to_string(frame_index) + ".jpg";
        cv::imwrite(output_file_name, frame);
        frame_index++;
    }
    cap.release();

    return 0;
}

void OnMouse(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_MOUSEMOVE)
    {
        cv::Mat *image = static_cast<cv::Mat *>(userdata);
        cv::Mat imageCopy = image->clone();
        cv::circle(imageCopy, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
        cv::putText(imageCopy, "Mouse Position: (" + std::to_string(x) + ", " + std::to_string(y) + ")",
                    cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        cv::imshow("Image with Mouse Position", imageCopy);
    }
}

int test_opencv_get_mouse_position()
{
    cv::Mat image;
    cv::Mat box_img;
    std::string img_path;

    img_path = "/mnt/remote/190-mnt/zhangjunyi/Documents/VCR/src-color.jpg";
    image = cv::imread(img_path);
    if (image.empty())
    {
        std::cerr << "Error loading image" << std::endl;
        return -1;
    }
    box_img = image.clone();
    cv::namedWindow("Image with Mouse Position");
    cv::namedWindow("Image with box");
    // cv::rectangle(box_img, cv::Point(429, 818), cv::Point(979, 513), cv::Scalar(0, 255, 0), 2);
    cv::Rect rect;
    // rect.x = 429;
    // rect.y = 486;
    // rect.width = 550;
    // rect.height = 400;

    rect.x = 312;
    rect.y = 329;
    rect.width = 713;
    rect.height = 450;

    cv::rectangle(box_img, rect, cv::Scalar(0, 0, 255), 2);
    cv::setMouseCallback("Image with Mouse Position", OnMouse, &image);
    cv::imshow("Image with Mouse Position", image);
    cv::imshow("Image with box", box_img);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

int test_opencv_create_rect()
{
    cv::Point pt1(429, 818);
    cv::Point pt2(429, 486);
    cv::Point pt3(979, 847);
    cv::Point pt4(979, 513);

    cv::RotatedRect rotatedRect = cv::minAreaRect(std::vector<cv::Point2f>{pt1, pt2, pt3, pt4});
    cv::Rect boundingRect = rotatedRect.boundingRect();
    std::cout << "Bounding Rect: (x=" << boundingRect.x << ", y=" << boundingRect.y
              << ", width=" << boundingRect.width << ", height=" << boundingRect.height << ")" << std::endl;

    cv::Mat image;
    cv::Mat box_img;
    std::string img_path;

    img_path = "/mnt/remote/190-mnt/zhangjunyi/src-color.jpg";
    image = cv::imread(img_path);
    if (image.empty())
    {
        std::cerr << "Error loading image" << std::endl;
        return -1;
    }
    box_img = image.clone();
    cv::namedWindow("Image with box");
    cv::rectangle(image, cv::Point(429, 818), cv::Point(979, 513), cv::Scalar(0, 0, 255), 2);
    cv::rectangle(image, boundingRect, cv::Scalar(0, 255, 0), 2);
    cv::imshow("Image with Mouse Position", image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

bool IsRectangleInsideQuadrilateral(const cv::Point2f& p1,
                                    const cv::Point2f& p2,
                                    const cv::Point2f& p3,
                                    const cv::Point2f& p4,
                                    const cv::Rect& rect)
{
    std::vector<cv::Point2f> quadPoints = {p1, p2, p3, p4};
    cv::Mat quadMat = cv::Mat(quadPoints).reshape(1);
    cv::convexHull(quadMat, quadPoints);
    std::vector<cv::Point2f> rectPoints(4);
    rectPoints[0] = cv::Point2f(rect.x, rect.y);
    rectPoints[1] = cv::Point2f(rect.x + rect.width, rect.y);
    rectPoints[2] = cv::Point2f(rect.x + rect.width, rect.y + rect.height);
    rectPoints[3] = cv::Point2f(rect.x, rect.y + rect.height);

    for (const cv::Point2f& point: rectPoints)
    {
        if (cv::pointPolygonTest(quadMat, point, false) < 0)
        {
            return false;
        }
    }

    return true;
}

int test_is_rectangle_inside_quadrilateral()
{
    cv::Point2f p1(100, 100);
    cv::Point2f p2(300, 100);
    cv::Point2f p3(300, 200);
    cv::Point2f p4(100, 200);

    cv::Rect rect(150, 150, 50, 50);
    if (IsRectangleInsideQuadrilateral(p1, p2, p3, p4, rect))
    {
        std::cerr << "Rectangle is inside in the quadrilateral" << std::endl;
    }
    else
    {
        std::cerr << "Rectangle is not inside in the quadrilateral" << std::endl;
    }

    return 0;
}

int test_draw_rotation_rect()
{
    cv::Mat image(400, 400, CV_8UC3, cv::Scalar(255, 255, 255)); // 创建白色背景图像

    cv::Point center(200, 200);
    float width = 200;
    float height = 100;
    double angle = 30;
    cv::RotatedRect rb(center, cv::Size2f(width, height), angle);
    cv::Scalar color(0, 0, 255); // 蓝色

    // 使用椭圆函数绘制旋转矩形框
    cv::drawContours(image, rb, color, 2);

    cv::imwrite("/home/user/zjy-190/workspace/unit_test/rb.jpeg", image);

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
        else if (arg == "--test-draw-rotation-rect")
        {
            test_draw_rotation_rect();
        }
        else if (arg == "--test-is-rectangle-inside-quadrilateral")
        {
            test_is_rectangle_inside_quadrilateral();
        }
        else if (arg == "--test-opencv-create-rect")
        {
            test_opencv_create_rect();
        }
        else if (arg == "--test-opencv-get-mouse-position")
        {
            test_opencv_get_mouse_position();
        }
        else if (arg == "--test-opencv-video-2-capture")
        {
            test_opencv_video2picture();
        }
        else if (arg == "--test-opencv-rotated-rect-points")
        {
            test_opencv_rotatedRect_points();
        }
        else if (arg == "--test-opencv-fillpoly")
        {
            test_opencv_fillpoly();
        }
        else if (arg == "--test-opencv-ptr")
        {
            test_opencv_ptr();
        }
        else if (arg == "--test_opencv_polygon")
        {
            test_opencv_polygon();
        }
        else if (arg == "--test-opencv-at")
        {
            test_opencv_at();
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