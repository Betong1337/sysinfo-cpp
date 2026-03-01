//os
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/uptime.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_uptime() {
    InfoEntry result;

    result.prefix = UPTIME_PREFIX;
    result.value = "32 GB / 500 GB (12%)";
    return result;
}