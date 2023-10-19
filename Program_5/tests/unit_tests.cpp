#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch2/catch.hpp>
#include "../../Program_4/BitStream.h"

TEST_CASE("Simple test") {
    
    SECTION("Read bits from an input file") {
        BitStream bitStrm("../resources/input.bin", "../resources/output.bin");

        REQUIRE(bitStrm.readOneFileBit(0) == 1);
        REQUIRE(bitStrm.readOneFileBit(1) == 0);
        REQUIRE(bitStrm.readOneFileBit(2) == 1);
        REQUIRE(bitStrm.readOneFileBit(3) == 1);
        REQUIRE(bitStrm.readOneFileBit(0) == 1);
        REQUIRE(bitStrm.readOneFileBit(1) == 0);
        REQUIRE(bitStrm.readOneFileBit(2) == 1);
        REQUIRE(bitStrm.readOneFileBit(3) == 1);
        
        bitStrm.close();

        cout << "Single Bits read sucessfully!\n";
    }
    
    SECTION("Write bits to an output file") {
        BitStream bitStrm("../resources/input.bin", "../resources/output.bin");
        bitStrm.writeOneFileBit(0);
        bitStrm.writeOneFileBit(1);
        bitStrm.writeOneFileBit(0);
        bitStrm.writeOneFileBit(1);
        bitStrm.writeOneFileBit(1);
        bitStrm.writeOneFileBit(0);
        bitStrm.writeOneFileBit(1);
        bitStrm.writeOneFileBit(0);

        bitStrm.close();
        BitStream readTester("../resources/output.bin", "");

        REQUIRE(readTester.readOneFileBit(0) == 0);
        REQUIRE(readTester.readOneFileBit(1) == 1);
        REQUIRE(readTester.readOneFileBit(2) == 0);
        REQUIRE(readTester.readOneFileBit(3) == 1);
        REQUIRE(readTester.readOneFileBit(4) == 1);
        REQUIRE(readTester.readOneFileBit(5) == 0);
        REQUIRE(readTester.readOneFileBit(6) == 1);
        REQUIRE(readTester.readOneFileBit(7) == 0);

        readTester.close();

        cout << "Single Bits written sucessfully!\n";
    }
    
    SECTION("Write and read multiple bits to an output file") {
        BitStream bitStrm("../resources/input.bin", "../resources/output.bin");
        bitStrm.writeNFileBit(vector <int> {0, 0, 0, 0, 1, 1, 1, 1});
        bitStrm.close();

        BitStream readTester("../resources/output.bin", "");
        REQUIRE(readTester.readNFileBit(0, 8) == vector <int> {0, 0, 0, 0, 1, 1, 1, 1});
        readTester.close();

        cout << "Multiple Bits written sucessfully!\n";
        cout << "Multiple Bits read sucessfully!\n";
    }
    
    SECTION("Write and read chars") {
        BitStream bitStrm("../resources/input.bin", "../resources/output.bin");
        bitStrm.writeFileChar('R');
        bitStrm.close();

        BitStream readTester("../resources/output.bin", "");
        REQUIRE(readTester.readFileChar(0) == 'R');
        readTester.close();

        cout << "Characters written sucessfully!\n";
        cout << "Characters read sucessfully!\n";
    }
    
    SECTION("Write and read strings") {
        BitStream bitStrm("../resources/input.bin", "../resources/output.bin");
        bitStrm.writeFileString("PRamos");
        bitStrm.close();

        BitStream readTester("../resources/output.bin", "");
        REQUIRE(readTester.readFileString(0, 6) == "PRamos");
        readTester.close();

        cout << "Strings written sucessfully!\n";
        cout << "Strings read sucessfully!\n";
    }
}