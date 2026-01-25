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
#include "user/info.h"

using namespace std;

int main(int argc, char **argv) {

    InfoEntry user = parse_user();
    InfoEntry cpu = parse_cpu();
    InfoEntry ram = parse_ram();
    InfoEntry swap = parse_swap();
    InfoEntry os = parse_os();
    InfoEntry kernel = parse_kernel();
    InfoEntry hostname = parse_hostname();
    InfoEntry uptime = parse_uptime();
    InfoEntry gpu;

    string cmd;

    bool parameter = false;

    if (argc > 1) {
        parameter = true;
        cmd = argv[1];
    }

    if (cmd == "--os") {
        print_module(os);
    } else if (cmd == "--kernel") {
        print_module(kernel);
    } else if (cmd == "--cpu") {
        print_module(cpu);
    } else if (cmd == "--gpu") {
        gpu = parse_gpu();
        print_module(gpu);
    } else if (cmd == "--ram") {
        print_module(ram);
    } else if (cmd == "--swap") {
        print_module(swap);
    } else if (cmd == "--uptime") {
        print_module(uptime);
    } else if (cmd == "--hostname") {
        print_module(hostname);
    } else if (cmd == "--username") {
        print_module(user);
    } else if (cmd == "--version" || cmd == "-v") {
        cout << "sysinfo-cpp, v0.1" << endl;
    } else {
        if (parameter) cout << USAGE_MSG << endl;
    }

    if (parameter) return 1;
    gpu = parse_gpu();

    print_title(hostname, user);
    print_module(os);
    print_module(kernel);
    print_module(cpu);
    print_module(gpu);
    print_module(ram);
    print_module(swap);
    print_module(uptime);

    return 0;
}
