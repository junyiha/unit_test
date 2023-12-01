/**
 * @file protocol.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <vector>
#include <string>

class Message
{
public:
    std::string first_layer;
    std::string second_layer;
    std::string third_layer;
    std::vector<std::string> message_pool;

public:
    Message()
    {
        first_layer = "";
        second_layer = "";
        third_layer = "";
        message_pool.resize(0);
    }
    Message(const Message& other)
    {
        first_layer = other.first_layer;
        second_layer = other.second_layer;
        third_layer = other.third_layer;
        message_pool = other.message_pool;
    }
    ~Message()
    {
        first_layer = "";
        second_layer = "";
        third_layer = "";
        message_pool.clear();
    }

public:
    Message& operator=(const Message& other)
    {
        if (this != &other)
        {
            first_layer = other.first_layer;
            second_layer = other.second_layer;
            third_layer = other.third_layer;
            message_pool = other.message_pool;
        }

        return *this;
    }
};