#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class BitStream {
    public:
        int readOneFileBit(string inFile, int charIndex, int bitIndex) {
            ifstream file (inFile, ios::binary | ios::in);
            char c;

            for (int i = 0; i <= charIndex; i++) {
                file.get(c);
            }

            return ((c >> (7 - bitIndex)) & 1);

        }

        int readNFileBit(string inFile, int charStartIndex, int bitStartIndex, int numBits) {
            ifstream file (inFile, ios::binary | ios::in);
            char c;

            for (int i = 0; i < charStartIndex; i++) {
                file.get(c);
            }

            int numBitsPassed = 0;

            while (file.get(c) && numBitsPassed < numBits) {                
                for (int i = 7 - bitStartIndex; i >= 0 && numBitsPassed < numBits; i--) {
                    cout << ((c >> i) & 1);
                    numBitsPassed++;
                }
            }

        }

        int readAllFileBit(string inFile) {
            ifstream file (inFile, ios::binary | ios::in);
            char c;

            while (file.get(c)) {
                for (int i = 7; i >= 0; i--)
                    cout << ((c >> i) & 1);
                //cout << "\n";

            }

        }

        void writeOneFileBit(string inFile, int charIndex, int bitIndex) {
            ifstream fileOriginal (inFile, ios::binary | ios::in);
            ofstream file (inFile, ios::binary | ios::out);
            char c;

            for (int i = 0; i <= charIndex; i++) {
                file.put(c);
            }

            cout << ((c >> (7 - bitIndex)) & 1);

        }

};

int main() {

    BitStream bitSt;

    cout << bitSt.readOneFileBit("test.txt", 0, 0) << "\n";
    
    cout << bitSt.readNFileBit("test.txt", 0, 0, 10) << "\n";

    cout << bitSt.readAllFileBit("test.txt") << "\n";
}