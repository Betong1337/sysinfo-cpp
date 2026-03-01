//ram
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/ram.h"
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

InfoEntry parse_ram() {
    InfoEntry result;
    ostringstream oss;

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);

    GlobalMemoryStatusEx(&statex);

    DWORDLONG totalRAM = statex.ullTotalPhys / (1024 * 1024 * 1024);
    DWORDLONG usedRAM =
        (statex.ullTotalPhys - statex.ullAvailPhys) / (1024 * 1024 * 1024);

    const int used_percent =
    static_cast<double>(usedRAM) / totalRAM * 100;
    
    const char* percentage_color = get_percentage_color(used_percent);

    oss << usedRAM << " GB / " << totalRAM << " GB "
        << "(" << percentage_color << used_percent << "%" << RESET << ")";
    string parsed_str = oss.str();

    result.prefix = RAM_PREFIX;
    result.value = parsed_str;
    return result;
}

InfoEntry parse_swap() {
    InfoEntry result;
    result.value = "";
    return result;
}
