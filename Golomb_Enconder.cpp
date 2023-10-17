#include "GolombEncoder.hpp"

using namespace std;

GolombEncoder::GolombEncoder (int param) : m (param) {
    if(m <= 0 ){
        cerr<<"Error: The golomb parameter m should be positive" ;
    }
}

vector<bool> GolombEncoder::encode(int num) {
    int quotient = num / m;
    int remainder = num % m;

    vector<bool> encodedQuotient = unaryCode(quotient);
    vector<bool> encodedRemainder;

    int k = static_cast<int>(ceil(log2(m)));

    for (int i = k - 1; i >= 0; --i) {
        encodedRemainder.push_back((remainder >> i) & 1);
    }

    vector<bool> encodedNumber = encodedQuotient;

    encodedNumber.insert(encodedNumber.end(), encodedRemainder.begin(), encodedRemainder.end());

    return encodedNumber;
}

// Codificação unária de um número não negativo
vector<bool> GolombEncoder::unaryCode(int num) {
    vector<bool> code;

    for (int i = 0; i < num; ++i) {
        code.push_back(1);
    }
    
    code.push_back(0); // Adicionar um 0 no final
    
    return code;
}

