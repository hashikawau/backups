

//===========================================================
//===========================================================
#include <iostream>
#include <math.h>

using namespace std;

#include "Mathematics/FDM.h"
#include "Mathematics/FDM_cpp.h"

//===========================================================
//===========================================================
int main()
{
    
    int numx[2];
    numx[0] = 11;
    numx[1] = 11;
    double dx = 0.1;
    double vars[numx[0] *numx[1]];
    double source[numx[0] *numx[1]];
    for(int i=0; i< numx[0] *numx[1]; ++i){
        vars[i] = 0;
        source[i] = 0;
    }
    
    int numBCD = 2 *(numx[1] -2);
    int indexBCD[numBCD];
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
    
    int numBCN[2];
    numBCN[0] = 0;
    numBCN[1] = 2 *numx[0];
    int* indexBCN[2];
    indexBCN[0] = new int[numBCN[0]];
    indexBCN[1] = new int[numBCN[1]];
    double* bcN[2];
    bcN[0] = new double[numBCN[0]];
    bcN[1] = new double[numBCN[1]];
    for(int i=0; i< numx[0]; ++i){
        indexBCN[1][i] = i;
        indexBCN[1][i+numx[0]] = i+(numx[1]-1)*numx[0];
        bcN[1][i] = -10;
        bcN[1][i+numx[0]] = -10;
    }
    
    FDM::poisson_2d(
        numx,
        dx,
        vars,
        source,
        numBCD,
        indexBCD,
        bcD,
        numBCN,
        indexBCN,
        bcN);
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.setf(ios::showpos);
    cout.setf(ios::unitbuf);
    cout.setf(ios::scientific);
    cout.precision(2);
    for(int j=0; j< numx[1]; ++j){
        for(int i=0; i< numx[0]; ++i){
            cout << vars[j*numx[0] +i] << "\t";
        }
        cout << endl;
    }
    
    
    return 0;
}
//===========================================================
//===========================================================

