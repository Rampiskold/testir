#include <iomanip>
#include <iostream>
#include <limits>
#include <fstream>
#include "rank.h"


int main(int, char *[])
{
    float sumPrev = 0;
    int i = 1;
    float curErr = 0;


    std::ofstream ofs("serialisation.txt");
    

    float sumCur  = sumrank(i++, 0.f);
    if (!ofs.bad()) {
        ofs << i-1 << " " << sumCur << std::endl;
    }
    do {
        sumPrev = sumCur;
        sumCur = sumrank(i++, 0.f);
        curErr = abs(sumPrev - sumCur);
        if (!ofs.bad()) {
            ofs << i-1 << " " << sumCur << std::endl;
        }
    } while(curErr > 0.0001);
    
    if (!ofs.bad()) {
        ofs.close();
    }

    std::cout << "--(0.90154)-- sumCur " << sumCur << std::endl;
}

