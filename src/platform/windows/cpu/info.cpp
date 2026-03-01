//cpu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/cpu.h"
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

InfoEntry parse_cpu() {
    InfoEntry result;
    result.prefix = CPU_PREFIX;

    HKEY hKey;
    char cpuName[256];
    DWORD size = sizeof(cpuName);

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,
        "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
        0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        RegQueryValueExA(hKey, "ProcessorNameString",
            NULL, NULL, (LPBYTE)cpuName, &size);
        RegCloseKey(hKey);
        result.value = string(cpuName);
        return result;
    }

    return "Unknown CPU";
}