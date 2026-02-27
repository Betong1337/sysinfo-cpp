// main.cpp
#include <iostream>
#include <vector>
#include <string>

#include "headers/cpu.h"
#include "headers/disk.h"
#include "headers/gpu.h"
#include "headers/hostname.h"
#include "headers/os.h"
#include "headers/ram.h"
#include "headers/uptime.h"
#include "headers/user.h"
#include "core/color.h"
#include "core/ascii.h"

using namespace std;

int main(int argc, char **argv) {

    InfoEntry user = parse_user();
    InfoEntry cpu = parse_cpu();
    InfoEntry ram = parse_ram();
    InfoEntry swap = parse_swap();
    InfoEntry os = parse_os();
    InfoEntry os_id = parse_os_id();
    InfoEntry kernel = parse_kernel();
    InfoEntry hostname = parse_hostname();
    InfoEntry uptime = parse_uptime();
    InfoEntry disk = parse_disk();
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
    } else if (cmd == "--disk") {
        print_module(disk);
    } else if (cmd == "--swap") {
        print_module(swap);
    } else if (cmd == "--uptime") {
        print_module(uptime);
    } else if (cmd == "--hostname") {
        print_module(hostname);
    } else if (cmd == "--username") {
        print_module(user);
    } else if (cmd == "--art") {
        printAscii(os_id);
    } else if (cmd == "--version" || cmd == "-v") {
        cout << "sysinfo-cpp, v0.1" << endl;
    } else {
        if (parameter) cout << USAGE_MSG << endl;
    }
    if (parameter) return 1;

    printAscii(os_id);
    print_title(user, hostname);

    print_module(os);
    print_module(kernel);
    print_module(cpu);
    print_module(ram);
    print_module(swap);
    print_module(disk);
    print_module(uptime);
    gpu = parse_gpu();
    print_module(gpu);;

    return 0;
}
