//
// Created by tk on 13-10-2023.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vector>
#include "Golomb.cpp"

using namespace std;

/**
 * @brief Test case for Golomb Encoding and Decoding.
 *
 * This test case verifies the functionality of the GolombEncoder and GolombDecoder classes
 * by encoding and decoding multiple values and ensuring the decoded values match the original input.
 */
TEST_CASE("Golomb Encoding and Decoding Test", "[Golomb]")
{
    /**
     * @brief Encoding and Decoding with Golomb.
     *
     * This section initiates variables, creates GolombEncoder and GolombDecoder objects,
     * and tests multiple values for encoding and decoding.
     */
    SECTION("Encoding and Decoding with Golomb")
    {
        cout << "Initiating variables\n\n";
        int m = 10; // Golomb parameter
        Golomb golomb(m, "output.bin", "output.bin");

        // Test multiple values for encoding and decoding
        vector<int> testValues = {42};

        for (const auto &num : testValues)
        {
            cout << " Testing value: " << num << " ...";
            const int position = 0;
            //Encode and write the encode values in the output file
            vector<int> encodedBits = golomb.encode(num);

            //Read and decode the values from the output file
            int decodedValues = golomb.decode(position);

            // Ensure the decoded values match the original input
            cout << " Testing value: " << num << " ...";

            REQUIRE(decodedValues == num);

            cout << " Success!\n";
        }
    }
}