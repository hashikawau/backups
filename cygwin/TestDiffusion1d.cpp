

//===========================================================
//===========================================================

#include <iostream>
#include "../base/math/Diffusion.h"
#include "../base/math/Diffusion_cpp.h"
#include "../base/math/Poisson.h"
#include "../base/math/Poisson_cpp.h"
using namespace std;

//===========================================================
//===========================================================
int main()
{
    double dt = 0.01;
    int numStep =10000;
    int numx = 21;
    double dx = 0.1;
    double vars[numx];
    double source[numx];
    for(int i=0; i< numx; ++i){
        vars[i] = 0;
        source[i] = 0;
        if(i<numx/2){
            //vars[i] = 10;
        }
    }
    //source[10] = 100;
    
    unsigned int numBCD =2;
    unsigned int indexBCD[numBCD];
    indexBCD[0] = 0;
    indexBCD[1] = numx -1;
    double bcD[2];
    bcD[0] = 10;
    bcD[1] = 0;
    
    unsigned int numBCN =2;
    unsigned int indexBCN[numBCN];
    indexBCN[0] = 0;
    indexBCN[1] = numx -1;
    double bcNx[2];
    bcNx[0] = 0;
    bcNx[1] = 0;
    double coefficients =1;
    
    ///*
    Diffusion::fdm_1d(
        dt,
        numStep,
        numx,
        dx,
        vars,
        source,
        2,
        indexBCD,
        bcD,
        0,
        indexBCN,
        bcNx,
        coefficients);
    //*/
    /*
    Poisson::fdm_1d(
        numx,
        dx,
        vars,
        source,
        2,
        static_cast<int*>(indexBCD),
        bcD,
        0,
        static_cast<int*>(indexBCN),
        bcNx);
    */
    
    for(int i=0; i< numx; ++i){
        cout << vars[i] << endl;
    }
    
    return 0;
}
//===========================================================
//===========================================================

