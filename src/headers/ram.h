//ram
#pragma once

#include <string>
#include <vector>
#include "core/core.h"
#include "core/color.h"

#define RAM_PREFIX "Memory: "
#define SWAP_PREFIX "Swap: "
#define RAM_MEMTOTAL "MemTotal:"
#define RAM_AVAILABLE "MemAvailable"
#define SWAP_TOTAL_CMP "SwapTotal"
#define SWAP_FREE_CMP "SwapFree"
#define SWAP_CACHED_CMP "SwapCached"
#define RAM_PATH "/proc/meminfo"

std::string removesuffix(std::string input);
float kbTOgb(std::string input);
InfoEntry parse_ram();
InfoEntry parse_swap();