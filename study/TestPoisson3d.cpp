

//===========================================================
//===========================================================
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

#include "Mathematics/FDM.h"
#include "Mathematics/FDM_cpp.h"

//===========================================================
//===========================================================
int main()
{
    
    int numx[3];
    numx[0] = 10;
    numx[1] = 10;
    numx[2] = 10;
    double dx = 0.1;
    double vars[numx[0] *numx[1] *numx[2]];
    double source[numx[0] *numx[1] *numx[2]];
    for(int i=0; i< numx[0] *numx[1] *numx[2]; ++i){
        vars[i] = 0;
        source[i] = 10;
    }
    
    int numBCD = numx[0]*numx[1]*numx[2]
        - (numx[0]-2)*(numx[1]-2)*(numx[2]-2);
    int indexBCD[numBCD];
    int count =0;
    for(int i=0; i< numx[0]*numx[1]; ++i){
        indexBCD[count] = i;
//cout << count << ", " << indexBCD[count] << endl;
        ++count;
    }
//cout << endl;
    for(int k=1; k< numx[2] -1; ++k){
        for(int i=0; i< numx[0]; ++i){
            indexBCD[count] = numx[0]*numx[1]*k +i;
//cout << count << ", " << indexBCD[count] << endl;
            ++count;
        }
//cout << endl;
        
        for(int j=1; j< numx[1] -1; ++j){
            indexBCD[count] = numx[0]*numx[1]*k + numx[0]*j;
//cout << count << ", " << indexBCD[count] << endl;
            ++count;
            indexBCD[count] = numx[0]*numx[1]*k + numx[0]*(j+1) -1;
//cout << count << ", " << indexBCD[count] << endl;
            ++count;
        }
//cout << endl;
        
        for(int i=0; i< numx[0]; ++i){
            indexBCD[count] = numx[0]*numx[1]*(k+1) -numx[0] +i;
//cout << count << ", " << indexBCD[count] << endl;
            ++count;
        }
//cout << endl;
    }
    for(int i= numx[0]*numx[1]*(numx[2]-1); i< numx[0]*numx[1]*numx[2]; ++i){
        indexBCD[count] = i;
//cout << count << ", " << indexBCD[count] << endl;
        ++count;
    }
    
    double bcD[numBCD];
    for(int i=0; i< numBCD; ++i){
        bcD[i] = 0;
    }
    
    int numBCN[3];
    numBCN[0] = 0;
    numBCN[1] = 0;//2 *numx[0];
    numBCN[2] = 0;
    int* indexBCN[3];
    indexBCN[0] = new int[numBCN[0]];
    indexBCN[1] = new int[numBCN[1]];
    indexBCN[2] = new int[numBCN[2]];
    double* bcN[3];
    bcN[0] = new double[numBCN[0]];
    bcN[1] = new double[numBCN[1]];
    bcN[2] = new double[numBCN[2]];
    /*
    for(int i=0; i< numx[0]; ++i){
        indexBCN[1][i] = i;
        indexBCN[1][i+numx[0]] = i+(numx[1]-1)*numx[0];
        bcN[1][i] = 10;
        bcN[1][i+numx[0]] = 10;
    }
    */
    
    FDM::poisson_3d(
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
    for(int k=0; k< numx[2]; ++k){
        for(int j=0; j< numx[1]; ++j){
            for(int i=0; i< numx[0]; ++i){
                cout << vars[k*numx[0]*numx[1] +j*numx[0] +i] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    
    return 0;
}
//===========================================================
//===========================================================

