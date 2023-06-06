/**
 * @file ParseMjpeg.hpp
 * @author your name (you@domain.com)
 * @brief 解析mjpeg图片，输出图片数据和结构化数据
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>

class ParseMjpeg
{
public:
    using EnumRet_t = enum 
    {
        RET_ERR = -1,
        RET_OK = 0
    };

public:
    int ParseMjpegFile(std::string file);
    int ParseShmMjpegFile(std::string file);
    int SaveOriginPicFile(std::string origin_file);
    int SaveThumbPicFile(std::string thumb_file);
    int SaveStructDataFile(std::string struct_data_file);
    int GetOriginPicData(std::vector<char> &out);
    int GetThumbPicData(std::vector<char> &out);
    int GetStructData(std::vector<char> &out);
    int GetStructData(std::string &out);

private:
    std::vector<char> ReadFileToMemory(const std::string& filename);
    bool SaveMemoryToFile(const std::vector<char>& data, const std::string& filename);
    void CharToInt(std::vector<char> &in, std::size_t &out);
    int GetLenDataFromShmFile();
    int GetDataFromShmFile();

public:
    ParseMjpeg();
    virtual ~ParseMjpeg();

private:
    std::size_t m_proto_size {20};
    std::size_t m_data_num {3};

private:
    int m_shm_fd;
    std::vector<char> m_file_data {};

    std::vector<char> m_origin_pic_data {};
    std::vector<char> m_thumb_pic_data {};
    std::vector<char> m_struct_data {};

    std::vector<char> m_origin_pic_len_data;
    std::vector<char> m_thumb_pic_len_data;
    std::vector<char> m_struct_len_data;

    std::size_t m_origin_pic_len {};
    std::size_t m_thumb_pic_len {};
    std::size_t m_struct_len {};
};

ParseMjpeg::ParseMjpeg()
{
    m_origin_pic_len_data.resize(20);
    m_thumb_pic_len_data.resize(20);
    m_struct_len_data.resize(20);
}

ParseMjpeg::~ParseMjpeg()
{
    m_origin_pic_len_data.clear();
    m_thumb_pic_len_data.clear();
    m_struct_len_data.clear();

    m_file_data.clear();
    m_origin_pic_data.clear();
    m_thumb_pic_data.clear();
    m_struct_data.clear();
}

inline int ParseMjpeg::ParseMjpegFile(std::string file)
{
    int ret {RET_ERR};
    if (file.empty())
    {
        std::cerr << "Invalid input, file: " << file << std::endl;
        return RET_ERR;
    }
    m_file_data = ReadFileToMemory(file);
    if (m_file_data.empty())
    {
        std::cerr << "Failed to read file data to memory" << std::endl;
        return RET_ERR;
    }
    for (std::size_t col {0}; col < m_proto_size; col++)
    {
        m_origin_pic_len_data[col] = m_file_data[m_file_data.size() - m_proto_size * m_data_num + col];
        m_thumb_pic_len_data[col] = m_file_data[m_file_data.size() - m_proto_size * (m_data_num - 1) + col];
        m_struct_len_data[col] = m_file_data[m_file_data.size() - m_proto_size * (m_data_num - 2) + col];
    }
    CharToInt(m_origin_pic_len_data, m_origin_pic_len);
    CharToInt(m_thumb_pic_len_data, m_thumb_pic_len);
    CharToInt(m_struct_len_data, m_struct_len);

    m_origin_pic_data.clear();
    for (std::size_t col {0}; col < m_origin_pic_len; col++)
    {
        m_origin_pic_data.push_back(m_file_data.at(col));
    }

    m_thumb_pic_data.clear();
    for (std::size_t col {m_origin_pic_len}; col < (m_origin_pic_len + m_thumb_pic_len); col++)
    {
        m_thumb_pic_data.push_back(m_file_data.at(col));
    }

    m_struct_data.clear();
    for (std::size_t col {m_origin_pic_len + m_thumb_pic_len}; col < (m_origin_pic_len + m_thumb_pic_len + m_struct_len); col++)
    {
        m_struct_data.push_back(m_file_data.at(col));
    }

    return RET_OK;
}

inline int ParseMjpeg::ParseShmMjpegFile(std::string file)
{
    int ret {RET_ERR};
    m_shm_fd = shm_open(file.c_str(), O_RDWR, 0666);
    if (m_shm_fd == RET_ERR)
        return RET_ERR;
    
    ret = GetLenDataFromShmFile();
    if (ret == RET_ERR)
    {
        close(m_shm_fd);
        return RET_ERR;
    }

    CharToInt(m_origin_pic_len_data, m_origin_pic_len);
    CharToInt(m_thumb_pic_len_data, m_thumb_pic_len);
    CharToInt(m_struct_len_data, m_struct_len);

    ret = GetDataFromShmFile();
    if (ret == RET_ERR)
    {
        close(m_shm_fd);
        return RET_ERR;
    }

    close(m_shm_fd);
    return RET_OK;
}

inline int ParseMjpeg::SaveOriginPicFile(std::string origin_file)
{
    if (!SaveMemoryToFile(m_origin_pic_data, origin_file))
    {
        std::cerr << "Failed to save origin picture file from memory data" << std::endl;
        return RET_ERR;
    }

    return RET_OK;
}

inline int ParseMjpeg::SaveThumbPicFile(std::string thumb_file)
{
    if (!SaveMemoryToFile(m_thumb_pic_data, thumb_file))
    {
        std::cerr << "Failed to save thunb picture file from memory data" << std::endl;
        return RET_ERR;
    }

    return RET_OK;
}

inline int ParseMjpeg::SaveStructDataFile(std::string struct_data_file)
{
    if (!SaveMemoryToFile(m_struct_data, struct_data_file))
    {
        std::cerr << "Failed to save struct data file from memory data" << std::endl;
        return RET_ERR;
    }

    return RET_OK;
}

inline int ParseMjpeg::GetOriginPicData(std::vector<char> &out)
{
    if (m_origin_pic_data.empty())
    {
        std::cerr << "Empty origin picture data" << std::endl;
        return RET_ERR;
    }
    out = m_origin_pic_data;

    return RET_OK;
}

inline int ParseMjpeg::GetThumbPicData(std::vector<char> &out)
{
    if (m_thumb_pic_data.empty())
    {
        std::cerr << "Empty thumb picture data" << std::endl;
        return RET_ERR;
    }
    out = m_thumb_pic_data;

    return RET_OK;
}

inline int ParseMjpeg::GetStructData(std::vector<char> &out)
{
    if (m_struct_data.empty())
    {
        std::cerr << "Empty struct data" << std::endl;
        return RET_ERR;
    }
    out = m_struct_data;

    return RET_OK;
}

inline int ParseMjpeg::GetStructData(std::string &out)
{
    if (m_struct_data.empty())
    {
        std::cerr << "Empty struct data" << std::endl;
        return RET_ERR;
    }
    out.clear();
    for (auto &it : m_struct_data)
    {
        out += it;
    }

    return RET_OK;
}

// 读取文件内容到内存
inline std::vector<char> ParseMjpeg::ReadFileToMemory(const std::string& filename) 
{
    std::ifstream file(filename, std::ios::binary);
    
    if (!file) 
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return {};
    }
    
    // 获取文件大小
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // 分配内存缓冲区
    std::vector<char> buffer(fileSize);
    
    // 读取文件内容到缓冲区
    if (!file.read(buffer.data(), fileSize)) 
    {
        std::cerr << "Failed to read file: " << filename << std::endl;
        return {};
    }
    
    return buffer;
}

// 将内存内容保存为新文件
inline bool ParseMjpeg::SaveMemoryToFile(const std::vector<char>& data, const std::string& filename) 
{
    std::ofstream file(filename, std::ios::binary);
    
    if (!file) 
    {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return false;
    }
    
    // 将内存内容写入文件
    if (!file.write(data.data(), data.size())) 
    {
        std::cerr << "Failed to write file: " << filename << std::endl;
        return false;
    }
    
    return true;
}

inline void ParseMjpeg::CharToInt(std::vector<char> &in, std::size_t &out)
{
    std::string tmp_str {};
    for (auto &it : in)
    {
        tmp_str += static_cast<char>(it);
    }
    out = std::stoi(tmp_str);
}

inline int ParseMjpeg::GetLenDataFromShmFile()
{
    int ret {RET_ERR};

    ret = lseek(m_shm_fd, -(m_proto_size * m_data_num), SEEK_END);
    if (ret == RET_ERR)
        return RET_ERR;
    m_origin_pic_len_data.clear();
    m_origin_pic_len_data.resize(m_proto_size);
    ret = read(m_shm_fd, m_origin_pic_len_data.data(), m_proto_size);
    if (ret == RET_ERR)
        return RET_ERR;

    ret = lseek(m_shm_fd, -(m_proto_size * (m_data_num - 1)), SEEK_END);
    if (ret == RET_ERR)
        return RET_ERR;
    m_thumb_pic_len_data.clear();
    m_thumb_pic_len_data.resize(m_proto_size);
    ret = read(m_shm_fd, m_thumb_pic_len_data.data(), m_proto_size);
    if (ret == RET_ERR)
        return RET_ERR;

    ret = lseek(m_shm_fd, -(m_proto_size * (m_data_num - 2)), SEEK_END);
    if (ret == RET_ERR)
        return RET_ERR;
    m_struct_len_data.clear();
    m_struct_len_data.resize(m_proto_size);
    ret = read(m_shm_fd, m_struct_len_data.data(), m_proto_size);
    if (ret == RET_ERR)
        return RET_ERR;

    return RET_OK;
}

inline int ParseMjpeg::GetDataFromShmFile()
{
    int ret {RET_ERR};
    
    ret = lseek(m_shm_fd, 0, SEEK_SET);
    if (ret == RET_ERR)
        return RET_ERR;
    m_origin_pic_data.clear();
    m_origin_pic_data.resize(m_origin_pic_len);
    ret = read(m_shm_fd, m_origin_pic_data.data(), m_origin_pic_len);
    if (ret == RET_ERR)
        return RET_ERR;

    ret = lseek(m_shm_fd, m_origin_pic_len, SEEK_SET);
    if (ret == RET_ERR)
        return RET_ERR;
    m_thumb_pic_data.clear();
    m_thumb_pic_data.resize(m_thumb_pic_len);
    ret = read(m_shm_fd, m_thumb_pic_data.data(), m_thumb_pic_len);
    if (ret == RET_ERR)
        return RET_ERR;

    ret = lseek(m_shm_fd, m_origin_pic_len + m_thumb_pic_len, SEEK_SET);
    if (ret == RET_ERR)
        return RET_ERR;
    m_struct_data.clear();
    m_struct_data.resize(m_struct_len);
    ret = read(m_shm_fd, m_struct_data.data(), m_struct_len);
    if (ret == RET_ERR)
        return RET_ERR;
    
    return RET_OK;
}