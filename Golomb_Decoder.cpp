#include "GolombDecoder.hpp"

using namespace std;

GolombDecoder::GolombDecoder (int param) : m (param) {
    if(m <= 0 ){
        cerr<<"Error: The golomb parameter m should be positive" ;
    }
}

/**
 * @brief Converts a binary string to a decimal integer.
 *
 * This method takes a binary string as input and converts it to a decimal integer.
 *
 * @param n The binary string to be converted.
 * @return The decimal integer representation of the binary string.
 */
int GolombDecoder::binaryToDecimal(string n) {
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

/**
 * @brief Decodes a sequence of encoded bits.
 *
 * This method takes a vector of boolean values representing the encoded bits and decodes them using the Golomb decoding algorithm.
 *
 * @param encodedBits The vector of boolean values representing the encoded bits.
 * @return The decoded integer value.
 */
int GolombDecoder::decode(const vector<bool>& encodedBits) {
    vector<bool> decodedValues;
    int n = 0;
    int quotient = 0;
    int remainder = 1;
    string binValue;

    while (n < encodedBits.size() && encodedBits[n] == 1) {
        quotient++;
        n++;
    }

    n++; // Skip the delimiter '0'

    for(int i = n; i < encodedBits.size() ; i ++){
        binValue.append(to_string(encodedBits[i]));
    }

    remainder  = binaryToDecimal(binValue);

    int decodedValue = quotient * m + remainder;

    decodedValues.push_back(decodedValue);

    return decodedValue;
}


