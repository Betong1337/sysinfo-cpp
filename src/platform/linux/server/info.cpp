//server
#include "headers/server.h"
#include <unistd.h>
#include <limits.h>
#include <curl/curl.h>

using namespace std;
//Stage 1: Write the config and functions

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
        break;
    }
    return config;
}

int SendInfo(InfoEntry hostname, InfoEntry uptime, InfoEntry disk, InfoEntry ram) {

    ConfInfo config = readConfig();
    CURL* curl = curl_easy_init();
    string URL = string("http://") + string("127.0.0.1") + string("/server");

    if (!curl)
        return 1;

    string json = R"({
    "hostname": ")" + hostname.value + R"(",
    "uptime": )" + uptime.value + R"(,
    "disk": )" + disk.value + R"(,
    "ram": )" + ram.value + R"(
    })";

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // POST-data
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        std::cerr << "curl error: "
                  << curl_easy_strerror(res) << '\n';
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);


    return 0;
}