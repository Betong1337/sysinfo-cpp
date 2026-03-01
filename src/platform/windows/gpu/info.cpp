//gpu
#include <iostream>
#include <fstream>
#include "headers/gpu.h"
#include <bits/stdc++.h>

#include <windows.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <string>
#include <vector>

#pragma comment(lib, "wbemuuid.lib")

using namespace std;

InfoEntry parse_gpu() {
    InfoEntry result;
    result.prefix = GPU_PREFIX;

    HRESULT hres;

    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
        result.value = "N/A";
        return result;

    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL);

    IWbemLocator* pLoc = nullptr;
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID*)&pLoc);

    if (FAILED(hres)) {
        CoUninitialize();
        return "N/A";
    }

    IWbemServices* pSvc = nullptr;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        &pSvc);

    if (FAILED(hres)) {
        pLoc->Release();
        CoUninitialize();
        return "N/A";
    }

    CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE);

    IEnumWbemClassObject* pEnumerator = nullptr;

    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT Name FROM Win32_VideoController"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres)) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "N/A";
    }

    vector<string> gpus;

    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;

    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (!uReturn)
            break;

        VARIANT vtProp;
        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);

        if (SUCCEEDED(hr) && vtProp.vt == VT_BSTR) {
            wstring ws(vtProp.bstrVal);
            string gpu(ws.begin(), ws.end());

            // Filtrera bort basic display adapter
            if (gpu.find("Microsoft Basic") == std::string::npos)
                gpus.push_back(gpu);
        }

        VariantClear(&vtProp);
        pclsObj->Release();
    }

    pEnumerator->Release();
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();

    if (gpus.empty()) {
        result.value = "N/A";
        return result;
    }

    string res;

    for (size_t i = 0; i < gpus.size(); ++i) {
        res += gpus[i];
        if (i != gpus.size() - 1)
            res += " | ";
    }

    result.value = res;
    return result;
}