//cpu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/cpu.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_cpu() {
    InfoEntry info = get_info(CPU_PATH, CPU_MODEL_NAME);
    info.prefix = CPU_PREFIX;
    return info;
}