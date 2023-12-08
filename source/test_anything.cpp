/**
 * @file test_anything.cc
 * @author your name (you@domain.com)
 * @brief 为分类的单元测试
 * @version 0.1
 * @date 2023-11-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "entry.hpp"

#include "boost/log/core.hpp"
#include "boost/log/trivial.hpp"
#include "boost/log/expressions.hpp"
#include "boost/log/sinks/text_file_backend.hpp"
#include "boost/log/utility/setup/file.hpp"
#include "boost/log/utility/setup/common_attributes.hpp"
#include "boost/log/sources/severity_logger.hpp"
#include "boost/log/sources/record_ostream.hpp"
#include "boost/asio.hpp"
#include "boost/beast.hpp"

const int ALERT_INTERVAL_SECONDS = 3;  // 告警时间间隔为60秒
std::time_t lastAlertTime = 0;  // 上次告警时间的初始值为0

int processRequest()
{
    // 模拟请求处理过程
    bool hasError = true;  // 假设出现异常情况

    if (hasError)
    {
        std::time_t currentTime = std::time(nullptr);  // 获取当前时间
        if (currentTime - lastAlertTime > ALERT_INTERVAL_SECONDS)
        {
            // 满足告警条件，进行告警操作
            std::cerr << "time: " << std::time(nullptr) << std::endl;
            std::cout << "Alert: An error occurred!" << std::endl;

            // 更新上次告警时间为当前时间
            lastAlertTime = currentTime;
        }
    }

    return 0;
}

int test_asan()
{
    int *buffer = (int *)malloc(sizeof(int) * 10);
    buffer[10] = 42; // 内存越界访问

    free(buffer);
    return 0;
}

int test_ascii()
{
    int num = 4;
    // char char_num = static_cast<char>(num);
    std::string tmp_str;
    tmp_str = std::to_string(num);
    char char_num = tmp_str[0];
    // char char_num = (char)(num);


    // char ch = 'A';
    char ch = '4';
    int ascii = static_cast<int>(ch);
    
    std::cout << "Character: " << ch << std::endl;
    std::cout << "ASCII Value: " << ascii << std::endl;
    
    return 0;
}

int test_eigen_hello() {
    // 创建矩阵
    Eigen::Matrix3f A;
    A << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    // 创建向量
    Eigen::Vector3f b(1, 2, 3);

    // 解线性方程 Ax = b
    Eigen::Vector3f x = A.lu().solve(b);

    // 输出结果
    std::cout << "Solution:\n" << x << std::endl;

    // 计算特征值和特征向量
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigensolver(A);
    if (eigensolver.info() != Eigen::Success) {
        std::cout << "Failed to compute eigenvalues!" << std::endl;
        return 1;
    }
    std::cout << "Eigenvalues:\n" << eigensolver.eigenvalues() << std::endl;
    std::cout << "Eigenvectors:\n" << eigensolver.eigenvectors() << std::endl;

    return 0;
}

int test_eigen_vector3f()
{
    // 声明两个三维浮点数向量
    Eigen::Vector3f v1(1.0, 2.0, 3.0);
    Eigen::Vector3f v2(4.0, 5.0, 6.0);

    // 向量加法
    Eigen::Vector3f sum = v1 + v2;

    // 向量点积
    float dotProduct = v1.dot(v2);

    // 向量叉积
    Eigen::Vector3f crossProduct = v1.cross(v2);

    // 打印结果
    std::cout << "v1: " << v1.transpose() << std::endl;
    std::cout << "v2: " << v2.transpose() << std::endl;
    std::cout << "Sum: " << sum.transpose() << std::endl;
    std::cout << "Dot product: " << dotProduct << std::endl;
    std::cout << "Cross product: " << crossProduct.transpose() << std::endl;

    return 0;
}

class MyClass {
private:
    int privateData;

public:
    MyClass() : privateData(0) {}

    // 声明友元函数
    friend void FriendFunction(const MyClass& obj);

    // 声明友元类
    friend class FriendClass;
};

// 友元函数的定义
void FriendFunction(const MyClass& obj) {
    std::cout << "Friend function accessing private data: " << obj.privateData << std::endl;
}

// 友元类的定义
class FriendClass {
public:
    void AccessPrivateData(const MyClass& obj) {
        std::cout << "Friend class accessing private data: " << obj.privateData << std::endl;
    }
};

extern "C"
{


}

int test_ftok()
{
    key_t key = ftok("path/to/my/directory/share_memory", 1);
    key_t key2 = ftok("path/to/my/directory/share_memory", 1);
    
    if (key == -1) {
        perror("ftok");
        return 1;
    }
    if (key2 == -1) {
        perror("ftok");
        return 1;
    }

    printf("Generated key: %d\n", key);
    printf("Generated key: %d\n", key2);
    
    return 0;
}

// 要测试运行时间的函数
void myFunction()
{
    // 在这里添加你的函数逻辑
    for (int i = 0; i < 1000000; ++i)
    {
        // 执行一些操作
    }
}

int x86_time()
{
    // 获取当前时间点
    auto startTime = std::chrono::high_resolution_clock::now();

    // 调用要测试的函数
    myFunction();

    // 获取当前时间点
    auto endTime = std::chrono::high_resolution_clock::now();

    // 计算时间差
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // 输出结果
    std::cout << "函数运行时间： " << duration.count() << " 毫秒" << std::endl;

    return 0;
}

int arm_time()
{
    // 获取当前时间点
    auto startTime = std::chrono::steady_clock::now();

    // 调用要测试的函数
    myFunction();

    // 获取当前时间点
    auto endTime = std::chrono::steady_clock::now();

    // 计算时间差
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // 输出结果
    std::cout << "函数运行时间： " << duration.count() << " 毫秒" << std::endl;

    return 0;
}

int generateRandomMixedString() {
    int size = 5;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);

    std::string randomString;
    randomString.reserve(size);

    for (int i = 0; i < size; ++i) 
    {
        int choice = dist(gen);
        if (choice == 0) 
        {
            // 生成数字字符
            std::uniform_int_distribution<int> numDist('0', '9');
            randomString.push_back(static_cast<char>(numDist(gen)));
        } 
        // else if (choice == 1) 
        // {
        //     // 生成大写字母字符
        //     std::uniform_int_distribution<int> upperDist('A', 'Z');
        //     randomString.push_back(static_cast<char>(upperDist(gen)));
        // } 
        else 
        {
            // 生成小写字母字符
            std::uniform_int_distribution<int> lowerDist('a', 'z');
            randomString.push_back(static_cast<char>(lowerDist(gen)));
        }
    }
    std::cerr << randomString << std::endl;

    return 0;
}

int GetMemInfo()
{
    int ret;
    struct sysinfo sys_info {};

    ret = sysinfo(&sys_info);
    if (ret == -1)
    {
        std::cerr << "Failed to get system information" << std::endl;
        return -1;
    }

    std::size_t total_memory = sys_info.totalram / 1024 / 1024;
    std::size_t free_memory = sys_info.freeram / 1024 / 1024;
    std::size_t used_memory = total_memory - free_memory / 1024 / 1024;

    std::cerr << "total memory: " << total_memory << " MB" << std::endl;
    std::cerr << "free memory: " << free_memory << " MB" << std::endl;
    std::cerr << "used memory: " << used_memory << " MB" << std::endl;
    return 0;
}

int test_hashmap_1()
{
    // 创建一个哈希表
    std::unordered_map<std::string, int> hashMap;

    // 插入键值对
    hashMap["Alice"] = 25;
    hashMap["Bob"] = 30;

    // 查找键的值
    if (hashMap.find("Alice") != hashMap.end())
    {
        std::cout << "Alice's age is " << hashMap["Alice"] << std::endl;
    }
    else
    {
        std::cout << "Alice not found in the map." << std::endl;
    }

    // 删除键值对
    hashMap.erase("Bob");

    // 遍历哈希表
    for (const auto &pair : hashMap)
    {
        std::cout << pair.first << "'s age is " << pair.second << std::endl;
    }

    return 0;
}

int test_kill_process()
{
    pid_t pid = 13509;  // 要杀死的进程的PID

    // 发送SIGKILL信号来终止指定的进程
    if (kill(pid, SIGKILL) == 0) {
        std::cout << "进程已成功终止" << std::endl;
    } else {
        std::cerr << "无法终止进程" << std::endl;
    }

    return 0;
}

int test_lambda()
{
    std::string str{"hahahahah"};
    std::string str2{"aaaaa"};
    int x {999};
    auto lambda = [&](int in)
    {
        int index {0};
        while (true)
        {
            if (index > 10)
                break;
            std::cerr << "index: " << index << "\n"
                      << "hello world" << "\n"
                      << str << "\n"
                      << str2 << "\n"
                      << in << "\n"
                      << std::endl;
            sleep(1);
            index++;
        }
    };
    std::thread tmp;
    tmp = std::thread(lambda, x);
    // t.join();
    if (tmp.joinable())
    {
        tmp.join();
    }
    return 0;
}

int test_ceil()
{
    double num = 12.34;
    double result = ceil(num);

    printf("Original Number: %.2f\n", num);
    printf("Ceil Value: %.2f\n", result);

    return 0;
}

int test_marco()
{
    printf("date: %s \n", __DATE__);
    printf("date: %s \n", __TIME__);
    printf("date: %s \n", __FILE__);
    printf("date: %d \n", __LINE__);
    printf("date: %d \n", __STDC__);

    return 0;
}

int test_for_loop()
{
    for (int i = 0; i < -1; i++)
    {
        printf("%d\n", i);
    }

    std::vector<int> tmp_array(3,1);

    // for (int j = 0; j < tmp_array.size() - 1; j++)
    // {
    //     printf("%d\n", j);
    // }

    for (auto it = tmp_array.begin(); it != tmp_array.end(); it++)
    {
        if (it == tmp_array.end() - 1)
            break;

        printf("%d \n", *it);
    }

    return 0;
}

int test_httplib_client()
{
    // httplib::Client cli("http://192.169.0.152:28001");
    httplib::Client cli("192.169.0.152", 28001);

    auto res = cli.Get("/api/extension/common/list");

    printf("%s \n", res->body.c_str());

    return 0;
}

int test_mnc()
{
    httplib::SSLClient cli("www.norzoro.cn");

    std::string data = R"(
        {
            "device":"123456qer"
        }
    )";

    auto res = cli.Post("/ecms/api/cmd/playlist", data, "Content-Type: application/json");

    printf("%s \n", res->body.c_str());

    return 0;
}

int test_robot()
{
    httplib::Client cli("192.169.0.125:9999");

    auto res = cli.Get("/api/common/getCurStatus");

    printf("%s \n", res->body.c_str());

    return 0;
}


namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

void init()
{
#ifdef LOG_V1
    // /*v1*/
    logging::add_file_log("/data/home/user/workspace/unit_test/data/test_anything.log");
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );

