//hostname
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/disk.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_hostname() {
    InfoEntry result;

    result.prefix = HOSTNAME_PREFIX;
    result.value = "laptop";
    return result;
}