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
#include <string>

static void Help()
{
    std::string help_info {R"(
        ./test_polymorphism.exe  多态性单元测试

        --help  帮助信息
        --test-polymorphism-1  第一个单元测试
    )"};

    std::cerr << help_info << std::endl;
}

// 基类
class Animal
{
public:
    virtual void sound()
    {
        std::cout << "动物发出声音" << std::endl;
    }
};

// 派生类1
class Dog : public Animal
{
public:
    void sound() override
    {
        std::cout << "狗在汪汪叫" << std::endl;
    }
};

// 派生类2
class Cat : public Animal
{
public:
    void sound() override
    {
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

int test_polymorphism_1()
{
    Animal *animal1 = new Dog();
    Animal *animal2 = new Cat();
    std::unique_ptr<Animal> a(new Dog);

    a->sound();

    Tmp t;
    t.a->sound();

    animal1->sound(); // 输出：狗在汪汪叫
    animal2->sound(); // 输出：猫在喵喵叫

    delete animal1;
    delete animal2;

    return 0;
}

class Robots
{
public:
    virtual void MoveTo() = 0;
};

class Beijing final : public Robots
{
public:
    virtual void MoveTo() override
    {
        std::cerr << "beijing robot move to" << std::endl;
    }
};

class Wuxi final : public Robots
{
public:
    virtual void MoveTo() override
    {
        std::cerr << "wuxi robot move to" << std::endl;
    }
};

int test_polymorphism_robot()
{
    // Robots *robot = new Beijing();
    Robots *robot = new Wuxi();

    robot->MoveTo();

    delete robot;
    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg;
    for (int col{1}; col < argc; col++)
    {
        arg = argv[col];
        if (arg == "--help" || arg == "-h")
        {
            Help();
        }
        else if (arg == "--test-polymorphism-1")
        {
            test_polymorphism_1();
        }
        else if (arg == "--test-polymorphism-robot")
        {
            test_polymorphism_robot();
        }
        else
        {
            Help();
        }
    }

    return 0;
}