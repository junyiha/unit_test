/**
 * @file mnc_logger.hpp
 * @author your name (you@domain.com)
 * @brief 日志类，用于日志数据的管理
 * @version 0.1
 * @date 2023-05-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <sys/stat.h>
#include <cassert>

// 日志类
class Logger 
{
public:
    using EnumLoggerRet_t = enum 
    {
        RET_ERR = -1,
        RET_OK = 0
    };

public:
    Logger() = default;
    Logger(const std::string& filename) : logfile_(filename, std::ios::app) {}

    void OpenFile(const std::string &filename);
    void OpenFile(const std::string &dir_path, const std::string &filename);
    void CloseFile();
    void SetMaxFileSize(std::size_t &in);
    void GetMaxFileSize(std::size_t &out);

    template<typename... Args>
    void log(const Args&... args);

private:
    // 递归终止条件
    void logInternal(std::ostringstream& oss) {}

    template<typename T, typename... Args>
    void logInternal(std::ostringstream& oss, const T& value, const Args&... args);

    void writeLog(const std::string& message);

    int GetFileSize(std::size_t &out);

    int CheckFileSize();

    bool createDirectory(const std::string& path);
    bool createDirectoriesRecursive(const std::string& path); 

private:
    std::ofstream logfile_;
    std::string m_filename {};
    std::size_t m_max_file_size {10 * 1024 * 1024};
};

inline void Logger::OpenFile(const std::string &filename)
{
    logfile_.open(filename, std::ios::app);
    assert(logfile_.is_open());
    m_filename = filename;
}
inline void Logger::OpenFile(const std::string &dir_path, const std::string &filename)
{
    bool ret {false};
    ret = createDirectoriesRecursive(dir_path);
    assert(ret);

    m_filename = dir_path + "/" + filename;
    logfile_.open(m_filename, std::ios::app);
    assert(logfile_.is_open());
}

inline void Logger::CloseFile()
{
    logfile_.close();
}

template<typename... Args>
inline void Logger::log(const Args&... args) 
{
    std::ostringstream oss;
    CheckFileSize();
    logInternal(oss, args...);
    writeLog(oss.str());
}

template<typename T, typename... Args>
inline void Logger::logInternal(std::ostringstream& oss, const T& value, const Args&... args) 
{
    oss << value << ' ';
    logInternal(oss, args...);
}

inline void Logger::writeLog(const std::string& message) 
{
    std::time_t now = std::time(nullptr);
    std::tm timeInfo = *std::localtime(&now);
    logfile_ << std::put_time(&timeInfo, "[%Y-%m-%d %H:%M:%S] ") << message << std::endl;
}

inline int Logger::GetFileSize(std::size_t &out)
{
    struct stat st;
    if (stat(m_filename.c_str(), &st) == 0) 
    {
        out = st.st_size;
        return RET_OK;
    }

    return RET_ERR;
}

inline int Logger::CheckFileSize()
{
    int ret {RET_ERR};
    std::size_t file_size {};

    ret = GetFileSize(file_size);
    if (ret == RET_OK)
    {
        if (file_size > m_max_file_size)
        {
            std::ofstream tmp(m_filename);
            if (tmp.is_open())
            {
                tmp.close();
                return RET_OK;
            }
        }
    }

    return RET_ERR;
}

inline void Logger::SetMaxFileSize(std::size_t &in)
{
    m_max_file_size = in;
}

inline void Logger::GetMaxFileSize(std::size_t &out)
{
    out = m_max_file_size;
}

inline bool Logger::createDirectory(const std::string& path) 
{
    // 检查路径是否存在
    struct stat info;
    if (stat(path.c_str(), &info) != 0) 
    {
        // 路径不存在，创建目录
        if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0) 
        {
            std::cerr << "Created directory: " << path << std::endl;
            return true;
        } 
        else 
        {
            std::cerr << "Failed to create directory: " << path << std::endl;
            return false;
        }
    } 
    else if (info.st_mode & S_IFDIR) 
    {
        // 路径已存在且为目录
        return true;
    } 
    else 
    {
        // 路径已存在但不是目录
        std::cerr << "Path already exists but not a directory: " << path << std::endl;
        return false;
    }
}

inline bool Logger::createDirectoriesRecursive(const std::string& path) 
{
    size_t pos = 0;
    std::string subPath;
    
    while ((pos = path.find_first_of("/\\", pos + 1)) != std::string::npos) 
    {
        subPath = path.substr(0, pos);
        if (!createDirectory(subPath)) 
        {
            return false;
        }
    }
    
    return createDirectory(path);
}