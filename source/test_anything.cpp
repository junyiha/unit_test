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

int test_generate_random_id()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> ds(1, 9);

    std::string random_id;
    for (int i = 1; i < 10; i++)
    {
        int random_num = ds(gen);
        random_id = random_id + std::to_string(random_num);
        LOG(INFO) << "random_num: " << random_num << "\n";
    }
    LOG(INFO) << "random id: " << random_id << "\n";

    return 1;
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

int test_httplib_server_v2()
{
    httplib::Server svr;

    svr.Get("/hi", [](const httplib::Request& , httplib::Response& res) {
        res.set_content("hello world", "text/plain");
    });

    svr.listen("0.0.0.0", 13000);

    return 1;
}

int test_httplib_client_v2()
{
    httplib::Client cli("http://192.169.4.16:13000");

    auto res = cli.Get("/hi");
    if (res.error() != httplib::Error::Success)
    {
        LOG(ERROR) << "connect to server failed\n";
        return 0;
    }

    LOG(INFO) << res->body << "\n";

    return 1;
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

int test_ifstream_read_data()
{
    std::string config_file = "/data/home/user/workspace/unit_test/data/static.conf";
    std::ifstream file;

    file.open(config_file, std::ios::in);
    if (!file.is_open())
    {
        LOG(ERROR) << "open config file failed: " << config_file << "\n";
        return 0;
    }

    file.seekg(0, std::ios::end);
    std::streampos file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> data_buffer(file_size);

    file.read(data_buffer.data(), file_size);
    file.close();

    std::string data_string = std::string(data_buffer.data());
    LOG(INFO) << "data string: " << data_string << "\n";

    return 1;
}

static bool CustomPredicate(double a, double b)
{
    if (std::abs(a - b) <= 0.05)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

int test_std_equal()
{
    std::vector<double> vec1 = {2.2, 2.1, 2.2};
    std::vector<double> vec2 = {2.22, 2.12, 2.22};

    bool is_equal = std::equal(vec1.begin(), vec1.end(), vec2.begin(), CustomPredicate);
    if (is_equal)
    {
        LOG(INFO) << "两个序列中对应元素误差在0.05以内,所以相等 \n";
    }
    else 
    {
        LOG(ERROR) << "两个序列中对应元素误差在0.05以外,所以不相等 \n";
    }

    return 1;
}

int test_thread_hardware_concurrency()
{
    const uint32_t num_threads = std::thread::hardware_concurrency();

    LOG(INFO) << "std::thread::hardware_concurrency(): " << num_threads << "\n";

    return 1;
}

int test_thread_lambda_creator()
{
    std::string msg = "this is a message";
    std::thread tmp([](std::string msg){
        LOG(INFO) << "lambda function creator\n"
                  << "message: " << msg << "\n";
    }, msg);

    tmp.join();

    class Test
    {
    public:
        std::string message;

    public:
        void test(std::string msg)
        {
            std::thread tmp([](std::string msg){
                LOG(INFO) << "lambda function in class\n"
                          << "message: " << msg << "\n";
                return;
            }, msg);

            tmp.join();
        }

        void test2()
        {
            std::thread tmp([](std::string msg){
                LOG(INFO) << "lambda function in class\n"
                          << "member message: " << msg << "\n";
                return;
            }, message);

            tmp.join();
        }

        void test3()
        {
            std::thread tmp([](Test* this_ptr){
                LOG(INFO) << "lambda function in class\n"
                          << "this_ptr->message: " << this_ptr->message << "\n";
                return;
            }, this);

            tmp.join();
        }

        void test4()
        {
            std::thread tmp([this](){
                LOG(INFO) << "lambda function in class\n"
                          << "this_ptr->message: " << this->message << "\n";
                return;
            });

            tmp.join();
        }
    };

    Test test;
    test.message = "hello world";
    test.test(msg);
    test.test2();
    test.test3();
    test.test4();

    return 1;
}

int GetFilesInDirectory()
{
    int ec = 0;
    std::string dir_path = "/data/vcr/VisionAlgorithms/";
    std::vector<std::string> directorys;
    std::vector<std::string> files;

    ec = get_dir_and_file_from_path(dir_path, directorys, files);
    if (ec != 1)
    {
        return 0;
    }

    for (const std::string& directory : directorys)
    {
        LOG(INFO) << directory << "\n";
        std::string tmp_dir_path = dir_path + directory;
        std::vector<std::string> tmp_directorys;
        std::vector<std::string> tmp_files;
        ec = get_dir_and_file_from_path(tmp_dir_path, tmp_directorys, tmp_files);
        if (ec != 1)
        {
            LOG(ERROR) << "Invalid directory value: " << tmp_dir_path << "\n";
            continue;
        }

        LOG(INFO) << "directory path:" << tmp_dir_path << "\n";
        for (const std::string& tmp_directory : tmp_directorys)
        {
            LOG(INFO) << tmp_directory << "\n";
        }
        LOG(INFO) << "files: \n";
        for (const std::string& tmp_file : tmp_files)
        {
            LOG(INFO) << tmp_file << "\n";
        }
    }
    return 1;
}

int test_default_creator_function()
{
    class Test 
    {
    private:
        std::string m_data;
    
    public:
        Test() = delete;
        Test(const std::string data) : m_data(data)
        {

        };
        ~Test()
        {
            m_data = "";
        }
    
        void Print()
        {
            LOG(INFO) << m_data << "\n";
        }
    };

    // Test test;
    // test.Print();

    Test test2("hello, world");
    test2.Print();

    return 1;
}

int test_exception_logic_error()
{
    auto tmp = [](int x, int y){
        if (y == 0)
        {
            throw std::logic_error("Division by zero is not allowed");
        }
        LOG(INFO) << "Result of division: " << x / y << std::endl;
    };

    try
    {
        tmp(10, 0);
    }
    catch (const std::logic_error& e)
    {
        LOG(ERROR) << "Caught logic_error: " << e.what() << std::endl;
        return 0;
    }

    return 1;
}

void handle_request(int client_socket)
{
    char buffer[1024];
    memset(buffer, 0, 1024);

    // read data from client
    read(client_socket, buffer, 1024 - 1);
    printf("Received request:\n%s\n", buffer);

    // send HTTP response
    const char* response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>Hello, this is a simple HTTP server in C</hi>";
    write(client_socket, response, strlen(response));

    // close connection of client
    close(client_socket);
}

int test_c_http_server()
{
    const unsigned int port = 8080;
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t addr_len = sizeof(client_addr);

    // create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Socket creation failed\n");
        return EXIT_FAILURE;
    }

    // set address and port 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    server_addr.sin_port = htons(port);

    // bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr))  == -1 )
    {
        perror("Socket listen failed");
        close(server_socket);
        return EXIT_FAILURE;
    }

    printf("Server running on port %d...\n", port);

    if (listen(server_socket, 5) == -1)
    {
        perror("listen failed");
        return EXIT_FAILURE;
    }

    while (1)
    {
        // accept connection of client
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket == -1)
        {
            perror("Accept failed\n");
            continue;;
        }

        // process request of client
        handle_request(client_socket);
    }

    close(server_socket);

    return EXIT_SUCCESS;
}

