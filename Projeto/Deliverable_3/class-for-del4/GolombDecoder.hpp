#ifndef GOLOMBDECODER_HPP
#define GOLOMBDECODER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief A class for decoding Golomb-encoded bit sequences.
 *
 * The GolombDecoder class provides methods to decode Golomb-encoded bit sequences using the Golomb decoding algorithm.
 */
class GolombDecoder
{
private:
    /**
     * @brief Converts a binary string to a decimal integer.
     *
     * This method takes a binary string as input and converts it to a decimal integer.
     *
     * @param n The binary string to be converted.
     * @return The decimal integer representation of the binary string.
     */
    int binaryToDecimal(string n);

public:
    /**
     * @brief Constructs a GolombDecoder object with the specified parameter.
     *
     * This constructor initializes a GolombDecoder object with the specified parameter value.
     *
     * @param param The value of the parameter used in the Golomb decoding algorithm.
     */
    GolombDecoder(int param);

    /**
     * @brief Decodes a sequence of encoded bits.
     *
     * This method takes a vector of boolean values representing the encoded bits and decodes them using the Golomb decoding algorithm.
     *
     * @param encodedBits The vector of boolean values representing the encoded bits.
     * @return The decoded integer value.
     */
    int decode(const vector<int> &encodedBits);

    int m; ///< The value of parameter m used in the Golomb decoding algorithm.
};

#endif // GOLOMBDECODER_HPP
