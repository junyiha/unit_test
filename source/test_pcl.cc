/**
 * @file test_pcl.cc
 * @author your name (you@domain.com)
 * @brief PCL(Point Cloud Library) unit test
 * @version 0.1
 * @date 2023-08-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <string>

#ifdef OPEN_VIEWER
#include <pcl/visualization/cloud_viewer.h>
#endif

#include <pcl/point_cloud.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/surface/surfel_smoothing.h>
#include <pcl/surface/mls.h>
#include <pcl/surface/gp3.h>
#include <pcl/surface/impl/mls.hpp>
#include <pcl/filters/passthrough.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>                     //体素滤波器头文件
#include <pcl/filters/statistical_outlier_removal.h>    //统计滤波头文件
#include <pcl/common/transforms.h>
#include <pcl/common/projection_matrix.h>
#include <pcl/features/moment_of_inertia_estimation.h>  //提取点云特征

static void Help()
{
    std::string help_info =
    R"(
        ./test_pcl.exe  PCL(Point Cloud Library) unit test

        --help
        --test-load-pcd-file
        --test-pcl-cloud
    )";

    std::cerr << help_info << std::endl;
}

#ifdef OPEN_VIEWER
int test_load_pcd_file()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("/mnt/remote/190-mnt/zhangjunyi/workspace/vca_dir/master/video_process/build/data/cloud-computer-test-aaa.pcd", *cloud);

    pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
    voxel_filter.setInputCloud(cloud);
    voxel_filter.setLeafSize(0.01f, 0.01f, 0.01f);
    pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    voxel_filter.filter(*filtered_cloud);

    pcl::visualization::CloudViewer viewer("Point Cloud Viewer");
    // viewer.showCloud(cloud);
    viewer.showCloud(filtered_cloud);
    while (!viewer.wasStopped()) {}

    return 0;
}
#endif
void PointCloudComputer(pcl::PointCloud<pcl::PointXYZ>::Ptr pointCloud)
{
    // 统计滤波器 (移除离群点)
    pcl::VoxelGrid<pcl::PointXYZ> VoxlFilter;                          // 下采样 VoxelGrid 滤波对象
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> statisFilter;        // 统计滤波器 (移除离群点)
    pcl::MomentOfInertiaEstimation<pcl::PointXYZ> feature_extractor;   // 创建特征提取类

    // pcl::io::savePCDFile("/tmp/data/cloud-computer-test-0.pcd", *pointCloud);
    //体素滤波
    pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("/tmp/data/cloud-computer-test-0.pcd", *input_cloud);
    VoxlFilter.setInputCloud(input_cloud);
    VoxlFilter.setLeafSize(0.005f, 0.005f, 0.005f);
    // VoxlFilter.setLeafSize(0.002f, 0.002f, 0.002f);
    // VoxlFilter.filter(*pointCloud);  // 段错误
    VoxlFilter.filter(*output_cloud);  // 段错误
    // pcl::io::savePCDFile("/mnt/remote/190-mnt/zhangjunyi/workspace/vca_dir/master/video_process/build/data/cloud-computer-test-bbb.pcd", *output_cloud);
    // return;

    //统计滤波去离群点
    statisFilter.setInputCloud(output_cloud);
    statisFilter.setMeanK(50);              // 对每个点分析的临近点个数设为50
    statisFilter.setStddevMulThresh(2.0);   // 将标准差倍数设为1，意味着一个点的距离超出平均距离1个标准差以上，就会被标记为离群点，并被移除。
    statisFilter.filter(*output_cloud);

    //设置要计算的点云
    feature_extractor.setInputCloud(output_cloud);  //设置要计算的点云
    feature_extractor.compute(); //开始计算

    std::vector <float> moment_of_inertia;  //惯性矩 ;  创建一个惯性矩 浮点数 数组
    std::vector <float> eccentricity;   // 主轴
    pcl::PointXYZ min_point_AABB;
    pcl::PointXYZ max_point_AABB;
    pcl::PointXYZ min_point_OBB;
    pcl::PointXYZ max_point_OBB;
    pcl::PointXYZ position_OBB;
    Eigen::Matrix3f rotational_matrix_OBB;  //矩阵，旋转变换
    float major_value, middle_value, minor_value; //浮点数
    Eigen::Vector3f major_vector, middle_vector, minor_vector; // 分别表示 x轴的三个向量，y轴的三个向量，z轴的三个向量
    Eigen::Vector3f mass_center;   //质心

    //计算输入点云的所有几何属性值
    feature_extractor.getMomentOfInertia(moment_of_inertia);  //计算点云的惯性矩阵
    feature_extractor.getEccentricity(eccentricity);    //计算点云的离心率
    feature_extractor.getAABB(min_point_AABB, max_point_AABB);
    feature_extractor.getOBB(min_point_OBB, max_point_OBB, position_OBB, rotational_matrix_OBB);
    feature_extractor.getEigenValues(major_value, middle_value, minor_value);
    feature_extractor.getEigenVectors(major_vector, middle_vector, minor_vector);
    feature_extractor.getMassCenter(mass_center);

    Eigen::Vector3f position(position_OBB.x, position_OBB.y, position_OBB.z);// 赋值给向量对象 position
    Eigen::Quaternionf quat(rotational_matrix_OBB);  //构造一个四元数对象; 输入的是旋转矩阵

    //position obb-box的中心点坐标,x y z ;
    std::cerr << "obbxyz: " << position << "\n"
                << "width: " << max_point_OBB.x -min_point_OBB.x << "\n"
                << "height: " << max_point_OBB.y - min_point_OBB.y << "\n"
                << "depth: " << max_point_OBB.z - min_point_OBB.z << "\n"
                << std::endl;

    std::cerr << "obb包围盒法向量"
                << minor_vector[0] << " , "
                << minor_vector[1] << " , "
                << minor_vector[2]
                << std::endl;     // 包围盒的法向量

    // 相机坐标系中的位姿，转换到机械臂的基坐标中
    Eigen::Vector3d camera_point(position[0] / 1000.0,position[1] / 1000.0, position[2] / 1000.0);
    Eigen::Vector3d camera_dir(minor_vector[0], minor_vector[1], minor_vector[2]);
    Eigen::Vector3d camera_base(0.0, 0.0, 1.0);
    Eigen::Matrix3d rotMatrix = Eigen::Quaterniond::FromTwoVectors(camera_base, camera_dir).toRotationMatrix();

    Eigen::Isometry3d T_camera = Eigen::Isometry3d::Identity();
    T_camera.rotate(rotMatrix);
    T_camera.pretranslate(camera_point);

    // 标定数据
    Eigen::Matrix3d R_base_camera;
    Eigen::Vector3d t_base_camera;
    R_base_camera << 0.00618494, -0.999793, 0.0193524,
                        -0.999214,-0.00693682,-0.0390261,
                        0.0391521,-0.0190958,-0.999051;
    t_base_camera << 0.554424,0.0134749,1.46398;

    Eigen::Isometry3d T_base_camera = Eigen::Isometry3d::Identity();
    T_base_camera.rotate(R_base_camera);
    T_base_camera.pretranslate(t_base_camera);

    Eigen::Vector3d euler(-M_PI/2,0,0);
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix = Eigen::AngleAxisd(euler[0], Eigen::Vector3d::UnitZ()) *
                        Eigen::AngleAxisd(euler[1], Eigen::Vector3d::UnitY()) *
                        Eigen::AngleAxisd(euler[2], Eigen::Vector3d::UnitX());
    Eigen::Vector3d zero_translation(0.0,0.0,0.0);
    Eigen::Isometry3d T_base = Eigen::Isometry3d::Identity();
    T_base.rotate(rotation_matrix);
    T_base.pretranslate(zero_translation);

    Eigen::Isometry3d T_target = T_base * T_base_camera * T_camera;

    Eigen::Matrix3d R_target = T_target.rotation();
    Eigen::Vector3d t_target = T_target.translation();
    Eigen::AngleAxisd rotation_vector;
    rotation_vector.fromRotationMatrix(R_target);

    std::cerr << "x y z is: " << t_target.transpose() << "\n"
                << "AngleAxisd is: " << rotation_vector.angle() * rotation_vector.axis().transpose() << "\n"
                << std::endl;
}


int test_pcl_load_pcd_file()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    // std::string path = "/mnt/remote/190-mnt/zhangjunyi/workspace/vca_dir/master/video_process/build/data/cloud-computer-test-aaa.pcd";
    std::string path = "/tmp/data/cloud-computer-test-0.pcd";
    pcl::io::loadPCDFile(path, *cloud);

    pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
    voxel_filter.setInputCloud(cloud);
    voxel_filter.setLeafSize(0.005f, 0.005f, 0.005f);
    pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    voxel_filter.filter(*output_cloud);

    // pcl::io::savePCDFile("/mnt/remote/190-mnt/zhangjunyi/workspace/vca_dir/master/video_process/build/data/cloud-computer-test-bbb.pcd", *output_cloud);
    pcl::io::savePCDFile("data/pcl/cloud-computer-test-bbb.pcd", *output_cloud);
        // 统计滤波器 (移除离群点)
    pcl::VoxelGrid<pcl::PointXYZ> VoxlFilter;                          // 下采样 VoxelGrid 滤波对象
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> statisFilter;        // 统计滤波器 (移除离群点)
    pcl::MomentOfInertiaEstimation<pcl::PointXYZ> feature_extractor;   // 创建特征提取类

    //统计滤波去离群点
    statisFilter.setInputCloud(output_cloud);
    statisFilter.setMeanK(50);              // 对每个点分析的临近点个数设为50
    statisFilter.setStddevMulThresh(2.0);   // 将标准差倍数设为1，意味着一个点的距离超出平均距离1个标准差以上，就会被标记为离群点，并被移除。
    statisFilter.filter(*output_cloud);
    //设置要计算的点云
    feature_extractor.setInputCloud(output_cloud);  //设置要计算的点云
    feature_extractor.compute(); //开始计算

    std::vector <float> moment_of_inertia;  //惯性矩 ;  创建一个惯性矩 浮点数 数组
    std::vector <float> eccentricity;   // 主轴
    pcl::PointXYZ min_point_AABB;
    pcl::PointXYZ max_point_AABB;
    pcl::PointXYZ min_point_OBB;
    pcl::PointXYZ max_point_OBB;
    pcl::PointXYZ position_OBB;
    Eigen::Matrix3f rotational_matrix_OBB;  //矩阵，旋转变换
    float major_value, middle_value, minor_value; //浮点数
    Eigen::Vector3f major_vector, middle_vector, minor_vector; // 分别表示 x轴的三个向量，y轴的三个向量，z轴的三个向量
    Eigen::Vector3f mass_center;   //质心

    //计算输入点云的所有几何属性值
    feature_extractor.getMomentOfInertia(moment_of_inertia);  //计算点云的惯性矩阵
    feature_extractor.getEccentricity(eccentricity);    //计算点云的离心率
    feature_extractor.getAABB(min_point_AABB, max_point_AABB);
    feature_extractor.getOBB(min_point_OBB, max_point_OBB, position_OBB, rotational_matrix_OBB);
    feature_extractor.getEigenValues(major_value, middle_value, minor_value);
    feature_extractor.getEigenVectors(major_vector, middle_vector, minor_vector);
    feature_extractor.getMassCenter(mass_center);

    Eigen::Vector3f position(position_OBB.x, position_OBB.y, position_OBB.z);// 赋值给向量对象 position
    Eigen::Quaternionf quat(rotational_matrix_OBB);  //构造一个四元数对象; 输入的是旋转矩阵

    //position obb-box的中心点坐标,x y z ;
    std::cerr << "obbxyz: " << position << "\n"
                << "width: " << max_point_OBB.x -min_point_OBB.x << "\n"
                << "height: " << max_point_OBB.y - min_point_OBB.y << "\n"
                << "depth: " << max_point_OBB.z - min_point_OBB.z << "\n"
                << std::endl;

    std::cerr << "obb包围盒法向量"
                << minor_vector[0] << " , "
                << minor_vector[1] << " , "
                << minor_vector[2]
                << std::endl;     // 包围盒的法向量

    return 0;
}

int test_pcl_PointCloudCompute()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr(new pcl::PointCloud<pcl::PointXYZ>);
    PointCloudComputer(cloud_ptr);
}

int test_pcl_cloud()
{
    pcl::PointCloud<pcl::PointXYZ> cloud;

    pcl::PointXYZ point;
    point.x = 1.0;
    point.y = 2.0;
    point.z = 3.0;

    cloud.push_back(point);

    for (const auto& p : cloud.points) {
        std::cout << "Point: (" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg;
    for (int col{1}; col < argc; col++)
    {
        arg = argv[col];
        if (arg == "--test-load-pcd-file")
        {
#ifdef OPEN_VIEWER
            test_load_pcd_file();
#endif
        }
        else if (arg == "--test-pcl-PointCloudCompute")
        {
            test_pcl_PointCloudCompute();
        }
        else if (arg == "--test-pcl-load-pcd-file")
        {
            test_pcl_load_pcd_file();
        }
        else if (arg == "--test-pcl-cloud")
        {
            test_pcl_cloud();
        }
        else if (arg == "--help")
        {
            Help();
        }
        else
        {
            Help();
        }
    }
}