#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BitStream {

    private:
        ifstream inputFile;
        ofstream outputFile;
        int bitBuffer[8];
        int bufferLen;

    public:
        BitStream(string inFile, string outFile) {
            bufferLen = 0;
            inputFile = ifstream (inFile, ios::binary | ios::in);
            outputFile = ofstream (outFile, ios::binary | ios::out);
        }

        int readOneFileBit(int bitPosition) {
            char c;
            const auto [byteIndex, bitIndex] = std::div(bitPosition, 8);
            inputFile.seekg(0, ios::beg);

            for (int i = 0; i <= byteIndex; i++) {
                inputFile.get(c);
            }

            int tmp = ((c >> (7 - bitIndex)) & 1);

            return tmp;
        }

        vector<int> readNFileBit(int initialBitPosition, int numBits) {
            vector<int> bitVector;

            for (int bitPosition = 0; bitPosition < numBits; bitPosition++) {
                bitVector.push_back(readOneFileBit(initialBitPosition + bitPosition));
            }

            return bitVector;
        }
        
        char readFileChar(int initialBitPosition) {
            vector<int> charBits = readNFileBit(initialBitPosition, 8);
            char finalChar;

            for (int bitIndex = 7; bitIndex >= 0; bitIndex--) {
                finalChar |= charBits[7 - bitIndex] << (bitIndex);
            }

            return finalChar;
        }
        
        string readFileString(int initialBitPosition, int numChars) {
            string output;
            int nextIndex = initialBitPosition;

            for (int charIndex = 0; charIndex < numChars; charIndex++) {
                output += readFileChar(nextIndex);
                nextIndex += 8;
            }

            return output;
        }


        void writeOneFileBit(int newBit) {

            if (bufferLen < 7) {
                bitBuffer[bufferLen] = newBit;
                bufferLen++;
                cout << " + inbuf: " << newBit << "\n";
            }
            else {
                unsigned char byte = 0;
                bitBuffer[bufferLen] = newBit;

                cout << " - outbuff: ";
                for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
                    byte |= bitBuffer[bitIndex] << (7 - bitIndex);
                cout << bitBuffer[bitIndex] << " ";
                }
                cout << "\n";

                bufferLen = 0;

                outputFile << byte;
            }
        }
        
        void writeNFileBit(vector<int> bitVector) {
            
            for (int bit : bitVector) {
                writeOneFileBit(bit);
            }

            return;
        }
        
        void writeFileChar(char newChar) {
            for (int bitIndex = 7; bitIndex >= 0; bitIndex--) {
                writeOneFileBit(((newChar >> bitIndex) & 1));
            }
            return;
        }
        
        void writeFileString(string newString) {
            for (long unsigned int charIndex = 0; charIndex < newString.length(); charIndex++) {
                writeFileChar(newString[charIndex]);
            }
            return;
        }

        void close() {
            unsigned char byte = 0;

            if (bufferLen > 0) {
                for (int bitIndex = bufferLen; bitIndex < 8; bitIndex++) {
                    bitBuffer[bitIndex] = 0;
                }

                cout << " - outbuff: ";
                for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
                    byte |= bitBuffer[bitIndex] << (7 - bitIndex);

                    if (bitIndex < bufferLen) {
                        cout << bitBuffer[bitIndex] << " ";
                    }
                    else {
                        cout << "x ";
                    }
                }
                cout << "\n";

                bufferLen = 0;
                outputFile << byte;
            }

            inputFile.close();
            outputFile.close();
        }
};

int main() {

    //  Initiate BitStream object
    BitStream bitSt("input.bin", "output.bin");

    bitSt.writeOneFileBit(1);
    bitSt.writeOneFileBit(0);
    bitSt.writeOneFileBit(1);
    bitSt.writeOneFileBit(1);
    bitSt.writeOneFileBit(0);
    bitSt.writeOneFileBit(0);
    bitSt.writeOneFileBit(0);
    bitSt.writeOneFileBit(1);

    bitSt.writeOneFileBit(0);
    bitSt.writeOneFileBit(0);
    bitSt.writeOneFileBit(1);
    bitSt.writeOneFileBit(0);
    bitSt.writeOneFileBit(0);
    bitSt.writeOneFileBit(1);
    bitSt.writeOneFileBit(0);
    bitSt.writeOneFileBit(0);

    cout << " > read: [";
    for (int i = 0; i < 8; i++) {
        cout << bitSt.readOneFileBit(i);
    }
    cout << "] \n";

    //  Get all bits in the file
    std::vector<int> bits = bitSt.readNFileBit(0,16);
    
    //  Print the bits
    int counter = 0;
    cout << " > read: [";
    for(int i : bits) {

        if (counter % 8 == 0 && counter != 0) {
            cout << "] [";
        }
		std::cout << i;
        counter++;
    }    
    cout << "] \n";

    bitSt.writeNFileBit(bits);
    bitSt.close();


    BitStream charFiles("inputStrings.txt", "outputStrings.txt");

    charFiles.writeFileChar('P');
    charFiles.writeFileString("Ramos");

    
    cout << " > read Char: " << charFiles.readFileChar(0) << "\n";
    cout << " > read Char: " << charFiles.readFileChar(8) << "\n";
    cout << " > read Char: " << charFiles.readFileChar(16) << "\n";
    cout << " > read Char: " << charFiles.readFileChar(24) << "\n";
    cout << " > read Char: " << charFiles.readFileChar(32) << "\n";
    cout << " > read String: " << charFiles.readFileString(0, 5) << "\n";
    charFiles.close();
}