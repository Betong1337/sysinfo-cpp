//os
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/os.h"
#include <bits/stdc++.h>

using namespace std;

InfoEntry parse_os() {
    InfoEntry result;
    result.prefix = OS_PREFIX;
    ostringstream oss;

    OSVERSIONINFOEXW osInfo = {};
    osInfo.dwOSVersionInfoSize = sizeof(osInfo);

    typedef LONG(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
    HMODULE hMod = GetModuleHandleW(L"ntdll.dll");
    RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");

    if (fxPtr != nullptr) {
        fxPtr((PRTL_OSVERSIONINFOW)&osInfo);
        oss << "Windows " << to_string(osInfo.dwMajorVersion) << "." << to_string(osInfo.dwMinorVersion) <<
            " (Build " << to_string(osInfo.dwBuildNumber) << ")";
        string parsed_str = oss.str();
        result.value = parsed_str;
        return result;
    }

    return "Unknown Windows";
}

InfoEntry parse_os_id() {
    InfoEntry result;

    result.prefix = OS_PREFIX;
    result.value = "windows";
    return result;
}

InfoEntry parse_kernel() {
    InfoEntry result;
    ostringstream oss;
    result.prefix = KERNEL_VER_PREFIX;

    OSVERSIONINFOEXW osInfo = {};
    osInfo.dwOSVersionInfoSize = sizeof(osInfo);

    typedef LONG(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
    HMODULE hMod = GetModuleHandleW(L"ntdll.dll");
    RtlGetVersionPtr fxPtr =
        (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");

    if (fxPtr != nullptr) {
        fxPtr((PRTL_OSVERSIONINFOW)&osInfo);

        oss "NT " << to_string(osInfo.dwMajorVersion) << "." <<
            to_string(osInfo.dwMinorVersion) <<
            "." << to_string(osInfo.dwBuildNumber);
        string parse_str = oss.str();
        result.value = parse_str;
        return result;
    }

    return "Unknown Kernel";
}