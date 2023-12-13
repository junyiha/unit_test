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
        {"test-cidr-to-decimal-subnet-mask", test_CIDRToDecimalSubnetMask}
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