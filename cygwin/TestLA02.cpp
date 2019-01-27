

//===========================================================
//===========================================================
#include <iostream>
#include <math.h>
using namespace std;
//===========================================================
//===========================================================
double* dotproduct2_2(double* matrix1, double* matrix2, int numrow);
double* dotproduct2_1(double* matrix1, double* vector1, int numrow);
double dotproduct1_1(double* a, double* b, int numrow);
double* transpose(double* matrix1, int numrow);
void showmatrix(double* matrix, int numrow);
void showmatrix(double* matrix, int numrow, int numcolumn);
//===========================================================
//===========================================================
void ludecomp(double* matrix, int numrow, int* index, double& d)
{
    
    int imax;
    //double big, dum, sum, temp;
    double vv[numrow];
    d =1.;
    
    for(int i=0; i< numrow; ++i){
        double big =0.;
        //big =0.;
        for(int j=0; j< numrow; ++j){
            double temp = fabs(matrix[i*numrow +j]);
            //temp = fabs(matrix[i*numrow +j]);
            if(temp > big){
                big = temp;
            }
        }
        vv[i] = 1. /big;
    }
    
    for(int j=0; j< numrow; ++j){
        for(int i=0; i< j; ++i){
            double sum =matrix[i*numrow +j];
            //sum =matrix[i*numrow +j];
            for(int k=0; k <i; ++k){
                sum -= matrix[i*numrow +k] *matrix[k*numrow +j];
            }
            matrix[i*numrow +j] =sum;
        }
        
        double big =0.;
        //big =0.;
        for(int i=j; i< numrow; ++i){
            double sum =matrix[i*numrow +j];
            //sum =matrix[i*numrow +j];
            for(int k=0; k< j; ++k){
                sum -= matrix[i*numrow +k] *matrix[k*numrow +j];
            }
            matrix[i*numrow +j] =sum;
            double dum = vv[i] *fabs(sum);
            //dum = vv[i] *fabs(sum);
            if(dum >= big){
                big =dum;
                imax =i;
            }
        }
        
        if(j != imax){
            for(int k=0; k< numrow; ++k){
                double dum = matrix[imax*numrow +k];
                //dum = matrix[imax*numrow +k];
                matrix[imax*numrow +k] =matrix[j*numrow +k];
                matrix[j*numrow +k] =dum;
            }
            d *= -1;
            vv[imax] = vv[j];
        }
        index[j] = imax;
        
        if(j != numrow){
            double dum =1. /matrix[j*numrow +j];
            //dum =1. /matrix[j*numrow +j];
            for(int i=j+1; i< numrow; ++i){
                matrix[i*numrow +j] *=dum;
            }
        }
    }
    
}
void lubacks(double* matrix, int numrow, int* index, double* vector)
{
    int ii=0;
    double sum;
    
    
    
    for(int i=0; i<numrow; ++i){
        int ip = index[i];
        //double sum =vector[ip];
        sum =vector[ip];
        vector[ip] = vector[i];
        if(ii){
            for(int j=ii; j<i; ++j){
                sum -= matrix[i*numrow +j] *vector[j];
            }
        }else
        if(sum){
            ii =i;
        }
        vector[i] =sum;
    }
    
    for(int i= numrow-1; i>=0; --i){
        //double sum =vector[i];
        sum =vector[i];
        for(int j= i+1; j<numrow; ++j){
            sum -= matrix[i*numrow +j] *vector[j];
        }
        vector[i] = sum /matrix[i*numrow +i];
    }
}
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
         2, -1,  1,  4,
        -1,  2, -1,  1,
         0.5, -0.5,  1, -1,
         2,  0.5, -1,  1.5};
    double matrix[] ={
         1,  2,
         3,  4};
    double matrix6[] ={
         2, -1,  7, -1,
        -2,  5, -3, -8,
         8,  2, -1,  2,
         1, -8,  1, -2};
    
    
    
    double vector[] ={1, 2, 3, 4};
    
    
    
    int numrow =2;
    double* copy = new double[numrow *numrow];
    for(int i=0; i< numrow *numrow; ++i){
        copy[i] = matrix[i];
    }
    double* temp0;
    double* temp1;
    double* temp2;
    
    
    showmatrix(copy, numrow, numrow);
    cout << endl;
    
    int index[numrow];
    double d;
    
    ludecomp(copy, numrow, index, d);
    cout << "LU decomposition" << endl;
    showmatrix(copy, numrow, numrow);
    cout << endl;
    cout << "LU decomposition index = ";
    for(int i=0; i< numrow; ++i){
        cout << index[i] << " ";
    }
    cout << d;
    cout << endl;
    double alpha[numrow *numrow];
    double beta[numrow *numrow];
    for(int i=0; i< numrow *numrow; ++i){
        alpha[i] = copy[i];
        beta[i] = copy[i];
    }
    for(int i=0; i< numrow; ++i){
        for(int j=i+1; j< numrow; ++j){
            alpha[i*numrow +j] =0;
        }
        alpha[i*numrow +i] =1;
    }
    for(int i=0; i< numrow; ++i){
        for(int j=0; j< i; ++j){
            beta[i*numrow +j] =0;
        }
    }
    cout << "alpha = " << endl;
    showmatrix(alpha, numrow, numrow);
    cout << endl;
    cout << "beta = " << endl;
    showmatrix(beta, numrow, numrow);
    cout << endl;
    temp0 = dotproduct2_2(alpha, beta, numrow);
    for(int i=0; i< numrow; ++i){
        if(index[i] != i){
            int p = index[i];
            double t;
            for(int j=0; j< numrow; ++j){
                t = temp0[i*numrow +j];
                temp0[i*numrow +j] = temp0[p*numrow +j];
                temp0[p*numrow +j] = t;
            }
        }
    }
    cout << "alpha *beta = " << endl;
    showmatrix(temp0, numrow, numrow);
    cout << endl;
    delete [] temp0;
    
    
    
    
    lubacks(copy, numrow, index, vector);
    /*
    for(int i=0; i< numrow; ++i){
        if(index[i] != i){
            int p = index[i];
            double t = vector[i];
            vector[i] = vector[p];
            vector[p] = t;
        }
    }
    */
    showmatrix(vector, numrow);
    cout << endl;
    
    temp0 = dotproduct2_1(matrix, vector, numrow);
    showmatrix(temp0, numrow);
    cout << endl;
    delete [] temp0;
    
    return 0;
}
//===========================================================
//===========================================================



