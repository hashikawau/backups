
#include <fstream>
using namespace std;


//===========================================================
//===========================================================
static void SWAP(double& a, double& b);
template<class T>
static T SIGN(T a, T b);
static double pythag(double a, double b);
static void gaussj(double** a, int n, double** b, int m);
static void ludcmp(double** a, int n, int* indx, double& d);
static void lubksb(double** a, int n, int* indx, double** b, int m);
static void tred2(double** a, int n, double* d, double* e);
static void tqli(double* d, double* e, int n, double** z);
static void balanc(double** a, int n);
static void elmhes(double** a, int n);
static void hqr(double** a, int n, double* wr, double* wi);
static void eigvec(double** a, int n, double* x);
static void eigenvector(double** A, int n, double* y);
static void hessenberg(double** a, int n, double** trans);
//===========================================================
//===========================================================
class Matrix
{
private:
    class Vector
    {
    public:
        double* _a;
        int _nrow;
    public:
        Vector(double* a, int numRow);
        ~Vector();
        double operator[](int numRow) const;
        double& operator[](int numRow);
    };
    
public:
    double* _a;
    int _nrow;
    int _ncol;
    
    Matrix(int numRow, int numColumn, double* a);
    void read(ifstream& stream);
    void show(const char* delimiter =" \t");
    
public:
    Matrix();
    Matrix(int numRow, int numColumn);
    ~Matrix();
    Matrix(const Matrix& ref);
    Matrix& operator=(const Matrix& ref);
    Vector operator[](int numRow) const;
    int getLength(int rorc);
    
    
    void copy(int numRow, int numColumn, double* a);
    void copy(int numRow, int numColumn, double** a);
    void zero();
    void identity();
    void transpose();
    void inverse();
    void solveeq(Matrix& mb);
    double determinant();
    
