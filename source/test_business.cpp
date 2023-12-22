/**
 * @file business.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "entry.hpp"
#include "TargetPool.hpp"

static int generate_target(TargetPool &out)
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
        Target_t target;
        target.first = i;
        target.second = {x_dis(gen), y_dis(gen), z_dis(gen), rx_dis(gen), ry_dis(gen), rz_dis(gen)};
        out.Push(target);
    }

    return 1;
}

int target_pool_business()
{
    LOG(INFO) << "hello" << "\n";
    Target_t target;
    TargetPool target_pool;

    generate_target(target_pool);

    while (true)
    {
        std::deque<Target_t> pool;
        target_pool.GetPool(pool);
        LOG(INFO) << "Original target pool: " << "\n";
        for (const auto &it : pool)
        {
            LOG(INFO) << it.second[0] << ", "
                      << it.second[1] << ", "
                      << it.second[2] << ", "
                      << it.second[3] << ", "
                      << it.second[4] << ", "
                      << it.second[5] << "\n";
        }
        int res = target_pool.Pop(target);
        if (res != 1)
        {
            LOG(WARNING) << "target pool is empty" << "\n";
            break;
        }
        LOG(INFO) << "cart info: " << "\n"
                  << "index: " << target.first << "\n"
                  << target.second[0] << ", "
                  << target.second[1] << ", "
                  << target.second[2] << ", "
                  << target.second[3] << ", "
                  << target.second[4] << ", "
                  << target.second[5] << "\n";
    }

    return 1;
}

int test_target_pool_area()
{
    // x: -0.186795, y: -0.436419, z: 0.0515753
    // -0.186795, -0.436419, 0.0515753
    TargetPoolV2::SpacePoint_t left_back_point(-0.5, -0.2, 0);
    TargetPoolV2::SpacePoint_t left_front_point(0, -0.2, 0);
    TargetPoolV2::SpacePoint_t right_back_point(-0.5, -0.7, 0);
    TargetPoolV2::SpacePoint_t right_front_point(0, -0.7, 0);

    TargetPoolV2::TargetArea_t target_area(left_back_point, right_back_point, left_front_point, right_front_point);

    TargetPoolV2::TargetPool target_pool;
    TargetPoolV2::Target_t target;

    target_pool.SetTargetArea(target_area);
    target.first.index = 1;
    target.second = {-0.186795, -0.436419, 0.0515753, 12, 23, 45};
    target_pool.Push(target);

    TargetPoolV2::Target_t tmp;
    int res = target_pool.Pop(tmp);
    if (res != 1)
    {
        LOG(WARNING) << "no target data" << "\n";
        return 0;
    }

    LOG(INFO) << "x: " << tmp.second.at(0) << ", y: " << tmp.second.at(1) << ", z: " << tmp.second.at(2) << "\n";
    return 1;
}

/**
    #使能方法。
    #static：静态网络配置。
    #dhcp：动态网络配置。
    #resolv：DNS服务器地址配置。
    --enable
    static

    #网卡名称。
    --ifname
    eth1

    #IPV4地址，掩码前缀长度，网关，跃点
    #注1：网关和跃点可以为空，但分割符必须存在。
    #注2：如果存在多个网关，则必须指定不同的跃点。
    #注3：第一个网关，将被指定为默认网关。
    --address4
    192.168.1.150,24,192.168.1.1,0
    172.16.1.150,16,172.16.1.1,100

    #IPV6地址，掩码前缀长度，网关，跃点
    --address6
    fe80::6e2b:59ff:feec:9447,64,fe80::6e2b:59ff:feec:9447::0001,0
 */
int modify_ip_config()
{
    std::string config_file = "/data/home/user/workspace/unit_test/data/ip_config.txt";
    nlohmann::json request_data;

    request_data["enable"] = "static";
    request_data["ifname"] = "eth0";
    request_data["address4"] = "192.169.5.68";
    request_data["netmask"] = "16";
    request_data["gateway"] = "192.169.4.1";
    request_data["address6"] = "fe80::6e2b:59ff:feec:9447,64,fe80::6e2b:59ff:feec:9447::0001,0";

    std::string output_data = request_data.dump();

    LOG(INFO) << "request data: " << "\n"
              << output_data << "\n";

    std::fstream file(config_file, std::ios::in | std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        LOG(ERROR) << "can't not open file: " << config_file << "\n";
        return 0;
    }

    std::ostringstream os_out;

    os_out << "# 使能方法:" << "\n"
           << "--enable" << "\n"
           << std::string(request_data["enable"]) << "\n"
           << "# 网卡名称: " << "\n"
           << "--ifname" << "\n"
           << std::string(request_data["ifname"]) << "\n"
           << "# IPV4地址: " << "\n"
           << "--address4" << "\n"
           << std::string(request_data["address4"]) << ", " << std::string(request_data["netmask"]) << ", " << std::string(request_data["gateway"]) << "\n";

    file.write(os_out.str().c_str(), os_out.str().size());

    file.close();

    return 1;
}

