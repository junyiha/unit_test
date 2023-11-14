/**
 * @file ProducerIndex.hpp
 * @author your name (you@domain.com)
 * @brief 生产者的数据读取
 * @version 0.1
 * @date 2023-06-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include "BaseIndex.hpp"

class ProducerIndex final : public BaseIndex
{
public:
    void GetFileName(std::string &out) override;
    int SetFileName(std::string &in) override;
    int Open() override;
    void Close() override;
    int ReadIndex(std::size_t &out) override;

public:
    ProducerIndex();
    virtual ~ProducerIndex();

private:
    int m_shm_fd;
    std::string m_file_name {"aaa-producer.idx"};
    std::vector<char> m_idx_data;
    std::string m_idx_string {};
};

inline ProducerIndex::ProducerIndex()
{
    m_idx_data.resize(20);
}

inline ProducerIndex::~ProducerIndex()
{
    Close();
    m_idx_data.clear();
}

inline void ProducerIndex::GetFileName(std::string &out)
{
    out = m_file_name;
}

inline int ProducerIndex::SetFileName(std::string &in)
{
    if (!in.empty())
    {
        m_file_name = in;
        return RET_OK;
    }

    return RET_ERR;
}

inline int ProducerIndex::Open()
{
    int ret {RET_ERR};
    m_shm_fd = shm_open(m_file_name.c_str(), O_RDONLY, 0666);
    if (m_shm_fd == -1)
        return RET_ERR;

    return RET_OK;
}

inline void ProducerIndex::Close()
{
    close(m_shm_fd);
}

inline int ProducerIndex::ReadIndex(std::size_t &out)
{
    int ret {RET_ERR};

    ret = lseek(m_shm_fd, 0, SEEK_SET);
    if (ret != -1)
    {
        ret = read(m_shm_fd, m_idx_data.data(), m_idx_data.size());
        if (ret != -1 && ret != 0)
        {
            m_idx_string.clear();
            for (auto &it : m_idx_data)
            {
                if (it == ' ')
                    continue;
                
                m_idx_string += it;
            }
            try
            {
                out = std::stoi(m_idx_string);
                return RET_OK;
            }
            catch (std::invalid_argument &e)
            {
                std::cerr << "error message: " << e.what() << std::endl;
                std::cerr <<"invalid m_idx_string: " << m_idx_string << std::endl;
                return RET_ERR;
            }
        }
    }
    
    return RET_ERR;
}