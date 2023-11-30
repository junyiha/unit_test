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

#include "boost/log/core.hpp"
#include "boost/log/trivial.hpp"
#include "boost/log/expressions.hpp"
#include "boost/log/sinks/text_file_backend.hpp"
#include "boost/log/utility/setup/file.hpp"
#include "boost/log/utility/setup/common_attributes.hpp"
#include "boost/log/sources/severity_logger.hpp"
#include "boost/log/sources/record_ostream.hpp"
#include "boost/asio.hpp"
#include "boost/beast.hpp"

#include "old_src/json.hpp"

#include "glog/logging.h"

int test_business();