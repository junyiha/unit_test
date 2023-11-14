/**
 * @file test_eigen.cc
 * @author your name (you@domain.com)
 * @brief Eigen 工具的单元测试
 * @version 0.1
 * @date 2023-07-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <Eigen/Dense>
#include <string>

static void Help()
{
    std::string help_info =
    R"(
        ./test_eigen.exe

        --help
        --test-eigen-hello
        --test-eigen-vector3f
    )";

    std::cerr << help_info << std::endl;
}

int test_eigen_hello() {
    // 创建矩阵
    Eigen::Matrix3f A;
    A << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    // 创建向量
    Eigen::Vector3f b(1, 2, 3);

    // 解线性方程 Ax = b
    Eigen::Vector3f x = A.lu().solve(b);

    // 输出结果
    std::cout << "Solution:\n" << x << std::endl;

    // 计算特征值和特征向量
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigensolver(A);
    if (eigensolver.info() != Eigen::Success) {
        std::cout << "Failed to compute eigenvalues!" << std::endl;
        return 1;
    }
    std::cout << "Eigenvalues:\n" << eigensolver.eigenvalues() << std::endl;
    std::cout << "Eigenvectors:\n" << eigensolver.eigenvectors() << std::endl;

    return 0;
}

int test_eigen_vector3f()
{
    // 声明两个三维浮点数向量
    Eigen::Vector3f v1(1.0, 2.0, 3.0);
    Eigen::Vector3f v2(4.0, 5.0, 6.0);

    // 向量加法
    Eigen::Vector3f sum = v1 + v2;

    // 向量点积
    float dotProduct = v1.dot(v2);

    // 向量叉积
    Eigen::Vector3f crossProduct = v1.cross(v2);

    // 打印结果
    std::cout << "v1: " << v1.transpose() << std::endl;
    std::cout << "v2: " << v2.transpose() << std::endl;
    std::cout << "Sum: " << sum.transpose() << std::endl;
    std::cout << "Dot product: " << dotProduct << std::endl;
    std::cout << "Cross product: " << crossProduct.transpose() << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg;
    for (int row{1}; row < argc; row++)
    {
        arg = argv[row];
        if (arg == "--test-eigen-hello")
        {
            test_eigen_hello();
        }
        else if (arg == "--test-eigen-vector3f")
        {
            test_eigen_vector3f();
        }
        else
        {
            Help();
        }
    }

    return 0;
}