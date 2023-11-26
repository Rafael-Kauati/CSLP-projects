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
 * @brief A class for decoding Golomb-encoded bit sequences.
 *
 * The Golomb_Decoder class provides methods to decode Golomb-encoded bit sequences using the Golomb decoding algorithm.
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

    int readInt(int numBytes);

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
    cv::Mat decodeBlock(int block_size);

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
