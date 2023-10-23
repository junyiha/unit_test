/**
 * @file BaseIndex.hpp
 * @author your name (you@domain.com)
 * @brief 维护索引的基类，为生产生类和消费者类提供同一对外接口
 * @version 0.1
 * @date 2023-06-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <iostream>

class BaseIndex 
{
public:
    using EnumRet_t = enum 
    {
        RET_ERR = -1,
        RET_OK = 0
    };

public:
    virtual void GetFileName(std::string &out) {}
    virtual int SetFileName(std::string &in) {}
    virtual int Open() {}
    virtual void Close() {}
    virtual int ReadIndex(std::size_t &out) {}
    virtual int WriteIndex(std::size_t &in) {}

public:
    BaseIndex() = default;
    virtual ~BaseIndex() = default;
};