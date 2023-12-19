#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    std::cout << " ---------- YUV 4:4:4 Reader Test ---------- \n";

    int wordNum = 0;

    char ch;
    ifstream yuvFile("outputDucks00.y4m", fstream::in);

    //  Get the first line
    string dataLine;
    getline( yuvFile, dataLine );

    cout << dataLine << "\n";


    while (yuvFile >> noskipws >> ch && wordNum < 1) {
        if (ch == ' ') {
            cout << "\n";
            wordNum++;
            continue;
        }

        cout << ch;
    }


    cout << "\n";
    
    return 0;
}
