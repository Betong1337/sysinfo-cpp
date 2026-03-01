//user
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/user.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_user() {
    InfoEntry result;

    result.prefix = USER_PREFIX;
    result.value = "betong";
    return result;
}