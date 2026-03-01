//os
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/uptime.h"
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

InfoEntry parse_uptime() {
    InfoEntry result;
    ostringstream oss;
    string parsed_str;
    result.prefix = UPTIME_PREFIX;

    ULONGLONG ms = GetTickCount64();
    ULONGLONG seconds = ms / 1000;

    int days = seconds / 86400;
    seconds %= 86400;
    int hours = seconds / 3600;
    seconds %= 3600;
    int minutes = seconds / 60;

    if (hours < 24) {
        if (hours < 1) {
            oss << " " << minutes << " Minutes";
            result.value = oss.str();
            return result;
        }
        oss << " " << (int) hours << " Hours, " << minutes << " Minutes"; 
        parsed_str = oss.str();
        result.value = parsed_str;
        return result;
    }

    oss << " " << days <<  " Days, " << (int) hours << " Hours, " << minutes << " Minutes";
    parsed_str = oss.str();
    result.value = parsed_str;
    return result;
}