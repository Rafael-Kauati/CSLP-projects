//
// Created by tk on 13-10-2023.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vector>
#include "GolombDecoder.hpp"
#include "GolombEncoder.hpp"

TEST_CASE("Golomb Encoding and Decoding Test", "[Golomb]") {
    SECTION("Encoding and Decoding with Golomb") {
        int m = 4; // Golomb parameter
        GolombEncoder encoder(m);
        GolombDecoder decoder(m);

        // Test multiple values for encoding and decoding
        std::vector<int> testValues = {7, 12, 3, 19, 8};

        for (const auto& num : testValues) {
        std::vector<bool> encodedBits = encoder.encode(num);
        int decodedValues = decoder.decode(encodedBits);

        // Ensure the decoded values match the original input
        REQUIRE(decodedValues == num);

        }
    }
}
/*
 */