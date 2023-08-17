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

private:
    std::vector<std::string> m_str_arr;
};

class Camera : public Base
{

};

class Detector : public Base
{

};

int main()
{
    Camera camera;
    Detector detector;
    std::string str;

    camera.Enqueue("hahahah");
    detector.Get(str);
    std::cerr << "str: " << str << std::endl;

    return 0;
}