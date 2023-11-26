#ifndef Golomb_Decoder_HPP
#define Golomb_Decoder_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "../Predictor/BitStream.h"

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
    /**
     * @brief Constructs a Golomb_Decoder object with specified input and output files.
     *
     * Initializes a Golomb_Decoder object with the provided input and output file names.
     *
     * @param inputFile The name of the input file.
     * @param outputFile The name of the output file.
     */
    Golomb_Decoder(string inputFile, string outputFile);

    /**
     * @brief Constructs a Golomb_Decoder object with a given BitStream.
     *
     * Initializes a Golomb_Decoder object with a provided BitStream for decoding.
     *
     * @param stream The BitStream to be associated with the decoder.
     */
    Golomb_Decoder(BitStream stream);

    /**
     * @brief Decodes a sequence of encoded bits using the Golomb decoding algorithm.
     *
     * This method takes a vector of boolean values representing the encoded bits
     * and decodes them using the Golomb decoding algorithm, returning the decoded integer value.
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
     * @brief The associated BitStream for decoding Golomb-encoded data.
     */
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
