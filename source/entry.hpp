/**
 * @file entry.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

extern "C"
{
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/sysinfo.h>
    #include <signal.h>
}

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <Eigen/Dense>
#include <random>
#include <unordered_map>
#include <thread>
#include <cmath>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#include "old_src/json.hpp"

#include "glog/logging.h"

int test_business();

int test_asio();