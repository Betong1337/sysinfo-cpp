//os
#pragma once

#include <string>
#include <vector>
#include "core/core.h"

#define KERNEL_VER_PREFIX "Kernel: "
#define KERNEL_ERROR "Error: Could not print kernel..."

#define OS_PREFIX "OS: "
#define OS_NAME_CMP "NAME"
#define OS_VERSION_CMP "VERSION"
#define OS_ERROR "Error: Could not print OS..."

#define OS_PATH          "/etc/os-release"
#define KERNEL_PATH      "/proc/version"

InfoEntry parse_os();
InfoEntry parse_kernel();