#include "GolombDecoder.hpp"
using namespace std;
GolombDecoder::GolombDecoder(int param)  : m(param){
    if(m <= 0 ){
        std::cerr<<"Error :  the golomb parameter m should be positive" ;
    }
}


    int GolombDecoder::binaryToDecimal(std::string n)
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


    int GolombDecoder::decode(const std::vector<bool>& encodedBits) {
        std::vector<bool> decodedValues;
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
            binValue.append(to_string(encodedBits[i]));
        }
        remainder  = binaryToDecimal(binValue);


        int decodedValue = quotient * m + remainder;
        decodedValues.push_back(decodedValue);



        return decodedValue;
    }


/*
int main() {
    int m = 4; // Parâmetro Golomb
    std::vector<bool> encodedBits = {1,0,1,1}; // Valores codificados Golomb

    GolombDecoder decoder(m);
    int decodedValues = decoder.decode(encodedBits);

    std::cout << "Decoded value: " << decodedValues << std::endl;

    return 0;
}
*/