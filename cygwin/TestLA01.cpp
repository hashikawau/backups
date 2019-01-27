

//===========================================================
//===========================================================
#include <iostream>
#include <math.h>

using namespace std;
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
        for(int j=0; j< numrow; ++j){
            cout << matrix[i*numrow +j] << "  \t";
        }
        cout << endl;
    }
}
double dotproduct1_1(double* a, double* b, int numrow)
{
    double c =0.0;
    for(int i=0; i< numrow; ++i){
        c += a[i] *b[i];
    }
    return c;
}
//===========================================================
//===========================================================
// reduce Hessenberg form (inplace). 
// O ( n^3 )
void hessenberg(//matrix &A
    double* A, int numrow, double* transformation)
{
  //const int n = A.size();
  const int n = numrow;
  for (int k = 1; k <= n-2; ++k) {
//    array u(n);
    double u[n];
    //for (int i = k; i < n; ++i) u[i] = A[i][k-1];
    for (int i = k; i < n; ++i) u[i] = A[i*n +k-1];

    //number ss = 0;
    double ss = 0;
    for (int i = k+1; i < n; ++i) ss += u[i] * u[i];
    //if (abs(ss) <= 0.0) continue;
    if (fabs(ss) <= 0.0) continue;
    //number s = sqrt( ss + u[k]*u[k] );
    double s = sqrt( ss + u[k]*u[k] );
    if (u[k] > 0.0) s = -s;

    u[k] -= s;
    //number uu = sqrt( ss + u[k]*u[k] );
    double uu = sqrt( ss + u[k]*u[k] );
    for (int i = k; i < n; ++i) u[i] /= uu;

    //array f(n), g(n);
    double f[n];
    double g[n];
    //for (int i = 0; i < n; ++i)
    //  for (int j = k; j < n; ++j)
    //    f[i] += A[i][j] * u[j],
    //    g[i] += A[j][i] * u[j];
    for (int i = 0; i < n; ++i){
      for (int j = k; j < n; ++j){
        f[i] += A[i*n +j] * u[j];
        g[i] += A[j*n +i] * u[j];
      }
    }
    //number gamma = inner_product(u, g);
    double gamma = dotproduct1_1(u, g, n);
    //for (int i = 0; i < n; ++i)
    //  f[i] -= gamma * u[i],
    //  g[i] -= gamma * u[i];
    for (int i = 0; i < n; ++i){
      f[i] -= gamma * u[i];
      g[i] -= gamma * u[i];
    }

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        //A[i][j] = A[i][j] - 2*u[i]*g[j] - 2*f[i]*u[j];
        A[i*n +j] = A[i*n +j] - 2*u[i]*g[j] - 2*f[i]*u[j];
  }
}

// find all eigenvalues using Hessenberg-QR Method
// O( n^3 + M n^2 ) where M is the number of iterations.
//vector<number> eigenvalues(matrix A) {
void eigenvalues(double* A, int numrow, double* lambda){
  //const int n = A.size();
  const int n = numrow;
  //hessenberg(A);
  hessenberg(A, numrow, 0);
cout << "\n\nshjkl;\n\n";
showmatrix(A, numrow);
cout << "\n\n\n\n";
  //vector<number> s(n), c(n);
  double s[n];
  double c[n];
  double eps =1e-6;
  for (int m = n; m >= 2; ) {
    //if (abs(A[m-1][m-2]) < eps) { --m; continue; }
    if (fabs(A[(m-1)*n +m-2]) < eps) { --m; continue; }
    //number shift = A[m-1][m-1];
    double shift = A[(m-1)*n +m-1];
    //for (int i = 0; i < m; ++i) A[i][i] -= shift;
    for (int i = 0; i < m; ++i) A[i*(n+1)] -= shift;
    for (int k = 0; k < m-1; ++k) {
      //number a = A[k][k],
      //b = A[k+1][k],
      //r = sqrt(a*a + b*b);
      double a = A[k*(n+1)];
      double b = A[(k+1)*n +k];
      double r = sqrt(a*a + b*b);
      //s[k] = r == 0.0 ? 0.0 : b/r,
      s[k] = r == 0.0 ? 0.0 : b/r;
      c[k] = r == 0.0 ? 0.0 : a/r;
      for (int j = k; j < m; ++j) {
        //number x = A[k][j], y = A[k+1][j];
        //A[ k ][j] =  c[k] * x + s[k] * y;
        //A[k+1][j] = -s[k] * x + c[k] * y;
        double x = A[(k)*n +j];
        double y = A[(k+1)*n +j];
        A[(k)*n +j] =  c[k] * x + s[k] * y;
        A[(k+1)*n +j] = -s[k] * x + c[k] * y;
      }
    }
    for (int k = 0; k < m-1; ++k) {
      for (int i = 0; i <= k+1; ++i) {
        //number x = A[i][k], y = A[i][k+1];
        //A[i][ k ] =  c[k] * x + s[k] * y;
        //A[i][k+1] = -s[k] * x + c[k] * y;
        double x = A[i*n +k];
        double y = A[i*n +k+1];
        A[i*n +k] =  c[k] * x + s[k] * y;
        A[i*n +k+1] = -s[k] * x + c[k] * y;
      }
    }
    //for (int i = 0; i < m; ++i) A[i][i] += shift;
    for (int i = 0; i < m; ++i) A[i*(n+1)] += shift;
  }
  //vector<number> lambda;
  for (int i = 0; i < n; ++i)
    //lambda.push_back( A[i][i] );
    lambda[i] = A[i*(n+1)];
  //return lambda;
}

