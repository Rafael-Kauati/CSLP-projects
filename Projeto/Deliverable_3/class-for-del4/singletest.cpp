//
// Created by tk on 30-10-2023.
//
#include "Golomb.cpp"
#include <iostream>
using namespace std;
int main(){
    Golomb golomb(4, "output.bin", "output.bin");

    std::cout << "Encoded : ";
    vector<int> enc= golomb.encode(7);
    for(int b  : enc){
        std::cout << b ;
    }

    golomb.decode();


    return 0;
}