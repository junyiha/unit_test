#include "ParseMjpeg.hpp"

int main()
{
    int ret {ParseMjpeg::RET_ERR};
    ParseMjpeg pm;
    std::string json_string;

    // ret = pm.ParseMjpegFile("aaa-frame-1.jpg");
    // ret = pm.ParseMjpegFile("aaa-frame-5.jpg");
    std::string origin_file {"origin-frame-"};
    std::string thumb_file {"thumb-frame-"};
    std::string struct_file {"struct-"};
    std::string in_file {"aaa-frame-"};
    for (int col {0}; col < 5; col++)
    {
        std::cerr << "count: " << col << std::endl;
        in_file = "aaa-frame-";
        origin_file = "origin-frame-";
        thumb_file = "thumb-frame-";
        struct_file = "struct-";

        in_file += std::to_string(col) + ".jpg";
        origin_file += std::to_string(col) + ".jpg";
        thumb_file += std::to_string(col) + ".jpg";
        struct_file += std::to_string(col) + ".json";
        ret = pm.ParseShmMjpegFile(in_file);
        if (ret == ParseMjpeg::RET_OK)
        {
            ret = pm.SaveOriginPicFile(origin_file);
            if (ret == ParseMjpeg::RET_OK)
            {
                std::cerr << "Success to save origin picture file" << std::endl;
            }
            ret = pm.SaveThumbPicFile(thumb_file);
            if (ret == ParseMjpeg::RET_ERR)
            {
                std::cerr << "Success to save thumb picture file" << std::endl;
            }
            ret = pm.SaveStructDataFile(struct_file);
            if (ret == ParseMjpeg::RET_OK)
            {
                std::cerr << "Success to save struct data file" << std::endl;
            }
            // ret = pm.GetStructData(json_string);
            // if (ret == ParseMjpeg::RET_OK)
            // {
            //     std::cerr << "Success to get struct data, data: " << json_string << std::endl;
            // }
        }
    }

    return 0;
}