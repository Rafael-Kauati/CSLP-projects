#include "Goulomb_Decoder.hpp"
#include "BitStream.h"

using namespace std;

Goulomb_Decoder::Goulomb_Decoder (int param, BitStream& newStream) : m(param), stream(newStream) {
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
int Goulomb_Decoder::decode(int num_pixels_in_frame) {
    int quotient = 0;
    bool startUnary = 0;
    int remainder = 0;
    int n = 0;

    const vector<int> encodedBits = stream.readNFileBit();

    for(int b : encodedBits)
    {
        cout << b;
    }

    // Decoding the unary part to find the quotient
    for (; n < encodedBits.size() ; n++) {
        if(startUnary == 0){
            //Encotrou o início da parte unary do número codificado (primeiro '1')

            if(encodedBits[n] == 1){
                startUnary = 1;
                quotient++;
                continue;
            }
        }
        else
        {
            if(encodedBits[n] != 0){
                quotient++;
            }
            //Encotrou o fim da parte unary do número codificado (primeiro '0' após os '1's)
            else
            {
                break;
            }
        }
    }


    n++; // Skip the delimiter '0'

    // Decoding the binary part to find the remainder
    int b = static_cast<int>(floor(log2(m))); // Calculate b as floor(log2(m))
    string binValue;

    for (int i = 0; i < b; ++i) {
        binValue += to_string(encodedBits[n]);
        n++;
    }

    // Check if the decoded remainder needs b+1 bits
    if (stoi(binValue, nullptr, 2) >= (1 << (b + 1)) - m) {
        binValue += to_string(encodedBits[n]);
        n++;
    }

    remainder = stoi(binValue, nullptr, 2);

    int decodedValue = quotient * m + remainder;
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
int Goulomb_Decoder::binaryToDecimal(string n) {


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




