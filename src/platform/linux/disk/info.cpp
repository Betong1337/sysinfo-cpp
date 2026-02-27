//disk
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <sstream>
#include <sys/statvfs.h>
#include "headers/disk.h"

using namespace std;

InfoEntry parse_disk() {
    InfoEntry info;
    ostringstream oss;

    string result;
    struct statvfs stat;

    if (statvfs("/", &stat) != 0) {
        perror("statvfs");
        return info;
    }

    unsigned long long total = (stat.f_blocks * stat.f_frsize) / (1024*1024*1024);
    unsigned long long free  = (stat.f_bfree  * stat.f_frsize) / (1024*1024*1024);

    unsigned long long used = total - free;

    double percent = (double)used / total * 100.0;

    const char* percentage_color = get_percentage_color(percent);

    oss << used << " GB / " << total << " GB (" << percentage_color << fixed << setprecision(2) << percent << "%" << RESET << ")";
    result = oss.str();
    
    info.prefix = DISK_PREFIX;
    info.value = result;
    return info;
}