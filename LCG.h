//
// Created by Sam Thompson on 14/03/2019.
//

#ifndef RNG_TESTING_LNG_H
#define RNG_TESTING_LNG_H

#include <cmath>
#include <cstdint>
#include "random_convert.h"

// Values taken from Numerical Recipes
const uint64_t modulus = static_cast<unsigned long>(pow(2, 62)-1);
const uint64_t multiplier = 1664525;
const uint64_t increment = 1013904223;

class LCG
{
private:
    unsigned long x;
public:
    explicit LCG(unsigned long seed) : x(seed)
    {

    }

    /**
     * @brief Generates the next random integer.
     * @return a random integer from 0 to max of 2^64
     */
    uint64_t next()
    {
        x = (multiplier * x + increment) % modulus;
        return x;
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

#endif //RNG_TESTING_LNG_H
