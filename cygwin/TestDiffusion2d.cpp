

//===========================================================
//===========================================================

#include <iostream>
#include <windows.h>
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
    int numStep =10;
    unsigned int numx[2];
    numx[0] = 30;
    numx[1] = 30;
    double dx[2];
    dx[0] = 0.1;
    dx[1] = 0.1;
    double vars[numx[0] *numx[1]];
    double source[numx[0] *numx[1]];
    for(int i=0; i< numx[0] *numx[1]; ++i){
        vars[i] = 20;
        source[i] = 0;
    }
    
    unsigned int numBCD = 2 *(numx[1] -2);
    unsigned int indexBCD[numBCD];
    int count =0;
    for(int i=0; i< numx[0]; ++i){
        //indexBCD[count] = i;
        //++count;
    }
    for(int i=1; i< numx[1] -1; ++i){
        indexBCD[count] = numx[0] *i;
        ++count;
        indexBCD[count] = numx[0] *(i+1) -1;
        ++count;
    }
    for(int i= numx[0] *(numx[1] -1); i< numx[0] *numx[1]; ++i){
        //indexBCD[count] = i;
        //++count;
    }
    
    double bcD[numBCD];
    for(int i=0; i< numBCD; ++i){
        bcD[i] = 0;
    }
    
    unsigned int numBCN[2];
    numBCN[0] = 0;
    numBCN[1] = 2 *numx[0];
    unsigned int* indexBCN[2];
    indexBCN[0] = new unsigned int[numBCN[0]];
    indexBCN[1] = new unsigned int[numBCN[1]];
    double* bcN[2];
    bcN[0] = new double[numBCN[0]];
    bcN[1] = new double[numBCN[1]];
    for(int i=0; i< numx[0]; ++i){
        indexBCN[1][i] = i;
        indexBCN[1][i+numx[0]] = i+(numx[1]-1)*numx[0];
        bcN[1][i] = 0;
        bcN[1][i+numx[0]] = 0;
    }
    double coefficients[2];
    coefficients[0] =1;
    coefficients[1] =1;
    
    ///*
    unsigned long long time = GetTickCount();
    for(int k=0; k< 1; ++k){
        for(int i=0; i< numx[0] *numx[1]; ++i){
            source[i] = (10 -vars[i]);
        }
        Diffusion::fdm_2d(
            dt,
            numStep,
            numx,
            dx,
            vars,
            source,
            numBCD,
            indexBCD,
            bcD,
            numBCN,
            indexBCN,
            bcN,
            coefficients);
    }
    time = GetTickCount() -time;
    //*/
    /*
    Poisson::fdm_2d(
        static_cast<int*>(numx),
        dx[0],
        vars,
        source,
        numBCD,
        static_cast<int*>(indexBCD),
        bcD,
        static_cast<int*>(numBCN),
        static_cast<int**>(indexBCN),
        bcN);
    */
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    //cout.setf(ios::showpos);
    cout.setf(ios::unitbuf);
    cout.setf(ios::scientific);
    cout.precision(2);
    for(int j=0; j< numx[1]; ++j){
        for(int i=0; i< numx[0]; ++i){
            cout << vars[j*numx[0] +i] << "  ";
        }
        cout << endl;
    }
    cout << time << endl;
    
    
    return 0;
}
//===========================================================
//===========================================================

