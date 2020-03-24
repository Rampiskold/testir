#include <iostream>

float  sumrank(size_t n, float rev);

int run_revtest() 
{
    float rank_2 = sumrank(2, 1.f);
    std::cout << "-1/(2^3) + 1: " << rank_2 << std::endl;
    if (rank_2 == 0.875f) {
        return 0; // Passed
    }
    else {
        return 1; // Failed
    }
}
template<class T>
T sumrankAlg(T error, size_t& iterations, T& reserr, bool rev);

int main (int , char *[])
{
    size_t i;
    float err;
    float sum = sumrankAlg(0.0001f, i, err, false);
    

    return run_revtest();
}