//
// Created by tk on 08-10-2023.
//

#include "Golomb_Enconder.h"


using namespace std;

class Golomb_Enconder
{
    private:
        int m, quotient, remainder;
    std::vector<int> encodedBits; //
    public:

        Golomb_Enconder(int param) : m(param) { std::cout << "Golomb parameter: " << m << std::endl; }

        void encode(int value)
        {
            std::cout << "Int : "<<value<< std::endl;
            quotient = value / m;
            remainder = value % m;

            std::cout << "Quotient: " << quotient << ", Remainder: " << remainder << std::endl;

            for (int i = 0; i < quotient; ++i) {
                encodedBits.push_back(1);
            }
            encodedBits.push_back(0);

            //Use the remainder as ⌈log2​(m)⌉ bits
            int numBits = static_cast<int>(std::log2(m));
            for (int i = numBits - 1; i >= 0; --i) {
                encodedBits.push_back((remainder >> i) & 1);
            }

            // Show the  bits encoded after each number of the non-negative sequence
            std::cout << "Encoded bits: ";
            for (int bit : encodedBits) {
                std::cout << bit;
            }
            std::cout << std::endl;
            std::cout << std::endl;

            
        }

    void printEncodedBits() {

        int nBit = 1;
        for (bool bit : encodedBits) {
            std::cout << "\n| "<< nBit << " : "<< bit;
            nBit ++;
        }
        std::cout << std::endl;
    }
};

int main() {
    int golombParameter = 11;
    Golomb_Enconder encoder(golombParameter);

   // std::vector<int> values = {2, 5, 7, 3, 1, 8};
   // for (int value : values) {
        //encoder.encode(value);
    //}

    encoder.encode(37);

    std::cout << "Encoded bits using Golomb coding: \n";
    //encoder.printEncodedBits();

    return 0;
}