//hostname
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/hostname.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_hostname() {
    InfoEntry result;
    char buffer[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(buffer);

    GetComputerNameA(buffer, &size);
    result.value = string(buffer);
    result.prefix = USER_PREFIX;
    return result;
}