int multi_modify_ip_config()
{
    std::string config_dir = "/data/home/user/workspace/unit_test/data/";
    nlohmann::json request_data;
    nlohmann::json item_data;

    item_data["enable"] = "static";
    item_data["ifname"] = "eth0";
    item_data["address4"] = "192.169.5.68";
    item_data["netmask"] = "16";
    item_data["gateway"] = "192.169.4.1";
    item_data["address6"] = "fe80::6e2b:59ff:feec:9447,64,fe80::6e2b:59ff:feec:9447::0001,0";
    request_data["ip_config_array"].push_back(item_data);

    item_data["enable"] = "dhcp";
    item_data["ifname"] = "eth1";
    request_data["ip_config_array"].push_back(item_data);

    std::string output_data = request_data.dump();

    LOG(INFO) << "request data: " << "\n"
              << output_data << "\n";

    for (auto& it : request_data["ip_config_array"])
    {
        std::string config_file = config_dir + std::string(it["enable"]) + ".conf";
        std::fstream file(config_file, std::ios::in | std::ios::out | std::ios::trunc);
        if (!file.is_open())
        {
            LOG(ERROR) << "can't not open file: " << config_file << "\n";
            return 0;
        }

        std::ostringstream os_out;

        os_out << "# 使能方法:" << "\n"
            << "--enable" << "\n"
            << std::string(it["enable"]) << "\n"
            << "# 网卡名称: " << "\n"
            << "--ifname" << "\n"
            << std::string(it["ifname"]) << "\n"
            << "# IPV4地址: " << "\n"
            << "--address4" << "\n"
            << std::string(it["address4"]) << ", " << std::string(it["netmask"]) << ", " << std::string(it["gateway"]) << "\n";

        file.write(os_out.str().c_str(), os_out.str().size());

        file.close();
    }

    return 1;
}

/**
I20231207 17:21:36.527149 66512 zhangjunyi_business.cpp:1204] point cloud compute successfully
I20231207 17:21:36.527206 66512 zhangjunyi_business.cpp:1214] index: 0
timestamp: 2.67614e+06
timestamp_str: 2676142.992336
x: -0.317008,y: -0.444065,z: 0.0538538,rx: -2.70031,ry: -1.57728,rz: 0.015535
I20231207 17:21:36.527253 66512 TargetPool.hpp:321] x: -0.317008, y: -0.444065, z: 0.0538538
I20231207 17:21:36.527272 66512 zhangjunyi_business.cpp:1214] index: 1
timestamp: 2.67614e+06
timestamp_str: 2676142.992336
x: -0.585516,y: -0.411483,z: 0.0589553,rx: -2.27372,ry: -2.13099,rz: 0.0251893
I20231207 17:21:36.527297 66512 TargetPool.hpp:321] x: -0.317008, y: -0.444065, z: 0.0538538
I20231207 17:21:36.527312 66512 TargetPool.hpp:321] x: -0.585516, y: -0.411483, z: 0.0589553
I20231207 17:21:36.527329 66512 zhangjunyi_business.cpp:1214] index: 2
timestamp: 2.67614e+06
timestamp_str: 2676142.992336
x: 0.371249,y: -0.512091,z: 0.0415001,rx: 3.12769,ry: -0.0613223,rz: -0.0235519
 * 
 */
int test_target_pool_double_free()
{
    TargetPoolV2::Target_t target;
    TargetPoolV2::TargetPool target_pool;

    TargetPoolV2::SpacePoint_t detect_area_left_back_point(-0.5, -0.2, 0);
    TargetPoolV2::SpacePoint_t detect_area_left_front_point(0, -0.2, 0);
    TargetPoolV2::SpacePoint_t detect_area_right_back_point(-0.5, -0.7, 0);
    TargetPoolV2::SpacePoint_t detect_area_right_front_point(0, -0.7, 0);
    TargetPoolV2::TargetArea_t detect_area(detect_area_left_back_point, detect_area_right_back_point, detect_area_left_front_point, detect_area_right_front_point);

    target_pool.SetTargetArea(detect_area);

    target.first.index = 0;
    target.second = {-0.317008, -0.444065, 0.0538538, -2.70031, -1.57728, 0.015535};
    target_pool.Push(target);

    target.first.index = 1;
    target.second = {-0.585516, -0.411483, 0.0589553, -2.27372, -2.13099, 0.0251893};
    target_pool.Push(target);

    target.first.index = 2;
    target.second = {0.371249, -0.512091, 0.0415001, 3.12769, -0.0613223, -0.0235519};
    target_pool.Push(target);

    return 1;
}

