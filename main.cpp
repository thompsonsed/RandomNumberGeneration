#include <iostream>
#include <numeric>
#include <iomanip>
#include "Xoshiro256plus.h"
#include "LCG.h"
#include "MersenneTwisterCpp.h"
#include "Xoroshiro128plus.h"
#include "MersenneTwister.h"
#include "PCG.h"

// Runs the performance test for each RNG
int main()
{
    clock_t start1, end1, start2, end2, start3, end3, start4, end4;
    clock_t start5, end5, start6, end6, start7, end7, start8, end8;
    clock_t start9, end9;
    const unsigned int total = 1000000000;
    unsigned long long tot1 = 0;
    unsigned long long tot2 = 0;
    unsigned long long tot3 = 0;
    unsigned long long tot4 = 0;
    unsigned long long tot5 = 0;
    unsigned long long tot6 = 0;
    unsigned long long tot7 = 0;
    unsigned long long tot8 = 0;
    unsigned long long tot9 = 0;
    Xoshiro256plus rand1(1);
    SplitMix64 rand2(1);
    LCG rand3(1);
    MersenneTwisterCpp rand4(1);
    Xoroshiro128plus rand5(1);
    MersenneTwister rand6(1);
    std::minstd_rand msr;
    msr.seed(1);
    PCG rand7(101);
    start1 = clock();
    for(unsigned long i = 0; i < total; i++)
    {
        tot1 += rand1.next();
    }
    end1 = clock();
    start2 = clock();
    for(unsigned long i = 0; i < total; i++)
    {
        tot2 += rand2.next();
    }
    end2 = clock();
    start3 = clock();
    for(unsigned long i = 0; i < total; i++)
    {
        tot3 += rand3.next();
    }
    end3 = clock();
    start4 = clock();
    for(unsigned long i = 0; i < total; i++)
    {
        tot4 += rand4.next();
    }
    end4 = clock();
    start5 = clock();
    for(unsigned long i = 0; i < total; i++)
    {
        tot5 += rand5.next();
    }
    end5 = clock();
    start6 = clock();
    for(unsigned long i = 0; i < total; i++)
    {
        tot6 += rand6.next();
    }
    end6 = clock();
    start7 = clock();
    for(unsigned long i = 0; i < total; i++)
    {
        tot7 += rand();
    }
    end7 = clock();
    start8 = clock();
    for(unsigned long i = 0; i < total; i++)
    {
        tot8 += msr();
    }
    end8 = clock();
    start9 = clock();
    for(unsigned long i = 0; i < total; i++)
    {
        tot9 += rand7.next();
    }
    end9 = clock();

    std::cout << std::setprecision(4);
    std::cout << "RNG\t\t\t\tTime\t\tTotal" << std::endl;
    std::cout << "Xoshiro256+\t" << double(end1 - start1) / CLOCKS_PER_SEC << "\t\t" << tot1 << std::endl;
    std::cout << "Xoroshiro128+\t" << double(end5 - start5) / CLOCKS_PER_SEC << "\t\t" << tot5 << std::endl;
    std::cout << "SplitMix64\t\t" << double(end2 - start2) / CLOCKS_PER_SEC << "\t\t" << tot2 << std::endl;
    std::cout << "LCG\t\t\t\t" << double(end3 - start3) / CLOCKS_PER_SEC << "\t\t" << tot3 << std::endl;
    std::cout << "PCG\t\t\t\t" << double(end9 - start9) / CLOCKS_PER_SEC << "\t\t" << tot9 << std::endl;
    std::cout << "MT\t\t\t\t" << double(end6 - start6) / CLOCKS_PER_SEC << "\t\t" << tot6 << std::endl;
    std::cout << "Base rand\t\t" << double(end7 - start7) / CLOCKS_PER_SEC << "\t\t" << tot7 << std::endl;
    std::cout << "Base MT1\t\t" << double(end4 - start4) / CLOCKS_PER_SEC << "\t\t" << tot4 << std::endl;
    std::cout << "Base minstd\t\t" << double(end8 - start8) / CLOCKS_PER_SEC << "\t\t" << tot8 << std::endl;


    return 0;
}