int test_c_poll_http_server()
{
    const unsigned int port = 8080;
    const unsigned int max_clients = 100;
    int server_socket, client_sockets[max_clients];
    struct sockaddr_in server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t addr_len = sizeof(client_addr);

    // create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Socket creation failed\n");
        return EXIT_FAILURE;
    }

    // set address and port 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    server_addr.sin_port = htons(port);

    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Setsockopt failed");
        return EXIT_FAILURE;
    }

    // bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr))  == -1 )
    {
        perror("Socket listen failed");
        close(server_socket);
        return EXIT_FAILURE;
    }

    printf("Server running on port %d...\n", port);

    if (listen(server_socket, 5) == -1)
    {
        perror("listen failed");
        return EXIT_FAILURE;
    }

    memset(client_sockets, 0, sizeof(client_sockets));
    struct pollfd fds[max_clients];
    int num_clients = 0;

    // add server socket to the poll list
    fds[0].fd = server_socket;
    fds[0].events = POLLIN;
    num_clients++;

    while (1)
    {
        int activity = poll(fds, num_clients, -1);
        if (activity < 0)
        {
            perror("Poll error");
            return EXIT_FAILURE;
        }

        // check for incoming connect
        if (fds[0].revents & POLLIN)
        {
            int new_socket;
            if ((new_socket = accept(server_socket, (struct sockaddr*)&client_addr, (socklen_t *)&addr_len)) < 0)
            {
                perror("Accept failed");
                return EXIT_FAILURE;
            }

            // add new connection to the array
            int i;
            for (i = 1; i < max_clients; i++)
            {
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = new_socket;
                    fds[i].fd = new_socket;
                    fds[i].events = POLLIN;
                    num_clients++;
                    break;
                }
            }
        }

        // check for IO operation on client sockets
        for (int i = 1; i < num_clients; i++)
        {
            if (fds[i].revents & POLLIN)
            {
                int valread;
                size_t buffer_max_size = 10240;
                char buffer[buffer_max_size];
                if ((valread = read(fds[i].fd, buffer, buffer_max_size)) <= 0)
                {
                    close(fds[i].fd);
                    client_sockets[i] = 0;
                    fds[i].fd = -1;
                    num_clients--;
                }
                else 
                {
                    // handle request and send response
                    printf("Received request:\n%s\n", std::string(buffer, valread).c_str());
                    const char* response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>Hello, this is a simple HTTP server in C</hi>\n";
                    write(fds[i].fd, response, strlen(response));
                    close(fds[i].fd);
                }
            }
        }
    }

    close(server_socket);

    return EXIT_SUCCESS;
}

