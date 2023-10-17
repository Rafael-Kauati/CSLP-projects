#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../Program_4/BitStream.h"

int main() {

    cout << " ---------- Test program for BitStream ----------\n";
    //  Initiate BitStream object
    BitStream bitSt("resources/input.bin", "resources/output.bin");

    cout << "\n ---------- Write One bit to a file one by one ----------\n";
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

    cout << " > write: [10110001] [00100100]\n";

    cout << "\n ---------- Read the bits in a file one by one ----------\n";
    cout << " > read:  [";
    for (int i = 0; i < 8; i++) {
        cout << bitSt.readOneFileBit(i);
    }
    cout << "] \n";

    cout << "\n ---------- Read N bits in a file ----------\n";
    //  Get all bits in the file
    std::vector<int> bits = bitSt.readNFileBit(0,16);
    
    //  Print the bits
    int counter = 0;
    cout << " > read:  [";
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


    BitStream charFiles("resources/inputStrings.txt", "resources/outputStrings.txt");

    cout << "\n ---------- Write a Char to a file ----------\n";
    charFiles.writeFileChar('P');
    cout << " > write: 'P'\n";

    cout << "\n ---------- Write a String to a file ----------\n";
    charFiles.writeFileString("Ramos");
    cout << " > write: 'Ramos'\n";

    
    cout << "\n ---------- Read a Char in a file one by one ----------\n";
    cout << " > read Char: " << charFiles.readFileChar(0) << "\n";
    cout << " > read Char: " << charFiles.readFileChar(8) << "\n";
    cout << " > read Char: " << charFiles.readFileChar(16) << "\n";
    cout << " > read Char: " << charFiles.readFileChar(24) << "\n";
    cout << " > read Char: " << charFiles.readFileChar(32) << "\n";
    cout << " > read Char: " << charFiles.readFileChar(40) << "\n";
    cout << "\n ---------- Read a String in a file ----------\n";
    cout << " > read String: " << charFiles.readFileString(0, 6) << "\n";
    charFiles.close();
}