//gpu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/gpu.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_gpu() {
    InfoEntry result;

    result.prefix = GPU_PREFIX;
    result.value = "32 GB / 500 GB (12%)";
    return result;
}