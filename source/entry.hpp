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
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    #include <sys/poll.h>
    #include <arpa/inet.h>
    #include <signal.h>
    #include <dirent.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <netinet/in.h>
}

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <random>
#include <unordered_map>
#include <thread>
#include <memory>

#include <Eigen/Dense>

#include "protocol.hpp"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#include "old_src/json.hpp"

#include "glog/logging.h"

int test_business(Message& message);

int test_asio(Message& message);

int test_anything(Message& message);

int test_network(Message& message);

///////////////////////////////////////////////////////////////

/**
 * @brief Get the dir and file from path object
 * 
 * @param path 
 * @param directorys 
 * @param files 
 * @return int 1 success | 0 fail | other unknown
 */
int get_dir_and_file_from_path(const std::string path, std::vector<std::string>& directorys, std::vector<std::string>& files);

/**
 * @brief using recursive method to obtain parameters
 * 
 * @param path 
 * @param fields 
 */
void ExtractFields(const std::string& path, std::vector<std::string>& fields);