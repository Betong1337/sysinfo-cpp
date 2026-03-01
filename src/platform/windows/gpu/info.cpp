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
    result.value = "AMD RX 7900 XT";
    return result;
}