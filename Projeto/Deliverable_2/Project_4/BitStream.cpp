#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BitStream {

    public:
        int readOneFileBit(string inFile, int charIndex, int bitIndex) {
            ifstream file (inFile, ios::binary | ios::in);
            char c;

            for (int i = 0; i <= charIndex; i++) {
                file.get(c);
            }

            file.close();
            return ((c >> (7 - bitIndex)) & 1);

        }

        std::vector<int> readNFileBits(string inFile, int charStartIndex, int bitStartIndex, int numBits) {
            ifstream file (inFile, ios::binary | ios::in);
            char c;

            vector <int> output;

            for (int i = 0; i < charStartIndex; i++) {
                file.get(c);
            }

            int numBitsPassed = 0;

            while (file.get(c) && numBitsPassed < numBits) {                
                for (int i = 7 - bitStartIndex; i >= 0 && numBitsPassed < numBits; i--) {
                    output.push_back((c >> i) & 1);
                    numBitsPassed++;
                    bitStartIndex = 0;
                }
            }

            file.close();
            return output;

        }

        std::vector<int> readAllFileBits(string inFile) {
            ifstream file (inFile, ios::binary | ios::in);
            char c;

            vector <int> output;

            int numBitsPassed = 0;

            while (file.get(c)) {
                for (int i = 7; i >= 0; i--) {
                    output.push_back((c >> i) & 1);
                    numBitsPassed++;
                }
            }
            
            file.close();
            return output;
        }

        void writeOneFileBit(string inFile, int charIndex, int bitIndex, int newBit) {
            fstream file (inFile, ios::binary | ios::in | ios::out);
            char c;

            for (int i = 0; i < charIndex; i++) {
                file.get(c);
            }            
            
            bitIndex = 7 - bitIndex;

            c = ((c & ~(1 << bitIndex)) | (newBit << bitIndex));
            
            file.put(c);
        }

};

int main() {

    //  Initiate BitStream object
    BitStream bitSt;



    //  Print bit at byte 3 position 6
    std::cout << bitSt.readOneFileBit("test.txt", 3, 6) << "\n";
    



    //  Get 10 bits starting from position 2, 7 
    std::vector<int> bits = bitSt.readNFileBits("test.txt", 2, 7, 10);
    
    //  Print the bits
    for(int i : bits) {
		std::cout << i << " ";
    }
    std::cout << "\n";




    //  Get all bits in the file
    std::vector<int> otherbits = bitSt.readAllFileBits("test.txt");
    
    //  Print the bits
    for(int i : otherbits) {
		std::cout << i << " ";
    }    
    std::cout << "\n";

   

    bitSt.writeOneFileBit("test.txt", 0, 0, 0);
    bitSt.writeOneFileBit("test.txt", 0, 1, 1);
    bitSt.writeOneFileBit("test.txt", 0, 2, 1);
    bitSt.writeOneFileBit("test.txt", 0, 3, 0);
    bitSt.writeOneFileBit("test.txt", 0, 4, 1);
    bitSt.writeOneFileBit("test.txt", 0, 5, 0);
    bitSt.writeOneFileBit("test.txt", 0, 6, 0);
    bitSt.writeOneFileBit("test.txt", 0, 7, 0);

}