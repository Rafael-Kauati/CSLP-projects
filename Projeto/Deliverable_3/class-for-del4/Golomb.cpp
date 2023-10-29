#include "GolombEncoder.hpp"
#include "GolombDecoder.hpp"

class Golomb {
public:
    Golomb(int param) : encoder(param), decoder(param) {}

    /**
     * @brief Encodes an integer using the Golomb encoding algorithm.
     *
     * This method takes an integer as input and encodes it using the Golomb encoding algorithm.
     *
     * @param num The integer to be encoded.
     * @return A vector of boolean values representing the encoded bits.
     */
    vector<bool> encode(int num) {
        return encoder.encode(num);
    }

    /**
     * @brief Decodes a sequence of encoded bits using Golomb decoding algorithm.
     *
     * This method takes a vector of boolean values representing the encoded bits and decodes them using Golomb decoding algorithm.
     *
     * @param encodedBits The vector of boolean values representing the encoded bits.
     * @return The decoded integer value.
     */
    int decode(const vector<bool>& encodedBits) {
        return decoder.decode(encodedBits);
    }

private:
    GolombEncoder encoder;
    GolombDecoder decoder;
};
