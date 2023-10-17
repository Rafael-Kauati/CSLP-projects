//
// Created by tk on 10-10-2023.
//

#ifndef CSLP_PROJECTS_GOLOMB_H
#define CSLP_PROJECTS_GOLOMB_H

#include "stdlib.h"
#include "stdio.h"
#include "iostream"

class GolombParam {
protected:
    int m;

public:

    GolombParam(int param): m(param){ std::cout << "Golomb paramamenter  : "<< m << "\n";};

    void set(int param) {m=param;};
    int  get() {return m;};
};


#endif //CSLP_PROJECTS_GOLOMB_H
