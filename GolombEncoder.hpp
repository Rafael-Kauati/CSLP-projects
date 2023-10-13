#ifndef GOLOMBENCODER_HPP
#define GOLOMBENCODER_HPP

#include "Golomb_Param.h"
#include <vector>
#include <iostream>
#include <cmath>

class GolombEncoder{
public:
    GolombEncoder( int param);

    std::vector<bool> encode(int num);

    int m;

private:
    std::vector<bool> golombRemainder(int num);
    std::vector<bool> unaryCode(int num);
};

#endif // GOLOMBENCODER_HPP
