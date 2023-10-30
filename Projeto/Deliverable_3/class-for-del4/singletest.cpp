//
// Created by tk on 30-10-2023.
//
#include "Golomb.cpp"
#include <iostream>
using namespace std;
int main(){
    Golomb golomb(1, "output.bin", "output.bin");

    std::cout << "Encoded : ";
    for(int b  : golomb.encode(6)){
        std::cout << b ;
    }

    golomb.decode(0);


    return 0;
}