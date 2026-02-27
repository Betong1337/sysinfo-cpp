//os
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <sstream>
#include "headers/os.h"

using namespace std;

InfoEntry parse_os() {
    InfoEntry os_name = get_info(OS_PATH, OS_NAME_CMP);
    InfoEntry os_version = get_info(OS_PATH, OS_VERSION_CMP);

    InfoEntry result;
    ostringstream oss;

    auto extract_value = [](string line) -> string {
        line.erase(0, line.find_first_not_of(" \t\n\r"));

        size_t pos = line.find('=');
        if (pos == string::npos)
            return "";

        string value = line.substr(pos + 1);

        value.erase(0, value.find_first_not_of(" \t\n\r"));
        value.erase(value.find_last_not_of(" \t\n\r") + 1);

        if (!value.empty() && value.front() == '"')
            value.erase(0, 1);

        if (!value.empty() && value.back() == '"')
            value.pop_back();

        return value;
    };

    string os_name_str = extract_value(os_name.value);
    string os_version_str = extract_value(os_version.value);

    oss << os_name_str;

    if (!os_version_str.empty())
        oss << " " << os_version_str;

    result.prefix = OS_PREFIX;
    result.value = oss.str();

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

InfoEntry parse_os_id() {
    InfoEntry os_name = get_info(OS_PATH, OS_NAME_ID_CMP);
    InfoEntry result;
    ostringstream oss;

    string os_name_str = ltrim(os_name.value);

    os_name_str = trim(os_name_str, "ID=");

    int os_name_len = os_name_str.length();
    
    os_name_str.erase(os_name_len, 1);

    oss << os_name_str;
    string os_str = oss.str();

    result.prefix = OS_PREFIX;
    result.value = os_str;
    return result;
}