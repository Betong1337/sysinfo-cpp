//os
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/os.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_os() {
    InfoEntry result;

    result.prefix = OS_PREFIX;
    result.value = "32 GB / 500 GB (12%)";
    return result;
}

InfoEntry parse_os_id() {
    InfoEntry result;

    result.prefix = OS_PREFIX;
    result.value = "windows";
    return result;
}

InfoEntry parse_kernel() {
    InfoEntry result;

    result.value = "Windows NT";
    result.prefix = KERNEL_VER_PREFIX;
}