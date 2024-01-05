/**
 * @file test_utils.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "entry.hpp"

/**
 * @brief Get the dir and file from path object
 * 
 * @param path 
 * @param directorys 
 * @param files 
 * @return int 1 success | 0 fail | other unknown
 */
int get_dir_and_file_from_path(const std::string path, std::vector<std::string>& directorys, std::vector<std::string>& files)
{
    DIR* dir = opendir(path.c_str());
    if (dir == NULL)
    {
        LOG(ERROR) << "Error: " << path << " is not a directory or not exist!\n";
        return 0;
    }
    struct dirent* d_ent = NULL;
    while ((d_ent = readdir(dir)) != NULL)
    {
        if (d_ent->d_type == DT_DIR && strcasecmp(d_ent->d_name, ".") != 0 && strcasecmp(d_ent->d_name, "..") != 0)
        {
            directorys.push_back(std::string(d_ent->d_name));
        }
        if (d_ent->d_type != DT_DIR)
        {
            files.push_back(std::string(d_ent->d_name));
        }
    }
    closedir(dir);

    return 1;
}

/**
 * @brief using recursive method to obtain parameters
 * 
 * @param path 
 * @param fields 
 */
void ExtractFields(const std::string& path, std::vector<std::string>& fields)
{
    size_t pos = path.find('/');

    if (pos != std::string::npos)
    {
        std::string field = path.substr(0, pos);
        fields.push_back(field);

        ExtractFields(path.substr(pos + 1), fields);
    }
    else 
    {
        fields.push_back(path);
    }
}

/**
 * @brief 
 * 
 * @param input 
 * @param length 
 * @return char* 
 */
char *base64_encode(const unsigned char *input, int length) 
{
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char *encoded = (char *)malloc(bufferPtr->length);
    memcpy(encoded, bufferPtr->data, bufferPtr->length - 1);
    encoded[bufferPtr->length - 1] = '\0';

    BIO_free_all(bio);

    return encoded;
}

/**
 * @brief 
 * 
 * @param input 
 * @param length 
 * @return unsigned char* 
 */
unsigned char *base64_decode(const char *input, int length) 
{
    BIO *bio, *b64;
    unsigned char *buffer = (unsigned char *)malloc(length);
    memset(buffer, 0, length);

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new_mem_buf((void *)input, length);
    bio = BIO_push(b64, bio);

    BIO_read(bio, buffer, length);

    BIO_free_all(bio);

    return buffer;
}