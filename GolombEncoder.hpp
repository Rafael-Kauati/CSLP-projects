#ifndef GOLOMBENCODER_HPP
#define GOLOMBENCODER_HPP

#include "Golomb_Param.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief A class for encoding integers using the Golomb encoding algorithm.
 *
 * The GolombEncoder class provides methods to encode integers using the Golomb encoding algorithm.
 */
class GolombEncoder
{
public:
    /**
     * @brief Constructs a GolombEncoder object with the specified parameter.
     *
     * This constructor initializes a GolombEncoder object with the specified parameter value.
     *
     * @param param The value of the parameter used in the Golomb encoding algorithm.
     */
    GolombEncoder(int param);

    /**
     * @brief Encodes an integer using the Golomb encoding algorithm.
     *
     * This method takes an integer as input and encodes it using the Golomb encoding algorithm.
     *
     * @param num The integer to be encoded.
     * @return A vector of boolean values representing the encoded bits.
     */
    vector<bool> encode(int num);

    int m; ///< The value of parameter m used in the Golomb encoding algorithm.

private:
    /**
     * @brief Generates the unary code representation of an integer.
     *
     * This method takes an integer as input and generates its unary code representation.
     *
     * @param num The integer to be encoded.
     * @return A vector of boolean values representing the unary code.
     */
    vector<bool> unaryCode(int num);
};

#endif // GOLOMBENCODER_HPP
