/**
 * @file PictureServer.hpp
 * @author your name (you@domain.com)
 * @brief 图片服务器 接收mjpeg图片，解析，维护计数器
 * @version 0.1
 * @date 2023-06-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include <cassert>
#include <queue>
#include "ParseMjpeg.hpp"
#include "ConsumerIndex.hpp"
#include "ProducerIndex.hpp"
#include "ProcessFrame.hpp"

class PictureServer
{
public:
    void SetPrefix(std::string &in);
    void Init();
    int Process();
    bool GetStructData(std::string &out);
    bool GetOriginPicData(std::vector<char> &out);
    void DeleteQueueFrontData();
    bool SaveOriginPictureToDir(std::string &in);

public:
    PictureServer() = default;
    virtual ~PictureServer() = default;

private:
    void InitConsumer();
    void InitProducer();

private:
    void GetProducerName(std::string &out);
    void GetConsumerName(std::string &out);
    void GetPictureName(std::string &out);
    bool RemoveShmFile(std::string &in);
    void SaveDataToQueue(std::string &in);

private:
    bool ProcessFrame(std::string &pic_name, std::string &json_string);

private:
    ParseMjpeg m_pm;
    ConsumerIndex m_ci;
    ProducerIndex m_pi;
    ProcessPicture m_pp;

private:
    std::string m_prefix {"aaa"};
    std::string m_consumer_name {};
    std::string m_producer_name {};
    std::size_t m_consumer_idx {1};
    std::size_t m_producer_idx {1};
    std::size_t m_total_queue_size {5};

private:
    std::queue<std::string> m_struct_queue;
};

inline void PictureServer::SetPrefix(std::string &in)
{
    m_prefix = in;
}

inline void PictureServer::Init()
{
    InitConsumer();
    InitProducer();
}

inline int PictureServer::Process()
{
    int ret;
    std::string pic_name {};
    std::string json_string {};

    while (true)
    {
        ret = m_pi.ReadIndex(m_producer_idx);
        if (ret != ProducerIndex::RET_OK)
        {
            std::cerr << "Failed to read producer index, break"<< std::endl;
            break;
        }
        
        if (m_consumer_idx > m_producer_idx)
        {
            sleep(1);
            continue;
        }

        GetPictureName(pic_name);
        ret = m_pm.ParseShmMjpegFile(pic_name);
        if (ret == ParseMjpeg::RET_OK)
        {
            ret = m_pm.GetStructData(json_string);
            if (ret == ParseMjpeg::RET_OK)
            {
                SaveDataToQueue(json_string);
                ProcessFrame(pic_name, json_string);
                    
                if (!RemoveShmFile(pic_name))
                    std::cerr << "Failed to remove file: " << pic_name << std::endl;
            }
        }
        ret = m_ci.WriteIndex(m_consumer_idx);
        if (ret != ConsumerIndex::RET_OK)
        {
            std::cerr << "Failed to write data to consumer file" << std::endl;
            break;
        }
        m_consumer_idx++;
    }

    return 0;
}

inline bool PictureServer::GetStructData(std::string &out)
{
    if (m_struct_queue.empty())
        return false;

    out = m_struct_queue.front();
    DeleteQueueFrontData();

    return true;
}

inline bool PictureServer::GetOriginPicData(std::vector<char> &out)
{
    int ret {ParseMjpeg::RET_ERR};

    ret = m_pm.GetOriginPicData(out);
    if (ret == ParseMjpeg::RET_OK)
        return true;

    return false;
}

inline void PictureServer::DeleteQueueFrontData()
{
    m_struct_queue.pop();
}

inline bool PictureServer::SaveOriginPictureToDir(std::string &in)
{
    int ret {ParseMjpeg::RET_ERR};
    std::string pic_name;

    GetPictureName(pic_name);
    in += pic_name;
    ret = m_pm.SaveOriginPicFile(in);
    if (ret == ParseMjpeg::RET_OK)
        return true;

    return false;
}

inline void PictureServer::InitConsumer()
{
    int ret {ConsumerIndex::RET_ERR};

    GetConsumerName(m_consumer_name);
    ret = m_ci.SetFileName(m_consumer_name);
    assert(ret == ConsumerIndex::RET_OK);

    ret = m_ci.Open();
    assert(ret == ConsumerIndex::RET_OK);

    ret = m_ci.WriteIndex(m_consumer_idx);
    assert(ret == ConsumerIndex::RET_OK);
}

inline void PictureServer::InitProducer()
{
    int ret {ConsumerIndex::RET_ERR};
    
    GetProducerName(m_producer_name);
    ret = m_pi.SetFileName(m_producer_name);
    assert(ret == ConsumerIndex::RET_OK);

    ret = m_pi.Open();
    assert(ret == ConsumerIndex::RET_OK);

    ret = m_pi.ReadIndex(m_producer_idx);
    assert(ret == ConsumerIndex::RET_OK);
}

inline void PictureServer::GetProducerName(std::string &out)
{
    out = m_prefix + "-producer.idx";
}

inline void PictureServer::GetConsumerName(std::string &out)
{
    out = m_prefix + "-consumer.idx";
}

inline void PictureServer::GetPictureName(std::string &out)
{
    out = m_prefix + "-frame-" + std::to_string(m_consumer_idx) + ".jpg";
}

inline bool PictureServer::RemoveShmFile(std::string &in)
{
    int ret;
    std::string file_name;

    file_name = "/dev/shm/" + in;
    ret = remove(file_name.c_str());
    if (ret == 0)
        return true;

    return false;
}

inline void PictureServer::SaveDataToQueue(std::string &in)
{
    if (m_struct_queue.size() >= m_total_queue_size)
    {
        m_struct_queue.pop();
    }

    m_struct_queue.push(in);
}

inline bool PictureServer::ProcessFrame(std::string &pic_name, std::string &json_string)
{
    // m_pp.Process(pic_name);
    m_pp.Process(pic_name, json_string);
}