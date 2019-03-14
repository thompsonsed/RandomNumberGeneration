//
// Created by Sam Thompson on 14/03/2019.
//
// Implementation adapted from http://www.pcg-random.org/download.html
// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)
#ifndef RNG_TESTING_PCG_H
#define RNG_TESTING_PCG_H

#include <cstdint>
#include "SplitMix64.h"
#include "random_convert.h"
class PCG
{
protected:
    uint64_t state;
    uint64_t seq_constant;
    unsigned long seed;
public:

    PCG(unsigned long seed)
    {
        this->seed = seed;
        SplitMix64 tmp(seed);
        state = tmp.next();
        seq_constant = 1442695040888963407ULL;
    }

    void setState(uint64_t seed, uint64_t seq_constant)
    {
        this->seed = state;
        this->state = state;
        this->seq_constant = seq_constant;
    }

    uint64_t next()
    {
        uint64_t old_state = state;
        // Advance internal state
        state = old_state * 6364136223846793005ULL + (seq_constant|1);
        // Calculate output function (XSH RR), uses old state for max ILP
        uint32_t xorshifted = ((old_state >> 18u) ^ old_state) >> 27u;
        uint32_t rot = old_state >> 59u;
        return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
    }
};

#endif //RNG_TESTING_PCG_H
