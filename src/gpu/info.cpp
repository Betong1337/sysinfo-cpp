//gpu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <sstream>

#include "info.h"

using namespace std;

InfoEntry parse_gpu() {
    InfoEntry info;
    ostringstream oss;
    array<char, 128> buffer;
    string result;

    unique_ptr<FILE, int(*)(FILE*)> pipe(popen(GPU_COMMAND, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }

    vector<string> gpu_raw;
    string gpu_result;

    int count = 0;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
        gpu_raw = splitstring(result, ':');
        gpu_result = ltrim(gpu_raw[2]);
        oss << gpu_result << "|";
        count++;
    }

    if (result.empty()) {
        return info;
    }
    
    result = oss.str();

    if (!result.empty() && result.front() == '\n') {
        result.erase(0, 1);
    }


    info.prefix = GPU_PREFIX;
    info.value = result;
    return info;
}