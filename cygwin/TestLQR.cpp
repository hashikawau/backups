

//===========================================================
//===========================================================
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
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
    int numX = temp[0][0];
    int numU = temp[0][1];
    
    Matrix A(numX, numX);
    A.read(stream);
    //A.show();
    
    Matrix B(numX, numU);
    B.read(stream);
    //B.show();
    
    //Matrix C(numRad, numObsv);
    //C.read(stream);
    //C.show();
    
    Matrix Q(numX, numX);
    Q.read(stream);
    //Q.show();
    
    Matrix R(numU, numU);
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
    
    /*
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
    */
    
    
    Matrix Bt = B;
    Bt.transpose();
    R.inverse();
    Matrix K = -1 *R *Bt;
    
    temp = B *K;
    
    int n = numX;
    int nn = 2*n;
    Matrix H(nn, nn);
    H.zero();
    for(int i=0; i< n; ++i){
        for(int j=0; j< n; ++j){
            H[i][j] = A[i][j];
            H[n+i][n+j] = -A[j][i];
            H[i][n+j] = temp[i][j];
            H[n+i][j] = -Q[i][j];
        }
    }
    //H.show();
    //(H.rank()).show();
    Matrix copy = H;
    temp = H.eigenvalue();
    
    
    //H.show();
    //temp.show();
    
    /*
    for(int k=0; k< nn; ++k){
        Matrix Ap(2*nn, 2*nn);
        Matrix x(2*nn, 1);
        Ap.zero();
        for(int i=0; i< nn; ++i){
            for(int j=0; j< nn; ++j){
                Ap[i][j] = copy[i][j];
                Ap[nn+i][nn+j] = copy[i][j];
            }
            Ap[i][i] -= H[k][0];
            Ap[nn+i][nn+i] -= H[k][0];
            Ap[i][nn+i] += H[k][1];
            Ap[nn+i][i] -= H[k][1];
            
            x[i][0] = temp[i][k];
            x[nn+i][0] = temp[i][nn+k];
        }
        
        (Ap*x).show();
        //Ap.show();
        //x.show();
    }
    */
    
    /*
    for(int i=0; i< nn; ++i){
        double sum =0;
        for(int k=0; k< nn; ++k){
            sum += temp[k][i] *temp[k][i] + temp[k][nn+i] *temp[k][nn+i];
        }
        cout << sum << ", ";
    }
    cout << endl;
    */
    
    /*
    {
    Matrix tempt =temp;
    tempt.transpose();
    
    Matrix I = tempt *temp;
    I.show();
    for(int i=0; i< nn; ++i){
        for(int j=0; j< nn; ++j){
            tempt[i][j] = I[i][j] -I[nn+i][nn+j];
            tempt[nn+i][j] = I[i][nn+j] +I[nn+i][j];
        }
    }
    //tempt.show();
    }
    */
    
    //eigenvector(H, temp);
    
    
    Matrix ur(n, n);
    Matrix ui(n, n);
    Matrix vr(n, n);
    Matrix vi(n, n);
    int count =0;
    for(int i=0; i< nn && count< n; ++i){
        if(H[i][0] <0){
            for(int k=0; k< n; ++k){
                vr[k][count] = temp[k][i];
                vi[k][count] = temp[k][nn +i];
                ur[k][count] = temp[n +k][i];
                ui[k][count] = temp[n +k][nn +i];
            }
            ++count;
        }
    }
    //vr.show();
    //ur.show();
    //vi.show();
    //ui.show();
    Matrix vinr =vr;
    Matrix vini =vi;
    
    Matrix compA(nn, nn);
    Matrix compx(nn, n);
    compx.zero();
    for(int i=0; i< n; ++i){
        for(int j=0; j< n; ++j){
            compA[i][j] = vr[i][j];
            compA[i][n+j] = -vi[i][j];
            compA[n+i][j] = vi[i][j];
            compA[n+i][n+j] = vr[i][j];
        }
        compx[i][i] =1;
    }
    //compA.show();
    //compx.show();
    compA.solveeq(compx);
    //compx.show();
    for(int i=0; i< n; ++i){
        for(int j=0; j< n; ++j){
            vinr[i][j] = compx[i][j];
            vini[i][j] = compx[n+i][j];
        }
    }
    //(vr*vinr - vi*vini).show();
    //(vr*vini + vi*vinr).show();
    
    
    //(ur*vinr - ui*vini).show();
    //(ur*vini + ui*vinr).show();
    
    
    
    temp = ur*vinr - ui*vini;
    temp.show();
    
    K = K *temp;
    K.show();
    
    
    
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


