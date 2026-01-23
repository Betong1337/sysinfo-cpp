//os
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "info.h"
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

InfoEntry parse_os() {
    InfoEntry os_name = get_info(OS_PATH, OS_NAME_CMP);
    InfoEntry os_version = get_info(OS_PATH, OS_VERSION_CMP);
    InfoEntry result;
    ostringstream oss;

    string os_name_str = ltrim(os_name.value);
    string os_version_str = ltrim(os_version.value);

    os_name_str = trim(os_name_str, "NAME=");
    os_version_str = trim(os_version_str, "VERSION=");

    os_name_str.erase(0, 1);
    os_version_str.erase(0, 1);

    int os_name_len = os_name_str.length();
    int os_version_len = os_version_str.length();
    
    os_name_str.erase(os_name_len-1, 1);
    os_version_str.erase(os_version_len-1, 1);

    oss << os_name_str << " " << os_version_str;
    string os_ver_str = oss.str();

    result.prefix = OS_PREFIX;
    result.value = os_ver_str;
    return result;
}

InfoEntry parse_kernel() {
    InfoEntry kernel_ver = get_info(KERNEL_PATH, "0");
    InfoEntry result;

    string segment;
    vector<string> seglist;
    istringstream iss(kernel_ver.value);
    
    while(getline(iss, segment, '(')){
        seglist.push_back(segment);
    }

    result.prefix = KERNEL_VER_PREFIX;
    result.value = seglist[0];
    return result;
}