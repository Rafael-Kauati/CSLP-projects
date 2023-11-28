#include <bitset>
#include "Golomb_Encoder.hpp"
#include <opencv4/opencv2/opencv.hpp>

using namespace std;

/**
 * @brief Golomb Encoder Constructor.
 *
 * This constructor initializes a Golomb Encoder object. It takes input and output file
 * paths to create a BitStream for encoding. The encoder will use this BitStream for
 * writing encoded data.
 *
 * @param inputFile The path to the input file.
 * @param outputFile The path to the output file.
 */
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


/**
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

/**
 * @brief Writes an integer to the Golomb encoder stream.
 *
 * This method writes the binary representation of the specified integer to
 * the BitStream. The number of bits to write can
 * be controlled by the 'numBytes' parameter. The most significant bits
 * are written first.
 *
 * @param num The integer value to be written.
 * @param numBytes The number of bytes (and bits) to write from the integer.
 * @see Golomb_Encoder, Golomb_Decoder, BitStream
 */
void Golomb_Encoder::writeInt(int num, int numBytes) {

    for (int i = (numBytes * 8) - 1; i >= 0; i--) {
        stream.writeOneFileBit((num >> i) & 1);
    }

    return;
}

/**
 * @brief Sets the value of the parameter 'm' for Golomb encoding.
 *
 * This method sets the value of the parameter 'm' used in Golomb encoding.
 * The parameter 'm' is a positive integer that influences the efficiency
 * of Golomb encoding. Adjusting this parameter can affect the compression
 * ratio and performance of the Golomb encoding algorithm.
 *
 * @param mParam The new value to set for the 'm' parameter.
 */
void Golomb_Encoder::setMParam(int mParam) {
    this->m = mParam;
}

/**
 * @brief Closes the stream used by the Golomb encoder.
 *
 * This method closes the BitStream. It is
 * essential to call this method to ensure proper cleanup and resource
 * management after encoding is complete.
 *
 * @see Golomb_Encoder, Golomb_Decoder, BitStream
 */
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
 * @param block The size of the piel block.
 */
void Golomb_Encoder::encodeBlock(vector<vector<int>> block, int block_size) {
    for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < block_size; j++) {
            encode(block[i][j]);
        }
    }
    return;
}