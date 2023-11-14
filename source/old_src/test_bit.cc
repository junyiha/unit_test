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

    return 0;
}

int test_bit_size()
{
    uint8_t device {0x09};
    uint16_t register_id {0x03E8};

    std::cerr << "device size: " << sizeof(device) << "\n"
              << "register_id size: " << sizeof(register_id) << "\n"
              << std::endl;
    return 0;
}

int test_modbus_write_1()
{
    typedef struct
    {
        uint8_t address;
        uint8_t function;
        uint16_t start;
        uint16_t count;
        uint16_t crc;
    } ModbusCommand;

    ModbusCommand cmd;
    cmd.address = 1;
    cmd.function = 1;
    cmd.start = 100;
    cmd.count = 8;
    uint8_t *cmd_bytes = (uint8_t *)&cmd;
    for (size_t row = 0; row < sizeof(ModbusCommand); row++)
    {
        printf("it: %u \n", cmd_bytes[row]);
        printf("it: 0x%X \n", cmd_bytes[row]);
    }

    return 0;
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
        else if (arg == "--test-modbus-write-1")
        {
            test_modbus_write_1();
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