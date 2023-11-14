/**
 * @file test_anything.cc
 * @author your name (you@domain.com)
 * @brief 为分类的单元测试
 * @version 0.1
 * @date 2023-11-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>

const int ALERT_INTERVAL_SECONDS = 3;  // 告警时间间隔为60秒
std::time_t lastAlertTime = 0;  // 上次告警时间的初始值为0

void processRequest()
{
    // 模拟请求处理过程
    bool hasError = true;  // 假设出现异常情况

    if (hasError)
    {
        std::time_t currentTime = std::time(nullptr);  // 获取当前时间
        if (currentTime - lastAlertTime > ALERT_INTERVAL_SECONDS)
        {
            // 满足告警条件，进行告警操作
            std::cerr << "time: " << std::time(nullptr) << std::endl;
            std::cout << "Alert: An error occurred!" << std::endl;

            // 更新上次告警时间为当前时间
            lastAlertTime = currentTime;
        }
    }
}

#include <cstdio>
#include <cstdlib>

int test_asan()
{
    int *buffer = (int *)malloc(sizeof(int) * 10);
    buffer[10] = 42; // 内存越界访问

    free(buffer);
    return 0;
}

int test_ascii()
{
    int num = 4;
    // char char_num = static_cast<char>(num);
    std::string tmp_str;
    tmp_str = std::to_string(num);
    char char_num = tmp_str[0];
    // char char_num = (char)(num);


    // char ch = 'A';
    char ch = '4';
    int ascii = static_cast<int>(ch);
    
    std::cout << "Character: " << ch << std::endl;
    std::cout << "ASCII Value: " << ascii << std::endl;
    
    return 0;
}

#include <Eigen/Dense>

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

class MyClass {
private:
    int privateData;

public:
    MyClass() : privateData(0) {}

    // 声明友元函数
    friend void FriendFunction(const MyClass& obj);

    // 声明友元类
    friend class FriendClass;
};

// 友元函数的定义
void FriendFunction(const MyClass& obj) {
    std::cout << "Friend function accessing private data: " << obj.privateData << std::endl;
}

// 友元类的定义
class FriendClass {
public:
    void AccessPrivateData(const MyClass& obj) {
        std::cout << "Friend class accessing private data: " << obj.privateData << std::endl;
    }
};

extern "C"
{
    #include <sys/types.h>
    #include <sys/ipc.h>
}

int test_ftok()
{
    key_t key = ftok("path/to/my/directory/share_memory", 1);
    key_t key2 = ftok("path/to/my/directory/share_memory", 1);
    
    if (key == -1) {
        perror("ftok");
        return 1;
    }
    if (key2 == -1) {
        perror("ftok");
        return 1;
    }

    printf("Generated key: %d\n", key);
    printf("Generated key: %d\n", key2);
    
    return 0;
}

#include <chrono>

// 要测试运行时间的函数
void myFunction()
{
    // 在这里添加你的函数逻辑
    for (int i = 0; i < 1000000; ++i)
    {
        // 执行一些操作
    }
}

int x86_time()
{
    // 获取当前时间点
    auto startTime = std::chrono::high_resolution_clock::now();

    // 调用要测试的函数
    myFunction();

    // 获取当前时间点
    auto endTime = std::chrono::high_resolution_clock::now();

    // 计算时间差
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // 输出结果
    std::cout << "函数运行时间： " << duration.count() << " 毫秒" << std::endl;

    return 0;
}

int arm_time()
{
    // 获取当前时间点
    auto startTime = std::chrono::steady_clock::now();

    // 调用要测试的函数
    myFunction();

    // 获取当前时间点
    auto endTime = std::chrono::steady_clock::now();

    // 计算时间差
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // 输出结果
    std::cout << "函数运行时间： " << duration.count() << " 毫秒" << std::endl;

    return 0;
}

#include <random>

std::string generateRandomMixedString(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);

    std::string randomString;
    randomString.reserve(size);

    for (int i = 0; i < size; ++i) 
    {
        int choice = dist(gen);
        if (choice == 0) 
        {
            // 生成数字字符
            std::uniform_int_distribution<int> numDist('0', '9');
            randomString.push_back(static_cast<char>(numDist(gen)));
        } 
        // else if (choice == 1) 
        // {
        //     // 生成大写字母字符
        //     std::uniform_int_distribution<int> upperDist('A', 'Z');
        //     randomString.push_back(static_cast<char>(upperDist(gen)));
        // } 
        else 
        {
            // 生成小写字母字符
            std::uniform_int_distribution<int> lowerDist('a', 'z');
            randomString.push_back(static_cast<char>(lowerDist(gen)));
        }
    }

    return randomString;
}

extern "C"
{
    #include <sys/sysinfo.h>
}

int GetMemInfo()
{
    int ret;
    struct sysinfo sys_info {};

    ret = sysinfo(&sys_info);
    if (ret == -1)
    {
        std::cerr << "Failed to get system information" << std::endl;
        return -1;
    }

    std::size_t total_memory = sys_info.totalram / 1024 / 1024;
    std::size_t free_memory = sys_info.freeram / 1024 / 1024;
    std::size_t used_memory = total_memory - free_memory / 1024 / 1024;

    std::cerr << "total memory: " << total_memory << " MB" << std::endl;
    std::cerr << "free memory: " << free_memory << " MB" << std::endl;
    std::cerr << "used memory: " << used_memory << " MB" << std::endl;
    return 0;
}

#include <unordered_map>

int test_hashmap_1()
{
    // 创建一个哈希表
    std::unordered_map<std::string, int> hashMap;

    // 插入键值对
    hashMap["Alice"] = 25;
    hashMap["Bob"] = 30;

    // 查找键的值
    if (hashMap.find("Alice") != hashMap.end())
    {
        std::cout << "Alice's age is " << hashMap["Alice"] << std::endl;
    }
    else
    {
        std::cout << "Alice not found in the map." << std::endl;
    }

    // 删除键值对
    hashMap.erase("Bob");

    // 遍历哈希表
    for (const auto &pair : hashMap)
    {
        std::cout << pair.first << "'s age is " << pair.second << std::endl;
    }

    return 0;
}

extern "C"
{
    #include <unistd.h>
    #include <signal.h>
}

int test_kill_process()
{
    pid_t pid = 13509;  // 要杀死的进程的PID

    // 发送SIGKILL信号来终止指定的进程
    if (kill(pid, SIGKILL) == 0) {
        std::cout << "进程已成功终止" << std::endl;
    } else {
        std::cerr << "无法终止进程" << std::endl;
    }

    return 0;
}

#include <thread>

int test_lambda()
{
    std::string str{"hahahahah"};
    std::string str2{"aaaaa"};
    int x {999};
    auto lambda = [&](int in)
    {
        int index {0};
        while (true)
        {
            if (index > 10)
                break;
            std::cerr << "index: " << index << "\n"
                      << "hello world" << "\n"
                      << str << "\n"
                      << str2 << "\n"
                      << in << "\n"
                      << std::endl;
            sleep(1);
            index++;
        }
    };
    std::thread tmp;
    tmp = std::thread(lambda, x);
    // t.join();
    if (tmp.joinable())
    {
        tmp.join();
    }
    return 0;
}

#include <cmath>

int test_ceil()
{
    double num = 12.34;
    double result = ceil(num);

    printf("Original Number: %.2f\n", num);
    printf("Ceil Value: %.2f\n", result);

    return 0;
}

int test_marco()
{
    printf("date: %s \n", __DATE__);
    printf("date: %s \n", __TIME__);
    printf("date: %s \n", __FILE__);
    printf("date: %d \n", __LINE__);
    printf("date: %d \n", __STDC__);

    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "")
        {

        }
        else if (arg == "--test-marco")
        {
            test_marco();
        }
        else if (arg == "--test-ceil")
        {
            test_ceil();
        }
        else if (arg == "--test-hashmap-1")
        {
            test_hashmap_1();
        }
        else if (arg == "--test-get-memery-info")
        {
            GetMemInfo();
        }
        else if (arg == "--test-generate-random-id")
        {
            generateRandomMixedString(5);
        }
        else if (arg == "--test-eigen-hello")
        {
            test_eigen_hello();
        }
        else if (arg == "--test-eigen-vector3f")
        {
            test_eigen_vector3f();
        }
        else if (arg == "--test-ascii")
        {
            test_ascii();
        }
        else if (arg == "--test-asan")
        {
            test_asan();
        }
        else if (arg == "--process-request")
        {
            processRequest();
        }
        else 
        {

        }
    }

    return 0;
}