#ifndef Golomb_Encoder_HPP
#define Golomb_Encoder_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include "BitStream.h"

using namespace std;

/**
 * @brief A class for encoding integers using the Golomb encoding algorithm.
 *
 * The Golomb_Encoder class provides methods to encode integers using the Golomb encoding algorithm.
 */
class Golomb_Encoder {
    public:
        /**
         * @brief Constructs a Golomb_Encoder object with the specified parameter.
         *
         * This constructor initializes a Golomb_Encoder object with the specified parameter value.
         *
         * @param param The value of the parameter used in the Golomb encoding algorithm.
         */
        Golomb_Encoder(int param, BitStream& newStream);

        /**
         * @brief Encodes an integer using the Golomb encoding algorithm.
         *
         * This method takes an integer as input and encodes it using the Golomb encoding algorithm.
         *
         * @param num The number to be encoded.
         */
        void encode(int num);


        void closeStreams();

        int m; ///< The value of parameter m used in the Golomb encoding algorithm.
        BitStream& stream;

    private:
        /**
         * @brief Generates the unary code representation of an integer.
         *
         * This method takes an integer as input and generates its unary code representation.
         *
         * @param num The integer to be encoded.
         */
        void unaryCode(int num);
};

#endif // Golomb_Encoder_HPP
