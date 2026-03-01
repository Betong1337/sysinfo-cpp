//disk
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/disk.h"
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

InfoEntry parse_disk() {
    InfoEntry result;
    ostringstream oss;
    result.prefix = DISK_PREFIX;

    ULARGE_INTEGER totalBytes;
    ULARGE_INTEGER freeBytes;

    if (GetDiskFreeSpaceExA(
            "C:\\",
            nullptr,
            &totalBytes,
            &freeBytes))
    {
        unsigned long long usedBytes =
            totalBytes.QuadPart - freeBytes.QuadPart;

        unsigned long long totalGB =
            totalBytes.QuadPart / (1024ULL * 1024ULL * 1024ULL);

        unsigned long long usedGB =
            usedBytes / (1024ULL * 1024ULL * 1024ULL);

        int percent = static_cast<int>(
            (double)usedBytes / totalBytes.QuadPart * 100.0
        );
        
        const char* percentage_color = get_percentage_color(percent);

        oss << to_string(usedGB) << "GB / " << to_string(totalGB) << "GB" << "(" << percentage_color << percent <<
        "%" << RESET << ")";
        string parsed_str = oss.str();
        result.value = parsed_str;
        return result;
    }
    
    result.value = "Unknown Disk";
    return result;
}