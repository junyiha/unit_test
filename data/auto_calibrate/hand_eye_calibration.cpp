/********************************************************************************************************************
* @brief      在相机标定获取相机内参和畸变系数的前提下，利用opencv函数calibrateCamera计算外参
* @note       importance:
* @note          1. 输入的机械臂末端位姿格式：x,y,z,rx,ry,rz(欧拉角) or x,y,z,q0,q1,q2,q3(四元素)  or x,y,z,rvctor(旋转矩阵)
* @note          2. 欧拉角：输入的顺序：x,y,z?    
* @note       标定版：棋盘格 or 圆（对称 or 非对称） 
* @note       角点检测
* @param       
********************************************************************************************************************/

#include "opencv2/calib3d.hpp"
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include "utils.h"

using namespace std;
using namespace cv;

//标定板选择：棋盘格-CHESSBOARD，非对称圆-ASYMMETRIC_CIRCLES_GRID，对称圆-CIRCLES_GRID
enum Pattern {CHESSBOARD, ASYMMETRIC_CIRCLES_GRID, CIRCLES_GRID};

//计算标定板方法选择（标定板位姿）
enum Solve_Board_Pose {CALIBRATECAMERA, SOLVEPNP };

// 计算重投影误差
static double computeReprojectionErrors(
        const vector<vector<Point3f> >& objectPoints,
        const vector<vector<Point2f> >& imagePoints,
        const vector<Mat>& rvecs, const vector<Mat>& tvecs,
        const Mat& cameraMatrix, const Mat& distCoeffs,
        vector<float>& perViewErrors)
{
    vector<Point2f> imagePoints2;
    int i, totalPoints = 0;
    double totalErr = 0, err;
    perViewErrors.resize(objectPoints.size());
    for (i = 0; i < (int)objectPoints.size(); i++)
    {
        cv::projectPoints(Mat(objectPoints[i]), rvecs[i], tvecs[i], cameraMatrix, distCoeffs, imagePoints2);
        err = norm(Mat(imagePoints[i]), Mat(imagePoints2), NORM_L2);
        int n = (int)objectPoints[i].size();
        perViewErrors[i] = (float)std::sqrt(err * err / n);
        totalErr += err * err;
        totalPoints += n;
    }
    return std::sqrt(totalErr / totalPoints);
}

//计算标定板角点
static void calcBoardCorners(Size boardSize, vector<Point3f> &corners, float squareSize, Pattern patternType)
{
    corners.resize(0);
    switch(patternType)
    {
        case CHESSBOARD:
        case CIRCLES_GRID:
            for( int i = 0; i < boardSize.height; i++ )
                for( int j = 0; j < boardSize.width; j++ )
                    corners.push_back(Point3f(float(j*squareSize), float(i*squareSize), 0));
            break;
        // 非对称圆形
        case ASYMMETRIC_CIRCLES_GRID:
            for( int i = 0; i < boardSize.height; i++ )
                for( int j = 0; j < boardSize.width; j++ )
                    corners.push_back(Point3f(float((2*j + i % 2)*squareSize), float(i*squareSize), 0));
            break;
        default:
            CV_Error(Error::StsBadArg, "Unknown pattern type\n");
    }
}

