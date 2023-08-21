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

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/cloud_viewer.h>

#include <pcl/point_cloud.h>

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

int test_load_pcd_file()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("data/pcl/VSLAMRGBD.pcd", *cloud);

    pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
    voxel_filter.setInputCloud(cloud);
    voxel_filter.setLeafSize(0.01f, 0.01f, 0.01f);
    pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    voxel_filter.filter(*filtered_cloud);

    pcl::visualization::CloudViewer viewer("Point Cloud Viewer");
    viewer.showCloud(filtered_cloud);
    while (!viewer.wasStopped()) {}

    return 0;
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
            test_load_pcd_file();
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