// x: 0.241932,y: -0.443853,z: 0.053811,rx: -2.6995,ry: -1.57606,rz: 0.0188795
int test_grab_area_target_pool()
{
    TargetPoolV2::Target_t target;
    TargetPoolV2::TargetPool grab_area_target_pool;
    TargetPoolV2::SpacePoint_t grab_area_left_back_point(0.2, -0.2, 0);
    TargetPoolV2::SpacePoint_t grab_area_left_front_point(0.45, -0.2, 0);
    TargetPoolV2::SpacePoint_t grab_area_right_back_point(0.2, -0.45, 0);
    TargetPoolV2::SpacePoint_t grab_area_right_front_point(0.45, -0.45, 0);
    TargetPoolV2::TargetArea_t grab_area(grab_area_left_back_point, grab_area_right_back_point, grab_area_left_front_point, grab_area_right_front_point);

    grab_area_target_pool.SetTargetArea(grab_area);
    target.first.index = 0;
    target.second = {0.241932, -0.443853, 0.053811, -2.6995, -1.57606, 0.0188795};
    grab_area_target_pool.Push(target);

    while (true)
    {
        TargetPoolV2::Target_t tmp_target;
        int res = grab_area_target_pool.Pop(tmp_target);
        if (res != 1)
        {
            break;
        }
        LOG(INFO) << "index: " << target.first.index << "\n"
                  << target.second[0] << ", "
                  << target.second[1] << ", "
                  << target.second[2] << ", "
                  << target.second[3] << ", "
                  << target.second[4] << ", "
                  << target.second[5] << "\n";       
    }

    return 1;
}

// 192.169.5.68, 16, 192.169.4.1
int test_parse_string_in_regex()
{
    // std::string data_str = "192.169.5.68, 16, 192.169.4.1";
    std::string data_str = "192.169.5.68, 16, ";

    std::vector<char> addr, netmask, gateway;
    addr.resize(20);
    netmask.resize(20);
    gateway.resize(20);

    int num = std::sscanf(data_str.c_str(), "%[^,], %[^,], %[^,]", addr.data(), netmask.data(), gateway.data());
    LOG(INFO) << "address: " << std::string(addr.data()) << "\n"
                << "netmask: " << std::string(netmask.data()) << "\n"
                << "gateway: " << std::string(gateway.data()) << "\n";

    return 1;
}

// 192.169.5.68, 16, 192.169.4.1
int test_parse_string_in_regex_v2()
{
    // std::string data_str = "192.169.5.68, 16, 192.169.4.1";
    std::string data_str = "192.169.5.68, 16, ";

    std::string addr, netmask, gateway;

    int cnt = 0;
    for (auto& it : data_str)
    {
        if (it != ',' && cnt == 0)
        {
            addr += it;
        }
        else if (it != ',' && cnt == 1)
        {
            netmask += it;
        }
        else if (it != ',' && cnt == 2)
        {
            gateway += it;
        }
        else 
        {
            cnt++;
        }
    }

    LOG(INFO) << "addr: " << addr << "\n"
              << "netmask: " << netmask << "\n"
              << "gateway: " << gateway << "\n";

    return 1;
}

bool test_CheckSubnetMask(const std::string subnet_mask)
{
    bool found_zero = false;
    std::string tmp = subnet_mask;
    tmp.erase(std::remove(tmp.begin(), tmp.end(), '.'), tmp.end());
    std::bitset<32> bits(tmp);

    for (int i = 31; i >= 0; --i)
    {
        if (!bits.test(i))
        {
            found_zero = true;
        }
        else if (found_zero)
        {
            return false;
        }
    }

    return true;
}

// 255.255.0.0
/**
 * @brief 十进制子网掩码转二进制，并输出CIDR(classless inter-domain routing，无类域间路由)
 * 
 * @return int 
 */
int test_DecimalToBinarySubnetMask()
{
    const std::string subnet_mask = "255.255.0.0";
    // const std::string subnet_mask = "255.255.0.255";

    std::stringstream ss(subnet_mask);
    std::string segment;
    std::vector<int> decimal_segments;

    while (std::getline(ss, segment, '.'))
    {
        int decimal_value = std::stoi(segment);
        decimal_segments.push_back(decimal_value);
    }

    std::string binary_subnet_mask;
    int subnet_mask_number = 0;
    for (int segment_value : decimal_segments)
    {
        std::bitset<8> bits(segment_value);
        subnet_mask_number += bits.count();
        binary_subnet_mask += bits.to_string();
        binary_subnet_mask += ".";
    }

    binary_subnet_mask.pop_back();

    if (test_CheckSubnetMask(binary_subnet_mask))
    {
        LOG(INFO) << "decimal subnet mask: " << subnet_mask << "\n" 
                  << "subnet mask number: " << subnet_mask_number << "\n"
                  << "binary subnet mask: " << binary_subnet_mask << "\n";
    }
    else 
    {
        LOG(ERROR) << "decimal subnet mask: " << subnet_mask << "\n" 
                   << "subnet mask number: " << subnet_mask_number << "\n"
                   << "binary subnet mask: " << binary_subnet_mask << "\n";
    }

    return 1;
}

