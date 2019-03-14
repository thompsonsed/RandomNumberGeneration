//
// Created by Sam Thompson on 14/03/2019.
//

#ifndef RNG_TESTING_MERSENNETWISTER_CPP_H
#define RNG_TESTING_MERSENNETWISTER_CPP_H
#include <random>
#include "random_convert.h"

class MersenneTwisterCpp
{
private:
    std::mt19937 mt_rand;
public:
    explicit MersenneTwisterCpp(unsigned long seed) : mt_rand(seed)
    {

    }

    /**
     * @brief Generates the next random integer.
     * @return a random integer from 0 to max of 2^64
     */
    uint64_t next()
    {
        return mt_rand();
    }

    /**
     * @brief Get a random double between 0 and 1
     * @return a randomly generated double on [0, 1].
     */
    double d01()
    {
        return intToDouble(next());
    }
};

#endif //RNG_TESTING_MERSENNETWISTER_CPP_H
