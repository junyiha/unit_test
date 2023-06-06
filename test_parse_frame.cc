#include <iostream>
#include "VCAFrame.hpp"
#include "json.hpp"

int main ()
{
    std::string frame_string = R"({"frame":{"detector":[{"boxs":[{"index":836,"index2":"836","label":10001,"number":54801,"score":79,"x1":707,"x2":762,"y1":233,"y2":337},{"index":-1,"index2":"-1","label":10001,"number":54802,"score":10,"x1":723,"x2":764,"y1":219,"y2":274}],"id":"1"}],"height":1080,"index":133223,"number":133230,"width":1920},"monotonic":115081724,"next_protocol":{"param":"","seqnum":1},"realtime":1686044277818,"task":"aaa","version":"6.1.1"})";

    std::cerr << "frame string: " << frame_string << std::endl;

    nlohmann::json parsed_data;
    Frame_t f;
    FrameDetector_t fd;
    FrameDetectorBox_t fdb;

    try 
    {
        parsed_data = nlohmann::json::parse(frame_string);
        f.monotonic = parsed_data["monotonic"];
        f.real_time = parsed_data["realtime"];
        f.task = parsed_data["task"];
        f.version = parsed_data["version"];
        f.next_protocol.seqnum = parsed_data["next_protocol"]["seqnum"];
        f.next_protocol.param = parsed_data["next_protocol"]["param"];
        f.height = parsed_data["frame"]["height"];
        f.width = parsed_data["frame"]["width"];
        f.index = parsed_data["frame"]["index"];
        f.number = parsed_data["frame"]["index"];
        if (parsed_data["frame"]["detector"].is_array())
        {
            for (auto &item_data : parsed_data["frame"]["detector"])
            {
                fd.id = item_data["id"];
                if (item_data["boxs"].is_array())
                {
                    for (auto &it : item_data["boxs"])
                    {
                        fdb.index = it["index"];
                        fdb.index2 = it["index2"];
                        fdb.label = it["label"];
                        fdb.number = it["number"];
                        fdb.score = it["score"];
                        fdb.x1 = it["x1"];
                        fdb.x2 = it["x2"];
                        fdb.y1 = it["y1"];
                        fdb.y2 = it["y2"];
                        fd.box_arr.push_back(fdb);
                    }
                }  // 遍历键为 boxs 的值
                f.detector_arr.push_back(fd);
            }  // 遍历键为 detector 的值
        }
    }
    catch (nlohmann::json::parse_error &e)
    {
        std::cerr << "Failed to parse frame string, the error information: " << e.what() << std::endl;
        return -1;
    }
    catch (nlohmann::json::type_error &e)
    {
        std::cerr << "Failed to process json data, the error information: "<< e.what() << std::endl;
        return -1;
    }

    return 0;
}