//
// Created by tk on 30-10-2023.
//
#include "Golomb.cpp"
#include <iostream>
using namespace std;
int main(){
    Golomb golomb(4, "output.bin", "output.bin");
    //12: 111000
    std::cout << "Encoded : ";
    vector<int> enc= golomb.encode(12);
    for(int b  : enc){
        std::cout << b ;
    }

    golomb.decode();


    return 0;
}