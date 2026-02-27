//uptime
#pragma once
#include "core/core.h"

#define UPTIME_PREFIX "Uptime:"
#define UPTIME_ERROR "Error: Could not print uptime..."
#define UPTIME_PATH "/proc/uptime"

InfoEntry parse_uptime();