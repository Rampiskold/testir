#include <iostream>

float getItemf(size_t i);

int run_itemtest() 
{
    float item_2 = getItemf(2);
    std::cout << "1/2: " << item_2 << std::endl;
    if (item_2 == -0.125f) {
        return 0; // Passed
    }
    else {
        return 1; // Failed
    }
}

int main (int , char *[])
{
    return run_itemtest();
}