int test_BinaryToDecimalSubnetMask()
{
    const std::string binary_subnet_mask = "11111111.11111111.00000000.00000000";    
    
    std::stringstream ss(binary_subnet_mask);
    std::string segment;
    std::vector<std::string> binary_segments;

    while (std::getline(ss, segment, '.'))
    {
        std::bitset<8> bits(segment);
        std::stringstream s;
        s << bits.to_ulong();
        binary_segments.push_back(s.str());
    }

    std::string decimal_subnet_mask;
    for (const std::string& segment_value : binary_segments)
    {
        decimal_subnet_mask += segment_value;
        decimal_subnet_mask += ".";
    }

    decimal_subnet_mask.pop_back();

    LOG(INFO) << "binary subnet mask: " << binary_subnet_mask << "\n"
              << "decimal subnet mask: " << decimal_subnet_mask << "\n";

    return 1;
}

int test_CIDRToDecimalSubnetMask()
{
    // int cidr = 16;
    int cidr = 15;
    std::bitset<32> bits;
    std::vector<std::bitset<8>> binary_subnet_mask_array(4, std::bitset<8>(0));
    // std::vector<std::bitset<8>> binary_subnet_mask_array;
    // binary_subnet_mask_array.resize(4);
    
    for (int i = 0; i < cidr; i++)
    {
        binary_subnet_mask_array.at(i / 8).set(i % 8);
    }
    std::string decimal_subnet_mask;
    for (auto& binary_subnet_mask : binary_subnet_mask_array)
    {
        decimal_subnet_mask += std::to_string(binary_subnet_mask.to_ulong());
        decimal_subnet_mask += ".";
    }
    decimal_subnet_mask.pop_back();

    LOG(INFO) << "CIDR: " << cidr << "\n"
              << "decimal subnet mask: " << decimal_subnet_mask << "\n";
    
    return 1;
}

int test_vcr_get_velocity()
{
    httplib::Client cli("http://192.169.0.152:28001");

    auto res = cli.Get("/api/detectors/detector/getVelocity");
    if (res.error() != httplib::Error::Success)
    {
        LOG(ERROR) << "Get request failed \n";
        return 0;
    }

    LOG(INFO) << "response body data: \n"
              << res->body << "\n";
 
    return 1;
}

int test_vcr_vision_algorithm()
{
    int ec {0};
    const std::string vision_algorithm_dir = "/data/vcr/VisionAlgorithms/";
    std::vector<std::string> files;
    std::vector<std::string> directorys;

    ec = get_dir_and_file_from_path(vision_algorithm_dir, directorys, files);
    if (ec != 1)
    {
        return 0;
    }

    std::vector<std::string> json_configs;
    for (const std::string& directory : directorys)
    {
        std::string tmp_dir_path = vision_algorithm_dir + directory;
        std::vector<std::string> tmp_directorys;
        std::vector<std::string> tmp_files;
        ec = get_dir_and_file_from_path(tmp_dir_path, tmp_directorys, tmp_files);
        if (ec != 1)
        {
            LOG(ERROR) << "Invalid directory value: " << tmp_dir_path << "\n";
            continue;
        }
        for (const std::string& tmp_file : tmp_files)
        {
            if (tmp_file == "detector.json")
            {
                std::string tmp_dir = tmp_dir_path + "/" + tmp_file;
                json_configs.push_back(tmp_dir);
            }
        }
    }

    std::vector<DetectorConfig> detector_configs;
    for (const std::string& json_config : json_configs)
    {
        LOG(INFO) << "json configuration file path: " << json_config << "\n";
        DetectorConfig detector_config;
        nlohmann::json parsed_data;
        std::ifstream file(json_config, std::ios::in);
        
        if (!file.is_open())
        {
            LOG(ERROR) << "Invalid json config file: " << json_config << "\n";
            continue;
        }
        try 
        {
            file >> parsed_data;
            detector_config.detector_type = parsed_data["detector-type"];
            detector_config.detector_gap = parsed_data["detector-gap"];
            detector_config.detector_fps = parsed_data["detector-fps"];
            detector_config.detector_thresholds = parsed_data["detector-thresholds"];
            detector_config.tracker_type = parsed_data["tracker-type"];
            detector_config.trace_case = parsed_data["trace-case"];
            detector_config.detector_model.name = parsed_data["detector-models"]["name"];
            for (auto& file : parsed_data["detector-models"]["file"])
            {
                detector_config.detector_model.file.push_back(std::string(file));
            }
            detector_config.detector_model.type = parsed_data["detector-models"]["type"];
        }
        catch (nlohmann::json::parse_error &e)
        {
            LOG(ERROR) << "parse error: " << e.what() << "\n";
            file.close();
            continue;
        }
        catch (nlohmann::json::type_error &e)
        {
            LOG(ERROR) << "type error: " << e.what() << "\n";
            file.close();
            continue;
        }
        detector_configs.push_back(detector_config);
    }

    for (const auto& detector_config : detector_configs)
    {
        LOG(INFO) << "detector-type: " << detector_config.detector_type << "\n"
                  << "detector-fps: " << detector_config.detector_fps << "\n";
        for (const auto& it : detector_config.detector_model.file)
        {
            LOG(INFO) << "model file path: " << it << "\n";
        }
    }

    return 1;
}

