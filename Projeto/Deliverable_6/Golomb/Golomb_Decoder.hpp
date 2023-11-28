#ifndef Golomb_Decoder_HPP
#define Golomb_Decoder_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <opencv4/opencv2/opencv.hpp>
#include "../HybridCodec/BitStream.h"

using namespace std;

/**
 * @class Golomb_Decoder
 *
 * @brief Represents a Golomb decoder for integer decompression.
 *
 * The Golomb_Decoder class provides functionality to decode Golomb-encoded
 * integers from a sequence of bits. It supports customization of the decoding
 * parameter 'm' and manages the associated BitStream for reading encoded data.
 */
class Golomb_Decoder
{
public:
    Golomb_Decoder(string inputFile, string outputFile);
    /**
     * @brief Constructs a Golomb_Decoder object with the specified parameter.
     *
     * This constructor initializes a Golomb_Decoder object with the specified parameter value.
     *
     * @param param The value of the parameter used in the Golomb decoding algorithm.
     */
    Golomb_Decoder(BitStream stream);

    /**
     * @brief Decodes a sequence of encoded bits.
     *
     * This method takes a vector of boolean values representing the encoded bits and decodes them using the Golomb decoding algorithm.
     *
     * @return The decoded integer value.
     */
    int decode();

    /**
     * @brief Reads an integer from the associated BitStream.
     *
     * Reads a binary representation of an integer from the BitStream. The number
     * of bits to read is controlled by the 'numBytes' parameter.
     *
     * @param numBytes The number of bytes (and bits) to read from the BitStream.
     * @return The decoded integer value.
     */
    int readInt(int numBytes);

    /**
     * @brief Sets the value of the parameter 'm' for Golomb decoding.
     *
     * This method sets the value of the parameter 'm' used in the Golomb decoding
     * algorithm. The parameter 'm' is a positive integer that influences the
     * efficiency of the decoding process.
     *
     * @param mParam The new value to set for the 'm' parameter.
     */
    void setMParam(int mParam);

    /**
     * @brief Decodes a block of Golomb-encoded values into a OpenCV Mat.
     *
     * This method decodes a square block of Golomb-encoded values with a specified size and returns the decoded block
     * represented as an OpenCV Mat. The Golomb decoding algorithm is applied to each element in the block to reconstruct
     * the pixel values.
     *
     * @param block_size The size of the square block to be decoded.
     * @return The decoded block represented as an OpenCV Mat.
     */
    vector<vector<int>> decodeBlock(int block_size);

    BitStream stream;

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

    int m; ///< The value of parameter m used in the Golomb decoding algorithm.
};

#endif // Golomb_Decoder_HPP
