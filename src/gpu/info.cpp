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
    array<char, 256> buffer;

    unique_ptr<FILE, int(*)(FILE*)> pipe(popen(GPU_COMMAND, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }

    int count = 0;

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        string line = buffer.data();
        line = ltrim(line);

        if (line.empty() || line == "\n")
            continue;

        if (line.find("VGA") == string::npos)
            continue;

        size_t pos = line.find(": ");
        if (pos == string::npos)
            continue;

        string gpu_result = line.substr(pos + 2);

        if (!gpu_result.empty() && gpu_result.back() == '\n')
            gpu_result.pop_back();

        oss << gpu_result << "|";
        count++;
    }

    if (count == 0)
        return info;

    string result = oss.str();

    if (!result.empty())
        result.pop_back();

    info.prefix = GPU_PREFIX;
    info.value = result;

    return info;
}