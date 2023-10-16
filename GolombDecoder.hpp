#ifndef GOLOMBDECODER_HPP
#define GOLOMBDECODER_HPP

#include "Golomb_Param.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
class GolombDecoder {
private:
    int binaryToDecimal(std::string n);

public:
    GolombDecoder(int param);

    int decode(const std::vector<bool>& encodedBits);

    int m;
};

#endif // GOLOMBDECODER_HPP
