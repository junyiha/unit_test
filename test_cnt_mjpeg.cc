/**
 * @file test_cnt_mjpeg.cc
 * @author your name (you@domain.com)
 * @brief 测试保存原图模块
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ParseMjpeg.hpp"

void Help()
{
    std::string help_info {R"(
        test_cnt_mjpeg.exe  测试保存文件功能

        -h, --help   输出帮助信息
        -o, --old-version  第一次测试
    )"};

    std::cerr << help_info << std::endl;
}

int old_version()
{
    int ret {ParseMjpeg::RET_ERR};
    std::string file{"Q4H0v-frame-43643.jpg"};
    std::string object_file {"path/1.jpg"};
    ParseMjpeg parse_mjpeg;

    ret = parse_mjpeg.ParseMjpegFile(file);
    if (ret != ParseMjpeg::RET_OK)
    {
        std::cerr << "Failed to parse mjpeg file: " << file << std::endl;
        return -1;
    }

    ret = parse_mjpeg.SaveOriginPicFile(object_file);
    if (ret != ParseMjpeg::RET_OK)
    {
        std::cerr << "Failed to save origin picture to : " << object_file << std::endl;
        return -1;
    }

    return 0;
}

int CountMjpeg()
{
    int ret {ParseMjpeg::RET_ERR};
    std::string file{"Q4H0v-frame-45385.jpg"};
    std::string object_file_dir {"path/origin_pictures/"};
    std::string object_file_name {};
    std::string object_file {};
    ParseMjpeg parse_mjpeg;
    int max {100};

    ret = parse_mjpeg.ParseMjpegFile(file);
    if (ret != ParseMjpeg::RET_OK)
    {
        std::cerr << "Failed to parse mjpeg file: " << file << std::endl;
        return -1;
    }

    int cnt {0};
    while (true)
    {
        if (cnt > max)
            break;
        object_file_name = std::to_string(cnt) + ".jpg";
        object_file = object_file_dir + object_file_name;
        ret = parse_mjpeg.SaveOriginPicFile(object_file);
        if (ret != ParseMjpeg::RET_OK)
        {
            std::cerr << "Failed to save origin picture to : " << object_file << std::endl;
            return -1;
        }
        cnt++;
        // sleep(1);
    }

    return 0;
}

static int max {1000};
static int cnt {0};

int SaveOriginPicture(ParseMjpeg &in)
{
    int ret {ParseMjpeg::RET_ERR};
    std::string file {};
    std::string file_dir {"path/origin_pictures/"};
    std::string file_name {};

    if (cnt >= max)
        return -1;
    
    file_name = std::to_string(cnt) + ".jpg";
    file = file_dir + file_name;
    ret = in.SaveOriginPicFile(file);
    if (ret != ParseMjpeg::RET_OK)
    {
        std::cerr << "Failed to save origin picture to directory: " << file_dir << std::endl;
        return -1;
    }
    cnt++;

    return 0;
}

int TestSaveOriginPicture()
{
    int ret {ParseMjpeg::RET_ERR};
    std::string file{"Q4H0v-frame-45385.jpg"};

    while (true)
    {
        ParseMjpeg parse_mjpeg;
        ret = parse_mjpeg.ParseMjpegFile(file);
        if (ret != ParseMjpeg::RET_OK)
        {
            std::cerr << "Failed to parse mjpeg file: " << file << std::endl;
            return -1;
        }

        ret = SaveOriginPicture(parse_mjpeg);
        if (ret != 0)
        {
            std::cerr << "Failed to save origin picture" << std::endl;
            return -1;
        }
    }
}

int main(int argc, char *argv[])
{
    std::string arg {};

    for (int col {1}; col < argc; ++col)
    {
        arg = argv[col];
        if (arg == "-h" || arg == "--help")
        {
            Help();            
        }
        else if (arg == "--count-mjpeg")
        {
            CountMjpeg();
        }
        else if (arg == "--test-save-origin-picture")
        {
            TestSaveOriginPicture();
        }
        else 
        {
            Help();            
        }

    }
}