int test_c_epoll_http_server()
{
    const unsigned int port = 8080;
    const unsigned int max_clients = 100;
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t addr_len = sizeof(client_addr);

    // create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Socket creation failed\n");
        return EXIT_FAILURE;
    }

    // set address and port 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    server_addr.sin_port = htons(port);

    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Setsockopt failed");
        return EXIT_FAILURE;
    }

    // bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr))  == -1 )
    {
        perror("Socket listen failed");
        close(server_socket);
        return EXIT_FAILURE;
    }

    printf("Server running on port %d...\n", port);

    if (listen(server_socket, 5) == -1)
    {
        perror("listen failed");
        return EXIT_FAILURE;
    }

    // create epoll instance
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) 
    {
        perror("Epoll creation failed");
        return EXIT_FAILURE;
    }

    struct epoll_event event, events[max_clients];
    event.events = EPOLLIN;
    event.data.fd = server_socket;

    // add server socket to epoll
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &event) == -1)
    {
        perror("Epoll control failed");
        return EXIT_FAILURE;
    }

    while (1)
    {
        int num_events = epoll_wait(epoll_fd, events, max_clients, -1);
        if (num_events == -1)
        {
            perror("Epoll wait failed");
            return EXIT_FAILURE;
        }

        for (int i = 0; i < num_events; i++)
        {
            if (events[i].data.fd == server_socket)
            {
                // accept incoming connection
                if ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, (socklen_t *)&addr_len)) < 0)
                {
                    perror("Accept failed");
                    return EXIT_FAILURE;
                }

                event.events = POLLIN | EPOLLET;
                event.data.fd = client_socket;

                // add client socket to epoll
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &event) == -1)
                {
                    perror("Epoll control failed");
                    return EXIT_FAILURE;
                }
                printf("New connection, socket fd: %d, ip: %s, port: %d\n", client_socket, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            }
            else 
            {
                // Handle data on client socket
                int fd = events[i].data.fd;
                int valread;
                char buffer[1024];
                if ((valread = read(fd, buffer, 1024)) <= 0) {
                    // Connection closed or error
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                    printf("Client disconnected, socket fd: %d\n", fd);
                } else {
                    // Handle request and send response
                    printf("Received request:\n%s\n", buffer);
                    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1></body></html>\n";
                    write(fd, response, strlen(response));
                    close(fd);
                }
            }
        }
    }

    close(server_socket);
    return EXIT_SUCCESS;
}

