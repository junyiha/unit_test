#include <iostream>
#include <vector>
#include <random>

std::string generateRandomMixedString(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);

    std::string randomString;
    randomString.reserve(size);

    for (int i = 0; i < size; ++i) 
    {
        int choice = dist(gen);
        if (choice == 0) 
        {
            // 生成数字字符
            std::uniform_int_distribution<int> numDist('0', '9');
            randomString.push_back(static_cast<char>(numDist(gen)));
        } 
        // else if (choice == 1) 
        // {
        //     // 生成大写字母字符
        //     std::uniform_int_distribution<int> upperDist('A', 'Z');
        //     randomString.push_back(static_cast<char>(upperDist(gen)));
        // } 
        else 
        {
            // 生成小写字母字符
            std::uniform_int_distribution<int> lowerDist('a', 'z');
            randomString.push_back(static_cast<char>(lowerDist(gen)));
        }
    }

    return randomString;
}

int main() {
    int size = 10;

    std::string randomString = generateRandomMixedString(size);

    // 打印生成的随机数字和字符混合序列
    std::cout << randomString << std::endl;

    return 0;
}