#elif LOG_V2
    // /*v2*/
    logging::add_file_log
    (
        keywords::file_name = "/data/home/user/workspace/unit_test/data/test_anything_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%]: %Message%"
    );
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );

#elif LOG_V3
    /*v3*/
    logging::add_file_log
    (
        keywords::file_name = "/data/home/user/workspace/unit_test/data/test_anything_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = 
        (
            expr::stream
                << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
                << ": <" << logging::trivial::severity
                << "> " << expr::smessage
        )
    );
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
#endif
}

int test_boost_log_trivial()
{
    init();
    logging::add_common_attributes();
    using namespace logging::trivial;
    src::severity_logger<severity_level> lg;

    BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";

    return 0;
}

int test_httplib_server()
{
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("hello, this is httplib HTTP server", "text/plain");
    });

    svr.Post("/api/play", [](const httplib::Request& req, httplib::Response& res) {
        if (req.has_header("Content-Type") && req.get_header_value("Content-Type") == "application/json")
        {
            std::cerr << "\ndata: \n" << req.body << std::endl;
        }

        nlohmann::json parsed_data;
        nlohmann::json reply_data;
        nlohmann::json item_data;
        std::vector<std::pair<std::string, std::string>> camera_list;

        try 
        {
            parsed_data = nlohmann::json::parse(req.body);
            for (auto &it : parsed_data["cameralist"])
            {
                camera_list.push_back(std::make_pair(it["id"], it["name"]));
            }
        }
        catch (nlohmann::json::parse_error &e)
        {

        }
        catch (nlohmann::json::type_error &e)
        {

        }
        if (!camera_list.empty())
        {
            item_data["camera_id"] = camera_list.at(0).first;
            item_data["record_uri"] = std::string("rtsp://192.169.5.60:554/live/cloud_play");
            item_data["record_fmt"] = "rtsp";
            reply_data["playlists"].push_back(item_data);
        }

        res.set_content(reply_data.dump(), "application/json");
    });

    svr.listen("0.0.0.0", 28009);

    return 0;
}

