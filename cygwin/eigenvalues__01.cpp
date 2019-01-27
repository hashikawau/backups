

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
    
    Matrix temp(1, 2);
    temp.read(stream);
    int numCon = temp[0][0];
    int numRad = temp[0][1];
    int numObsv = numCon +numRad;
    
    Matrix A(numObsv, numObsv);
    A.read(stream);
    //A.show();
    
    Matrix B(numObsv, numRad);
    B.read(stream);
    //B.show();
    
    Matrix C(numRad, numObsv);
    C.read(stream);
    //C.show();
    
    Matrix Q(numObsv +numRad, 1);
    Q.read(stream);
    //Q.show();
    
    Matrix R(numRad, 1);
    R.read(stream);
    //R.show();
    
    
    
    //===========================================================
    stream.close();
    
    
    
    /*
    Matrix controllability(numObsv, numRad*numObsv);
    controllability.zero();
    temp =B;
    for(int k=0; k< numObsv; ++k){
        for(int i=0; i< numObsv; ++i){
            for(int j=0; j< numRad; ++j){
                controllability[i][k*numRad +j] = temp[i][j];
            }
        }
        temp = A * temp;
    }
    //controllability.show();
    //(controllability.rank()).show();
    */
    
    
    Matrix Ap(numObsv +numRad, numObsv +numRad);
    Matrix Bp(numObsv +numRad, numRad);
    Ap.zero();
    Bp.zero();
    for(int i=0; i< numObsv; ++i){
        for(int j=0; j< numObsv; ++j){
            Ap[i][j] = A[i][j];
        }
        
        for(int j=0; j< numRad; ++j){
            Bp[i][j] = B[i][j];
        }
    }
    for(int i=0; i< numRad; ++i){
        for(int j=0; j< numObsv; ++j){
            Ap[numObsv +i][j] = C[i][j];
        }
    }
    //Ap.show();
    //Bp.show();
    
    temp = Ap;
    for(int i=0; i< numObsv; ++i){
        for(int j=0; j< numRad; ++j){
            temp[i][numObsv +j] = Bp[i][j];
        }
    }
    //(temp.rank()).show();
    
    
    int n = numObsv +numRad;
    
    temp = Bp;
    temp.transpose();
    for(int i=0; i< numRad; ++i){
        for(int j=0; j< n; ++j){
            temp[i][j] /= R[i][0];
        }
    }
    temp = Bp *temp;
    //temp.show();
    
    
    Matrix H(2*n, 2*n);
    H.zero();
    for(int i=0; i< n; ++i){
        for(int j=0; j< n; ++j){
            H[i][j] = Ap[i][j];
            H[n+i][n+j] = -Ap[j][i];
            H[i][n+j] = -temp[i][j];
        }
        H[n+i][i] = -Q[i][0];
    }
    //H.show();
    //(H.rank()).show();
    
    temp = H.eigenvalue();
    
    //H.show();
    //temp.show();
    
    Matrix u(n, n);
    Matrix v(n, n);
    int nn = 2*n;
    int count =0;
    for(int i=0; i< nn && count< n; ++i){
        if(H[i][0] <0){
            for(int k=0; k< n; ++k){
                v[k][count] = temp[k][i];
                u[k][count] = temp[n +k][i];
            }
            ++count;
        }
    }
    //v.show();
    //u.show();
    
    
    v.transpose();
    temp = Bp;
    temp.transpose();
    for(int i=0; i< numRad; ++i){
        for(int j=0; j< n; ++j){
            temp[i][j] /= -R[i][0];
        }
    }
    
    Matrix K = temp *u *v;
    K.show(",");
    
    
    
    
    //Matrix eigA =A;
    //Matrix Q = eigA.eigenvalue();
    //Q.show();
    //eigA.show();
    //Q.transpose();
    //(Q*B).show();
    /*
    Matrix I(size, size);
    I.identity();
    cout << endl;
    for(int i=0; i< size; ++i){
        Matrix T = A + -eigA[i][0] *I;
        double det = T.determinant();
        if(det > 1e-3){
            Matrix Tinverse =T;
            Tinverse.inverse();
            det = (T + eigA[i][1]*eigA[i][1] *Tinverse).determinant();
        }
        cout << det << ", ";
    }
    */
    
    /*
    Matrix Qt = Q;
    Qt.transpose();
    (Qt*A*Q).show();
    */
    
    return 0;
}
//===========================================================
//===========================================================