/********************************************************************************************************************
* @brief      相机标定
* @param      imagePoints       理解为一个二维数组，第一维表示不同的图像，第二维表示每个图像中的角点数量     
* @param      imageSize         标定板的大小，行，列数
* @param      imageSize         标定板的大小，行，列数
********************************************************************************************************************/
static bool runCalibration(const vector<vector<Point2f>> &imagePoints, Size imageSize, Size boardSize, Mat &cameraMatrix,
               Mat &distCoeffs, vector<Mat> &rvecs, vector<Mat> &tvecs, vector<float> &reprojErrs,
               vector<Point3f> &newObjPoints, double &totalAvgErr, float squareSize_, Pattern &pattern_type, Solve_Board_Pose &pose)
{
    cameraMatrix = Mat::eye(3, 3, CV_64F);

    vector<vector<Point3f> > objectPoints(1);
    // 计算棋盘格中角点的3D坐标
    calcBoardCorners(boardSize, objectPoints[0], squareSize_, pattern_type);
    newObjPoints = objectPoints[0];

    // 与2d角点数据对齐，2d-3d
    objectPoints.resize(imagePoints.size(), objectPoints[0]);

    double rms;
    // 修改标志位，考虑内参的影响

    /*****************************************************************
    * @brief   已知相机的内参和畸变系数，输入图片计算标定板的位姿（相机标定）
    * @note    method1: 利用opencv自带库函数去计算-------calibrateCamera
    * @note    method2: 利用solvepnp函数去计算标定板位姿
    ******************************************************************/

    switch(pose)
    {
        case CALIBRATECAMERA:
            // 这里的外参是：R_camera_board、t_camera_board
            // 修改标志位
            // 提供内参和畸变系数
            cameraMatrix = (Mat_<double>(3,3)<<1151.1412353516, 0,645.4006347656,0,1151.0734863281,451.1025390625,0,0,1);
            distCoeffs = (Mat_<double>(1,5)<<0,0,0,0,0);
            rms = calibrateCamera(objectPoints, imagePoints, imageSize,
                                cameraMatrix, distCoeffs, rvecs, tvecs, CALIB_USE_INTRINSIC_GUESS |
                                CALIB_FIX_PRINCIPAL_POINT | CALIB_FIX_FOCAL_LENGTH | CALIB_FIX_K1 |
                                CALIB_FIX_K2 | CALIB_FIX_K3 | CALIB_ZERO_TANGENT_DIST);

            printf("RMS error reported by calibrateCamera: %g\n", rms);
            break;
        case SOLVEPNP:
            //已知相机内参时，也可以使用solvePnP计算相机外参
            //使用solvePnP求解相机的外参
            cameraMatrix = (Mat_<double>(3,3)<<1151.1412353516, 0,645.4006347656,0,1151.0734863281,451.1025390625,0,0,1);
            distCoeffs = (Mat_<double>(1,5)<<0,0,0,0,0);
            rvecs.clear();
            tvecs.clear();
            for(int i = 0; i < imagePoints.size();i++)
            { 
                Mat rvec,tvec;
                cv::solvePnP(objectPoints[0], imagePoints[i], cameraMatrix,distCoeffs, rvec, tvec);
                rvecs.push_back(rvec);
                tvecs.push_back(tvec);
            }
            break;
        default:
            CV_Error(Error::StsBadArg, "Unknown Solve Method \n");
            break;
    }

    bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

    objectPoints.clear();
    objectPoints.resize(imagePoints.size(), newObjPoints);
    // 计算重投影误差
    totalAvgErr = computeReprojectionErrors(objectPoints, imagePoints, rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs);
    return ok;
}

