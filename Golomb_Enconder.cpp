#include "GolombEncoder.hpp"

GolombEncoder::GolombEncoder( int param) :  m(param) {
    if(m <= 0 ){
        std::cerr<<"Error :  the golomb parameter m should be positive" ;
    }
}

std::vector<bool> GolombEncoder::encode(int num) {
    int quotient = num / m;
    int remainder = num % m;

    std::vector<bool> encodedQuotient = unaryCode(quotient);

    int k = static_cast<int>(ceil(log2(m))); // Calculate the number of bits required to represent m
    std::vector<bool> encodedRemainder;
    for (int i = k - 1; i >= 0; --i) {
        encodedRemainder.push_back((remainder >> i) & 1);
    }

    std::vector<bool> encodedNumber = encodedQuotient;
    encodedNumber.insert(encodedNumber.end(), encodedRemainder.begin(), encodedRemainder.end());

    return encodedNumber;
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
    int m = 5;
    GolombEncoder encoder(m);

    int num = 12;
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