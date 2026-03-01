//cpu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/cpu.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_cpu() {
    InfoEntry result;

    result.prefix = CPU_PREFIX;
    result.value = "Intel i5-10700";
    return result;
}