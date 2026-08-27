//server
#include "headers/server.h"
#include <unistd.h>
#include <limits.h>
#include <curl/curl.h>

using namespace std;

ConfInfo readConfig() {
    const string path = "src/config";
    vector<string> info;
    string line;
    ifstream file(path);

    ConfInfo config;

    if (!file) {
        throw runtime_error("Could not open ");
        return config;
    }

    while (getline(file, line)) {
        info.push_back(line);
    }
    file.close();

    for (const auto& line : info) {
        int line_index_server_ip = line.find(SERVER_IP_CMP);
        int line_index_server_mode = line.find(SERVER_MODE_CMP);
        int line_index_interval = line.find(INTERVAL_CMP);

        string value;

        if (line_index_server_ip == 0) {
            auto pos = line.find('=');
            value = line.substr(pos + 1);
            config.ip = value;
        }

        if (line_index_server_mode == 0) {
            auto pos = line.find('=');
            value = line.substr(pos + 1);
            bool convertBool = false;

            if (value == "true") {
                convertBool = true;
            }
            config.server_mode = convertBool;
        }

        if (line_index_interval == 0) {
            auto pos = line.find('=');
            value = line.substr(pos + 1);
            int convertInt = stoi(value);
            config.interval = convertInt;
        }
    }
    return config;
}

/*Sending info:
    *IP from webserver
    *Hostname
    *Uptime
    *Disk
    *Ram
    *Swap
*/
int SendInfo(InfoEntry hostname, InfoEntry uptime, InfoEntry disk, InfoEntry ram, InfoEntry swap, ConfInfo config) {

    CURL* curl = curl_easy_init();

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    string URL = config.ip;

    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    string json =
    "{\"hostname\":\"" + hostname.value +
    "\",\"uptime\":\"" + uptime.value + 
    "\",\"disk\":\"" + disk.value + 
    "\",\"ram\":\"" + ram.value +
    "\",\"swap\":\"" + swap.value +
    "\"}";

    cout << json << '\n';
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());

    CURLcode res = curl_easy_perform(curl);
    int responseCode;

    if (res != CURLE_OK) {
        cerr << "curl error: "
              << curl_easy_strerror(res) << '\n';
    }
    else {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        cout << "HTTP status: " << responseCode << '\n';
    }
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return responseCode;
}