int test_glog()
{
    // // 输出到终端
    // FLAGS_logtostderr = 1;
    // LOG(INFO) << "stderr";
    // LOG(INFO) << "hello world";

    // // 输出到文件
    // FLAGS_logtostderr = 0;
    // FLAGS_log_dir = "/data/home/user/workspace/unit_test/data/";
    // FLAGS_log_prefix = true;
    // FLAGS_minloglevel = google::INFO;
    
    for (int i = 0; i < 100000; i++)
    {
        LOG(INFO) << "index: " << i << "\n";
        LOG(INFO) << "hello world" << "\n";
        LOG(INFO) << "stderr" << "\n";
    }

    return 0;
}

void Print(const boost::system::error_code& ec)
{
    std::cerr << "Hello world" << std::endl;

    return ;
}

int test_boost_asio_hello()
{
    boost::asio::io_service io_service;

    boost::asio::steady_timer timer(io_service, boost::asio::chrono::seconds(1));
    timer.async_wait(&Print);

    io_service.run();

    return 1;
}

int test_boost_beast_hello()
{
    boost::asio::io_context io_context;

    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8000));
    acceptor.listen();

    while (true)
    {
        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        try 
        {
            boost::beast::flat_buffer buffer;
            boost::beast::http::request<boost::beast::http::string_body> request;

            boost::beast::http::read(socket, buffer, request);

            boost::beast::http::response<boost::beast::http::string_body> response{boost::beast::http::status::ok, request.version()};
            response.set(boost::beast::http::field::server, "Boost HTTP Server");
            response.body() = "Hello, World!";
            response.prepare_payload();

            boost::beast::http::write(socket, response);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;    
}

namespace beast = boost::beast;  // from "boost/beast.hpp"
namespace http = beast::http;    // from "boost/beast/http.hpp"
namespace net = boost::asio;     // from "boost/asio.hpp"
using tcp = net::ip::tcp;        // from "boost/asio/ip/tcp.hpp"

int test_boost_beast_client()
{
    try 
    {
        // std::string host = "http://127.0.0.1";
        std::string host = "www.baidu.com";
        std::string port = "80";
        std::string target = "/";
        int version = 10;
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        auto const results = resolver.resolve(host, port);
        stream.connect(results);

        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(stream, req);

        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        std::cerr << res << std::endl;

        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);
        if (ec && ec != beast::errc::not_connected)
        {
            throw beast::system_error{ec};
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }

    return 1;
}

int test_boost_asio_thread_pool()
{
    boost::asio::io_context io_context;
    boost::asio::thread_pool pool(4);

    for (int i = 0; i < 8; ++i)
    {
        boost::asio::post(pool, [](){
            std::cout << "Task executed in thread: " << std::this_thread::get_id() << std::endl;
        });
    }

    pool.join();

    return 1;
}

int test_boost_asio_ip_tcp_socket()
{
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket(io_context);

    try
    {
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8000);
        socket.connect(endpoint);

        std::string message = "Hello, Server!";
        socket.write_some(boost::asio::buffer(message));

        char data[128];
        size_t len = socket.read_some(boost::asio::buffer(data, 128));
        std::cerr << "Received: " << std::string(data, len) << std::endl;

        socket.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 1;
}

// 模拟目标位姿 x,y,z,rx,ry,rz
int test_generate_target()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> x_dis(-40, 40);
    std::uniform_real_distribution<> y_dis(0, 40);
    std::uniform_real_distribution<> z_dis(0, 10);
    std::uniform_real_distribution<> rx_dis(-3.14, 3.14);
    std::uniform_real_distribution<> ry_dis(-3.14, 3.14);
    std::uniform_real_distribution<> rz_dis(-3.14, 3.14);

    for (int i = 0; i < 10; ++i)
    {
        LOG(INFO) << "x: " << x_dis(gen) << ", "
                  << "y: " << y_dis(gen) << ", "
                  << "z: " << z_dis(gen) << ", "
                  << "rx: " << rx_dis(gen) << ", "
                  << "ry: " << ry_dis(gen) << ", "
                  << "rz: " << rz_dis(gen) << "\n";
    }

    return 1;
}

