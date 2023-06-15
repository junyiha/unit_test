/**
 * @file test_polymorphism.cc
 * @author your name (you@domain.com)
 * @brief 测试多态特性
 * @version 0.1
 * @date 2023-06-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <memory>

// 基类
class Animal {
public:
    virtual void sound() {
        std::cout << "动物发出声音" << std::endl;
    }
};

// 派生类1
class Dog : public Animal {
public:
    void sound() override {
        std::cout << "狗在汪汪叫" << std::endl;
    }
};

// 派生类2
class Cat : public Animal {
public:
    void sound() override {
        std::cout << "猫在喵喵叫" << std::endl;
    }
};

class Tmp
{

public:
    Tmp()
    {
        a = std::make_shared<Cat>();
    }

public:
    std::shared_ptr<Animal> a;
};

int main() {
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();
    std::unique_ptr<Animal> a(new Dog);

    a->sound();

    Tmp t;
    t.a->sound();

    animal1->sound();  // 输出：狗在汪汪叫
    animal2->sound();  // 输出：猫在喵喵叫

    delete animal1;
    delete animal2;

    return 0;
}