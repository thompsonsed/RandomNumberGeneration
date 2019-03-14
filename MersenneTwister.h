/*
 * Adapted from http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
 * by Sam Thompson.
 */
/*
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.
   Before using, initialize the state by using init_genrand(seed)
   or init_by_array(init_key, key_length).
   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#ifndef RNG_TESTING_MERSENNETWISTER_H
#define RNG_TESTING_MERSENNETWISTER_H

#include <cstdint>
#include <array>

class MersenneTwister
{
private:
    static const int N = 312;
    static const int M = 156;
    // constant vector a
    static const uint64_t MATRIX_A = 0xB5026F5AA96619E9ULL;
    // most significant w-r bits
    static const uint64_t UPPER_MASK = 0xFFFFFFFF80000000ULL;
    // least significant r bits
    static const uint64_t LOWER_MASK = 0x7FFFFFFFULL;
    // the state vector
    std::array<uint64_t, N> mt_;
    int mti_;
    unsigned long seed;
public:

    explicit MersenneTwister(unsigned long s) : mti_(N + 1)
    {
        init(s);
        // Store the seed
        seed = s;
    }

    void init(unsigned long s)
    {
        mt_[0] = s;
        for(mti_ = 1; mti_ < N; mti_++)
        {
            mt_[mti_] = (6364136223846793005ULL * (mt_[mti_ - 1] ^ (mt_[mti_ - 1] >> 62)) + mti_);
        }

    }


    uint64_t next()
    {
        static unsigned long mag01[2] = {0x0UL, MATRIX_A};
        int i;
        unsigned long long x;

        if(mti_ >= N)
        { /* generate NN words at one time */

            /* if init_genrand64() has not been called, */
            /* a default initial seed is used     */
            if(mti_ == N + 1)
                init(5489ULL);

            for(i = 0; i < N - M; i++)
            {
                x = (mt_[i] & UPPER_MASK) | (mt_[i + 1] & LOWER_MASK);
                mt_[i] = mt_[i + M] ^ (x >> 1) ^ mag01[(int) (x & 1ULL)];
            }
            for(; i < N - 1; i++)
            {
                x = (mt_[i] & UPPER_MASK) | (mt_[i + 1] & LOWER_MASK);
                mt_[i] = mt_[i + (M - N)] ^ (x >> 1) ^ mag01[(int) (x & 1ULL)];
            }
            x = (mt_[N - 1] & UPPER_MASK) | (mt_[0] & LOWER_MASK);
            mt_[N - 1] = mt_[M - 1] ^ (x >> 1) ^ mag01[(int) (x & 1ULL)];

            mti_ = 0;
        }

        x = mt_[mti_++];

        x ^= (x >> 29) & 0x5555555555555555ULL;
        x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
        x ^= (x << 37) & 0xFFF7EEE000000000ULL;
        x ^= (x >> 43);

        return x;
    }
};

#endif //RNG_TESTING_MERSENNETWISTER_H
