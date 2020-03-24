#include <iostream>

float  sumrank(size_t n, float rev);

int run_test() 
{
    float rank_2 = sumrank(2, 0.f);
    std::cout << "1 - 1/(2^3): " << rank_2 << std::endl;
    if (rank_2 == 0.875f) {
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