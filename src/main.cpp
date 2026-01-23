// main.cpp
#include <iostream>
#include <vector>
#include <string>

#include "cpu/info.h"
#include "gpu/info.h"
#include "os/info.h"
#include "hostname/info.h"
#include "ram/info.h"
#include "uptime/info.h"
#include "core/core.h"
#include "core/color.h"

using namespace std;

int main() {
    
    InfoEntry cpu = parse_cpu();
    InfoEntry ram = parse_ram();
    InfoEntry swap = parse_swap();
    InfoEntry os = parse_os();
    InfoEntry kernel = parse_kernel();
    InfoEntry hostname = parse_hostname();
    InfoEntry uptime = parse_uptime();

    cout << "=== " << HEADER << getenv("USER") << "@" << hostname.value << RESET << " ===" << endl;
    cout << HEADER << os.prefix << RESET << os.value << endl;
    cout << HEADER << kernel.prefix << RESET << kernel.value << endl;
    cout << HEADER << cpu.prefix << RESET << cpu.value << endl;
    cout << HEADER << ram.prefix << RESET << ram.value << endl;
    cout << HEADER << swap.prefix << RESET << swap.value << endl;
    cout << HEADER << uptime.prefix << RESET << uptime.value << endl;

    return 0;
}