class Book 
{
public:
    std::string title;
    int year;

    Book(const std::string& t, int y) : title(t), year(y) {}
};

bool compareByYear(const Book& a, const Book& b)
{
    return a.year < b.year;
}

int test_sort_book_class()
{
    std::vector<Book> books = {
        {"Book A", 2000},
        {"Book B", 200},
        {"Book C", 20},
        {"Book D", 210},
        {"Book E", 203200}
    };

    LOG(INFO) << "Original order: " << "\n";
    for (const auto& book : books)
    {
        LOG(INFO) << "book's title: " << book.title << ", book's year: " << book.year << "\n";
    }

    std::sort(books.begin(), books.end(), compareByYear);

    LOG(INFO) << "Sorted by Year: " << "\n";
        for (const auto& book : books)
    {
        LOG(INFO) << "book's title: " << book.title << ", book's year: " << book.year << "\n";
    }

    return 1;
}

int test_vector_multi_delete()
{
    std::vector<int> arr = {1, 2, 3, 2, 523, 2, 52341, 2, 1, 2};

    for (auto& it : arr)
    {
        LOG(INFO) << "value: " << it << "\n";
    }

    for (auto it = arr.begin(); it != arr.end();)
    {
        if (*it == 2)
        {
            arr.erase(it);
        }
        else 
        {
            it++;
        }
    }

    for (auto& it : arr)
    {
        LOG(INFO) << "value: " << it << "\n";
    }
    
    return 1;
}

