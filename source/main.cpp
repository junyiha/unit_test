/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "entry.hpp"

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    google::EnableLogCleaner(1);
    
    // FLAGS_logtostderr = true;

    FLAGS_log_dir = "/data/home/user/workspace/unit_test/data";
    FLAGS_log_link = true;
    FLAGS_log_prefix = true;

    FLAGS_log_utc_time = false;

    FLAGS_log_year_in_prefix = false;

    FLAGS_logbufsecs = 0;

    FLAGS_alsologtostderr = true;
    
    FLAGS_colorlogtostderr = true;

    FLAGS_max_log_size = 10;  // 1MB
    FLAGS_minloglevel = google::GLOG_INFO;
    FLAGS_stop_logging_if_full_disk = true;
    FLAGS_timestamp_in_logfile_name = false;

    Message message;
    for (int i = 0; i < argc; i++)
    {
        message.message_pool.push_back(argv[i]);
    }
    
    std::map<std::string, std::function<int(Message& message)>> cmd_map = {
        {"--test-asio", test_asio},
        {"--test-anything", test_anything},
        {"--test-business", test_business}
    };

    auto it = cmd_map.find(argv[1]);
    if (it != cmd_map.end())
    {
        it->second(message);
    }
    else 
    {
        std::cerr << "invalid command: " << argv[1] << std::endl;
    }

    google::ShutdownGoogleLogging();

    return 0;
}
