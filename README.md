# Testing random number generation in C++


See the [blog post](http://thompsonsed.co.uk/?p=1337)  accompanying this code. Tests the performance of several PRNGs, including

- Xoshiro256+
- Xoroshiro128+
- Linear congruential generator (LCG)
- Permuted congruential generator (PCG)
- SplitMix64
- Mersenne Twister (MT)
- C++ base `minstd`
- C++ base `rand()`
- C++ base `mt`



## Installation and usage
Use the included cmake file to compile.

```
>> cmake .
>> make
>> ./rng_testing
```

## Contact
Email: thompsonsed@gmail.com

License: MIT