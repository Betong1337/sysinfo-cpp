//core.h
#pragma once
#include <string>
#include <vector>


struct InfoEntry {
    std::string prefix;
    std::string value;
    int value2;
};

std::vector<std::string> read_file(const std::string& path);
std::string ltrim(const std::string& s);
std::string trim(const std::string& s, std::string str);
InfoEntry get_info(std::string PATH, std::string INFO_TYPE);
std::vector<std::string> splitstring(std::string str, char character);