    Matrix eigenvalue();
    Matrix rank();
};
//===========================================================
//===========================================================
Matrix::Vector::Vector(double* a, int numRow):
    _a(a), _nrow(numRow)
{}
Matrix::Vector::~Vector(){}
double Matrix::Vector::operator[](int numRow) const
{
    if(numRow >= _nrow){
        throw int(0);
    }
    return *(_a +numRow);
}
double& Matrix::Vector::operator[](int numRow)
{
    if(numRow >= _nrow){
        throw int(0);
    }
    return *(_a +numRow);
}
//===========================================================
//===========================================================
Matrix operator+(const Matrix& ref1, const Matrix& ref2)
{
    if(ref1._nrow != ref2._nrow || ref1._ncol != ref2._ncol){
        throw int(0);
    }
    double* a = new double[ref1._nrow *ref2._ncol];
    for(int i=0; i< ref1._nrow; ++i){
        for(int j=0; j< ref2._ncol; ++j){
            a[i*ref2._ncol +j] = ref1[i][j] +ref2[i][j];
        }
    }
    return Matrix(ref1._nrow, ref2._ncol, a);
}
Matrix operator-(const Matrix& ref1, const Matrix& ref2)
{
    if(ref1._nrow != ref2._nrow || ref1._ncol != ref2._ncol){
        throw int(0);
    }
    double* a = new double[ref1._nrow *ref2._ncol];
    for(int i=0; i< ref1._nrow; ++i){
        for(int j=0; j< ref2._ncol; ++j){
            a[i*ref2._ncol +j] = ref1[i][j] -ref2[i][j];
        }
    }
    return Matrix(ref1._nrow, ref2._ncol, a);
}
Matrix operator*(double d, const Matrix& ref)
{
    int n = ref._nrow *ref._ncol;
    double* a = new double[n];
    for(int i=0; i< n; ++i){
        a[i] = d *ref._a[i];
    }
    return Matrix(ref._nrow, ref._ncol, a);
}
Matrix operator*(const Matrix& ref, double d)
{
    int n = ref._nrow *ref._ncol;
    double* a = new double[n];
    for(int i=0; i< n; ++i){
        a[i] = d *ref._a[i];
    }
    return Matrix(ref._nrow, ref._ncol, a);
}
Matrix operator/(const Matrix& ref, double d)
{
    int n = ref._nrow *ref._ncol;
    double* a = new double[n];
    for(int i=0; i< n; ++i){
        a[i] = ref._a[i] /d;
    }
    return Matrix(ref._nrow, ref._ncol, a);
}
Matrix operator*(const Matrix& ref1, const Matrix& ref2)
{
    if(ref1._ncol != ref2._nrow){
        throw int(0);
    }
    double* a = new double[ref1._nrow *ref2._ncol];
    for(int i=0; i< ref1._nrow; ++i){
        for(int j=0; j< ref2._ncol; ++j){
            a[i*ref2._ncol +j] = 0;
            for(int k=0; k< ref1._ncol; ++k){
                a[i*ref2._ncol +j] +=
                    ref1._a[i*ref1._ncol +k] *ref2._a[k*ref2._ncol +j];
            }
        }
    }
    return Matrix(ref1._nrow, ref2._ncol, a);
}
//===========================================================
//===========================================================
Matrix::Matrix(int numRow, int numColumn, double* a):
    _nrow(numRow), _ncol(numColumn), _a(a)
{}
void Matrix::read(ifstream& stream)
{
    if(!stream){
        cout << "no such file" << endl;
        return;
    }
    char ch;
    char str[20];
    int count =0;
    int countrow =0;
    int countcol =0;
    while(stream.get(ch)){
        if(ch == '\n'){
            if(count){
                if(countrow < _nrow && countcol < _ncol){
                    str[count] = '\0';
                    _a[countrow *_ncol +countcol] = atof(str);
                }
                /*
                ++countrow;
                if(countrow >= _nrow){
                    break;
                }
                */
            }
            if(count > 0 || countcol > 0){
                ++countrow;
                if(countrow >= _nrow){
                    break;
                }
            }
            count =0;
            countcol =0;
        }else
        if(ch == ' ' || ch == '\t' || ch == ','){
            if(count){
                if(countrow < _nrow && countcol < _ncol){
                    str[count] = '\0';
                    _a[countrow *_ncol +countcol] = atof(str);
                }
                ++countcol;
            }
            count =0;
        }else{
            str[count] = ch;
            ++count;
        }
        
        if(countrow > _nrow){
            break;
        }
    }
    if(count){
        str[count] = '\0';
    }
}
void Matrix::show(const char* delimiter)
{
    cout << "row = " << _nrow << ", ";
    cout << "column = " << _ncol << endl;
    for(int i=0; i< _nrow; ++i){
        for(int j=0; j< _ncol; ++j){
            cout << _a[i*_ncol +j] << delimiter;
        }
        cout << endl;
    }
}
//===========================================================
//===========================================================
Matrix::Matrix():
    _nrow(0), _ncol(0), _a(0)
{}
Matrix::Matrix(int numRow, int numColumn):
    _nrow(numRow),
    _ncol(numColumn),
    _a(new double[numRow *numColumn])
{}
Matrix::~Matrix()
{
    delete [] _a;
    _a =0;
}
Matrix::Matrix(const Matrix& ref):
    _nrow(ref._nrow),
    _ncol(ref._ncol),
    _a(new double[ref._nrow *ref._ncol])
{
    int n = _nrow *_ncol;
    for(int i=0; i< n; ++i){
        _a[i] = ref._a[i];
    }
}
Matrix& Matrix::operator=(const Matrix& ref)
{
    if(this == &ref){
        return *this;
    }
    
    _nrow = ref._nrow;
    _ncol = ref._ncol;
    int n = _nrow *_ncol;
    
    delete [] _a;
    _a = new double[n];
    for(int i=0; i< n; ++i){
        _a[i] = ref._a[i];
    }
    return *this;
}
Matrix::Vector Matrix::operator[](int numRow) const
{
    if(numRow >= _nrow){
        throw int(0);
    }
    return Vector(_a + numRow*_ncol, _ncol);
}
int Matrix::getLength(int rorc)
{
    return rorc <= 0?
        _nrow:
        _ncol;
}
//===========================================================
//===========================================================
void Matrix::copy(int numRow, int numColumn, double* a)
{
    delete [] _a;
    _nrow = numRow;
    _ncol = numColumn;
    
    int n = _nrow *_ncol;
    _a = new double[n];
    for(int i=0; i< n; ++i){
        _a[i] = a[i];
    }
}
void Matrix::copy(int numRow, int numColumn, double** a)
{
    delete [] _a;
    _nrow = numRow;
    _ncol = numColumn;
    
    int n = _nrow *_ncol;
    _a = new double[n];
    for(int i=0; i< _nrow; ++i){
        for(int j=0; j< _ncol; ++j){
            _a[i*_ncol] = a[i][j];
        }
    }
}
//===========================================================
//===========================================================
void Matrix::zero()
{
    int n = _nrow *_ncol;
    for(int i=0; i< n; ++i){
        _a[i] =0;
    }
}
void Matrix::identity()
{
    if(_nrow != _ncol){
        throw int(0);
    }
    int n = _nrow *_ncol;
    for(int i=0; i< n; ++i){
        _a[i] =0;
    }
    for(int i=0; i< _nrow; ++i){
        _a[i *(_nrow +1)] =1;
    }
}
void Matrix::transpose()
{
    double* temp = new double[_nrow *_ncol];
    for(int i=0; i< _nrow; ++i){
        for(int j=0; j< _ncol; ++j){
            temp[j*_nrow +i] = _a[i*_ncol +j];
        }
    }
    delete [] _a;
    _a = temp;
    int t = _nrow;
    _nrow = _ncol;
    _ncol = t;
}
void Matrix::inverse()
{
    if(_a == 0){
        throw int(0);
    }
    if(_nrow != _ncol){
        throw int(0);
    }
    
    
    
    if(_nrow < 10){
        double** a = new double*[_nrow+1];
        for(int i=0; i< _nrow; ++i){
            a[i+1] = _a + i*_nrow -1;
        }
        
        gaussj(a, _nrow, 0, 0);
        
        delete [] a;
    }else{
        double** a = new double*[_nrow+1];
        double** b = new double*[_nrow+1];
        for(int i=0; i< _nrow; ++i){
            a[i+1] = new double[_nrow+1];
            b[i+1] = _a + i*_nrow -1;
            for(int j=0; j< _nrow; ++j){
                a[i+1][j+1] = _a[i*_nrow +j];
                b[i+1][j+1] = 0.;
            }
            b[i+1][i+1] = 1.;
        }
        int* luindex = new int[_nrow+1];
        double d;
        
        ludcmp(a, _nrow, luindex, d);
        lubksb(a, _nrow, luindex, b, _nrow);
        
        for(int i=0; i< _nrow; ++i){
            delete [] a[i+1];
        }
        delete [] a;
        delete [] b;
        delete [] luindex;
    }
    
    
}
void Matrix::solveeq(Matrix& mb)
{
    if(_a == 0){
        throw int(0);
    }
    if(_nrow != _ncol){
        throw int(0);
    }
    if(mb._a == 0){
        throw int(0);
    }
    if(mb._nrow != _nrow){
        throw int(0);
    }
    
    double** a = new double*[_nrow+1];
    double** b = new double*[_nrow+1];
    for(int i=0; i< _nrow; ++i){
        a[i+1] = new double[_nrow+1];
        //a[i+1] = _a + i*_nrow -1;
        b[i+1] = mb._a + i*mb._ncol -1;
        for(int j=0; j< _nrow; ++j){
            a[i+1][j+1] = _a[i*_nrow +j];
        }
    }
    
    if(_nrow < 10){
        gaussj(a, _nrow, b, mb._ncol);
    }else{
        int* luindex = new int[_nrow+1];
        double d;
        ludcmp(a, _nrow, luindex, d);
        lubksb(a, _nrow, luindex, b, mb._ncol);
        delete [] luindex;
    }
    
    for(int i=0; i< _nrow; ++i){
        delete [] a[i+1];
    }
    delete [] a;
    delete [] b;
}
double Matrix::determinant()
{
    if(_a == 0){
        throw int(0);
    }
    if(_nrow != _ncol){
        throw int(0);
    }
    
    double** a = new double*[_nrow+1];
    for(int i=0; i< _nrow; ++i){
        a[i+1] = new double[_nrow+1];
        for(int j=0; j< _nrow; ++j){
            a[i+1][j+1] = _a[i*_nrow +j];
        }
    }
    int* luindex = new int[_nrow+1];
    double d;
    ludcmp(a, _nrow, luindex, d);
    
    for(int i=0; i< _nrow; ++i){
        d *= a[i+1][i+1];
        delete [] a[i+1];
    }
    delete [] a;
    delete [] luindex;
    
    return d;
}
Matrix Matrix::eigenvalue()
{
    if(_a == 0){
        throw int(0);
    }
    if(_nrow != _ncol){
        throw int(0);
    }
    
    int n = _nrow *_nrow;
    double* q = new double[2*n];
    
    double** a = new double*[_nrow+1];
    for(int i=0; i< _nrow; ++i){
        for(int j=0; j< _nrow; ++j){
            q[i*2*_nrow +j] = _a[i*_nrow +j];
            q[i*2*_nrow +_nrow +j] = 0;
        }
        a[i+1] = q + i*2*_nrow -1;
    }
    double* d1 = new double[_nrow+1];
    double* d2 = new double[_nrow+1];
    
    if(0){
        tred2(a, _nrow, d1, d2);
        tqli(d1, d2, _nrow, a);
        
        for(int i=0; i< n; ++i){
            _a[i] = 0;
        }
        for(int i=0; i< _nrow; ++i){
            _a[i*_nrow] = d1[i+1];
        }
    }else{
        balanc(a, _nrow);
        elmhes(a, _nrow);
        //double** trans = new double*[_nrow];
        //for(int i=0; i< _nrow; ++i){
        //    trans[i] = new double[_nrow];
        //}
        //hessenberg(a, _nrow, trans);
        hqr(a, _nrow, d1, d2);
//cout << "after hqr" << endl;
//for(int i=0; i< _nrow; ++i){
//    for(int j=0; j< _nrow; ++j){
//        cout << a[i+1][j+1] << " \t";
//    }
//    cout << endl;
//}
//cout << endl;
        
        delete [] a;
        int n2 = 2*_nrow;
        a = new double*[n2];
        for(int i=0; i< n2; ++i){
            a[i] = new double[n2];
        }
        
        for(int i=0; i< _nrow; ++i){
            if(d2[i+1] == 0.){
                double* x = new double[_nrow];
                for(int k=0; k< _nrow; ++k){
                    for(int j=0; j< _nrow; ++j){
                        a[k][j] = _a[k*_nrow +j];
                    }
                    a[k][k] -= d1[i+1];
                }
                
                eigvec(a, _nrow, x);
                //eigenvector(a, _nrow, x);
                
                for(int k=0; k< _nrow; ++k){
                    q[k*2*_nrow +i] = x[k];
                    q[k*2*_nrow +_nrow +i] = 0;
                }
                delete [] x;
            }else{
                double* x = new double[n2];
                for(int k=0; k< _nrow; ++k){
                    for(int j=0; j< _nrow; ++j){
                        a[k][j] = _a[k*_nrow +j];
                        a[_nrow +k][_nrow +j] = _a[k*_nrow +j];
                        a[k][_nrow +j] = 0;
                        a[_nrow +k][j] = 0;
                    }
                    a[k][k] -= d1[i+1];
                    a[_nrow +k][_nrow +k] -= d1[i+1];
                    a[k][_nrow +k] += d2[i+1];
                    a[_nrow +k][k] += -d2[i+1];
                }
                
                eigvec(a, n2, x);
                //eigenvector(a, n2, x);
                
                for(int k=0; k< _nrow; ++k){
                    q[k*2*_nrow +i] = x[k];
                    q[k*2*_nrow +_nrow +i] = x[_nrow +k];
                }
                delete [] x;
            }
        }
        
        
        for(int i=0; i< _nrow; ++i){
            _a[i*_nrow] = d1[i+1];
            _a[i*_nrow+1] = d2[i+1];
            
            for(int j=2; j< _nrow; ++j){
                _a[i*_nrow +j] =0;
            }
        }
        
        for(int i=0; i< n2; ++i){
            delete [] a[i];
        }
    }
    
    delete [] a;
    delete [] d1;
    delete [] d2;
    
    return Matrix(_nrow, 2*_nrow, q);
}
//===========================================================
//===========================================================
Matrix Matrix::rank()
{
    if(_a == 0){
        throw int(0);
    }
    
    int n = _nrow *_ncol;
    double* q = new double[n];
    
    double** a = new double*[_nrow];
    for(int i=0; i< _nrow; ++i){
        for(int j=0; j< _ncol; ++j){
            q[i*_ncol +j] = _a[i*_ncol +j];
        }
        a[i] = q + i*_ncol;
    }
    
    
    eigvec(a, _nrow, 0);
    
    delete [] a;
    
    return Matrix(_nrow, _ncol, q);
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
static void SWAP(double& a, double& b)
{
    double temp = a;
    a = b;
    b = temp;
}
template<class T>
static T SIGN(T a, T b)
{
    a = a >= 0?
        a:
        -a;
    return b >= 0.?
        a:
        -a;
}
static double pythag(double a, double b)
{
    return sqrt(a*a +b*b);
}
//===========================================================
//===========================================================
static void gaussj(double** a, int n, double** b, int m)
{
    int *indxc, *indxr, *ipiv;
    int i, j, k, p, pp;
    int icol, irow;
    double big, dum, pivinv, temp;
    
    indxc = new int[n+1];
    indxr = new int[n+1];
    ipiv = new int[n+1];
    
    for(j=1; j<=n; ++j) ipiv[j] =0;
    for(i=1; i<=n; ++i){
        big =0.;
        for(j=1; j<=n; ++j)
            if(ipiv[j] != 1)
                for(k=1; k<=n; ++k){
                    if(ipiv[k] == 0){
                        if(fabs(a[j][k]) >= big){
                            big = fabs(a[j][k]);
                            irow =j;
                            icol =k;
                        }
                    }else
                    if(ipiv[k] > 1) throw int(0);
                }
        ++(ipiv[icol]);
        
        if(irow != icol){
            for(p=1; p<=n; ++p) SWAP(a[irow][p], a[icol][p]);
            for(p=1; p<=m; ++p) SWAP(b[irow][p], b[icol][p]);
        }
        
        indxr[i] =irow;
        indxc[i] =icol;
        if(a[icol][icol] == 0.) throw int(0);
        
        pivinv = 1. /a[icol][icol];
        a[icol][icol] =1.;
        for(p=1; p<=n; ++p) a[icol][p] *= pivinv;
        for(p=1; p<=m; ++p) b[icol][p] *= pivinv;
        
        for(pp=1; pp<=n; ++pp)
            if(pp != icol){
                dum = a[pp][icol];
                a[pp][icol] =0.;
                for(p=1; p<=n; ++p) a[pp][p] -= a[icol][p] *dum;
                for(p=1; p<=m; ++p) b[pp][p] -= b[icol][p] *dum;
            }
    }
    
    for(p=n; p>=1; --p){
        if(indxr[p] != indxc[p])
            for(k=1; k<=n; ++k)
                SWAP(a[k][indxr[p]], a[k][indxc[p]]);
    }
    
    delete [] indxc;
    delete [] indxr;
    delete [] ipiv;
}
//===========================================================
//===========================================================
static void ludcmp(double** a, int n, int* indx, double& d)
{
    const double TINY =1.0e-20;
    int i, j, k;
    int imax;
    double big, dum, sum, temp;
    double* vv = new double[n+1];
    d =1;
    
    for(i=1; i<=n; ++i){
        big =0.;
        for(j=1; j<=n; ++j)
            if((temp = fabs(a[i][j])) > big) big =temp;
        if(big == 0.) throw int(0);
        vv[i] =1. /big;
    }
    for(j=1; j<=n; ++j){
        for(i=1; i< j; ++i){
            sum = a[i][j];
            for(k=1; k< i; ++k) sum -= a[i][k] *a[k][j];
            a[i][j] = sum;
        }
        big =0.;
        
        for(i=j; i<=n; ++i){
            sum = a[i][j];
            for(k=1; k< j; ++k) sum -= a[i][k] *a[k][j];
            a[i][j] = sum;
            if((dum = vv[i] *fabs(sum)) >= big){
                big = dum;
                imax = i;
            }
        }
        
        if(j != imax){
            for(k=1; k<=n; ++k){
                dum = a[imax][k];
                a[imax][k] = a[j][k];
                a[j][k] = dum;
            }
            d = -(d);
            vv[imax] = vv[j];
        }
        indx[j] =imax;
        if(a[j][j] == 0.) a[j][j] =TINY;
        if(j != n){
            dum = 1. /(a[j][j]);
            for(i= j+1; i<=n; ++i) a[i][j] *= dum;
        }
    }
    
    delete [] vv;
}
static void lubksb(double** a, int n, int* indx, double** b, int m)
{
    int i, j;
    int ip;
    int ii =0;
    double sum;
    
    for(int k=1; k<=m; ++k){
        ii =0;
        for(i=1; i<=n; ++i){
            ip =indx[i];
            sum =b[ip][k];
            b[ip][k] =b[i][k];
            if(ii)
                for(j=ii; j<= i-1; ++j) sum -= a[i][j] *b[j][k];
            else if(sum)
                ii=i;
            b[i][k] =sum;
        }
        for(i=n; i>=1; --i){
            sum = b[i][k];
            for(j= i+1; j<=n; ++j) sum -= a[i][j] *b[j][k];
            b[i][k] = sum /a[i][i];
        }
    }
}
//===========================================================
//===========================================================
static void tred2(double** a, int n, double* d, double* e)
{
    int i, j, k, p;
    double scale, hh, h, g, f;
    
    for(i=n; i>=2; --i){
        p =i-1;
        h = scale =0.;
        
        if(p >1){
            for(k=1; k<=p; ++k)
                scale += fabs(a[i][k]);
            
            if(scale == 0.)
                e[i] =a[i][p];
            else{
                for(k=1; k<= p; ++k){
                    a[i][k] /= scale;
                    h += a[i][k] *a[i][k];
                }
                
                f = a[i][p];
                g = (f>= 0.? -sqrt(h): sqrt(h));
                e[i] = scale *g;
                h -= f *g;
                a[i][p] = f -g;
                f =0.;
                
                for(j=1; j<= p; ++j){
                    a[j][i] = a[i][j] /h;
                    g =0.;
                    for(k=1; k<=j; ++k)
                        g += a[j][k] *a[i][k];
                    for(k= j+1; k<= p; ++k)
                        g += a[k][j] *a[i][k];
                    e[j] = g /h;
                    f += e[j] *a[i][j];
                }
                
                hh = f /(h +h);
                for(j=1; j<= p; ++j){
                    f = a[i][j];
                    e[j] = g = e[j] -hh *f;
                    for(k=1; k<=j; ++k)
                        a[j][k] -= (f *e[k] +g *a[i][k]);
                }
            }
        }else
            e[i] = a[i][p];
        
        d[i] =h;
    }
    
    d[1] =0.;
    e[1] =0.;
    
    for(i=1; i<=n; ++i){
        p = i-1;
        
        if(d[i]){
            for(j=1; j<=p; ++j){
                g =0.;
                
                for(k=1; k<=p; ++k)
                    g += a[i][k] *a[k][j];
                for(k=1; k<=p; ++k)
                    a[k][j] -= g *a[k][i];
            }
        }
        
        d[i] = a[i][i];
        a[i][i] =1.;
        for(j=1; j<= p; ++j) a[j][i] = a[i][j] =0.;
    }
}
static void tqli(double* d, double* e, int n, double** z)
{
    int i, j, k, m;
    int iter;
    double s, r, p, g, f, dd, c, b;
    
    for(i=2; i<=n; ++i) e[i-1] =e[i];
    e[n] =0.;
    
    for(j=1; j<=n; ++j){
        iter =0;
        do{
            for(m=j; m<= n-1; ++m){
                dd = fabs(d[m]) +fabs(d[m+1]);
                if(fabs(e[m]) +dd == dd) break;
            }
            
            if(m != j){
                if(iter++ == 30) throw int(0);
                
                g = (d[j+1] -d[j]) /(2. *e[j]);
                r =pythag(g, 1.);
                g = d[m] -d[j] +e[j] /(g +SIGN(r, g));
                s =c =1.;
                p =0.;
                
                for(i= m-1; i>= j; --i){
                    f = s *e[i];
                    b = c *e[i];
                    e[i+1] = (r =pythag(f, g));
                    if(r == 0.){
                        d[i+1] -= p;
                        e[m] =0.;
                        break;
                    }
                    
                    s = f /r;
                    c = g /r;
                    g = d[i+1] -p;
                    r = (d[i] -g) *s +2. *c *b;
                    d[i+1] = g +(p =s*r);
                    g = c*r -b;
                    for(k=1; k<=n; ++k){
                        f =z[k][i+1];
                        z[k][i+1] = s *z[k][i] + c*f;
                        z[k][i] = c*z[k][i] - s*f;
                    }
                }
                
                if(r == 0. && i>=j) continue;
                
                d[j] -= p;
                e[j] =g;
                e[m] =0.;
            }
            
        }while(m != j);
    }
}
//===========================================================
//===========================================================
static void balanc(double** a, int n)
{
    const double RADIX =2.;
    int i, j, last;
    double c, f, g, r, s, sqrdx;
    
    sqrdx = RADIX *RADIX;
    last =0;
    while(last == 0){
        last =1;
        for(i=1; i<=n; ++i){
            r = c =0.;
            for(j=1; j<=n; ++j)
                if(j != i){
                    c += fabs(a[j][i]);
                    r += fabs(a[i][j]);
                }
            
            if(c && r){
                g = r /RADIX;
                f =1.;
                s = c +r;
                while(c < g){
                    f *= RADIX;
                    c *= sqrdx;
                }
                g = r *RADIX;
                while(c > g){
                    f /= RADIX;
                    c /= sqrdx;
                }
                if((c +r) /f < 0.95 *s){
                    last =0;
                    g = 1. /f;
                    for(j=1; j<=n; ++j) a[i][j] *= g;
                    for(j=1; j<=n; ++j) a[j][i] *= f;
                }
            }
        }
    }
}
static void elmhes(double** a, int n)
{
    int i, j, m;
    double x, y;
    
    for(m=2; m< n; ++m){
        x =0.;
        i =m;
        for(j=m; j<=n; ++j){
            if(fabs(a[j][m-1]) > fabs(x)){
                x = a[j][m-1];
                i = j;
            }
        }
        
        if(i != m){
            for(j= m-1; j<= n; ++j) SWAP(a[i][j], a[m][j]);
            for(j=1; j<= n; ++j) SWAP(a[j][i], a[j][m]);
        }
        
        if(x != 0.){
            for(i= m+1; i<=n; ++i){
                if((y =a[i][m-1]) != 0.){
                    y /= x;
                    a[i][m-1] =y;
                    for(j=m; j<=n; ++j) a[i][j] -= y *a[m][j];
                    for(j=1; j<=n; ++j) a[j][m] += y *a[j][i];
                }
            }
        }
    }
}
static int IMAX(int a, int b)
{
    return a > b?
        a:
        b;
}
static void hqr(double** a, int n, double* wr, double* wi)
{
    int i, j, k, m, o;
    int its, mmin, nn;
    double x, y, z;
    double u, v, w;
    double p, q, r, s, t;
    double anorm;
    
    anorm =0.;
    for(i=1; i<=n; ++i)
        for(j= IMAX(i-1, 1); j<=n; ++j)
            anorm += fabs(a[i][j]);
    
    nn =n;
    t =0.;
    while(nn >= 1){
        its =0;
        do{
            for(o=nn; o>=2; --o){
                s = fabs(a[o-1][o-1]) +fabs(a[o][o]);
                if(s == 0.) s =anorm;
                if(fabs(a[o][o-1]) +s == s) break;
            }
            
            x =a[nn][nn];
            if(o == nn){
                wr[nn] = x +t;
                wi[nn--] =0.;
            }else{
                y = a[nn-1][nn-1];
                w = a[nn][nn-1] *a[nn-1][nn];
                
                if(o == nn-1){
                    p = 0.5 *(y -x);
                    q = p*p +w;
                    z = sqrt(fabs(q));
                    x += t;
                    
                    if(q >= 0.){
                        z = p +SIGN(z, p);
                        wr[nn-1] = wr[nn] = x +z;
                        if(z) wr[nn] = x - w/z;
                        wi[nn-1] = wi[nn] = 0.;
                    }else{
                        wr[nn-1] = wr[nn] = x +p;
                        wi[nn-1] = -(wi[nn] = z);
                    }
                    
                    nn -= 2;
                }else{
                    if(its == 30) throw int(0);
                    if(its == 10 || its == 20){
                        t += x;
                        for(i=1; i<=nn; ++i) a[i][i] -= x;
                        s = fabs(a[nn][nn-1]) +fabs(a[nn-1][nn-2]);
                        y =x = 0.75 *s;
                        w = -0.4375 *s *s;
                    }
                    
                    ++its;
                    for(m= nn-2; m>=o; --m){
                        z =a[m][m];
                        r = x -z;
                        s = y -z;
                        p = (r*s -w) /a[m+1][m] + a[m][m+1];
                        q = a[m+1][m+1] -z -r -s;
                        r = a[m+2][m+1];
                        s = fabs(p) +fabs(q) +fabs(r);
                        p /=s;
                        q /=s;
                        r /=s;
                        if(m == o) break;
                        u = fabs(a[m][m-1]) *(fabs(q) +fabs(r));
                        v = fabs(p) *(
                            fabs(a[m-1][m-1])
                            + fabs(z)
                            + fabs(a[m+1][m+1]));
                        
                        if(u+v == v) break;
                    }
                    
                    for(i= m+2; i<=nn; ++i){
                        a[i][i-2] =0.;
                        if(i != m+2) a[i][i-3] =0.;
                    }
                    
                    for(k=m; k<= nn-1; ++k){
                        if(k != m){
                            p =a[k][k-1];
                            q =a[k+1][k-1];
                            r =0.;
                            if(k != nn-1) r =a[k+2][k-1];
                            if((x = fabs(p) +fabs(q) +fabs(r)) != 0.){
                                p /= x;
                                q /= x;
                                r /= x;
                            }
                        }
                        if((s = SIGN(sqrt(p*p +q*q +r*r), p)) != 0.){
                            if(k == m){
                                if(o != m)
                                    a[k][k-1] = -a[k][k-1];
                            }else
                                a[k][k-1] = -s *x;
                            
                            p += s;
                            x = p /s;
                            y = q /s;
                            z = r /s;
                            q /= p;
                            r /= p;
                            
                            for(j=k; j<=nn; ++j){
                                p = a[k][j] + q *a[k+1][j];
                                if(k != nn-1){
                                    p += r *a[k+2][j];
                                    a[k+2][j] -= p *z;
                                }
                                a[k+1][j] -= p*y;
                                a[k][j] -= p*x;
                            }
                            mmin = nn < k+3? nn: k+3;
                            for(i=o; i<=mmin; ++i){
                                p = x *a[i][k] + y *a[i][k+1];
                                if(k != nn-1){
                                    p += z *a[i][k+2];
                                    a[i][k+2] -= p*r;
                                }
                                a[i][k+1] -= p*q;
                                a[i][k] -= p;
                            }
                        }
                    }
                }
            }
        }while(o < nn-1);
    }
}
//===========================================================
//===========================================================
static void eigvec(double** a, int n, double* x)
{
    
    int indexfree =n;
    for(int k=0; k<n; ++k){
//cout << "\n\nin eigvec befor " << k << endl;
//for(int i=0; i< n; ++i){
//    for(int j=0; j< n; ++j){
//        cout << a[i][j] << " \t";
//    }
//    cout << endl;
//}
//cout << endl;
        
        
        
        
        double max = 0.;
        int index = k;
        for(int i=k; i<n; ++i){
            double temp = fabs(a[i][k]);
            if(temp > max){
                max = temp;
                index = i;
            }
        }
        
        if(max < 1e-10){
            indexfree = k;
            a[k][index] = 0;
            continue;
        }
        
        if(index != k){
            for(int j=0; j<n; ++j){
                SWAP(a[index][j], a[k][j]);
            }
        }
        
        //a[k][k] =1;
        //for(int j= k+1; j<n; ++j){
        max = a[k][k];
        for(int j= k; j<n; ++j){
            a[k][j] /= max;
        }
        
        for(int i=0; i<n; ++i){
            if(i != k){
                double temp = a[i][k];
                //a[i][k] = 0;
                //for(int j= k+1; j<n; ++j){
                for(int j= k; j<n; ++j){
                    a[i][j] -= temp *a[k][j];
                }
            }
        }
    }
    
    if(x == 0){
        return;
    }
    
    for(int i=0; i<n; ++i){
        x[i] = -a[i][indexfree];
    }
    x[indexfree] = 1;
    double norm = 0.;
    for(int i=0; i<n; ++i){
        norm += x[i]*x[i];
    }
    norm = sqrt(norm);
    for(int i=0; i<n; ++i){
        x[i] /= norm;
    }
    
    
    
/*
cout << "\n\nin eigvec  " << endl;
for(int i=0; i< n; ++i){
    for(int j=0; j< n; ++j){
        cout << a[i][j] << " \t";
    }
    cout << endl;
}
cout << endl;

cout << "\n\nin eigvec vector " << endl;
for(int i=0; i< n; ++i){
    cout << x[i] << " \t";
    cout << endl;
}
cout << endl;
*/
    
    
    
}
void eigenvector(double** A, int n, double* y)
{
    const double EPS =1e-9;
    for(int i=1; i< n; ++i){
        y[i] =0;
    }
    y[0] = 1;
    
    //LUinfo data = LU_decomposition(A);
    double** a = new double*[n+1];
    double** v = new double*[n+1];
    for(int i=0; i< n; ++i){
        a[i+1] = A[i] -1;
        v[i+1] = new double[2];
        v[i+1][1] = y[i];
    }
    int* luindex = new int[n+1];
    double d;
    
    ludcmp(a, n, luindex, d);
    
    double mu, v2, v2s;
    do {
        //array v = LU_backsubstitution(data, y); // A v = y 
        for(int i=0; i< n; ++i){
            v[i+1][1] = y[i];
        }
        lubksb(a, n, luindex, v, 1);
        
        //mu = inner_product(v, y);
        //v2 = inner_product(v, v);
        mu = 0;
        v2 = 0;
        for(int i=0; i< n; ++i){
            mu += v[i+1][1] *y[i];
            v2 += v[i+1][1] *v[i+1][1];
        }
        v2s = sqrt(v2);
        
        for (int i=0; i< n; ++i){
            y[i] = v[i+1][1] / v2s;
        }
    }while(fabs(1.0-mu*mu/v2) > EPS);
    
    for(int i=0; i< n; ++i){
        delete v[i+1];
    }
    delete [] a;
    delete [] v;
    delete [] luindex;
}
//===========================================================
//===========================================================
/*
void hessenberg(Matrix& A) {
    const int n = A.size();
    for (int k = 1; k <= n-2; ++k) {
        array u(n);
        for (int i = k; i < n; ++i) u[i] = A[i][k-1];
    
        number ss = 0;
        for (int i = k+1; i < n; ++i) ss += u[i] * u[i];
        if (abs(ss) <= 0.0) continue;
        number s = sqrt( ss + u[k]*u[k] );
        if (u[k] > 0.0) s = -s;
    
        u[k] -= s;
        number uu = sqrt( ss + u[k]*u[k] );
        for (int i = k; i < n; ++i) u[i] /= uu;
    
        array f(n), g(n);
        for (int i = 0; i < n; ++i)
          for (int j = k; j < n; ++j)
            f[i] += A[i][j] * u[j],
            g[i] += A[j][i] * u[j];
        number gamma = inner_product(u, g);
        for (int i = 0; i < n; ++i)
          f[i] -= gamma * u[i],
          g[i] -= gamma * u[i];
    
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < n; ++j)
            A[i][j] = A[i][j] - 2*u[i]*g[j] - 2*f[i]*u[j];
    }
}
*/
void hessenberg(double** a, int n, double** trans)
{
    double* u = new double[n];
    double** P = new double*[n];
    for(int i=0; i< n; ++i){
        P[i] = new double[n];
        for(int j=0; j< n; ++j){
            trans[i][j] =0.;
        }
        trans[i][i] =1.;
    }
    
    for(int k=1; k< n-1; ++k){
        
        
        
        
    }
}


void eigenvector(Matrix& A, Matrix& trans)
{
    Matrix copy =A;
    
    int n = A.getLength(0);
    //Matrix trans(n, n);
    trans = Matrix(n, n);
    trans.identity();
    
    for(int k=0; k< n-2; ++k){
    //for(int k=0; k< 1; ++k){
        Matrix u(n, 1);
        u.zero();
        double sigma =0;
        for(int i= k+1; i< n; ++i){
            u[i][0] = A[i][k];
            sigma += u[i][0] *u[i][0];
        }
        sigma = sqrt(sigma);
        u[k+1][0] += u[k+1][0] >0.?
            sigma:
            -sigma;
        
        
        double H =0;
        for(int i= k+1; i< n; ++i){
            H += u[i][0] *u[i][0];
        }
        H /= 2;
        
        
        Matrix ut = u;
        ut.transpose();
        Matrix P(n, n);
        P.identity();
        P = P - u * ut /H;
        
        A = P *A *P;
        
        trans = trans *P;
        
    }
    
    //A.show();
    
    int count =0;
    while(count <100){
        Matrix Q(n, n);
        Q.identity();
        
        for(int k=0; k< n-1; ++k){
            Matrix u(n, 1);
            u.zero();
            double sigma =0;
            for(int i= k; i< n; ++i){
                u[i][0] = A[i][k];
                sigma += u[i][0] *u[i][0];
            }
            sigma = sqrt(sigma);
            u[k][0] += u[k][0] >0.?
                sigma:
                -sigma;
            
            
            double H =0;
            for(int i= k; i< n; ++i){
                H += u[i][0] *u[i][0];
            }
            H /= 2;
            
            
            Matrix ut = u;
            ut.transpose();
            Matrix P(n, n);
            P.identity();
            P = P - u *ut /H;
            //P.show();
            
            A = P *A;
            
            Q = Q *P;
            
            //cout << "    count = " << k << endl;
            //A.show();
            //Q.show();
        }
        
        
        //A.show();
        //Q.show();
        /*
    Matrix Qt =Q;
    Qt.transpose();
    (Qt*A).show();
        */
        
        A = A *Q;
        
        Matrix I(n, n);
        I.identity();
        A = A -A[n-1][n-1] *I;
        //A.show();
        
        
        //trans = Q *trans;
        trans = trans *Q;
        
        ++count;
    }
    
    
    
    Matrix Qt =trans;
    Qt.transpose();
    //(Qt*trans).show();
    //(Qt*copy*trans).show();
    
    
    
    
}


