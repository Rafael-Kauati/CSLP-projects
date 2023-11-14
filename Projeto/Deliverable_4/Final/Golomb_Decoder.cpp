#include "Golomb_Decoder.hpp"
#include "BitStream.h"

using namespace std;

Golomb_Decoder::Golomb_Decoder (int param, BitStream& newStream) : m(param), stream(newStream) {
    if(m <= 0 ){
        cerr<<"Error: The golomb parameter m should be positive" ;
    }
}

/**
 * @brief Decodes a sequence of encoded bits.
 *
 * This method takes a vector of boolean values representing the encoded bits and decodes them using the Golomb decoding algorithm.
 *
 * @return The decoded integer value.
 */
int Golomb_Decoder::decode() {
    int quotient = 0;
    int remainder = 0;
    int encodedBit = 1;
    string binValue;

    // Decoding the unary part to find the quotient
    while (encodedBit == 1) {
        encodedBit = stream.readOneFileBit();
        quotient++;
    }
    
    quotient--;

    int b = static_cast<int>(floor(log2(m))); // Calculate b as floor(log2(m))

    for(int i = 0; i < b; i++){
        binValue.append(to_string(stream.readOneFileBit()));
    }

    remainder = binaryToDecimal(binValue);

    int decodedValue = quotient * m + remainder;

    //  Alter the number to encode to account for negative numbers
    if (decodedValue % 2 == 1) {
        decodedValue = (decodedValue + 1) / -2 ;
    }
    else {
        decodedValue = decodedValue / 2;
    }

    return decodedValue;
}

/**
 * @brief Converts a binary string to a decimal integer.
 *
 * This method takes a binary string as input and converts it to a decimal integer.
 *
 * @param n The binary string to be converted.
 * @return The decimal integer representation of the binary string.
 */
int Golomb_Decoder::binaryToDecimal(string n) {
    string num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}




