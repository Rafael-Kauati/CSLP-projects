#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch2/catch.hpp>
#include "../../Program_4/BitStream.h"

/**
 * @brief Test case for the BitStream class
 *
 * This test case includes multiple sections to test different functionalities of the BitStream class.
 */
TEST_CASE("Simple test")
{

    /**
     * @brief Section to test reading bits from an input file
     *
     * \n This section creates a BitStream object with an input file and an output file.
     * \n It reads individual bits from the input file and checks if the read bits match the expected values.
     * \n Finally, it closes the BitStream object and prints a success message.
     */
    SECTION("Read bits from an input file")
    {
        BitStream bitStrm("resources/input.bin", "resources/output.bin");

        REQUIRE(bitStrm.readOneFileBit() == 1);
        REQUIRE(bitStrm.readOneFileBit() == 0);
        REQUIRE(bitStrm.readOneFileBit() == 1);
        REQUIRE(bitStrm.readOneFileBit() == 1);
        REQUIRE(bitStrm.readOneFileBit() == 0);
        REQUIRE(bitStrm.readOneFileBit() == 0);
        REQUIRE(bitStrm.readOneFileBit() == 0);
        REQUIRE(bitStrm.readOneFileBit() == 1);

        bitStrm.close();

        cout << "Single Bits read sucessfully!\n";
    }

    /**
     * @brief Section to test writing bits to an output file
     *
     * \n This section creates a BitStream object with an input file and an output file.
     * \n It writes individual bits to the output file.
     * \n It then creates a new BitStream object with the output file and no input file.
     * \n It reads individual bits from the output file and checks if the read bits match the expected values.
     * \n Finally, it closes both BitStream objects and prints success messages.
     */
    SECTION("Write bits to an output file")
    {
        BitStream bitStrm("resources/input.bin", "resources/output.bin");
        bitStrm.writeOneFileBit(0);
        bitStrm.writeOneFileBit(1);
        bitStrm.writeOneFileBit(0);
        bitStrm.writeOneFileBit(1);
        bitStrm.writeOneFileBit(1);
        bitStrm.writeOneFileBit(0);
        bitStrm.writeOneFileBit(1);
        bitStrm.writeOneFileBit(0);

        bitStrm.close();
        BitStream readTester("resources/output.bin", "");

        REQUIRE(readTester.readOneFileBit() == 0);
        REQUIRE(readTester.readOneFileBit() == 1);
        REQUIRE(readTester.readOneFileBit() == 0);
        REQUIRE(readTester.readOneFileBit() == 1);
        REQUIRE(readTester.readOneFileBit() == 1);
        REQUIRE(readTester.readOneFileBit() == 0);
        REQUIRE(readTester.readOneFileBit() == 1);
        REQUIRE(readTester.readOneFileBit() == 0);

        readTester.close();

        cout << "Single Bits written sucessfully!\n";
    }

    /**
     * @brief Section to test writing and reading multiple bits to an output file
     *
     * \n This section creates a BitStream object with an input file and an output file.
     * \n It writes multiple bits to the output file.
     * \n It then creates a new BitStream object with the output file and no input file.
     * \n It reads multiple bits from the output file and checks if the read bits match the expected values.
     * \n Finally, it closes both BitStream objects and prints success messages.
     */
    SECTION("Write and read multiple bits to an output file")
    {
        BitStream bitStrm("resources/input.bin", "resources/output.bin");
        bitStrm.writeNFileBit(vector<int>{0, 0, 0, 0, 1, 1, 1, 1});
        bitStrm.close();

        BitStream readTester("resources/output.bin", "");
        REQUIRE(readTester.readNFileBit(8) == vector<int>{0, 0, 0, 0, 1, 1, 1, 1});
        readTester.close();

        cout << "Multiple Bits written sucessfully!\n";
        cout << "Multiple Bits read sucessfully!\n";
    }

    /**
     * @brief Section to test writing and reading chars
     *
     * \n This section creates a BitStream object with an input file and an output file.
     * \n It writes a char to the output file.
     * \n It then creates a new BitStream object with the output file and no input file.
     * \n It reads a char from the output file and checksif the read char matches the expected value.
     * \n Finally, it closes both BitStream objects and prints success messages.
     */
    SECTION("Write and read chars")
    {
        BitStream bitStrm("resources/input.bin", "resources/output.bin");
        bitStrm.writeFileChar('R');
        bitStrm.close();

        BitStream readTester("resources/output.bin", "");
        REQUIRE(readTester.readFileChar() == 'R');
        readTester.close();

        cout << "Characters written sucessfully!\n";
        cout << "Characters read sucessfully!\n";
    }

    /**
     * @brief Section to test writing and reading strings
     *
     * This section creates a BitStream object with an input file and an output file.
     * It writes a string to the output file.
     * It then creates a new BitStream object with the output file and no input file.
     * It reads a string from the output file and checks if the read string matches the expected value.
     * Finally, it closes both BitStream objects and prints success messages.
     */
    SECTION("Write and read strings")
    {
        BitStream bitStrm("resources/input.bin", "resources/output.bin");
        bitStrm.writeFileString("PRamos");
        bitStrm.close();

        BitStream readTester("resources/output.bin", "");
        REQUIRE(readTester.readFileString(6) == "PRamos");
        readTester.close();

        cout << "Strings written sucessfully!\n";
        cout << "Strings read sucessfully!\n";
    }
}