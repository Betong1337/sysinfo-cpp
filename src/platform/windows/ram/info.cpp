//ram
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/ram.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_ram() {
    InfoEntry result;

    result.prefix = RAM_PREFIX;
    result.value = "4 GB / 16 GB (12%)";
    return result;
}

InfoEntry parse_swap() {
    InfoEntry result;

    result.prefix = SWAP_PREFIX;
    result.value = "0 GB / 8GB (0%)";
    return result;
}
