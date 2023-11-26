#include <bitset>
#include "Golomb_Encoder.hpp"
#include <opencv4/opencv2/opencv.hpp>

using namespace std;

Golomb_Encoder::Golomb_Encoder(string inputFile, string outputFile) : stream(BitStream::makeFromFiles(inputFile, outputFile)) {}

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
    int quotient = numberToEncode / this->m;
    int remainder = numberToEncode % this->m;

    //  Write the unary code for the quotient 
    unaryCode(quotient);

    int k = static_cast<int>(floor(log2(this->m))); // Calculate b as floor(log2(m))
    for (int i = k - 1; i >= 0; i--)
    {
        stream.writeOneFileBit((remainder >> i) & 1);
    }


    return;
}


/**decodeBlock
 * @brief Generates the unary code representation of a non-negative integer.
 *
 * This method takes a non-negative integer as input and generates its unary code representation.
 *
 * @param num The non-negative integer to be encoded.
 */
void Golomb_Encoder::unaryCode(int num) {
    for (int i = 0; i < num; i++) {
        stream.writeOneFileBit(1);
    }

    stream.writeOneFileBit(0);  // Adicionar um 0 no final
    return;
}


//  Write an integer in the file with the maximum specified number of bytes
void Golomb_Encoder::writeInt(int num, int numBytes) {

    for (int i = (numBytes * 8) - 1; i >= 0; i--) {
        stream.writeOneFileBit((num >> i) & 1);
    }

    return;
}

void Golomb_Encoder::setMParam(int mParam) {
    this->m = mParam;
}

void Golomb_Encoder::closeStreams() {
    stream.close();
}

/**
 * @brief Encodes a block of pixel values using the Golomb encoding algorithm.
 *
 * This method encodes a square block of pixel values with a specified size using the Golomb encoding algorithm.
 * Each pixel value in the block is individually encoded using the Golomb encoding technique, and the resulting
 * encoded bits are written to the output bitstream.
 *
 * @param block The square block of pixel values to be encoded.
 */
void Golomb_Encoder::encodeBlock(cv::Mat block) {
    for (int i = 0; i < block.rows; i++) {
        for (int j = 0; j < block.cols; j++) {
            encode(block.at<uchar>(i, j));
        }
    }
    return;
}