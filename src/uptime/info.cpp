//uptime
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "info.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_uptime() {
    InfoEntry uptime = get_info(UPTIME_PATH, "0");
    InfoEntry result;
    
    vector<string> uptime_split = splitstring(uptime.value, ' ');

    cout << uptime_split[0] << endl;

    result.prefix = UPTIME_PREFIX;
    return result;
}