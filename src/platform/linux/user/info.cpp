//user
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "headers/user.h"

using namespace std;

InfoEntry parse_user() {
    InfoEntry info;
    info.prefix = USER_PREFIX;
    info.value = getenv("USER");
    return info;
}