void httplib_get_hello(const httplib::Request& req, httplib::Response& res)
{
    res.set_content("hello world", "text/plain");
}

void httplib_get_hi(const httplib::Request& req, httplib::Response& res)
{
    res.set_content("hi world", "text/plain");
}

void httplib_post_watch(const httplib::Request& req, httplib::Response& res)
{
    nlohmann::json parsed_data;
    nlohmann::json reply_data;
    if (req.has_header("Content-Type") && 
        req.get_header_value("Content-Type") == "application/json")
    {
        try 
        {
            parsed_data = nlohmann::json::parse(req.body);
            if (parsed_data["flag"] = 1)
            {
                reply_data["watch"] = true;
            }
            else 
            {
                reply_data["watch"] = false;
            }
        }
        catch (nlohmann::json::parse_error& e)
        {

        }
        catch (nlohmann::json::type_error& e)
        {

        }
    }
    else 
    {
        reply_data["watch"] = false;
    }
    res.set_content(reply_data.dump(), "application/json");

    return;
}

int test_httplib_server_search_table()
{
    std::map<std::string, httplib::Server::Handler> get_uri_map = 
    {
        {"/api/hello", httplib_get_hello},
        {"/api/hi", httplib_get_hi}
    };
    std::map<std::string, httplib::Server::Handler> post_uri_map = 
    {
        {"/api/watch", httplib_post_watch}
    };

    httplib::Server server;
    for (auto& it : get_uri_map)
    {
        server.Get(it.first, it.second);
    }
    for (auto& it : post_uri_map)
    {
        server.Post(it.first, it.second);
    }

    server.listen("0.0.0.0", 13001);

    return 1;
}

int test_httplib_server_in_class()
{
    class Network
    {
    private:
        httplib::Server m_server;
        std::string m_data;
        int m_flag;

    public:
        Network() 
        {
            m_data = "hahahaha";
        }
        ~Network() 
        {
            m_data = "";
        }

        int Start(std::string ip, size_t port)
        {
            m_server.Get(R"(/api/(.*))", [this](const httplib::Request& req, httplib::Response& res){
                NetworkMessage network_message;

                network_message.path = req.path;
                network_message.method = req.method;
                for (auto& it : req.headers)
                {
                    network_message.request_headers[it.first] = it.second;
                }
                this->Dispatch(network_message);

                res.set_content(network_message.response, network_message.response_type);
            });
            m_server.Post(R"(/api/(.*))", [this](const httplib::Request& req, httplib::Response& res){
                NetworkMessage network_message;

                network_message.path = req.path;
                network_message.body = req.body;
                network_message.method = req.method;
                for (auto& it : req.headers)
                {
                    network_message.request_headers[it.first] = it.second;
                }
                this->Dispatch(network_message);

                res.set_content(network_message.response, network_message.response_type);
            });

            m_server.listen(ip, port);
            return 1;
        }

        void Dispatch(NetworkMessage& network_message)
        {
            if (network_message.path == "/api/get/robot")
            {
                network_message.response = "SIMRobot 3kg";
                network_message.response_type = "text/plain";
            }
            else if (network_message.path == "/api/post/tool")
            {
                nlohmann::json parsed_data;
                nlohmann::json reply_data;
                LOG(INFO) << "request path: " << network_message.path << "\n"
                          << "request body: " << network_message.body << "\n";
                try 
                {
                    parsed_data = nlohmann::json::parse(network_message.body);
                    m_flag = parsed_data["flag"];
                    reply_data["code"] = 1;
                }
                catch (nlohmann::json::parse_error& e)
                {
                    reply_data["code"] = 0;
                }
                catch (nlohmann::json::type_error& e)
                {
                    reply_data["code"] = 0;
                }

                network_message.response = reply_data.dump();
                network_message.response_type = "application/json";
            }
            else if (network_message.path == "/api/get/tool")
            {
                network_message.response = std::to_string(m_flag);
                network_message.response_type = "text/plain";
            }
            else 
            {
                network_message.response = "invalid uri";
                network_message.response_type = "text/plain";
            }
        }
    };

    Network network;

    network.Start("0.0.0.0", 13001);


    return 1;
}

