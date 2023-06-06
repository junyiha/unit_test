#include <iostream>

int main() 
{
    int num = 4;
    // char char_num = static_cast<char>(num);
    std::string tmp_str;
    tmp_str = std::to_string(num);
    char char_num = tmp_str[0];
    // char char_num = (char)(num);


    // char ch = 'A';
    char ch = '4';
    int ascii = static_cast<int>(ch);
    
    std::cout << "Character: " << ch << std::endl;
    std::cout << "ASCII Value: " << ascii << std::endl;
    
    return 0;
}