int main()
{
    cv::Size boardSize(11, 8);
    // 标定板类型
    Pattern pattern = CHESSBOARD;

    //计算标定板位姿方法
    Solve_Board_Pose method = CALIBRATECAMERA;

    float squareSize = 35.0; // 棋盘格的尺寸；圆形标定板的圆心距，单位为mm
    float aspectRatio = 1;
    int winSize = 11;        // 窗口大小，用于提高角点精度

    // 存储图像路径的yml文件
    string inputFilename = "/home/duanziheng/hand_eye_cv/data1/calibration.yml"; // 图像放在同一路径下

    // 存放机械臂位姿的文件夹
    string poses_filepath_string = "/home/duanziheng/hand_eye_cv/data1/pose";
    boost::filesystem::path poses_filepath(poses_filepath_string);

    // 获取每张图像的路径
    vector<string> imageList;
    readStringList(samples::findFile(inputFilename), imageList);

    // 获取每个csv文件的路径
    vector<string> poses_filepath_list;
    retrieveFilesInDir(poses_filepath, poses_filepath_list, true);
    auto total_num_poses = poses_filepath_list.size();

    // 读取机械臂位姿
    vector<Mat> robot_poses_mat_vec(total_num_poses);    //创建一个大小为 total_num_poses的Mat型vector
    for (int i = 0; i < total_num_poses; ++i)
    {
        // 数据格式为：平移向量、欧拉角/四元数
        readPoseFromCSV(poses_filepath_list[i], robot_poses_mat_vec[i], ' ');
    }

    vector<Mat> robot_transform;
    vector<Mat> R_gripper2base;
    vector<Mat> t_gripper2base;
    Mat robot_R, robot_t;
    

    // 四元数->旋转矩阵，添加四元数判断 x,y,z,qw,qz,qy,qz
    if (robot_poses_mat_vec[1].total() == 7)
    {
        for (int i = 0; i < total_num_poses; ++i)
        {
            Mat transform = Mat::eye(4, 4, CV_64FC1);
            Mat temp = robot_poses_mat_vec[i].clone();
            Mat quan = temp({ 3,0,4,1 }); // 读取四元数

            // 四元数转换为旋转矩阵
            double w = quan.at<double>(0,0);
            double x = quan.at<double>(0,1);
            double y = quan.at<double>(0,2);
            double z = quan.at<double>(0,3);
            Eigen::Quaterniond q1(w, x, y, z);
            Eigen::Matrix3d R_tmp;
            R_tmp = q1.normalized().toRotationMatrix();
            cv::Mat rotation_temp;
            eigen2cv(R_tmp,rotation_temp);
            rotation_temp.copyTo(transform({ 0,0,3,3 }));
            
            // 存储平移向量
            transform({ 3,0,1,3 }) = temp({ 0,0,3,1 }).t();
            robot_transform.push_back(transform);

            // 变换矩阵拆分
            Transform2Rt(transform, robot_R, robot_t);
            
            // 对于眼在手外(eye to hand)，R、t需要求逆
            robot_R = robot_R.t();
            robot_t = -robot_R * robot_t;

            // 平移向量、旋转矩阵，用于手眼标定
            R_gripper2base.push_back(robot_R); // R_base_end
            t_gripper2base.push_back(robot_t); // t_base_end
        }
    }

    //判断是否为欧拉角  x,y,z rx,ry,rz
    else if(robot_poses_mat_vec[1].total() == 6)
    {
        // 欧拉角->旋转矩阵，R_base_end = Rz * Ry * Rx
        string sequence = "xyz";    // 欧拉角的存储与旋转顺序
        bool is_rad = true;         // 是否为弧度制
        if (true)
        {
            for (int i = 0; i < total_num_poses; ++i)
            {
                Mat transform = Mat::eye(4, 4, CV_64FC1);           //创建一个4X4的单位矩阵
                Mat temp = robot_poses_mat_vec[i].clone();
                Mat rotVec = temp({3, 0, 3, 1});                    // 读取欧拉角

                // 欧拉角转换为旋转矩阵
                Mat Grit = eulerAngleToRotateMatrix(rotVec, sequence, is_rad);     //返回得到一个旋转矩阵

                //存入旋转矩阵
                Grit.copyTo(transform({0, 0, 3, 3}));

                //存储平移向量
                transform({3, 0, 1, 3}) = temp({0, 0, 3, 1}).t();
                robot_transform.push_back(transform);

                // 变换矩阵拆分
                Transform2Rt(transform, robot_R, robot_t);

                // 对于眼在手外(eye to hand)，R、t需要求逆
                robot_R = robot_R.t();
                robot_t = -robot_R * robot_t;

                // 平移向量、旋转矩阵，用于手眼标定
                R_gripper2base.push_back(robot_R); // R_base_end
                t_gripper2base.push_back(robot_t); // t_base_end
            }
        }
    }
    cv::Size imageSize;
    vector<vector<cv::Point2f>> imagePoints; // 存储图片中检测到的角点
    int valid_num = 0;                       // 有效图像的数量
    int invalid_num = 0;                     // 无效图像的数量
    // 遍历每张图像
    for (auto &img : imageList)
    {
        cv::Mat view = cv::imread(img);      // 读取图像
        imshow("image",view);
        imageSize = view.size();
        cv::Mat viewGray;
        // 灰度化
        if (view.channels() == 3)
        {
            cvtColor(view, viewGray, COLOR_BGR2GRAY);
        } 
        else
        {
            viewGray = view.clone();
        }
        vector<cv::Point2f> point_buffer;
        // 检测角点
        
        //这一段代码服务于非对称圆形标定版
        bool found;
        cv::SimpleBlobDetector::Params params;
        params.minArea = 10;
        params.blobColor = 255;
        params.maxArea = 10000;
        params.minDistBetweenBlobs = 5;
        cv::Ptr<cv::SimpleBlobDetector> blob_detector = cv::SimpleBlobDetector::create(params);
        //

        switch(pattern)
        {
            // 棋盘格
            case CHESSBOARD:
                found = findChessboardCorners(view, boardSize, point_buffer,
                                              CALIB_CB_EXHAUSTIVE | CALIB_CB_ACCURACY | CALIB_CB_NORMALIZE_IMAGE);
                break;
            // 对称圆形
            case CIRCLES_GRID:
                found = findCirclesGrid(view,boardSize,point_buffer,CALIB_CB_SYMMETRIC_GRID,blob_detector);
                break;
            // 非对称圆形
            case ASYMMETRIC_CIRCLES_GRID:
                found = findCirclesGrid(view,boardSize,point_buffer,CALIB_CB_ASYMMETRIC_GRID,blob_detector);
                break;
            default:
                return fprintf( stderr, "Unknown pattern type\n" ), -1;
        }

        valid_num++;
        // 提高角点的坐标精度,亚像素精确化
        if (pattern == CHESSBOARD && found)
        {
            cv::cornerSubPix(viewGray, point_buffer, cv::Size(winSize, winSize),
                         cv::Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 100, 0.0001));
        }
        else if(!found)
        {
            invalid_num++;
            cout << "Invalid image is: " << valid_num << endl;
            continue;
        }

        cv::drawChessboardCorners(view, boardSize, cv::Mat(point_buffer), found);
       
        /*
        //显示棋盘格角点检测结果
        cv::namedWindow("image" + to_string(valid_num), cv::WINDOW_NORMAL);
        cv::resizeWindow("image" + to_string(valid_num), 1280, 900);
        cv::imshow("image" + to_string(valid_num), view);
        cv::waitKey(0);
        */

        // 存储角点
        imagePoints.push_back(point_buffer);
    }
    cv::destroyAllWindows();
    cout << "Invalid image number is: " << invalid_num << endl;
    if (valid_num != imageList.size())
    {
        cout << "Please remove invalid image and corresponding robot pose" << endl;
        return -1;
    }

    cv::Mat cameraMatrix, distCoeffs; // 存储相机内参，畸变系数
    vector<cv::Mat> rvecs, tvecs;     // 相机外参，用于后续手眼标定
    vector<float> reprojErrs;         // 重投影误差
    double totalAvgErr = 0;           // 平均重投影误差
    vector<cv::Point3f> newObjPoints;

    // 相机标定，参数：boardSize、squareSize、pattern
    bool ok = runCalibration(imagePoints, imageSize, boardSize, cameraMatrix, distCoeffs,
                             rvecs, tvecs, reprojErrs, newObjPoints, totalAvgErr, squareSize, pattern, method);
    printf("%s. avg projection error = %.7f\n", ok ? "Calibration succeeded" : "Calibration failed", totalAvgErr);

    // 判断相机数据和机械臂数据的数量是否一样
    if(rvecs.size() != total_num_poses)
    {
        cout << "The quantity of image data and robot pose data is different!" << endl;
        return -1;
    }

    // 旋转向量->旋转矩阵
    vector<Mat> camera_transform;
    vector<Mat> R_target2cam;
    vector<Mat> t_target2cam;
    Mat camera_R, camera_t;
    for (int i = 0; i < rvecs.size(); ++i)
    {
        Mat transform = Mat::eye(4, 4, CV_64FC1);
        Mat temp = rvecs[i].clone();
        cv::Rodrigues(temp, transform({0,0,3,3})); // 罗德里格斯公式

        // 存储平移向量，单位从毫米转换为米
        tvecs[i] = tvecs[i] * 0.001;
        tvecs[i].copyTo(transform({3,0,1,3}));
        camera_transform.push_back(transform);

        // 变换矩阵分解
        Transform2Rt(transform, camera_R, camera_t);

        // 用于手眼标定
        R_target2cam.push_back(camera_R); // R_camera_board
        t_target2cam.push_back(camera_t); // t_camera_board
    }