int test_generate_sql()
{
    std::stringstream os;

    os << "ATTACH DATABASE 'testDB.db' as '" << std::string("TEMP") << "';";

    LOG(INFO) << os.str() << "\n";

    return 1;
}

int test_parse_restful_path()
{
    const std::string path = "/api/algorithm/list";
    std::vector<std::string> list;

    ExtractFields(path, list);

    for (auto& it : list)
    {
        LOG(INFO) << it << "\n";
    }

    LOG(INFO) << "input index: >>>" << "\n";
    int cmd;
    std::cin >> cmd;
    try
    {
        LOG(INFO) << list.at(cmd) << "\n";
    }
    catch (std::out_of_range& e)
    {
        LOG(ERROR) << e.what() << "\n";
        return 0;
    }

    return 1;
}

int test_map_class_member_function()
{
    class Dispatcher
    {
    private:
        typedef void(Dispatcher::* p_f)(std::string);
        std::map<std::string, p_f> m_map = 
        {
            {"say", &Dispatcher::say},
            {"hello", &Dispatcher::hello}
        };
    public:
        void Dispatch(std::string cmd)
        {
            auto it = m_map.find(cmd);
            if (it != m_map.end())
            {
                (this->*m_map[cmd])("hhh");
            }
            else 
            {
                LOG(ERROR) << "invalid command: " << cmd << "\n";
            }
        }

    private:
        void say(std::string msg)
        {
            LOG(INFO) << "msg: " << msg << "\n";
        }

        void hello(std::string msg)
        {
            LOG(INFO) << "hello world\n" << msg << "\n";
        }
    };

    Dispatcher d;

    d.Dispatch("say");

    return 1;
}

    class DDD
    {
    private:
        std::string m_data;

    public:
        DDD() = delete;
        DDD(const std::string in) : m_data(in)
        {
            
        }
        ~DDD()
        {
            
        }
    
    public:
        void Print()
        {
            LOG(INFO) << m_data << "\n";
        }
    };

    class tmp 
    {
    private:
        DDD m_d;

    public:
        static std::string data;

    public:
        tmp() : m_d(data)
        {

        }
        ~tmp()
        {
            
        }
    
    public:
        void Echo()
        {
            m_d.Print();
        }

        static void Initialization()
        {
            data = "hhhhh";
        }
    };
    std::string tmp::data = "";

int test_class_static_member_function()
{

    DDD d("hello");

    d.Print();

    tmp::Initialization();

    tmp t;
    t.Echo();

    return 1;
}

int test_nlohmann_json_vector()
{
    std::vector<int> nums = {1, 2, 3, 4};

    nlohmann::json data;

    data["num"] = nums;

    LOG(INFO) << data.dump() << "\n";

    return 1;
}

int test_nlohmann_json_array_to_vector()
{
    std::string json_string = R"(
        {
            "my_array": [1, 2, 3, 4]
        }
    )";

    nlohmann::json data = nlohmann::json::parse(json_string);

    std::vector<int> v = data["my_array"].get<std::vector<int>>();

    for (auto& it : v)
    {
        LOG(INFO) << "value: " << it << "\n";
    }

    return 1;
}

void parseHTTPRequest(const std::string& httpRequest) {
    std::istringstream requestStream(httpRequest);
    std::string requestLine;
    std::getline(requestStream, requestLine);

    // 解析请求行
    std::istringstream requestLineStream(requestLine);
    std::string method, path, protocol;
    requestLineStream >> method >> path >> protocol;

    // 输出请求行信息
    std::cout << "Method: " << method << std::endl;
    std::cout << "Path: " << path << std::endl;
    std::cout << "Protocol: " << protocol << std::endl;

    // 解析请求头部
    std::string headerLine;
    while (std::getline(requestStream, headerLine) && headerLine != "\r") {
        std::cout << "Header: " << headerLine << std::endl;
        // 在此处可以进一步解析头部信息并存储
    }

    // 解析请求数据（主体）
    std::string requestBody;
    std::getline(requestStream, requestBody, '\0'); // 读取请求主体
    std::cout << "Request Body: " << requestBody << std::endl;
}

