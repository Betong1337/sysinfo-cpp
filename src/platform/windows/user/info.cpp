//user
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/user.h"
#include <bits/stdc++.h>
#include <windows.h>
#include <Lmcons.h>

using namespace std;

InfoEntry parse_user() {
    InfoEntry result;

    char username[UNLEN + 1];
    DWORD size = UNLEN + 1;

    if (GetUserNameA(username, &size)) {
        result.value = string(username);
        result.prefix = USER_PREFIX;
        return result;
    }

    return "Unknown";
}