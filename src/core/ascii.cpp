#include "ascii.h"

using namespace std;

void printAscii(InfoEntry os) {
    string os_raw = os.value;
    int pos = os_raw.find(" ");

    string sub = os_raw.substr(0, pos);

    string fileName = "src/asciiart/" + sub + ".txt";
    ifstream file(fileName);

    if (!file) {
        ifstream file("asciiart/Linux.txt");
    }
    
    string line;
    while (getline(file, line)) {
        cout << HEADER << line << "\n";
    }
    cout << RESET;

}