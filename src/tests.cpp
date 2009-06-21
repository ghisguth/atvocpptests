/* tests.cpp
 * This file is a part of atvocpptests library
 * Copyright (c) atvocpptests authors (see file `COPYRIGHT` for the license)
 */
//#include "common.h"

#include <iostream>
#include <tr1/memory>

int main()
{
    //std::tr1::shared_ptr<volatile int> i(new int(1));
    volatile int * i = new int(1);

    long long int h = 0;

    for(long long int j=0;j < 10000000000LL; j++)
    {
        h += *i;
    }

    std::cout << h << std::endl;
    return 0;
}

