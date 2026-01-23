//core.cpp
#include "core.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> read_file(const string& path) {
    vector<string> arr;
    string line;
    ifstream file(path);

    if (!file) {
        std::cerr << "Could not open file: " << path << std::endl;
        return {};
    }

    while (getline(file, line)) {
        arr.push_back(line);
    }

    file.close();

    return arr;
}

string ltrim(const string& s) {
    size_t start = s.find_first_not_of(" \t");
    if (start == string::npos)
        return "";
    return s.substr(start);
}

string trim(const string& s, string str) {
    size_t start = s.find_first_not_of(str);
    if (start == string::npos)
        return "";
    return s.substr(start);
}

InfoEntry get_info(string PATH, string INFO_TYPE) {
    InfoEntry infoentry;
    vector<string> info = read_file(PATH);

    for (const auto& line : info) {
        int line_index = line.find(INFO_TYPE);
        
        if (line_index == 0) {
            auto pos = line.find(':');
            string value = line.substr(pos + 1);
            value = ltrim(value);
            infoentry.value = value;
            break;
        } else if (INFO_TYPE == "0") {
            infoentry.value = line;
            break;
        }
    }

    return infoentry;
}

vector<string> splitstring(string str, char character) {
    string segment;
    vector<string> seglist;
    istringstream iss(str);
    
    while(getline(iss, segment, character)){
        seglist.push_back(segment);
    }
    return seglist;
}