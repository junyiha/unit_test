// #include <iostream>

// class MyClass {
// public:
//     void memberFunction(int x) {
//         std::cout << "Member function called with value: " << x << std::endl;
//     }
// };

// // 回调函数
// void callback(int x, MyClass* obj, void (MyClass::*memberFunc)(int)) {
//     (obj->*memberFunc)(x);  // 调用对象的成员函数
// }

// int main() {
//     MyClass obj;

//     // 将对象指针和成员函数指针传递给回调函数
//     callback(42, &obj, &MyClass::memberFunction);

//     return 0;
// }

#include <iostream>
#include <functional>

class MyClass {
public:
    void memberFunction(int x) {
        std::cout << "Member function called with value: " << x << std::endl;
    }
};

int main() {
    MyClass obj;

    // 使用 std::function 和 std::bind 封装成员函数和对象实例
    std::function<void(int)> callback = std::bind(&MyClass::memberFunction, &obj, std::placeholders::_1);

    // 调用回调函数
    callback(42);

    return 0;
}