int test_manage_multi_object()
{
    // 抽象类 Shape
    class Shape {
    public:
        // 纯虚函数，用于表示不同功能的对象
        virtual void draw() const = 0;
    };

    // 派生类 Circle
    class Circle : public Shape {
    public:
        void draw() const override {
            std::cout << "Drawing a circle" << std::endl;
            // 在这里实现绘制圆的具体功能
        }
    };

    // 派生类 Rectangle
    class Rectangle : public Shape {
    public:
        void draw() const override {
            std::cout << "Drawing a rectangle" << std::endl;
            // 在这里实现绘制矩形的具体功能
        }
    };

    Circle circle;
    Rectangle rectangle;

    Shape* shapes[] = {&circle, &rectangle};

    for (Shape* shape : shapes)
    {
        shape->draw();
    }

    int cmd;
    std::cin >> cmd;

    Robot* robot;

    switch (static_cast<RobotList>(cmd))
    {
        case RobotList::COB:
        {
            robot = new Cob();
            break;
        }
        case RobotList::DOB:
        {
            robot = new Dob();
            break;
        }
        case RobotList::EOB:
        {
            robot = new Eob();
            break;
        }
        default:
        {
            LOG(ERROR) << "Invalid valud" << "\n";
            return 0;
        }
    }

    LOG(INFO) << "robot's product: " << robot->Product() << "\n";

    std::vector<Robot*> robots;
    std::vector<int> cmds;

    while (true)
    {
        int tmp_cmd = 0;
        std::cin >> tmp_cmd;
        if (tmp_cmd == 0)
        {
            LOG(WARNING) << "quit...\n";
            break;
        }
        cmds.push_back(tmp_cmd);
    }
    for (const int i : cmds)
    {
        Robot* tmp_robot {nullptr};
        switch (static_cast<RobotList>(i))
        {
            case RobotList::COB:
            {
                tmp_robot = new Cob();
                break;
            }
            case RobotList::DOB:
            {
                tmp_robot = new Dob();
                break;
            }
            case RobotList::EOB:
            {
                tmp_robot = new Eob();
                break;
            }
            default:
            {
                LOG(ERROR) << "Invalid valud" << "\n";
                return 0;
            }
        }
        robots.push_back(tmp_robot);
    }
    
    LOG(INFO) << "multi robot:\n";
    for (Robot* it : robots)
    {
        LOG(INFO) << "robot's product: " << it->Product() << "\n";
        delete it;
        it = nullptr;
    }

    return 1;
}

int test_robot_pool()
{
    class RobotPool
    {
    private:
        std::vector<std::pair<RobotList, Robot*>> m_pool;
        unsigned int m_size;

    public:
        RobotPool() = delete;
        RobotPool(int max_size) : m_size(max_size)
        {

        }
        virtual ~RobotPool()
        {
            Clear();                                                                                
        }

    public:
        int Push(std::pair<RobotList, Robot*> robot)
        {
            m_pool.push_back(robot);

            return 1;
        }

        int Pop(RobotList robot_product, std::pair<RobotList, Robot*>& target)
        {
            auto it = std::find_if(m_pool.begin(), m_pool.end(), [=](std::pair<RobotList, Robot*> robot){
                return robot.first == robot_product;
            });

            if (it != m_pool.end())
            {
                target = *it;
                return 1;
            }

            LOG(ERROR) << "Invalid robot list enum value: " << static_cast<int>(robot_product) << "\n";

            return 0;
        }

        void Clear()
        {
            for (std::pair<RobotList, Robot*> robot : m_pool)
            {
                if (robot.second != nullptr)
                {
                    delete robot.second;
                    robot.second = nullptr;
                }
            }
            m_pool.clear();
        }
    };

    RobotPool robot_pool(10);
    std::vector<int> cmds;

    while (true)
    {
        int tmp_cmd = 0;
        std::cin >> tmp_cmd;
        if (tmp_cmd == 0)
        {
            LOG(WARNING) << "quit...\n";
            break;
        }
        cmds.push_back(tmp_cmd);
    }
    for (int cmd : cmds)
    {
        Robot* tmp_robot {nullptr};
        switch (static_cast<RobotList>(cmd))
        {
            case RobotList::COB:
            {
                tmp_robot = new Cob();
                robot_pool.Push(std::make_pair(RobotList::COB, tmp_robot));
                break;
            }
            case RobotList::DOB:
            {
                tmp_robot = new Dob();
                robot_pool.Push(std::make_pair(RobotList::DOB, tmp_robot));
                break;
            }
            case RobotList::EOB: 
            {
                tmp_robot = new Eob();
                robot_pool.Push(std::make_pair(RobotList::EOB, tmp_robot));
                break;
            }
            default:
            {
                LOG(ERROR) << "Invalid valud" << "\n";
                return 0;
            }
        }
    }

    int cmd;
    std::cin >> cmd;
    std::pair<RobotList, Robot*> robot;
    int res = robot_pool.Pop(static_cast<RobotList>(cmd), robot);
    if (res != 1)
    {
        return 0;
    }

    LOG(INFO) << "input command: " << cmd << ", and the robot's product is: " << robot.second->Product() << "\n";

    return 1;
}

