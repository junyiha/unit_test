/**
 * @file TYThread.hpp
 * @author your name (you@domain.com)
 * @brief 图漾线程
 * @version 0.1
 * @date 2023-08-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#ifndef XYZ_TYThread_HPP_
#define XYZ_TYThread_HPP_

#include <pthread.h>

class TYThreadImpl;

class TYThread
{
public:
    typedef void *(*Callback_t)(void *);

    TYThread();
    ~TYThread();

    int create(Callback_t cb, void *arg);
    int destroy();

private:
    TYThreadImpl *impl;
};

class TYThreadImpl
{
public:
    TYThreadImpl() {}
    int create(TYThread::Callback_t cb, void *arg)
    {
        int ret = pthread_create(&_thread, NULL, cb, arg);
        return ret;
    }
    int destroy()
    {
        pthread_join(_thread, NULL);
        return 0;
    }

private:
    pthread_t _thread;
};

inline TYThread::TYThread()
{
    impl = new TYThreadImpl();
}

inline TYThread::~TYThread()
{
    delete impl;
    impl = NULL;
}

inline int TYThread::create(Callback_t cb, void *arg)
{
    return impl->create(cb, arg);
}

inline int TYThread::destroy()
{
    return impl->destroy();
}

#endif