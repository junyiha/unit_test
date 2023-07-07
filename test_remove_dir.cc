#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

bool removeDirectory(const std::string& directoryPath) {
    DIR* dir = opendir(directoryPath.c_str());
    if (!dir) {
        std::cerr << "Failed to open directory: " << directoryPath << std::endl;
        return false;
    }

    struct dirent* entry;
    while ((entry = readdir(dir))) {
        std::string fileName = entry->d_name;
        if (fileName != "." && fileName != "..") {
            std::string filePath = directoryPath + "/" + fileName;

            if (entry->d_type == DT_DIR) {
                if (!removeDirectory(filePath)) {
                    closedir(dir);
                    return false;
                }
            } else {
                if (unlink(filePath.c_str()) != 0) {
                    std::cerr << "Failed to delete file: " << filePath << std::endl;
                    closedir(dir);
                    return false;
                }
            }
        }
    }

    closedir(dir);

    if (rmdir(directoryPath.c_str()) != 0) {
        std::cerr << "Failed to delete directory: " << directoryPath << std::endl;
        return false;
    }

    return true;
}

int main() {
    const std::string directoryPath = "path/tmp/";

    if (removeDirectory(directoryPath)) {
        std::cout << "Directory deleted: " << directoryPath << std::endl;
    } else {
        std::cerr << "Failed to delete directory: " << directoryPath << std::endl;
    }

    return 0;
}
