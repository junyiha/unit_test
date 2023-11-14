/**
 * @file ComcumerIndex.hpp
 * @author your name (you@domain.com)
 * @brief 处理索引数据的类
 * @version 0.1
 * @date 2023-06-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include "BaseIndex.hpp"

class ConsumerIndex final : public BaseIndex
{
public:
    void GetFileName(std::string &out) override;
    int SetFileName(std::string &in) override;
    int Open() override;
    void Close() override;
    int ReadIndex(std::size_t &out) override;
    int WriteIndex(std::size_t &in) override;

public:
    ConsumerIndex();
    virtual ~ConsumerIndex();

private:
    int m_shm_fd;
    std::string m_file_name {"aaa-consumer.idx"};
    std::vector<char> m_idx_data;
    std::string m_idx_string {};
};

inline ConsumerIndex::ConsumerIndex()
{
    m_idx_data.resize(20);
}

inline ConsumerIndex::~ConsumerIndex()
{
    Close();
}

inline void ConsumerIndex::GetFileName(std::string &out)
{
    out = m_file_name;    
}

inline int ConsumerIndex::SetFileName(std::string &in)
{
    if (!in.empty())
    {
        m_file_name = in;
        return RET_OK;
    }

    return RET_ERR;
}

inline int ConsumerIndex::Open()
{
    m_shm_fd = shm_open(m_file_name.c_str(), O_CREAT | O_RDWR, 0666);
    if (m_shm_fd != -1)
        return RET_OK;

    return RET_ERR;
}

inline void ConsumerIndex::Close()
{
    close(m_shm_fd);
}

inline int ConsumerIndex::ReadIndex(std::size_t &out)
{
    int ret {RET_ERR};

    ret = lseek(m_shm_fd, 0, SEEK_SET);
    if (ret != RET_ERR)
    {
        ret = read(m_shm_fd, m_idx_data.data(), m_idx_data.size());
        if (ret != -1 && ret != 0)
        {
            for (auto &it : m_idx_data)
                m_idx_string += it;
            
            out = std::stoi(m_idx_string);
            return RET_OK;
        }
    }

    return RET_ERR;
}

inline int ConsumerIndex::WriteIndex(std::size_t &in)
{
    int ret {RET_ERR};

    m_idx_string = std::to_string(in);
    for (int col {0}; col < m_idx_string.size(); col++)
        m_idx_data[col] = m_idx_string[col];

    ret = lseek(m_shm_fd, 0, SEEK_SET);
    if (ret != RET_ERR)
    {
        ret = write(m_shm_fd, m_idx_data.data(), m_idx_data.size());
        if (ret != -1 && ret != 0)
            return RET_OK;
    }

    return RET_ERR;
}