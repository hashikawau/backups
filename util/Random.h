

#ifndef _util_Random
#define _util_Random


//===========================================================
//===========================================================
class Random
{
protected:
    long long _seed;
    
    int next(int bits);
    
public:
    Random();
    Random(long long seed);
    void setSeed(long long seed);
    int nextInt();
    double nextDouble();
};
//===========================================================
//===========================================================


#endif //ifndef _util_Random