/*
    手眼标定，输入的参数是vector<Mat>类型的变量
    参数（输入）：R_base_end、t_base_end、R_camera_board、t_camera_board
    参数（输出）：R_end_camera、t_end_camera
    对于眼在手上可以直接输入，如上所示
    对于眼在手外，如下所所示
    输入参数：R_end_base、t_end_base、R_camera_board、t_camera_board
    输出参数：R_base_camera、t_base_camera
*/
    bool is_calibration = true;
    Eigen::Matrix4d T_base_camera;
    cv::Mat T_cam2gripper;
    cv::Mat R_cam2gripper = Mat(3, 3, CV_64FC1);
    cv::Mat t_cam2gripper = Mat(3, 1, CV_64FC1);
    if (is_calibration)
    {
        cout << "start hand_eye_calib" << endl;
        cv::calibrateHandEye(R_gripper2base, t_gripper2base, R_target2cam, t_target2cam,
                             R_cam2gripper, t_cam2gripper, CALIB_HAND_EYE_HORAUD);

        T_cam2gripper = R_t2Transform(R_cam2gripper, t_cam2gripper);
        cout << "T_cam2gripper: " << isRotatedMatrix(T_cam2gripper) << endl;
        cout << "hand eye calibration result is: " << endl << T_cam2gripper << endl;

        // 将旋转矩阵转化为轴角
        Eigen::Matrix3d r_out;
        cv2eigen(R_cam2gripper, r_out);
        Eigen::AngleAxisd rot_vector(r_out);
        Eigen::Vector3d rot_angle = rot_vector.axis() * rot_vector.angle();
        cout << "Angle is: " << rot_vector.angle() / M_PI * 180 << endl;
        cout << "Axis is: " << rot_vector.axis().transpose() << endl;
    }

    // 测试
    Eigen::Vector3d point(1,1,1);
    Eigen::Matrix3d rotation_CV;
    Eigen::Vector3d trans_CV;
    cv2eigen(R_cam2gripper, rotation_CV);
    cv2eigen(t_cam2gripper, trans_CV);
    Eigen::Vector3d target_CV = rotation_CV * point + trans_CV;

    Eigen::Matrix3d rotation_Mech;
    rotation_Mech << 0.0229893, -0.998503, -0.0496422,
                    -0.999736, -0.0229054, -0.00222696,
                     0.00108651, 0.0496802, -0.998765;
    Eigen::Vector3d trans_Mech(-1.2092, -0.186483, 1.33552);
    Eigen::Vector3d target_Mech = rotation_Mech * point + trans_Mech;

    cout << "target_CV is: " << target_CV.transpose() << endl;
    cout << "target_Mech is: " << target_Mech.transpose() << endl;

    Eigen::Vector3d error = target_Mech - target_CV;
    cout << "error is: " << error.norm() << endl;

    // 计算rmse
    double rmse = std::sqrt(error.array().pow(2).mean());
    cout << "rmse is: " << rmse << endl;

    return 0;
}
