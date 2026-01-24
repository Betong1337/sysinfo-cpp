//gpu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "info.h"
#include <bits/stdc++.h>
#include <sstream>

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
    
    result = oss.str();

    info.prefix = GPU_PREFIX;
    info.value = result;
    info.value2 = count;
    return info;
}