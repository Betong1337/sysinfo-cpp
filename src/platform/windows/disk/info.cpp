//disk
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/disk.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_disk() {
    InfoEntry result;

    result.prefix = DISK_PREFIX;
    result.value = "32 GB / 500 GB (12%)";
    return result;
}