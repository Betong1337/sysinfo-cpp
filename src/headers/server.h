//server
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "core/core.h"

struct ConfInfo {
    bool server_mode;
    int interval;
    std::string ip;
};

#define SERVER_MODE_CMP "server_mode"
#define INTERVAL_CMP "interval"
#define SERVER_IP_CMP "server_ip"

ConfInfo readConfig();
int SendInfo(InfoEntry hostname, InfoEntry uptime, InfoEntry disk, InfoEntry ram, InfoEntry swap, ConfInfo config);
