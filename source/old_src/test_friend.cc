/**
 * @file test_friend.cc
 * @author your name (you@domain.com)
 * @brief 友元单元测试
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>

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

int main() {
    MyClass obj;
    FriendFunction(obj);

    FriendClass friendObj;
    friendObj.AccessPrivateData(obj);

    return 0;
}
