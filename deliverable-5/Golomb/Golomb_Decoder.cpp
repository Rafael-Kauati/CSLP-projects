#include "Golomb_Decoder.hpp"
#include "../HybridCodec/BitStream.h"
#include <opencv4/opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

Golomb_Decoder::Golomb_Decoder(string inputFile, string outputFile) : stream(BitStream::makeFromFiles(inputFile, outputFile)) {}

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

    int b = static_cast<int>(floor(log2(this->m))); // Calculate b as floor(log2(m))

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

int Golomb_Decoder::readInt(int numBytes) {
    string binValue;

    for(int i = 0; i < (numBytes * 8); i++) {
        binValue.append(to_string(stream.readOneFileBit()));
    }

    return binaryToDecimal(binValue);
}

void Golomb_Decoder::setMParam(int mParam) {
    this->m = mParam;
}

cv::Mat Golomb_Decoder::decodeBlock(int block_size) {
    Mat block = Mat::zeros(block_size, block_size, CV_8UC1);
    int count = 0;
    for (int i = 0; i < block.rows; i++) {
        for (int j = 0; j < block.cols; j++) {
            block.at<uchar>(i, j) = decode();
            count++;
        }
    }
    return block;
}


