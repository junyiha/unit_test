/**
 * @file test_boost.cc
 * @author your name (you@domain.com)
 * @brief boost 单元测试
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include "boost/shared_ptr.hpp"

void Help()
{
    std::string help_info = R"(
        test_boost  

        --help
    )";

    std::clog << help_info << std::endl;
}

int test_shared_ptr()
{
    boost::shared_ptr<int> shared_int(new int(42));

    std::clog << "Shared pointer value: " << *shared_int << std::endl;
    std::clog << "Reference count: " << shared_int.use_count() << std::endl;

    // shared_int 在离开作用域时会自动释放内存
    return 0;
}

#include "boost/log/trivial.hpp"
#include "boost/log/core.hpp"
#include "boost/log/expressions.hpp"
#include "boost/log/sources/logger.hpp"
#include "boost/log/sources/global_logger_storage.hpp"
#include "boost/log/sinks.hpp"

#include "boost/log/utility/setup/console.hpp"
#include "boost/log/utility/setup/file.hpp"  // add_file_log()


namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

int test_log_file()
{
    boost::log::sources::logger lg;
    boost::log::add_file_log("/data/home/user/workspace/unit_test/data/auto_calibrate/sample.log");

    BOOST_LOG(lg) << "hello world";

    return 0;
}

int test_log()
{

    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);

	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    return 0;
}

int main(int argc, char *argv[])
{
    std::string arg;
    for (int i = 1; i < argc; i++)   
    {
        arg = argv[i];
        if (arg == "--help")
        {
            Help();
        }
        else if (arg == "--test-log-file")
        {
            test_log_file();
        }
        else if (arg == "--test-shared-ptr")
        {
            test_shared_ptr();
        }
        else if (arg == "--test-log")
        {
            test_log();
        }
        else 
        {
            Help();
        }
    }

    return 0;
}