int test_template_robot_pool()
{
    ObjectPool<RobotList, Robot> robot_pool(10);
    std::vector<int> cmds;

    while (true)
    {
        int tmp_cmd = 0;
        std::cin >> tmp_cmd;
        if (tmp_cmd == 0)
        {
            LOG(WARNING) << "quit...\n";
            break;
        }
        cmds.push_back(tmp_cmd);
    }
    for (int cmd : cmds)
    {
        Robot* tmp_robot {nullptr};
        switch (static_cast<RobotList>(cmd))
        {
            case RobotList::COB:
            {
                tmp_robot = new Cob();
                robot_pool.Push(std::make_pair(RobotList::COB, tmp_robot));
                break;
            }
            case RobotList::DOB:
            {
                tmp_robot = new Dob();
                robot_pool.Push(std::make_pair(RobotList::DOB, tmp_robot));
                break;
            }
            case RobotList::EOB: 
            {
                tmp_robot = new Eob();
                robot_pool.Push(std::make_pair(RobotList::EOB, tmp_robot));
                break;
            }
            default:
            {
                LOG(ERROR) << "Invalid valud" << "\n";
                return 0;
            }
        }
    }

    int cmd;
    std::cin >> cmd;
    ObjectPool<RobotList, Robot>::Object_t robot;
    int res = robot_pool.Pop(static_cast<RobotList>(cmd), robot);
    if (res != 1)
    {
        return 0;
    }

    LOG(INFO) << "input command: " << cmd << ", and the robot's product is: " << robot.second->Product() << "\n";

    return 1;
}

int test_template_robot_pool_in_class()
{
    class RoboticArm 
    {
    private:
        const std::vector<std::pair<RobotList, std::string>> m_robot_list = 
        {
            {RobotList::COB, "cob"},
            {RobotList::DOB, "dob"},
            {RobotList::EOB, "eob"}
        };

    private:
        ObjectPool<RobotList, Robot> m_robot_pool;

    public:
        RoboticArm() = delete;
        RoboticArm(unsigned int max_size) : m_robot_pool(max_size)
        {

        }
        virtual ~RoboticArm()
        {

        }

    public:
        void List(std::vector<std::string>& list)
        {
            for (auto& robotic_arm : m_robot_list)
            {
                list.push_back(robotic_arm.second);
            }
        }
        int Create(std::string product)
        {
            auto it = std::find_if(m_robot_list.begin(), m_robot_list.end(), [=](std::pair<RobotList, std::string> robot){
                return robot.second == product;
            });
            if (it != m_robot_list.end())
            {
                switch (it->first)
                {
                    case RobotList::COB:
                    {
                        Robot* tmp_robot = new Cob();
                        m_robot_pool.Push(std::make_pair(it->first, tmp_robot));
                        break;
                    }
                    case RobotList::DOB:
                    {
                        Robot* tmp_robot = new Dob();
                        m_robot_pool.Push(std::make_pair(it->first, tmp_robot));
                        break;
                    }
                    case RobotList::EOB:
                    {
                        Robot* tmp_robot = new Eob();
                        m_robot_pool.Push(std::make_pair(it->first, tmp_robot));
                        break;
                    }
                    default:
                    {
                        LOG(ERROR) << "Invalid value: " << static_cast<int>(it->first) << "\n";
                        break;
                    }
                }
                return 1;
            }
            LOG(ERROR) << "Invalid robot's product: " << product << "\n";

            return 0;
        }
        void Destroy(std::string product)
        {
            auto it = std::find_if(m_robot_list.begin(), m_robot_list.end(), [=](std::pair<RobotList, std::string> robot) {
                return robot.second == product;
            });
            if (it != m_robot_list.end())
            {
                m_robot_pool.Delete(it->first);
            }
        }
        int Message(std::string product, std::string& message)
        {
            auto it = std::find_if(m_robot_list.begin(), m_robot_list.end(), [=](std::pair<RobotList, std::string> robot) {
                return robot.second == product;
            });
            if (it != m_robot_list.end())
            {
                std::pair<RobotList, Robot*> robot;
                int res = m_robot_pool.Pop(it->first, robot);
                if (res == 1)
                {
                    message = std::string(robot.second->Product());
                    return 1;
                }
            }

            return 0;
        }
    };

    RoboticArm robotic_arm(10);

    std::vector<std::string> robotic_arm_list;
    robotic_arm.List(robotic_arm_list);
    LOG(INFO) << "robotic arm's list: \n";
    for (auto &it : robotic_arm_list)
    {
        LOG(INFO) << it << "\n";
    }
    
    std::string cmd;
    std::cin >> cmd;
    int res = robotic_arm.Create(cmd);
    if (res != 1)
    {
        LOG(ERROR) << "create robotic arm failed, cmd: " << cmd << "\n";
        return 0;
    }
    std::string message;
    res = robotic_arm.Message(cmd, message);
    if (res != 1)
    {
        LOG(ERROR) << "receive robotic arm's message failed, cmd: " << cmd << "\n";
        return 0;
    }

    LOG(INFO) << "robotic arm(" << cmd << ")'s message is: " << message << "\n";

    return 1;
}

