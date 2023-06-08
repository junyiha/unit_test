#include <iostream>
#include <string>

int main ()
{
    int ret {-1};
    std::string file {"fire_bitmainland.zips"};
    std::string cmd;

    cmd = "unzip " + file;
    ret = std::system(cmd.c_str());
    std::cerr << "ret: " << ret << std::endl;

    return 0;
}