/**
 * @file test_magic.cc
 * @author your name (you@domain.com)
 * @brief 测试 libmagic 第三方库
 * @version 0.1
 * @date 2023-07-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <magic.h>

int main() {
    magic_t magicCookie = magic_open(MAGIC_MIME_TYPE | MAGIC_NO_CHECK_COMPRESS);
    if (magicCookie == NULL) {
        std::cerr << "Failed to initialize libmagic" << std::endl;
        return 1;
    }

    if (magic_load(magicCookie, NULL) != 0) {
        std::cerr << "Failed to load magic database" << std::endl;
        magic_close(magicCookie);
        return 1;
    }

    const char* filename = "shm_open_unlink.cc";
    const char* mimeType = magic_file(magicCookie, filename);
    if (mimeType == NULL) {
        std::cerr << "Failed to determine file type" << std::endl;
    } else {
        std::cout << "File MIME type: " << mimeType << std::endl;
    }

    magic_close(magicCookie);
    return 0;
}