int test_template_tool_pool()
{
    ObjectPool<ToolList, Tool> tool_pool(10);
    std::vector<int> cmds;

    while (true)
    {
        int tmp_cmd = 0;
        std::cin >> tmp_cmd;
        if (tmp_cmd == 0)
        {
            LOG(WARNING) << "quit...\n";
            break;
        }
        cmds.push_back(tmp_cmd);
    }
    for (int cmd : cmds)
    {
        switch (static_cast<ToolList>(cmd))
        {
            case ToolList::SUCKER:
            {
                Tool* tmp_tool {nullptr};
                tmp_tool = new Sucker();
                tool_pool.Push(std::make_pair(ToolList::SUCKER, tmp_tool));
                break;
            }
            case ToolList::JAW:
            {
                Tool* tmp_tool {nullptr};
                tmp_tool = new Jaw();
                tool_pool.Push(std::make_pair(ToolList::JAW, tmp_tool));
                break;
            }
            default:
            {
                LOG(ERROR) << "Invalid value: " << cmd << "\n";
                return 0;
            }
        }
    }

    int cmd = 0;
    std::cin >> cmd;
    ObjectPool<ToolList, Tool>::Object_t tool;
    int res = tool_pool.Pop(static_cast<ToolList>(cmd), tool);
    if (res != 1)
    {
        LOG(ERROR) << "Invalid value: " << cmd << "\n";
        return 0;
    }

    LOG(INFO) << "tool's product: " << tool.second->Product() << "\n";

    return 1;
}

int get_devices_config(const std::string config_path, std::vector<RoboticArmConfig>& robotic_arm_configs)
{
    std::ifstream file(config_path, std::ios::in);
    if (!file.is_open())
    {
        LOG(ERROR) << "Invalid config path: " << config_path << "\n";
        return 0;
    }

    nlohmann::json parsed_data;
    try
    {
        file >> parsed_data;
        for (auto& it : parsed_data["robotic_arm"])
        {
            RoboticArmConfig robotic_arm_config;
            robotic_arm_config.meta.product = it["meta"]["product"];
            robotic_arm_config.meta.vendor = it["meta"]["vendor"];
            robotic_arm_config.address.ip = it["address"]["ip"];
            robotic_arm_config.address.port = it["address"]["port"];
            robotic_arm_config.GenerateHashId();
            robotic_arm_configs.push_back(robotic_arm_config);
        }
        file.close();
    }
    catch (nlohmann::json::parse_error& e)
    {
        LOG(ERROR) << "parse error, config file path: " << config_path << "\n";
        file.close();
        return 0;
    }
    catch (nlohmann::json::type_error& e)
    {
        LOG(ERROR) << "type error, config file path: " << config_path << "\n";
        file.close();
        return 0;
    }

    return 1;
}

int test_parse_devices_config()
{
    const std::string config_path = "/data/vcr/Configurations/devices.json";
    std::vector<RoboticArmConfig> robotic_arm_configs;

    int res = get_devices_config(config_path, robotic_arm_configs);
    if (res != 1)
    {
        return 0;
    }

    for (auto& robotic_arm_config : robotic_arm_configs)
    {
        LOG(INFO) << "product: " << robotic_arm_config.meta.product << "\n"
                  << "vendor: " << robotic_arm_config.meta.vendor << "\n"
                  << "hash id: " << robotic_arm_config.hash_id << "\n";
    }

    return 1;
}