int test_parse_http_protocol()
{
    std::string httpRequest = "POST /path/to/resource HTTP/1.1\r\n"
                              "Host: www.example.com\r\n"
                              "User-Agent: Mozilla/5.0\r\n"
                              "Content-Type: application/json\r\n"
                              "Content-Length: 26\r\n"
                              "\r\n"
                              "{\"key\": \"value\", \"num\": 42}";

    parseHTTPRequest(httpRequest);   
    
    return 1;
}

int test_openssl_base64_encode()
{
    const char *text = "Hello, this is a message to be encoded in Base64!";
    int length = strlen(text);
    char *encoded = base64_encode((const unsigned char *)text, length);

    printf("Base64 Encoded: %s\n", encoded);

    free(encoded);
    return 0;
}

int test_openssl_base64_decode()
{
    const char *encoded_text = "SGVsbG8sIHRoaXMgaXMgYSBtZXNzYWdlIHRvIGJlIGVuY29kZWQgaW4gQmFzZTY0IQ==";
    int length = strlen(encoded_text);
    unsigned char *decoded = base64_decode(encoded_text, length);

    printf("Base64 Decoded: %s\n", decoded);

    free(decoded);
    return 0;
}

int test_poll()
{
    int res{0};
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        LOG(ERROR) << "socket creation failed\n";
        return 0;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    server_addr.sin_port = htons(12001);

    int opt = 1;
    res = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (res == -1)
    {
        LOG(ERROR) << "set socket attribute failedn\n";
        return 0;
    }
    res = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (res == -1)
    {
        LOG(ERROR) << "set socket attribute failedn\n";
        return 0;
    }

    res = listen(server_socket, 5);
    if (res == -1)
    {
        LOG(ERROR) << "set socket attribute failedn\n";
        return 0;
    }

    size_t num_clients = 0;
    int max_size = 10;
    int client_sockets[max_size];
    memset(client_sockets, 0, sizeof(client_sockets));
    struct pollfd fds[max_size];
    fds[0].fd = server_socket;
    fds[0].events = POLLIN;
    num_clients++;
    struct sockaddr_in client_addr;
    
    while (1)
    {
        int activity = poll(fds, num_clients, -1);
        if (activity < 0)
        {
            LOG(ERROR) << "poll error \n";
            return 0;
        }
        if (fds[0].revents & POLLIN)
        {
            int new_socket;
            socklen_t len = sizeof(client_addr);
            new_socket = accept(server_socket, (struct sockaddr*)&client_addr, &len);
            if (new_socket < 0)
            {
                LOG(ERROR) << "accept failed\n";
                return 0;
            }

            int i;
            for (i = 1; i < max_size; i++)
            {
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = new_socket;
                    fds[i].fd = new_socket;
                    fds[i].events = POLLIN;
                    num_clients++;
                    break;
                }
            }
        }
        
        for (int i = 1; i < num_clients; i++)
        {
            if (fds[i].revents & POLLIN)
            {
                int valread;
                size_t buffer_max_size = 10240;
                char buffer[buffer_max_size];
                if ((valread = read(fds[i].fd, buffer, buffer_max_size)) <= 0)
                {
                    close(fds[i].fd);
                    client_sockets[i] = 0;
                    fds[i].fd = -1;
                    num_clients--;
                }
                else 
                {
                    // handle request and send response
                    printf("Received request:\n%s\n", std::string(buffer, valread).c_str());
                    const char* response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>Hello, this is a simple HTTP server in C</hi>\n";
                    write(fds[i].fd, response, strlen(response));
                    close(fds[i].fd);
                }
            }
        }
    }

    close(server_socket);

    return 1;
}

void signal_handler(int signum)
{
    printf("receive signal: %d\n", signum);
    exit(signum);
}

int test_signal()
{
    signal(SIGINT, signal_handler);

    std::thread tmp = std::thread([](){
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            LOG(INFO) << "hhh" << "\n";
        }
    });
    tmp.detach();

    std::this_thread::sleep_for(std::chrono::minutes(1));

    return 1;
}

