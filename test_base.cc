/**
 * @file test_base.cc
 * @author your name (you@domain.com)
 * @brief 测试父类 继承类
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string>
#include <iostream>
#include <vector>

static void Help()
{
    std::string info;

    info = R"sss(
        --help 
        --test-queue
        --test-static-member
    )sss";
}

class Base
{
public:
    Base()
    {
        m_str_arr.resize(3);
    }
    virtual ~Base()
    {

    }

public:
    void Enqueue(std::string in)
    {
        if (m_str_arr.size() > 2)
        {
            m_str_arr.pop_back();
        }

        m_str_arr.push_back(in);
    }
    void Get(std::string &out)
    {
        // out = m_str_arr.back();
        out = m_str_arr.front();
    }

    static void UpdateConfig(std::string in)
    {
        m_config = in;
    }

    static std::string m_config;
private:
    std::vector<std::string> m_str_arr;
};

class Camera : public Base
{

};

class Detector : public Base
{

};

std::string Base::m_config = "one";

int test_queue()
{
    Camera camera;
    Detector detector;
    std::string str;

    camera.Enqueue("hahahah");
    detector.Get(str);
    std::cerr << "str: " << str << std::endl;

    return 0;
}

int test_static_member()
{
    Camera camera;
    Detector detector;

    camera.UpdateConfig("two");
    Base::m_config = "three";
    

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg;
    for (int i = 1; i < argc; i++)
    {
        arg = argv[i];
        if (arg == "--test-queue")
        {
            test_queue();
        }
        else if (arg == "--test-static-member")
        {
            test_static_member();
        }
        else 
        {
            Help();
        }
    }

    return 0;
}