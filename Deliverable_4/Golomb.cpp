#include "Golomb_Encoder.hpp"
#include "Golomb_Decoder.hpp"
#include "BitStream.h"
#include <string>

class Golomb
{
public:
    Golomb(int param, string inputFile, string outputFile) : encoder(inputFile, outputFile), decoder(inputFile, outputFile), writer(inputFile, outputFile), reader(outputFile, "") {}

    /**
     * @brief Encodes an integer using the Golomb encoding algorithm.
     *
     * This method takes an integer as input and encodes it using the Golomb encoding algorithm.
     *
     * @param num The integer to be encoded.
     * @return A vector of boolean values representing the encoded bits.
     */
    void encode(int value)
    {
        encoder.encode(value);
    }

    /**
     * @brief Decodes a sequence of encoded bits using Golomb decoding algorithm.
     *
     * This method takes a vector of boolean values representing the encoded bits and decodes them using Golomb decoding algorithm.
     *
     * @param encodedBits The vector of boolean values representing the encoded bits.
     * @return The decoded integer value.
     */
    int decode()
    {
        int decodedNumber;

        decodedNumber = decoder.decode();

        return decodedNumber;
    }

    /**
     * @brief Closes the reader and writer, releasing associated resources.
     *
     * This method is responsible for closing the underlying reader and writer,
     * releasing any resources they may hold, such as file handles or network
     * connections. It is essential to call this method to ensure proper cleanup
     * and resource management.
     */

    void close()
    {
        reader.close();
        writer.close();
    }

private:
    Golomb_Encoder encoder;
    Golomb_Decoder decoder;
    BitStream writer, reader;
};