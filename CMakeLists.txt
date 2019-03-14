cmake_minimum_required(VERSION 3.10)
project(rng_testing)

set(CMAKE_CXX_STANDARD 14)

add_executable(rng_testing main.cpp Xoshiro256plus.h MersenneTwisterCpp.h
        Xoroshiro128plus.h LNG.h random_convert.h SplitMix64.h MersenneTwister.h PCG.h)