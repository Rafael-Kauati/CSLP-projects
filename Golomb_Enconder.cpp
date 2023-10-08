//
// Created by tk on 08-10-2023.
//

#include "Golomb_Enconder.h"
#include "stdio.h"
#include "iostream"
#include "string"
#include "vector"
#include "cmath"

using namespace std;

class Golomb_Enconder
{
    private:
        int m, quotient, remainder;
        std::vector<bool> encodedBits;

    public:

        Golomb_Enconder(int param) : m (param) {std::cout << "Golomb parameter : " << m};

        void encode(int value)
        {
            quotient = value / m;
            remainder = value % m;
        }
};