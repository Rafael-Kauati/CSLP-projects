#include "Video_Encoder.hpp"
#include "Video_Decoder.hpp"
#include "BitStream.h"
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
    vector<int> encode(int value) {
        vector<int> encodedBits;

        encodedBits = encoder.encode(value);
        cout << " Writing " << encodedBits.size() << " bits" << std::endl;

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
    int decode()
    {
         int decodedNumber;

        //readFileChar
        vector<int> encNumbers = reader.readNFileBit(8);

        decodedNumber = decoder.decode(encNumbers);
        std::cout << "\n\nDecoded : " << decodedNumber;

        cout<<std::endl;
        cout<<std::endl;

        return decodedNumber;
    }

    void close()
    {
        reader.close();
        writer.close();
    }


private:

    Video_Encoder encoder;
    Video_Decoder decoder;
    BitStream     writer, reader;

};


