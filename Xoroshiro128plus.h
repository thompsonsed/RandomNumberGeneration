/**
 * @brief Modified from code by David Blackman and Sebastiano Vigna (vigna@acm.org) by Sam Thompson
 */

#ifndef RNG_TESTING_XOROSHIRO128PLUS_H
#define RNG_TESTING_XOROSHIRO128PLUS_H

#include <cstdint>
#include <array>
#include "SplitMix64.h"
#include "random_convert.h"

class Xoroshiro128plus
{
protected:
    uint64_t shuffle_table[4];
public:

    Xoroshiro128plus() : shuffle_table()
    {

    }

    /**
     * @brief Explicit constructor which sets the rng seed.
     * @param seed the random seed
     */
    explicit Xoroshiro128plus(uint64_t seed) : shuffle_table()
    {
        setSeed(seed);
    }

    virtual void setSeed(uint64_t seed)
    {
        SplitMix64 seed_generator(seed);
        // Shuffle the seed generator 8 times
        seed_generator.shuffle();
        for(auto &item : shuffle_table)
        {
            item = seed_generator.next();
        }
    }

    /**
     * @brief Generates the next random integer.
     * @return a random integer from 0 to max of 2^64
     */
    uint64_t next(void)
    {
        uint64_t s1 = shuffle_table[0];
        uint64_t s0 = shuffle_table[1];
        uint64_t result = s0 + s1;
        shuffle_table[0] = s0;
        s1 ^= s1 << 23;
        shuffle_table[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5);
        return result;
    }

    /**
     * @brief Generates a random number in the range [0, 1)
     * @return a random double
     */
    double d01()
    {
        return intToDouble(next());
    }

    /**
     * @brief Jumps the generator forwards by the equivalent of 2^128 calls of next() - useful for parallel
     * computations where different random number sequences are required.
     */
    void jump()
    {
        static const uint64_t JUMP[] = { 0xdf900294d8f554a5, 0x170865df4b3201fc };

        uint64_t s0 = 0;
        uint64_t s1 = 0;
        for(int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
            for(int b = 0; b < 64; b++) {
                if (JUMP[i] & UINT64_C(1) << b) {
                    s0 ^= shuffle_table[0];
                    s1 ^= shuffle_table[1];
                }
                next();
            }

        shuffle_table[0] = s0;
        shuffle_table[1] = s1;
    }
};
#endif //RNG_TESTING_XOROSHIRO128PLUS_H