//struct LUinfo {
//  vector<number> value;
//  vector<int> index;
//};
class LUinfo {
public:
  LUinfo(int numrow): _numrow(numrow)
  {
    value = new double[_numrow *_numrow];
    index = new int[_numrow];
  }
  int _numrow;
  double* value;
  int* index;
};
// O( n^3 ), Gaussian forward elimination
//LUinfo LU_decomposition(matrix A) {
LUinfo LU_decomposition(double* A, int numrow) {
  //const int n = A.size();
  const int n = numrow;
  //LUinfo data;
  LUinfo data(n);
  int count =0;
showmatrix(A, n);
cout << endl;
  for (int i = 0; i < n; ++i) {
    int pivot = i;
    for (int j = i+1; j < n; ++j)
      //if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
      if (fabs(A[j*n +i]) > fabs(A[pivot*n +i])) pivot = j;
    //swap(A[pivot], A[i])
    for(int j=0; j< n; ++j){
        double temp = A[pivot*n +j];
        A[pivot*n +j] = A[i*n +j];
        A[i*n +j] = temp;
    }
    //data.index.push_back(pivot);
    data.index[i] = pivot;
    // if A[i][i] == 0, LU decomposition failed.
    for(int j = i+1; j < n; ++j) {
      //A[j][i] /= A[i][i];
      A[j*n +i] /= A[i*n +i];
      for(int k = i+1; k < n; ++k){
        //A[j][k] -= A[i][k] * A[j][i];
        A[j*n +k] -= A[i*n +k] * A[j*n +i];
      }
      //data.value.push_back(A[j][i]);
      data.value[count++] = A[j*n +i];
    }
  }
  for(int i = n-1; i >= 0; --i) {
    for(int j = i+1; j < n; ++j){
      //data.value.push_back(A[i][j]);
      data.value[count++] = A[i*n +j];
    }
    
    //data.value.push_back(A[i][i]);
    data.value[count++] = A[i*n +i];
  }
showmatrix(A, n);
cout << endl;
  
  return data;
}
// O( n^2 ) Gaussian backward substitution
//array LU_backsubstitution(const LUinfo &data, array b) {
void LU_backsubstitution(
    LUinfo data, double* original, int numrow, double* b)
{
  //const int n = b.size();
  const int n = numrow;
  int k = 0;
  for (int i = 0; i < n; ++i){
    b[i] = original[i];
  }
  for (int i = 0; i < n; ++i){
    //swap(b[data.index[i]], b[i]);
    double temp = b[data.index[i]];
    b[data.index[i]] = b[i];
    b[i] = temp;
    for(int j = i+1; j < n; ++j)
      b[j] -= b[i] * data.value[k++];
  }
  for (int i = n-1; i >= 0; --i) {
    for (int j = i+1; j < n; ++j)
      b[i] -= b[j] * data.value[k++];
    b[i] /= data.value[k++];
  }
  //return b;
}
// find the corresponding eigenvector from the eigenvalue.
// O ( n^3 + M n^2 ) where M is the number of iterations.
//array eigenvector(matrix A, number lambda) {
void eigenvector(double* A, int numrow, double lambda, double* y) {
  double eps =1e-6;
  //const int n = A.size();
  const int n = numrow;
  //array y(n); y[0] = 1;
  //for (int i = 0; i < n; ++i) A[i][i] -= lambda;
  for (int i = 0; i < n; ++i) A[i*n +i] -= lambda;
  LUinfo data = LU_decomposition(A, numrow);
  //number mu, v2, v2s;
  double mu, v2, v2s;
  double v[n];
  y[0] = 1;
  do {
    //array v = LU_backsubstitution(data, y); // A v = y 
    //mu = inner_product(v, y);
    //v2 = inner_product(v, v);
    LU_backsubstitution(data, y, numrow, v); // A v = y 
    mu = dotproduct1_1(v, y, n);
    v2 = dotproduct1_1(v, v, n);
    v2s = sqrt(v2);
    for (int j = 0; j < n; ++j) y[j] = v[j] / v2s;
    
/*
cout << "  in eigenvector() v = " << endl;
for (int j = 0; j < n; ++j){
  cout << v[j] << ", ";
}
cout << endl;
cout << "  in eigenvector() y = " << endl;
for (int j = 0; j < n; ++j){
  cout << y[j] << ", ";
}
cout << endl;
*/
  
  
  //} while (abs(1.0-mu*mu/v2) > eps);
  } while (fabs(1.0-mu*mu/v2) > eps);
  //return y;
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
         0,  1,  0,
         0,  0,  1,
         1,  0,  0};
    double matrix7_3[] ={
         0,  1,  0,
         0,  1,  1,
         0, -1, -1};
    
    int numrow =3;
    double* copy = new double[numrow *numrow];
    for(int i=0; i< numrow *numrow; ++i){
        copy[i] = matrix[i];
    }
    double* temp0;
    double* temp1;
    double* temp2;
    
    //double transformation[numrow *numrow];
    //hessenberg(matrix, numrow, transformation);
    double eigenvalue[numrow];
    double eit[numrow *numrow];
    for(int i=0; i< numrow *numrow; ++i){
        eit[i] =0;
    }
    
    eigenvalues(matrix, numrow, eigenvalue);
    showmatrix(matrix, numrow);
    cout << endl;
    cout << "eigenvalues = ";
    for(int i=0; i< numrow; ++i){
        cout << eigenvalue[i] << " ";
    }
    cout << endl;
    cout << endl;
    
    /*
    for(int i=0; i< numrow; ++i){
        eigenvector(copy, numrow, eigenvalue[i], &eit[i*numrow]);
        cout << "eigenvector = ";
        for(int j=0; j< numrow; ++j){
            cout << eit[i*numrow +j] << " ";
        }
        cout << endl;
        cout << "confirmation of eigenvector => ";
        for(int j=0; j< numrow; ++j){
            double temp =0;
            for(int k=0; k< numrow; ++k){
                temp += copy[j*numrow +k] *eit[i*numrow +k];
            }
            cout << temp /eigenvalue[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */
    /*
    double* eigen = transpose(eit, numrow);
    cout << "eigenvectors =>" << endl;
    showmatrix(eigen, numrow);
    cout << endl;
    cout << "confirmation of transformation matrix =>" << endl;
    temp0 = dotproduct2_2(eigen, eit, numrow);
    showmatrix(temp0, numrow);
    delete [] temp0;
    */
    
    
    /*
    double transformation[numrow *numrow];
    householder(matrix, numrow, transformation);
    
    double eigenvalue[numrow];
    qrmethod(matrix, numrow, eigenvalue);
    
    
    cout << "transformation matrix =>" << endl;
    showmatrix(transformation, numrow);
    cout << endl;
    double* trt = transpose(transformation, numrow);
    cout << "confirmation of transformation matrix =>" << endl;
    temp0 = dotproduct2_2(transformation, trt, numrow);
    showmatrix(temp0, numrow);
    delete [] temp0;
    delete [] trt;
    cout << endl;
    
    
    double* eigen = dotproduct2_2(transformation, matrix, numrow);
    cout << "eigenvectors =>" << endl;
    showmatrix(eigen, numrow);
    cout << endl;
    double* eit = transpose(eigen, numrow);
    cout << "confirmation of eigenvectors matrix =>" << endl;
    temp0 = dotproduct2_2(eigen, eit, numrow);
    showmatrix(temp0, numrow);
    delete [] temp0;
    cout << endl;
    
    cout << "eigenvalues = ";
    for(int i=0; i< numrow; ++i){
        cout << eigenvalue[i] << " ";
    }
    cout << endl;
    cout << endl;
    
    
    
    temp0 = dotproduct2_2(eit, copy, numrow);
    temp1 = dotproduct2_2(temp0, eigen, numrow);
    delete [] temp0;
    cout << "eigenvalues matrix = " << endl;
    showmatrix(temp1, numrow);
    cout << endl;
    
    for(int i=0; i< numrow; ++i){
        temp1[i*(numrow+1)] = 1 /temp1[i*(numrow+1)];
    }
    temp0 = dotproduct2_2(eigen, temp1, numrow);
    delete [] temp1;
    temp1 = dotproduct2_2(temp0, eit, numrow);
    delete [] temp0;
    cout << "inverse matrix = " << endl;
    showmatrix(temp1, numrow);
    cout << endl;
    
    temp0 = dotproduct2_2(copy, temp1, numrow);
    delete [] temp1;
    cout << "confirmation of inverse matrix =>" << endl;
    showmatrix(temp0, numrow);
    delete [] temp0;
    
    
    delete [] copy;
    delete [] eigen;
    delete [] eit;
    */
    
    return 0;
}
//===========================================================
//===========================================================


