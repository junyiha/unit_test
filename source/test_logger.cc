#include "mnc_logger.hpp"
#include <iostream>

int main()
{
    std::size_t cnt {};
    std::size_t size {};
    Logger logger;
    logger.OpenFile("/tmp/mnc", "mnc.log");

    logger.GetMaxFileSize(size);
    std::cerr << "default size : " << size << " kB" << std::endl;
    std::cerr << "input size: " << std::endl;
    // std::cin >> size;
    logger.SetMaxFileSize(size);

    while (true)
    {
        if (cnt > 1000)
            break;
        logger.log("test: ", cnt);
        cnt++;
    }

    return 0;
}