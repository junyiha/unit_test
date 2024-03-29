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

DEFINE_string(module_cmd, "test-anything", "module argument");
DEFINE_string(function_cmd, "test-signal", "function argument");

int main(int argc, char *argv[])
{
    gflags::SetUsageMessage("this is a unit test set.");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    LOG(INFO) << argv[0] << " [options] \n"
              << gflags::ProgramUsage() << "\n";

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
    message.first_layer = FLAGS_module_cmd;
    message.second_layer = FLAGS_function_cmd;
    
    std::map<std::string, std::function<int(Message& message)>> cmd_map = {
        {"test-asio", test_asio},
        {"test-anything", test_anything},
        {"test-business", test_business},
        {"test-network", test_network},
        {"test-libuv", test_libuv},
        {"test-opencv", test_opencv},
        {"test-leetcode", test_leetcode}
    };

    auto it = cmd_map.find(message.first_layer);
    if (it != cmd_map.end())
    {
        it->second(message);
    }
    else 
    {
        std::cerr << "invalid command: " << argv[1] << std::endl;
    }

    google::ShutdownGoogleLogging();
    gflags::ShutDownCommandLineFlags();

    return 0;
}
