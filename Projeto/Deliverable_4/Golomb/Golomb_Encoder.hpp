#ifndef Golomb_Encoder_HPP
#define Golomb_Encoder_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include "../Predictor/BitStream.h"

using namespace std;

/**
 * @class Golomb_Encoder
 *
 * @brief Represents a Golomb encoder for integer compression.
 *
 * The Golomb_Encoder class provides functionality to encode integers using
 * the Golomb encoding algorithm. It supports customization of the encoding
 * parameter 'm' and manages the associated BitStream for writing encoded
 * data.
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

    /**
     * @brief Writes an integer to the stream.
     *
     * This method writes the binary representation of the specified integer to
     * the BitStream. The number of bits to write is controlled by the
     * 'numBytes' parameter. The most significant bits are written first.
     *
     * @param num The integer value to be written to the stream.
     * @param numBytes The number of bytes (and bits) to write from the integer.
     * @see closeStreams()
     */
    void writeInt(int num, int numBytes);

    /**
     * @brief Sets the value of the parameter 'm'.
     *
     * This method sets the value of the parameter 'm' used in the Golomb encoding
     * algorithm. The parameter 'm' is a positive integer that influences the
     * efficiency of the encoding process.
     *
     * @param mParam The new value to set for the 'm' parameter.
     * @see writeInt(), closeStreams()
     */
    void setMParam(int mParam);

    /**
     * @brief Closes the associated stream.
     *
     * This method closes the BitStream. It is essential to call
     * this method to ensure proper cleanup and resource management after encoding
     * is complete.
     *
     * @see writeInt(), setMParam()
     */
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
