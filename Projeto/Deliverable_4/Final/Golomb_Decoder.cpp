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
    bool startUnary = 0;
    int remainder = 0;
    int n = 0;
    int encodedBit = 0;

    // Decoding the unary part to find the quotient
    while (1) {
        encodedBit = stream.readOneFileBit();
        if(startUnary == 0){
            //Encotrou o início da parte unary do número codificado (primeiro '1')

            if(encodedBit == 1){
                startUnary = 1;
                quotient++;
                continue;
            }
            else {
                cout << "ERRO!!!!\n";
            }
        }
        else
        {
            if(encodedBit != 0){
                quotient++;
            }
            //Encotrou o fim da parte unary do número codificado (primeiro '0' após os '1's)
            else
            {
                break;
            }
        }
    }

    cout << "quotient: " << quotient << "\n";

    // Decoding the binary part to find the remainder
    int b = static_cast<int>(floor(log2(m))); // Calculate b as floor(log2(m))
    string binValue;

    for (int i = 0; i < b; ++i) {
        encodedBit = stream.readOneFileBit();
        binValue += to_string(encodedBit);
    }

    // Check if the decoded remainder needs b+1 bits
    if (stoi(binValue, nullptr, 2) >= (1 << (b + 1)) - m) {
        encodedBit = stream.readOneFileBit();
        binValue += to_string(encodedBit);
    }

    remainder = stoi(binValue, nullptr, 2);

    int decodedValue = quotient * m + remainder;
    cout << "DECODED : " << decodedValue << "\n";
    int numberToDecode = 0;

    // TO CHECK PLS
    //  Alter the number to encode to account for negative numbers
    if (decodedValue < 0) {
        numberToDecode = -2 * decodedValue - 1;
    }
    else {
        numberToDecode = 2 * decodedValue;
    }

    return numberToDecode;
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




