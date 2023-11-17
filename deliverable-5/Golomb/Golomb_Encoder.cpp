#include <bitset>
#include "Golomb_Encoder.hpp"

using namespace std;

Golomb_Encoder::Golomb_Encoder(int param, BitStream& newStream) : m(param), stream(newStream)
{
    if (m <= 0)
    {
        cerr << "Error: The golomb parameter m should be positive";
    }
}

/**
 * @brief Encodes an integer using the Golomb encoding algorithm.
 *
 * This method takes an integer as input and encodes it using the Golomb encoding algorithm.
 *
 * @return A vector of boolean values representing the encoded bits.
 */
void Golomb_Encoder::encode(int num) {

    int numberToEncode = 0;

    //  Alter the number to encode to account for negative numbers
    if (num < 0) {
        numberToEncode = -2 * num - 1;
    }
    else {
        numberToEncode = 2 * num;
    }

    //  Iterate frame X and Y, encode each pixel and do bitstream write
    int quotient = num / m;
    int remainder = num % m;

    //  Write the unary code for the quotient 
    unaryCode(quotient);

    int b = static_cast<int>(floor(log2(m))); // Calculate b as floor(log2(m))

    if (remainder < (1 << (b + 1)) - m) {
        // If remainder < 2^(b+1) - m, code remainder using b bits
        for (int i = b - 1; i >= 0; --i) {
            stream.writeOneFileBit((remainder >> i) & 1);
        }
    }
    else {
        // If remainder >= 2^(b+1) - m, code remainder using b+1 bits
        for (int i = b; i >= 0; --i) {
            stream.writeOneFileBit((remainder >> i) & 1);
        }
    }

    return;
}

void Golomb_Encode::encodeBlock(Mat block) {
    int count = 0;
    for (int i = 0; i < block.rows; i++) {
        for (int j = 0; j < block.cols; j++) {
            encode(block.at<uchar>(i, j));
            count++;
        }
    }
    return;
}


/**
 * @brief Generates the unary code representation of a non-negative integer.
 *
 * This method takes a non-negative integer as input and generates its unary code representation.
 *
 * @param num The non-negative integer to be encoded.
 */
void Golomb_Encoder::unaryCode(int num) {
    for (int i = 0; i < num; ++i) {
        stream.writeOneFileBit(1);
    }

    stream.writeOneFileBit(0);  // Adicionar um 0 no final
    return;
}


void Golomb_Encoder::closeStreams() {
    stream.close();
}