int test_anything(Message& message)
{
    std::map<std::string, std::function<int()>> cmd_map = {
        {"--test-glog", test_glog},
        {"--test-httplib-server", test_httplib_server},
        {"--test-boost-log-trivial", test_boost_log_trivial},
        {"--test-robot", test_robot},
        {"--test-mnc", test_mnc},
        {"--test-httplib-client", test_httplib_client},
        {"--test-for-loop", test_for_loop},
        {"--test-marco", test_marco},
        {"--test-ceil", test_ceil},
        {"--test-hashmap-1", test_hashmap_1},
        {"--test-get-memery-info", GetMemInfo},
        {"--test-generate-random-id", generateRandomMixedString},
        {"--test-eigen-hello", test_eigen_hello},
        {"--test-eigen-vector3f", test_eigen_vector3f},
        {"--test-ascii", test_ascii},
        {"--test-asan", test_asan},
        {"--process-request", processRequest},
        {"--test-boost-asio-hello", test_boost_asio_hello},
        {"--test-boost-beast-hello", test_boost_beast_hello},
        {"--test-boost-beast-client", test_boost_beast_client},
        {"--test-boost-beast-thread-pool", test_boost_asio_thread_pool},
        {"--test-boost-asio-ip-tcp-socket", test_boost_asio_ip_tcp_socket},
        {"--test-generate-target", test_generate_target},
        {"--test-sort-book-class", test_sort_book_class},
        {"--test-vector-multi-delete",test_vector_multi_delete}
    };
    std::string cmd = message.message_pool[2];
    auto it = cmd_map.find(cmd);
    if (it != cmd_map.end())
    {
        it->second();
        return 1;
    }
    std::cerr << "invalid command: " << cmd << std::endl;

    return 0;
}