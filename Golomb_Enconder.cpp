#include <iostream>
#include <vector>
#include <cmath>
#include "Golomb.h"

class GolombEnconder  : public Golomb {
public:
    GolombEnconder(int param) : Golomb(param) {}

    // Codificar um número inteiro usando codificação de Golomb
    std::vector<bool> encode(int num) {
        int quotient = num / m;
        int remainder = num % m;

        std::cout << "quotient : " << quotient << std::endl;
        std::cout << "remainder : " << remainder << std::endl;

        std::vector<bool> encodedQuotient = unaryCode(quotient);
        std::vector<bool> encodedRemainder = golombCode(remainder);

        // Concatenar os bits codificados do quociente e do resto
        std::vector<bool> encodedNumber = encodedQuotient;
        encodedNumber.insert(encodedNumber.end(), encodedRemainder.begin(), encodedRemainder.end());

        return encodedNumber;
    }

private:
    std::vector<bool> golombCode(int num) {
        int q = num / m;
        int r = num % m;

        if(r%2!=0){
            r = ( num  +1 ) % m;
        }

        // Calcular o número de bits necessários para representar m
        int b = static_cast<int>(log2(m));
        int threshold = (1 << b) - m;

        std::vector<bool> binaryCodeRemainder;

        // Se r < 2^b - m, então codifique r usando b bits
        if (r < threshold) {
            for (int i = b - 1; i >= 0; --i) {
                binaryCodeRemainder.push_back((r >> i) & 1);
            }

            // Se r >= 2^b - m, codifique o número r + 2^b - m usando b + 1 bits
        } else {
            r += (1 << b) - m;
            for (int i = b; i >= 0; --i) {
                binaryCodeRemainder.push_back((r >> i) & 1);
            }
        }

        return binaryCodeRemainder;
    }

    // Codificação unária de um número não negativo
    std::vector<bool> unaryCode(int num) {
        std::vector<bool> code;
        for (int i = 0; i < num; ++i) {
            code.push_back(1);
        }
        code.push_back(0); // Adicionar um 0 no final
        return code;
    }

};

int main() {
    int m = 4;
    GolombEnconder encoder( m);

    int num = 6;
    std::vector<bool> encodedNumber = encoder.encode(num);

    std::cout << "Número original: " << num << std::endl;
    std::cout << "Bits codificados: ";
    for (bool bit : encodedNumber) {
        std::cout << bit;
    }
    std::cout << std::endl;

    return 0;
}