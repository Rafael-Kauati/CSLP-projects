#ifndef GOLOMBENCODER_HPP
#define GOLOMBENCODER_HPP

#include "Golomb_Param.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class GolombEncoder{
    public:
        GolombEncoder( int param);

        vector<bool> encode(int num);

        int m;

    private:
        vector<bool> unaryCode(int num);
};

#endif // GOLOMBENCODER_HPP
