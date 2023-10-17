#ifndef GOLOMBDECODER_HPP
#define GOLOMBDECODER_HPP

#include "Golomb_Param.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class GolombDecoder {
    private:
        int binaryToDecimal(string n);

    public:
        GolombDecoder(int param);

        int decode(const vector<bool>& encodedBits);

        int m;
};

#endif // GOLOMBDECODER_HPP
