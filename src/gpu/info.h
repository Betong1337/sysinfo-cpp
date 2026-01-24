//gpu
#pragma once

#include <string>
#include <vector>
#include "core/core.h"

#define GPU_COMMAND "/bin/lspci | grep -iE 'VGA|3D|video'"
#define GPU_PREFIX "GPU: "

InfoEntry parse_gpu();