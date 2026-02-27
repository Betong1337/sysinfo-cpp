//hostname
#pragma once

#include <string>
#include <vector>
#include "core/core.h"

#define HOSTNAME_PATH "/proc/sys/kernel/hostname"
#define HOSTNAME_PREFIX "Hostname: "
InfoEntry parse_hostname();