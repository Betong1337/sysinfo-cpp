#include "ascii.h"

using namespace std;

void printAscii(InfoEntry os) {
    string os_raw = os.value;
        
    int pos = os_raw.find(" ");

    string sub = os_raw.substr(0, pos);

    //string path = "/usr/local/share/sysinfo/asciiart/";
    string path = "src/asciiart/";


    string fileType = ".txt";
    string LinuxPath = path + "linux" + fileType;

    string fileName = path + sub + fileType;

    ifstream file(fileName);

    if (!file) {
        file.open(LinuxPath);
    }

    if (!file) {
        cerr << "Could not open any file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << HEADER << line << "\n";
    }
    cout << RESET;

}