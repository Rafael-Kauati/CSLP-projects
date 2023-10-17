#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BitStream {
    //  Private variables
    private:
        ifstream inputFile;
        ofstream outputFile;
        int bitBuffer[8];
        int bufferLen;

    //  Public methods
    public:

        //  Creator
        BitStream(string inFile, string outFile) {
            bufferLen = 0;
            inputFile = ifstream (inFile, ios::binary | ios::in);
            outputFile = ofstream (outFile, ios::binary | ios::out);
        }

        //  Read one bit from the input file based on the bit position
        int readOneFileBit(int bitPosition) {
            char c;
            //  Get the byte and bit index positions
            const auto [byteIndex, bitIndex] = std::div(bitPosition, 8);
            //  Go to the beggining of the file
            inputFile.seekg(0, ios::beg);

            //  Advance to the intended byte
            for (int i = 0; i <= byteIndex; i++) {
                inputFile.get(c);
            }

            //  Get the intended bit
            int tmp = ((c >> (7 - bitIndex)) & 1);

            return tmp;
        }

        //  Read N bits starting from the given bit position
        vector<int> readNFileBit(int initialBitPosition, int numBits) {
            vector<int> bitVector;

            //  Call readOneFileBit N times and append the outputs to a vector
            for (int bitPosition = 0; bitPosition < numBits; bitPosition++) {
                bitVector.push_back(readOneFileBit(initialBitPosition + bitPosition));
            }

            return bitVector;
        }
        
        //  Read 8 bits starting from the given bit position and assemble them as a char
        char readFileChar(int initialBitPosition) {
            //  Get the initial bit vector
            vector<int> charBits = readNFileBit(initialBitPosition, 8);
            char finalChar = '\0';

            //  Add the bits and shift them to the char
            for (int bitIndex = 7; bitIndex >= 0; bitIndex--) {
                finalChar |= charBits[7 - bitIndex] << (bitIndex);
            }

            return finalChar;
        }
        
        //  Read N chars starting from the given bit position and assemble them as a string
        string readFileString(int initialBitPosition, int numChars) {
            string output = "";
            int nextIndex = initialBitPosition;

            //  Call readFileChar N times and assemble the returned values inside a string
            for (int charIndex = 0; charIndex < numChars; charIndex++) {
                output += readFileChar(nextIndex);
                nextIndex += 8;
            }

            return output;
        }

        //  Write the bit into a buffer, if the buffer becomes full, flush it to the output file
        void writeOneFileBit(int newBit) {

            //  First fill the buffer
            if (bufferLen < 7) {
                bitBuffer[bufferLen] = newBit;
                bufferLen++;
            }
            //  If the buffer is full, arrange all the bits into a char and flush it to the file
            else {
                unsigned char byte = 0;
                bitBuffer[bufferLen] = newBit;

                for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
                    byte |= bitBuffer[bitIndex] << (7 - bitIndex);
                }

                bufferLen = 0;
                outputFile << byte;
            }
        }

        //  Write N bits into the output file
        void writeNFileBit(vector<int> bitVector) {
            
            //  For every bit in the vector, write it to the filw
            for (int bit : bitVector) {
                writeOneFileBit(bit);
            }

            return;
        }
        
        //  Write 8 bits from a givven char into the output file
        void writeFileChar(char newChar) {
            //  For every one of the 8 bits in the char
            for (int bitIndex = 7; bitIndex >= 0; bitIndex--) {
                //  Get the bit in the current position and write it
                writeOneFileBit(((newChar >> bitIndex) & 1));
            }
            return;
        }
        
        //  Write N chars from a string into the output file
        void writeFileString(string newString) {
            //  For every char in the string
            for (long unsigned int charIndex = 0; charIndex < newString.length(); charIndex++) {
                //  Write it to the output file
                writeFileChar(newString[charIndex]);
            }
            return;
        }

        //  Close all the files and flush the remainder of the buffer into the output file
        void close() {
            unsigned char byte = 0;

            //  If the buffer isn't empty
            if (bufferLen > 0) {
                //  Pad the rest of the buffer with zeros (arbitrary)
                for (int bitIndex = bufferLen; bitIndex < 8; bitIndex++) {
                    bitBuffer[bitIndex] = 0;
                }

                //  Write all the bits in the buffer (that is now padded) into a new char
                for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
                    byte |= bitBuffer[bitIndex] << (7 - bitIndex);
                }

                //  Write the char to the file
                bufferLen = 0;
                outputFile << byte;
            }

            //  Close the files
            inputFile.close();
            outputFile.close();
        }
};