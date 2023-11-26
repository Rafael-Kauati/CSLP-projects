#ifndef Golomb_Encoder_HPP
#define Golomb_Encoder_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include "../HybridCodec/BitStream.h"
#include <opencv4/opencv2/opencv.hpp>

using namespace std;

/**
 * @brief A class for encoding integers using the Golomb encoding algorithm.
 *
 * The Golomb_Encoder class provides methods to encode integers using the Golomb encoding algorithm.
 */
class Golomb_Encoder
{
public:
    Golomb_Encoder(string inputFile, string outputFile);
    /**
     * @brief Constructs a Golomb_Encoder object with the specified parameter.
     *
     * This constructor initializes a Golomb_Encoder object with the specified parameter value.
     *
     * @param param The value of the parameter used in the Golomb encoding algorithm.
     */
    Golomb_Encoder(BitStream newStream);

    /**
     * @brief Encodes an integer using the Golomb encoding algorithm.
     *
     * This method takes an integer as input and encodes it using the Golomb encoding algorithm.
     *
     * @param num The number to be encoded.
     */
    void encode(int num);

    void writeInt(int num, int numBytes);

    /**
     * @brief Encodes a block of pixel values using the Golomb encoding algorithm.
     *
     * This method encodes a square block of pixel values with a specified size using the Golomb encoding algorithm.
     * Each pixel value in the block is individually encoded using the Golomb encoding technique, and the resulting
     * encoded bits are written to the output bitstream.
     *
     * @param block The square block of pixel values to be encoded.
     */
    void encodeBlock(cv::Mat block);

    void setMParam(int mParam);

    void closeStreams();

    BitStream stream;

private:
    /**
     * @brief Generates the unary code representation of an integer.
     *
     * This method takes an integer as input and generates its unary code representation.
     *
     * @param num The integer to be encoded.
     */
    void unaryCode(int num);

    int m; ///< The value of parameter m used in the Golomb encoding algorithm.
};

#endif // Golomb_Encoder_HPP
