#include <iostream>
#include <iomanip>
#include <limits>
#include "rank.h"


int run_test() 
{
    float cmperr;
    size_t it;
    float rank = sumrank(0.0001f, &it, &cmperr, true);
    std::cout << std::setprecision(std::numeric_limits<float>::digits10 + 3)
        << "sum (0.90154): " << rank 
        << " it: " << it << " err: " << cmperr << std::endl;
    if (abs(rank - 0.90154f) < 0.0001f) {
        return 0; // Passed
    }
    else {
        return 1; // Failed
    }
}

int main (int , char *[])
{
    return run_test();
}