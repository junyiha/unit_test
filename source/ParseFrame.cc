#include "ParseFrame.hpp"

bool ParseFrame(std::string &in, struct Frame_t &out)
{
    FrameDetector_t fd;
    FrameDetectorBox_t fdb;
    nlohmann::json parsed_data;

    try 
    {
        parsed_data = nlohmann::json::parse(in);
        out.monotonic = parsed_data["monotonic"];
        out.real_time = parsed_data["realtime"];
        out.task = parsed_data["task"];
        out.version = parsed_data["version"];
        out.next_protocol.seqnum = parsed_data["next_protocol"]["seqnum"];
        out.next_protocol.param = parsed_data["next_protocol"]["param"];
        out.height = parsed_data["frame"]["height"];
        out.width = parsed_data["frame"]["width"];
        out.index = parsed_data["frame"]["index"];
        out.number = parsed_data["frame"]["index"];
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
                out.detector_arr.push_back(fd);
            }  // 遍历键为 detector 的值
        }
    }
    catch (nlohmann::json::parse_error &e)
    {
        std::cerr << "Failed to parse frame string, the error information: " << e.what() << std::endl;
        return false;
    }
    catch (nlohmann::json::type_error &e)
    {
        std::cerr << "Failed to process json data, the error information: "<< e.what() << std::endl;
        return false;
    }

    return true;
}