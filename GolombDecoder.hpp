#ifndef GOLOMBDECODER_HPP
#define GOLOMBDECODER_HPP

#include "Golomb_Param.h"
#include <vector>
#include <string>
#include <iostream>

class GolombDecoder {
private:
    int binaryToDecimal(std::string n);

public:
    GolombDecoder(int param) : m(param) {}

    int decode(const std::vector<bool>& encodedBits);

    int m;
};

#endif // GOLOMBDECODER_HPP
