//hostname
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/hostname.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_hostname() {
    InfoEntry result = get_info(HOSTNAME_PATH, "0");
    result.prefix = HOSTNAME_PREFIX;
    return result;
}