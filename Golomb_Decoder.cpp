#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Golomb.h"

using namespace std;

class GolombDecoder : public Golomb {

private:
    int binaryToDecimal(std::string n)
    {
        std::string num = n;
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
public:
    GolombDecoder(int param) : Golomb(param) {}

    std::vector<int> decode(const std::vector<int>& encodedBits) {
        std::vector<int> decodedValues;
        int n = 0;
        int quotient = 0;
        int remainder = 1;
        string binValue;

        while (n < encodedBits.size() && encodedBits[n] == 1) {
            quotient++;
            n++;
        }
        n++; // Skip the delimiter '0'


        for(int i = n; i < encodedBits.size() ; i ++){
            std::cout << "num : " << encodedBits[i] << std::endl;
            binValue.append(to_string(encodedBits[i]));
        }
        remainder  = binaryToDecimal(binValue);


        int decodedValue = quotient * m + remainder;
        decodedValues.push_back(decodedValue);

        std::cout << "Q value: " << quotient << std::endl;
        std::cout << "R value: " << remainder << std::endl;

        return decodedValues;
    }
};

int main() {
    int m = 5; // Parâmetro Golomb
    std::vector<int> encodedBits = {1,1,0,0,1,1}; // Valores codificados Golomb

    GolombDecoder decoder(m);
    std::vector<int> decodedValues = decoder.decode(encodedBits);

    std::cout << "Decoded value: " << decodedValues[0] << std::endl;

    return 0;
}
