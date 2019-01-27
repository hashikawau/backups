

#ifndef _util_Random_cpp
#define _util_Random_cpp


//===========================================================
//===========================================================
#include "Random.h"
#include <time.h>
//===========================================================
//===========================================================
Random::Random()
{
    setSeed(time(0));
}
Random::Random(long long seed)
{
    setSeed(seed);
}
void Random::setSeed(long long seed)
{
    _seed = (seed ^ 0x05DEECE66D) & (0x01000000000000 -1);
}
int Random::next(int bits)
{
    _seed *= static_cast<long long>(0x05DEECE66D);
    _seed += 0x0B;
    _seed &= 0x01000000000000 -1;
    return static_cast<int>(_seed >> (48 - bits));
}
int Random::nextInt()
{
    return next(32);
}
double Random::nextDouble()
{
    return ((static_cast<long long>(next(26)) <<27) + next(27))
        / static_cast<double>(0x20000000000000);
}
//===========================================================
//===========================================================


#endif //ifndef _util_Random_cpp

