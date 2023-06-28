#include <thread>
#include <sched.h>
#include "ParseMjpeg.hpp"
#include "ConsumerIndex.hpp"
#include "PictureServer.hpp"
// #include "VCAFrame.hpp"
#include "ParseFrame.hpp"

using EnumRET_t = enum 
{
    RET_ERR = -1, 
    RET_OK = 0
};

std::string id_string {"aaa"};

int GetProducerIdx(std::size_t &out)
{
    int ret {RET_ERR};
    std::vector<char> producer_data(20);
    std::string producer_file;
    std::string cnt_string {};

    producer_file = id_string + "-producer.idx";
    int shm_fd = shm_open(producer_file.c_str(), O_RDONLY, 0666);
    if (shm_fd == -1)
    {
        std::cerr << "Failed to open file: " << producer_file << std::endl;
        return RET_ERR;
    }

    ret = read(shm_fd, producer_data.data(), producer_data.size());
    if (ret == -1 || ret == 0)
    {
        std::cerr << "Failed to read data from file: " << producer_file << std::endl;
        return RET_ERR;
    }
    for (auto &it : producer_data)
        cnt_string += it;
    
    out = std::stoi(cnt_string);

    return RET_OK;
}

int GetPicFileName(std::size_t &in_idx, std::string &out)
{
    out = id_string + "-frame-" + std::to_string(in_idx) + ".jpg";
}

int test_v1()
{
    int ret {RET_ERR};
    std::string pic_name {};
    std::size_t producer_cnt {};
    std::size_t consumer_cnt {};
    std::string json_string {};
    std::string consumer_name {};
    ParseMjpeg pm;
    ConsumerIndex ci;

    ret = GetProducerIdx(producer_cnt);
    if (ret != RET_ERR)
    {
        std::cerr << "Success to get producer_cnt: " << producer_cnt << std::endl;
        pic_name = id_string + "-frame-" + std::to_string(producer_cnt) + ".jpg";
        std::cerr << "picture name: " << pic_name << std::endl;
        ret = pm.ParseShmMjpegFile(pic_name);
        if (ret == ParseMjpeg::RET_OK)
        {
            ret = pm.GetStructData(json_string);
            if (ret == ParseMjpeg::RET_OK)
            {
                std::cerr << "Success to get struct data from file: " << pic_name << std::endl;
                std::cerr << "struct data: " << json_string << std::endl;
                consumer_name = id_string + "-consumer.idx";
                ret = ci.SetFileName(consumer_name);
                if (ret == ConsumerIndex::RET_OK)
                {
                    ret = ci.Open();
                    if (ret == ConsumerIndex::RET_OK)
                    {
                        ret = ci.ReadIndex(consumer_cnt);
                        if (ret == ConsumerIndex::RET_OK)
                        {
                            std::cerr <<"Read the consumer count: " << consumer_cnt << std::endl;
                            consumer_cnt++;
                            ret = ci.WriteIndex(consumer_cnt);
                            if (ret == ConsumerIndex::RET_OK)
                            {
                                std::cerr << "Success to add count to consumer index file" << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

using EnumLabel_t = enum 
{
    FULL_BODY = 10001,
};

std::size_t threshold {60};

int main()
{
    struct Frame_t f;
    std::string json_string;
    std::string prefix {"J0E78"};
    std::string save_origin_path {"path/to/"};
    PictureServer ps;

    ps.SetPrefix(prefix);   
    ps.Init();
    // ps.Process();

    std::thread t{&PictureServer::Process, &ps};

    while (true)
    {
        if (ps.GetStructData(json_string))
        {
            if (ParseFrame(json_string, f))
            {
                if (!f.detector_arr.empty())
                {
                    for (auto &detector : f.detector_arr)
                    {
                        if (!detector.box_arr.empty())
                        {
                            for (auto &box : detector.box_arr)
                            {
                                if (box.label == FULL_BODY && box.score > threshold)
                                {
                                    save_origin_path = "path/to/";
                                    std::string file_name {};
                                    if (ps.SaveOriginPictureToDir(save_origin_path, file_name))
                                    {
                                        std::cerr << "Success to save record picture, and the information : " << std::endl;
                                        std::cerr << "\n++++++++++++++++++++++++++" << std::endl;
                                        std::cerr << "task: " << f.task << std::endl;
                                        std::cerr << "index: " << box.index << std::endl;
                                        std::cerr << "label: " << box.label << std::endl;
                                        std::cerr << "score: " << box.score << std::endl;
                                        std::cerr << "++++++++++++++++++++++++++\n" << std::endl;
                                    }  // 判断是否保存图片
                                }  // 判断检测框的标签和阈值
                            }  // 遍历检测器中的检测框
                        }  // 判断检测器中检测框是否为空
                    }  // 遍历检测器
                }  // 判断检测器是否为空
            }  // 判断是否成功解析字符串
        }  // 判断是否获取json字符串
    }

    return 0;
}