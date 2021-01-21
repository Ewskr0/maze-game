#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

std::string parseFile(std::string path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw "Could not open file";
    }

    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    return str;
}