#ifndef Golomb_Decoder_HPP
#define Golomb_Decoder_HPP

#include <vector>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include "BitStream.h"

using namespace std;
using namespace cv;

/**
 * @brief A class for decoding Golomb-encoded bit sequences.
 *
 * The Golomb_Decoder class provides methods to decode Golomb-encoded bit sequences using the Golomb decoding algorithm.
 */
class Golomb_Decoder {
    public:
        /**
         * @brief Constructs a Golomb_Decoder object with the specified parameter.
         *
         * This constructor initializes a Golomb_Decoder object with the specified parameter value.
         *
         * @param param The value of the parameter used in the Golomb decoding algorithm.
         */
        Golomb_Decoder(int param, BitStream& stream);

        /**
         * @brief Decodes a sequence of encoded bits.
         *
         * This method takes a vector of boolean values representing the encoded bits and decodes them using the Golomb decoding algorithm.
         *
         * @return The decoded integer value.
         */
        int decode();

        Mat decodeBlock(int block_size);

        int m; ///< The value of parameter m used in the Golomb decoding algorithm.
        BitStream& stream;

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
};

#endif // Golomb_Decoder_HPP
