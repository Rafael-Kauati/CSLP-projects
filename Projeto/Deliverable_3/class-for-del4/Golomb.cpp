#include "GolombEncoder.hpp"
#include "GolombDecoder.hpp"
#include "BitStreamWithPosition.h"
#include <string>



class Golomb {
public:
    Golomb(int param, string inputFile, string outputFile) : encoder(param), decoder(param), writer(inputFile, outputFile), reader(outputFile, "") {}

    /**
     * @brief Encodes an integer using the Golomb encoding algorithm.
     *
     * This method takes an integer as input and encodes it using the Golomb encoding algorithm.
     *
     * @param num The integer to be encoded.
     * @return A vector of boolean values representing the encoded bits.
     */
    vector<int> encode(int value ) {
        vector<int> encodedBits;

        encodedBits = encoder.encode(value);
        cout << " Writing " << std::endl;

        for(int v  : encodedBits){
            cout <<  v;
        }
        cout<<std::endl;
        cout<<std::endl;

        writer.writeNFileBit(  encodedBits);
        writer.close();
        return encodedBits;
    }

    /**
     * @brief Decodes a sequence of encoded bits using Golomb decoding algorithm.
     *
     * This method takes a vector of boolean values representing the encoded bits and decodes them using Golomb decoding algorithm.
     *
     * @param encodedBits The vector of boolean values representing the encoded bits.
     * @return The decoded integer value.
     */
    int decode(int pos) {
         int decodedNumber;

        vector<int> encNumbers = reader.readNFileBit(pos,8);
        //int num = static_cast<int>(byte);
        cout << "encNumbers  : " ;

        for(int v  : encNumbers){
            cout <<  v;
        }
        decodedNumber = decoder.decode(encNumbers);
        std::cout << "\n\nDecoded : " << decodedNumber;

        cout<<std::endl;
        cout<<std::endl;

        reader.close();
        return decodedNumber;
    }


private:

    GolombEncoder encoder;
    GolombDecoder decoder;
    BitStream     writer, reader;

};