double* dotproduct2_2(double* matrix1, double* matrix2, int numrow)
{
    double* matrix0 = new double[numrow *numrow];
    for(int i=0; i< numrow; ++i){
        for(int j=0; j< numrow; ++j){
            matrix0[i*numrow +j] =0;
            for(int k=0; k< numrow; ++k){
                matrix0[i*numrow +j] +=
                    matrix1[i*numrow +k] *matrix2[k*numrow +j];
            }
        }
    }
    
    return matrix0;
}
double* dotproduct2_1(double* matrix1, double* vector1, int numrow)
{
    double* vector0 = new double[numrow];
    for(int i=0; i< numrow; ++i){
        vector0[i] =0;
        for(int k=0; k< numrow; ++k){
            vector0[i] +=
                matrix1[i*numrow +k] *vector1[k];
        }
    }
    
    return vector0;
}
double dotproduct1_1(double* a, double* b, int numrow)
{
    double c =0.0;
    for(int i=0; i< numrow; ++i){
        c += a[i] *b[i];
    }
    return c;
}
double* transpose(double* matrix1, int numrow)
{
    double* matrix0 = new double[numrow *numrow];
    for(int i=0; i< numrow; ++i){
        for(int j=0; j< numrow; ++j){
            matrix0[i*numrow +j] = matrix1[j*numrow +i];
        }
    }
    
    return matrix0;
}
void showmatrix(double* matrix, int numrow)
{
    cout.precision(3);
    for(int i=0; i< numrow; ++i){
        cout << matrix[i] << "  \t";
    }
    cout << endl;
}
void showmatrix(double* matrix, int numrow, int numcolumn)
{
    cout.precision(3);
    for(int i=0; i< numrow; ++i){
        for(int j=0; j< numcolumn; ++j){
            cout << matrix[i*numrow +j] << "  \t";
        }
        cout << endl;
    }
}







