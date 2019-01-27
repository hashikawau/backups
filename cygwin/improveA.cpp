

//===========================================================
//===========================================================
#include <iostream>

#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "../base/math/Matrix.h"

using namespace std;
//===========================================================
//===========================================================

//===========================================================
//===========================================================
int main(int argc, char* argv[])
{
    //===========================================================
    
    ifstream stream;
    //===========================================================
    if(argc < 2){
        cout << "enter the file path" << endl;
        return 1;
    }
    
    stream.open(argv[1]);
    //===========================================================
    if(!stream){
        cout << "no such file" << endl;
        return 1;
    }
    
    Matrix temp(1, 3);
    temp.read(stream);
    int numX = temp[0][0];
    int numU = temp[0][1];
    int numdata = temp[0][2];
    int numV = numX +numU;
    
    Matrix Ap(numX, numX);
    Ap.read(stream);
    //Ap.show();
    
    Matrix Bp(numX, numU);
    Bp.read(stream);
    //Bp.show();
    
    Matrix Cp(numX, numV);
    for(int i=0; i< numX; ++i){
        for(int j=0; j< numX; ++j){
            Cp[i][j] = Ap[i][j];
        }
        for(int j=0; j< numU; ++j){
            Cp[i][numX +j] = Bp[i][j];
        }
    }
    Cp.show();
    
    temp = Matrix(numdata, numV +numX);
    temp.read(stream);
    //temp.show();
    
    
    //Matrix X(numdata, numX);
    //X.read(stream);
    //X.show();
    
    //Matrix U(numdata, numU);
    //U.read(stream);
    //U.show();
    
    Matrix V(numdata, numV);
    Matrix E(numdata, numX);
    //E.read(stream);
    //E.show();
    
    for(int i=0; i< numdata; ++i){
        for(int j=0; j< numV; ++j){
            V[i][j] = temp[i][j];
        }
        for(int j=0; j< numX; ++j){
            E[i][j] = temp[i][numV +j];
        }
    }
    //V.show();
    //E.show();
    Matrix Ecopy = E;
    
    
    //===========================================================
    stream.close();
    
    
    //===========================================================
    Cp.transpose();
    E = Ecopy - V*Cp;
    Cp.transpose();
    temp = Matrix(1, numX);
    for(int j=0; j< numX; ++j){
        temp[0][j] =0;
        for(int i=0; i< numdata; ++i){
            temp[0][j] += E[i][j] *E[i][j];
        }
    }
    temp.show();
    
    
    
    Matrix Vt = V;
    Vt.transpose();
    
    Vt = Vt *V;
    Vt.inverse();
    E.transpose();
    
    Matrix C;
    C = E *V *Vt;
    //C.show();
    
    
    
    Cp = Cp +C;
    
    for(int i=0; i< numX; ++i){
        for(int j=0; j< numV; ++j){
            if(Cp[i][j] < 0){
                //Cp[i][j] = 0;
            }
        }
    }
    //Cp.show();
    
    
    
    
    
    //===========================================================
    Matrix A(numX, numX);
    Matrix B(numX, numU);
    for(int i=0; i< numX; ++i){
        for(int j=0; j< numX; ++j){
            A[i][j] = Cp[i][j];
        }
        for(int j=0; j< numU; ++j){
            B[i][j] = Cp[i][numX +j];
        }
    }
    A.show();
    B.show();
    
    
    temp = A.eigenvalue();
    //A.show();
    
    Matrix Lre(numX, numX);
    Matrix Lim(numX, numX);
    Lre.zero();
    Lim.zero();
    Matrix Pre(numX, numX);
    Matrix Pim(numX, numX);
    double deltat = 10.;
    for(int i=0; i< numX; ++i){
        Lre[i][i] = A[i][0]*A[i][0] + A[i][1]*A[i][1];
        Lim[i][i] = atan(A[i][1] /A[i][0]);
        Lre[i][i] = log(Lre[i][i]) /2 /deltat;
        Lim[i][i] = Lim[i][i] /deltat;
        
        for(int j=0; j< numX; ++j){
            Pre[i][j] = temp[i][j];
            Pim[i][j] = temp[i][numX +j];
        }
        
        A[i][0] = Lre[i][i];
        A[i][1] = Lim[i][i];
    }
    A.show();
    
    Matrix Qre = Pre *Lre - Pim *Lim;
    Matrix Qim = Pre *Lim + Pim *Lre;
    Pre.transpose();
    Pim.transpose();
    
    (Qre *Pre - Qim *Pim).show();
    (Qre *Pim + Qim *Pre).show();
    
    
    
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    
    return 0;
}
//===========================================================
//===========================================================