int test_condition_variable()
{
    std::mutex mutex;
    std::condition_variable cv;

    std::thread work_thread = std::thread([](std::mutex &mutex, std::condition_variable &cv){
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [](){
                LOG(INFO) << "this is in cv.wait()\n";
                return false;
            });
            LOG(INFO) << "work...\n";
        }
    }, std::ref(mutex), std::ref(cv));

    std::string cmd;
    std::cin >> cmd;
    if (cmd == "notify")
    {
        cv.notify_one();
    }
    if (work_thread.joinable())
    {
        work_thread.join();
    }

    LOG(INFO) << "function quit...\n";
    return 1;
}

int test_anything(Message& message)
{
    std::map<std::string, std::function<int()>> cmd_map = {
        {"test-glog", test_glog},
        {"test-nlohmann-json-vector", test_nlohmann_json_vector},
        {"test-nlohmann-json-array-to-vector", test_nlohmann_json_array_to_vector},
        {"test-httplib-server", test_httplib_server},
        {"test-httplib-server-v2", test_httplib_server_v2},
        {"test-httplib-client-v2", test_httplib_client_v2},
        {"test-boost-log-trivial", test_boost_log_trivial},
        {"test-robot", test_robot},
        {"test-mnc", test_mnc},
        {"test-httplib-client", test_httplib_client},
        {"test-for-loop", test_for_loop},
        {"test-marco", test_marco},
        {"test-ceil", test_ceil},
        {"test-hashmap-1", test_hashmap_1},
        {"test-get-memery-info", GetMemInfo},
        {"test-generate-random-id", generateRandomMixedString},
        {"test-generate-random-id-v2", test_generate_random_id},
        {"test-eigen-hello", test_eigen_hello},
        {"test-eigen-vector3f", test_eigen_vector3f},
        {"test-ascii", test_ascii},
        {"test-asan", test_asan},
        {"process-request", processRequest},
        {"test-boost-asio-hello", test_boost_asio_hello},
        {"test-boost-beast-hello", test_boost_beast_hello},
        {"test-boost-beast-client", test_boost_beast_client},
        {"test-boost-beast-thread-pool", test_boost_asio_thread_pool},
        {"test-boost-asio-ip-tcp-socket", test_boost_asio_ip_tcp_socket},
        {"test-generate-target", test_generate_target},
        {"test-sort-book-class", test_sort_book_class},
        {"test-vector-multi-delete",test_vector_multi_delete},
        {"test-ifstream", test_ifstream_read_data},
        {"test-std-equal", test_std_equal},
        {"test-thread-hardware-concurrency", test_thread_hardware_concurrency},
        {"test-thread-lambda-creator", test_thread_lambda_creator},
        {"get-files-in-directory", GetFilesInDirectory},
        {"test-default-creator-function", test_default_creator_function},
        {"test-exception-logic-error", test_exception_logic_error},
        {"test-c-http-server", test_c_http_server},
        {"test-c-poll-http-server", test_c_poll_http_server},
        {"test-c-epoll-http-server", test_c_epoll_http_server},
        {"test-httplib-server-search-table", test_httplib_server_search_table},
        {"test-httplib-server-in-class", test_httplib_server_in_class},
        {"test-generate-sql", test_generate_sql},
        {"test-parse-restful-path", test_parse_restful_path},
        {"test-map-class-member-function", test_map_class_member_function},
        {"test-class-static-member-function", test_class_static_member_function},
        {"test-parse-http-protocol", test_parse_http_protocol},
        {"test-openssl-base64-encode", test_openssl_base64_encode},
        {"test-openssl-base64-decode", test_openssl_base64_decode},
        {"test-signal", test_signal},
        {"test-condition-variable", test_condition_variable}
    };
    std::string cmd = message.second_layer;
    auto it = cmd_map.find(cmd);
    if (it != cmd_map.end())
    {
        it->second();
        return 1;
    }
    std::cerr << "invalid command: " << cmd << std::endl;

    return 0;
}