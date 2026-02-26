//uptime
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "info.h"
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

InfoEntry parse_uptime() {
    InfoEntry uptime = get_info(UPTIME_PATH, "0");
    InfoEntry result;
    ostringstream oss;

    result.prefix = UPTIME_PREFIX;
    
    vector<string> uptime_split = splitstring(uptime.value, ' ');
    
    float hours = stof(uptime_split[0]) / 3600;
    int mins = (int)((hours - (int)hours) * 60);

    string parsed_str;

    if (hours < 24) {
        if (hours < 1) {
            oss << " " << mins << " Minutes";
            result.value = oss.str();
            return result;
        }
        oss << " " << (int) hours << " Hours, " << mins << " Minutes"; 
        parsed_str = oss.str();
        result.value = parsed_str;
        return result;
    }

    int days = hours / 24;
    hours -= days * 24;

    oss << " " << days <<  " Days, " << (int) hours << " Hours, " << mins << " Minutes";
    parsed_str = oss.str();
    result.value = parsed_str;
    return result;
}