cmake_minimum_required(VERSION 3.10)
project(rng_testing)

set(CMAKE_CXX_STANDARD 14)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_executable(rng_testing main.cpp Xoshiro256plus.h MersenneTwisterCpp.h
        Xoroshiro128plus.h LCG.h random_convert.h SplitMix64.h MersenneTwister.h PCG.h)