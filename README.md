# CSLP - Projects
### Our deliverable 3 project for the CSLP class of 23/24
---

## Codes do document : 

* Golomb_Decoder.cpp 
* GolombDecoder.hpp 
* Golomb_Enconder.cpp 
* GolombEncoder.hpp
* Tests.cpp

How to run : cmake . && make && ./GolombCodingTests

### Huffman enconding basic solution : 
In golomb enconding (variation from huffman enconding)

Cases that worked well : 

n = 6 with m = 1
quotient : 6
remainder : 0
Número original: 6
Bits codificados: 11111100 

n = 6 with m  = 4
quotient : 1
remainder : 2
Número original: 6
Bits codificados: 10010

n = 13 with m  = 5


quotient : 2
remainder : 3
Número original: 13
Bits codificados: 110011



represent :

n = 12 with m  = 5;

n -> q = 2(001) and r =2(10)

n --> 00110



represent :
n = 13 with m = 5

n -> q= 2 (001) r = 3(011)

n --> 001110
110011