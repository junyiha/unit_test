/**
 * @file test_bit.cc
 * @author your name (you@domain.com)
 * @brief 测试比特的读和写
 * @version 0.1
 * @date 2023-07-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

void Help()
{
    std::string help_info {R"(
    some help information

    -h, output help information
    )"};

    std::cerr << help_info << std::endl;
}

int test_bit_write()
{
    std::cerr << "bit write" << std::endl;

    std::size_t value;
    std::stringstream stream;
    std::vector<char> buffer(128);

    value = 0xFC;
    stream << std::hex << value;
    std::string hex_string = stream.str();
    for (auto &it : hex_string)
    {
        buffer.push_back(it);
    }

    std::cerr << buffer.data() << std::endl;
}

int test_bit_size()
{
    uint8_t device {0x09};
    uint16_t register_id {0x03E8};

    std::cerr << "device size: " << sizeof(device) << "\n"
              << "register_id size: " << sizeof(register_id) << "\n"
              << std::endl;
}

int main(int argc, char **argv)
{
    std::string arg;
    for (int col {1}; col < argc; ++col)
    {
        arg = argv[col];
        if (arg == "-h")
        {
            Help();
        }
        else if (arg == "--test-bit-write")
        {
            test_bit_write();
        }
        else if (arg == "--test-bit-size")
        {
            test_bit_size();
        }
        else
        {
            Help();
        }
    }
}