#include "GolombEncoder.hpp"

GolombEncoder::GolombEncoder( int param) :  m(param) {}

std::vector<bool> GolombEncoder::encode(int num) {
    int quotient = num / m;
    int remainder = num % m;

    std::cout << "quotient : " << quotient << std::endl;
    std::cout << "remainder : " << remainder << std::endl;

    std::vector<bool> encodedQuotient = unaryCode(quotient);
    std::vector<bool> encodedRemainder = golombRemainder(remainder);

    std::vector<bool> encodedNumber = encodedQuotient;
    encodedNumber.insert(encodedNumber.end(), encodedRemainder.begin(), encodedRemainder.end());

    return encodedNumber;
}
std::vector<bool> GolombEncoder::golombRemainder(int num) {
        int q = num / m;
        int r = num % m;

        std::vector<bool> binaryCodeRemainder;
        if (num == 0) {
            binaryCodeRemainder.push_back(0);
        }

        while (num > 0) {
            int resto = num % 2;
            binaryCodeRemainder.insert(binaryCodeRemainder.begin(), resto);
            num = num / 2;
        }

        return binaryCodeRemainder;
    }

    // Codificação unária de um número não negativo
    std::vector<bool> GolombEncoder::unaryCode(int num) {
        std::vector<bool> code;
        for (int i = 0; i < num; ++i) {
            code.push_back(1);
        }
        code.push_back(0); // Adicionar um 0 no final
        return code;
    }


/*
int main() {
    int m = 4;
    GolombEncoder encoder(m);

    int num = 7;
    std::vector<bool> encodedNumber = encoder.encode(num);

    std::cout << "Número original: " << num << std::endl;
    std::cout << "Bits codificados: ";
    for (bool bit : encodedNumber) {
        std::cout << bit;
    }
    std::cout << std::endl;

    return 0;
}
*/