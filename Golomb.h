//
// Created by tk on 10-10-2023.
//

#ifndef CSLP_PROJECTS_GOLOMB_H
#define CSLP_PROJECTS_GOLOMB_H

#include "stdlib.h"
#include "stdio.h"
#include "iostream"

class Golomb {
protected:
    int m;

public:

    Golomb(int param): m(param){ std::cout << "Golomb paramamenter  : "<< m << "\n";};
};


#endif //CSLP_PROJECTS_GOLOMB_H
