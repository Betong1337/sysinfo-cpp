//ram
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "info.h"
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

string removesuffix(string input) {
    input = ltrim(input);
    auto pos = input.find(' ');
    string result = input.substr(0, pos);
    return result;
}

float kbTOgb(std::string input) {
    float result = stof(input) / 1048576.0;
    return result;
}

const char* get_percentage_color(const int used_percent) {
    if (used_percent < 50) {
        return GREEN;
    } else if (used_percent > 49 && used_percent < 80) {
        return YELLOW;
    } else {
        return RED;
    }
}

InfoEntry parse_ram() {
    InfoEntry result;
    InfoEntry memtotal = get_info(RAM_PATH, RAM_MEMTOTAL);
    InfoEntry memavailable = get_info(RAM_PATH, RAM_AVAILABLE);
    ostringstream oss;

    string memTotal_kb = removesuffix(memtotal.value);
    string memavailable_kb = removesuffix(memavailable.value);

    float memtotal_gb_f = kbTOgb(memTotal_kb);
    float memavailable_gb_f = kbTOgb(memavailable_kb);
    float memused_gb_f = memtotal_gb_f - memavailable_gb_f;

    const int used_percent = (memused_gb_f / memtotal_gb_f) * 100;
    const char* percentage_color = get_percentage_color(used_percent);

    oss << fixed << setprecision(2) << memused_gb_f << " GB / "
        << fixed << setprecision(2) << memtotal_gb_f << " GB "
        << "(" << percentage_color << used_percent << "%" << RESET << ")";
    string parsed_str = oss.str();

    if (!parsed_str.empty() && parsed_str.front() == '\n') {
        parsed_str.erase(0, 1);
    }

    result.prefix = RAM_PREFIX;
    result.value = parsed_str;
    return result;
}

InfoEntry parse_swap() {
    InfoEntry swap_total = get_info(RAM_PATH, SWAP_TOTAL_CMP);
    InfoEntry swap_free = get_info(RAM_PATH, SWAP_FREE_CMP);
    InfoEntry swap_cache = get_info(RAM_PATH, SWAP_CACHED_CMP);
    ostringstream oss;
    InfoEntry result;

    float swap_total_f = kbTOgb(swap_total.value);
    float swap_free_f = kbTOgb(swap_free.value);
    float swap_cache_f = kbTOgb(swap_cache.value);

    float swap_used = swap_total_f - swap_free_f - swap_cache_f;
    int used_percent;

    if (swap_total_f == 0 || swap_total_f < 0) {
        used_percent = 0.00;
    } else {
        used_percent = (swap_used / swap_total_f) * 100;
    }

    const char* percentage_color = get_percentage_color(used_percent);

    oss << fixed << setprecision(2) << swap_used << " GB / "
        << fixed << setprecision(2) << swap_total_f << " GB "
        << "(" << percentage_color << used_percent << "%" << RESET << ")";
    string parsed_str = oss.str();

    result.prefix = SWAP_PREFIX;
    result.value = parsed_str;
    return result;

}