int test_template_robot_pool_in_class_hash_id()
{
    class RoboticArm 
    {
    private:
        ObjectPool<std::string, Robot> m_robot_pool;
        std::vector<RoboticArmConfig> m_robotic_arm_configs;
        std::string m_config_path;

    public:
        RoboticArm() = delete;
        RoboticArm(unsigned int max_size, const std::string config_path) : m_robot_pool(max_size), m_config_path(config_path)
        {
            if (get_devices_config(m_config_path, m_robotic_arm_configs) != 1)
            {
                throw std::logic_error("invalid config");
            }
            for (auto& robotic_arm_config : m_robotic_arm_configs)
            {
                if (robotic_arm_config.meta.product == "SIMRobot" &&
                    robotic_arm_config.meta.vendor == "3kg")
                {
                    Robot* tmp_robot = new SIMRobot3kg();
                    m_robot_pool.Push(std::make_pair(robotic_arm_config.hash_id, tmp_robot));
                }
                else if (robotic_arm_config.meta.product == "SIMRobot" && 
                         robotic_arm_config.meta.vendor == "10kg")
                {
                    Robot* tmp_robot = new SIMRobot10kg();
                    m_robot_pool.Push(std::make_pair(robotic_arm_config.hash_id, tmp_robot));
                }
                else 
                {
                    LOG(WARNING) << "invalid robotic arm's meta information\n";
                }
            }
        }
        virtual ~RoboticArm()
        {

        }

    public:
        void List(std::vector<std::string>& list)
        {
            for (auto& robotic_arm : m_robotic_arm_configs)
            {
                list.push_back(robotic_arm.hash_id);
            }
        }

        Robot* GetRobotPointer(std::string hash_id)
        {
            auto it = std::find_if(m_robotic_arm_configs.begin(), m_robotic_arm_configs.end(), [=](RoboticArmConfig robotic_arm_config) {
                return robotic_arm_config.hash_id == hash_id;
            });
            if (it != m_robotic_arm_configs.end())
            {
                ObjectPool<std::string, Robot>::Object_t robot;
                int res = m_robot_pool.GetObjectRef(it->hash_id, robot);
                if (res == 1)
                {
                    return robot.second;
                }
            }

            return nullptr;
        }
    };

    RoboticArm robotic_arm(10, std::string("/data/vcr/Configurations/devices.json"));

    std::vector<std::string> robotic_arm_list;
    robotic_arm.List(robotic_arm_list);
    LOG(INFO) << "robotic arm's list: \n";
    for (auto &it : robotic_arm_list)
    {
        LOG(INFO) << it << "\n";
    }
    
    std::string cmd;
    std::cin >> cmd;
    std::string message;
    Robot* tmp_robot = robotic_arm.GetRobotPointer(cmd);
    if (tmp_robot == nullptr)
    {
        LOG(ERROR) << "receive robotic arm's message failed, cmd: " << cmd << "\n";
        return 0;
    }

    LOG(INFO) << "robotic arm(" << cmd << ")'s message is: " << std::string(tmp_robot->Product()) << "\n";

    return 1;
}

int test_rk_sound_file_management()
{
    int res = 0;
    const std::string sound_directory = "/home/user/zjy-190/Media/";
    std::vector<std::string> directorys;
    std::vector<std::string> files;

    res = get_dir_and_file_from_path(sound_directory, directorys, files);
    if (res != 1)
    {
        LOG(ERROR) << "invalid directory: " << sound_directory << "\n";
        return 0;
    }

    nlohmann::json reply_data;
    for (auto &file : files)
    {
        LOG(INFO) << "file: " << sound_directory + file << "\n";
        reply_data["list"].push_back(file);
    }
    std::cerr << reply_data.dump() << "\n";

    return 1;
}

int test_business(Message& message)
{
    LOG(INFO) << "test business begin..." << "\n";

    std::map<std::string, std::function<int()>> cmd_map = {
        {"target-pool-business", target_pool_business},
        {"test-target-pool-area", test_target_pool_area},
        {"modify-ip-config", modify_ip_config},
        {"multi-modify-ip-config", multi_modify_ip_config},
        {"test-target-pool-double-free", test_target_pool_double_free},
        {"test-grab-area-target-pool", test_grab_area_target_pool},
        {"test-parse-string-in-regex", test_parse_string_in_regex},
        {"test-parse-string-in-regex-v2", test_parse_string_in_regex_v2},
        {"test-decimal-to-binary-subnet-mask", test_DecimalToBinarySubnetMask},
        {"test-binary-to-decimal-subnet-mask", test_BinaryToDecimalSubnetMask},
        {"test-cidr-to-decimal-subnet-mask", test_CIDRToDecimalSubnetMask},
        {"test-vcr-get-velocity", test_vcr_get_velocity},
        {"test-vcr-vision-algorithm", test_vcr_vision_algorithm},
        {"test-manage-multi-object", test_manage_multi_object},
        {"test-robot-pool", test_robot_pool},
        {"test-template-tool-pool", test_template_tool_pool},
        {"test-template-robot-pool-in-class", test_template_robot_pool_in_class},
        {"test-parse-devices-config", test_parse_devices_config},
        {"test-template-robot-pool-in-class-hash-id", test_template_robot_pool_in_class_hash_id},
        {"test-rk-sound-file-management", test_rk_sound_file_management}
    };
    std::string cmd = message.message_pool[2];
    auto it = cmd_map.find(cmd);
    if (it != cmd_map.end())
    {
        it->second();
        return 1;
    }
    LOG(ERROR) << "invalid command: " << cmd << "\n";
    LOG(INFO) << "test business end..." << "\n";

    return 0;
}