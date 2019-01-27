

//===========================================================
//===========================================================
#include <iostream>
#include <math.h>
#include "../base/math/Matrix.h"
using namespace std;
//===========================================================
//===========================================================

//===========================================================
//===========================================================
int main()
{
    double matrix1[] ={
         2, -1,  1,  4,
        -1,  2, -1,  1,
         1, -1,  2, -2,
         4,  1, -2,  3};
    double matrix2[] ={
        2,       4.2426, 0,      0,
        4.24261, 1.6667, 1.7795, 0,
        0,       1.7795, 4.0292, 0.9883,
        0,       0,      0.9883, 1.3041};
    double matrix3[] ={
         2, -1,  0,
        -1,  2, -1,
         0, -1,  2};
    double matrix4[] ={
         2,  0.5, -1,  1.5,
         0.5, -0.5,  1, -1,
         2, -1,  1,  4,
        -1,  2, -1,  1};
    double matrix5[] ={
         0,   1,
         0.75,   1};
    double matrix6[] ={
         2, -1,  7, -1,
        -2,  5, -3, -8,
         8,  2, -1,  2,
         1, -8,  1, -2};
    
    
    
    double matrix7_1[] ={
         0,  1,  0,
         0,  0,  1,
         1,  0,  0};
    double matrix7_2[] ={
         0,  0,  1,
         1,  0,  0,
         0,  1,  0};
    double matrix7_3[] ={
         0,  1,  0,
         0,  1,  1,
         0, -1, -1};
    
    
    
    
    double matrix8[] ={
        -3,  6,  4,
        -5,  8,  4,
         3, -3,  1};
    double matrix9[] ={
        -1, -7,  2,
         1,  4, -1,
         1,  2,  0};
    double matrix2_3[] ={
        -1,   1,
        -3,   1};
    double matrix2_4[] ={
         1,   -1,
         2,   1};
    
    
    
    
    double vector[] ={1, 2, 3, 4};
    
    
    
    int numrow =4;
    
    
    Matrix a(numrow, numrow);
    Matrix b(numrow, numrow);
    for(int i=0; i< numrow; ++i){
        for(int j=0; j< numrow; ++j){
            a[i][j] = matrix6[i*numrow +j];
            b[i][j] = matrix4[i*numrow +j];
        }
    }
    
    Matrix aa =a;
    a.show();
    Matrix bb =b;
    bb.identity();
    //bb.show();
    
//    while(1)
    b = a.eigenvalue();
    a.show();
    b.show();
    //bb = b;
    //bb.transpose();
    //(bb*aa*b).show();
    cout << endl;
    for(int i=0; i< numrow; ++i){
        Matrix T = aa +-a[i][0] *bb;
        double det = T.determinant();
        if(det > 1e-3){
            Matrix Tinverse =T;
            Tinverse.inverse();
            det = (T +a[i][1]*a[i][1] *Tinverse).determinant();
        }
        cout << det << ", ";
    }
    cout << endl;
    
    bb = b;
    bb.transpose();
    Matrix c = bb*aa*b;
    c.show();
    for(int i=0; i< numrow; ++i){
        for(int j=0; j< numrow; ++j){
            b[i][j] = c[i][j] - c[numrow +i][numrow +j];
            b[i][numrow +j] = c[i][numrow +j] + c[numrow +i][j];
        }
    }
    b.show();
    
    
    return 0;
}
//===========================================================
//===========================================================





