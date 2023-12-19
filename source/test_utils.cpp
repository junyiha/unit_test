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