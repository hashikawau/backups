

//===========================================================
//===========================================================

#include <iostream>
#include "../base/math/Poisson.h"
#include "../base/math/Poisson_cpp.h"
using namespace std;

//===========================================================
//===========================================================
int main()
{
    
    int numx = 21;
    double dx = 0.1;
    double vars[numx];
    double source[numx];
    for(int i=0; i< numx; ++i){
        vars[i] = 0;
        source[i] = 100;
    }
    source[10] = 100;
    
    int numDBC =2;
    int indexDBC[numDBC];
    indexDBC[0] = 0;
    indexDBC[1] = numx -1;
    double bcD[2];
    bcD[0] = 100;
    bcD[1] = 0;
    
    int numNBC =2;
    int indexNBC[numNBC];
    indexNBC[0] = numx -1;
    indexNBC[1] = numx -1;
    double bcNx[2];
    bcNx[0] = 100;
    bcNx[1] = 100;
    
    Poisson::fdm_1d(
        numx,
        dx,
        vars,
        source,
        1,
        indexDBC,
        bcD,
        1,
        indexNBC,
        bcNx);
    
    for(int i=0; i< numx; ++i){
        cout << vars[i] << endl;
    }
    
    return 0;
}
//===========================================================
//===========================================================

