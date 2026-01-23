//cpu
#pragma once

#include <string>
#include <vector>
#include "core/core.h"

#define CPU_PREFIX "CPU: "
#define CPU_MODEL_NAME "model name"
#define CPU_PATH "/proc/cpuinfo"

InfoEntry parse_cpu();