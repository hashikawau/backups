#include <stdlib.h>
#include <time.h>
#include <fstream.h>
#include "Tensor2.h"
//#include "Tensor2_operator.h"

/*****************************************************************************/
int random()
{
    static int i = 0;
    
    srand( (unsigned)time(NULL)+i );                //crete random integer
    
    i++;
    return rand();
}
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
class Tensor0
{
    double dt0;
    int n;
public:
    Tensor0(double t=0){ dt0 = t; }
    
    operator double(){ return dt0; }
    Tensor0 &operator=(double d)    { dt0=d;          return *this; }
    Tensor0 &operator=(Tensor0 &T0) { dt0=T0.dt0;     return *this; }
    Tensor0 &operator+=(double d)   { dt0=dt0+d;      return *this; }
    Tensor0 &operator+=(Tensor0 &T0){ dt0=dt0+T0.dt0; return *this; }
    Tensor0 &operator-=(double d)   { dt0=dt0-d;      return *this; }
    Tensor0 &operator-=(Tensor0 &T0){ dt0=dt0-T0.dt0; return *this; }
    Tensor0 &operator*=(double d)   { dt0=dt0*d;      return *this; }
    Tensor0 &operator*=(Tensor0 &T0){ dt0=dt0*T0.dt0; return *this; }
    Tensor0 &operator/=(double d)   { dt0=dt0/d;      return *this; }
    Tensor0 &operator/=(Tensor0 &T0){ dt0=dt0/T0.dt0; return *this; }
    friend istream &operator>>( istream &stream, Tensor0 &T0 );
};
inline istream &operator>>( istream &stream, Tensor0 &T0 )
{
    stream >> T0.dt0;
    return stream;
} 
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class T=double> class Tensor1
{
    T *pT;
    int num;
    
public:
    Tensor1(int n)
    {
        pT = new T;
        newData(n);
    }
    
    Tensor1( char *c, int n=0 )
    {
        pT = new T;
        readData( c, n );
    }
    
    ~Tensor1(){ delete [] pT; }
    
    void newData(int n)
    {
        delete [] pT;
        num = n;
        pT = new T[num];
        cout << "create Tensor1\n";
    }
    
    void readData( char *fileName, int n=0 )
    {
        if( ifstream in( fileName ) )
        {
            if(!n)
            {
                n = 0;
                T tens;
                while( in>> tens ){ n++; }
            }
            
            in.seekg( 0, ios::beg );
            newData(n);
            for( int i=0; i< num; i++ )
            {
                if( !(in >> pT[i]) )
                {
                    cout << "error in Tensor1-reading data\n";
                    break;
                }
            }
            in.close();
        }
        else{ cout << "error in Tensor1-opening file\n"; }
    }
    
    void show()
    {
        for( int i=0; i< num; i++ )
        {
            cout << &pT[i] << endl;
        }
        cout << num << endl << endl;
    }
};
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class T=double> class Tensor2
{
    T **ppT;
    int numRow;
    int numCol;
    int rank;
    static int count;
    
    void delData();
    
public:
    Tensor2();
    Tensor2( int n, int m );
    Tensor2( char *c, int n=0, int m=0 );
    ~Tensor2();

    T& set( int i, int j ){ return ppT[i][j]; }

    friend ostream &operator<<( ostream &stream, Tensor2 &T2 );

    Tensor2 &operator=(Tensor2 &T2);


    Tensor2 operator+(Tensor2 &T2);

    int row(){ return numRow; }
    int col(){ return numCol; }

    void newData( int n, int m );

    void readData( char *fileName, int n=0, int m=0 );

    void zeros( int n=0, int m=0 );

    void ident( int n=0, int m=0 );

    void show( int row=0, int col=0 );

    void multiAdd( double constant, int adding, int added,
               int colBeg, int colEnd );
    void multiply( double constant, int row, int colBeg, int colEnd );
    void multiply( double constant, int row, int col )
    {
        multiply( constant, row, col, col+1 );
    }
    void multiply( double constant, int row )
    {
        multiply( constant, row, 0, numCol );
    }



    void exchange( int row1, int row2, int colBeg, int colEnd );


    void insert( Tensor2 &T2, int x=0, int y=0 );
    void concatCol(Tensor2 &T2){ insert( T2, 0, numCol ); }
    void concatRow(Tensor2 &T2){ insert( T2, numRow, 0 ); }

    void inverse();

    void pick( int rowBeg, int colBeg, int rowEnd, int colEnd );
    void pick( int rowBeg, int colBeg )
    {
        pick( rowBeg, colBeg, numRow-1, numCol-1 );
    }

    int isZero(T t1)
    {
        if( fabs(t1) < 1e-9 ){ return 0; }
        else                 { return 1; }
    }
    void gause();

    int nonsingler()
    {
        if( rank == numRow ){ return 1; }
        else                { return 0; }
    }

    T product( T *pT, int col );

    void solution();


};

int Tensor2<>::count;
ostream &operator<<( ostream &stream, Tensor2<> &T2 )
{
    cout << "row " << T2.numRow;
    cout << "  column " << T2.numCol;
    cout << "  rank " << T2.rank << endl;
    for( int i=0; i< T2.numRow; i++ )
    {
        for( int j=0; j< T2.numCol; j++ )
        {
            cout << T2.ppT[i][j] << " ";
        }
        cout << endl;
    }
    
    return stream;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
inline void gause2()
{    
    int n = 2;
    double A[n][n];
    double b[n];
    double x[n];
    
    A[0][0] = 1;
    A[0][1] = 1;
    A[1][0] = 3;
    A[1][1] = 2;
    b[0]    = 3;
    b[1]    = 7;
    
    double tempA[n][n+1];
    double tempb[n];
    for( int i=0; i< n; i++ )
    {
        tempA[i][n] = b[i];
        for( int j=0; j< n; j++ )
        {
            tempA[i][j] = A[i][j];
        }
    }
    
    for( int i=0; i< n; i++ )
    {
        for( int j=0; j<= n; j++ )
        {
            cout << tempA[i][j] << "  ";
        }
        cout << endl;
    }
    
    for( int i=0; i< n; i++ )
    {   
        if( !tempA[i][i] )
        {
            for( int j=i+1; j<= n; j++ )
            {
                tempA[i][j] /= tempA[i][i];
                for( int x=0; x< i; x++ )
                {
                    tempA[x][j] -= tempA[i][j]*tempA[x][i];
                }
                for( int x=i+1; x< n; x++ )
                {
                    tempA[x][j] -= tempA[i][j]*tempA[x][i];
                }
            }
        }
        else
        {
            
        }
    }
    
    for( int i=0; i< n; i++ )
    {
        tempb[i] = tempA[i][n];
        cout << tempb[i] << endl;
    }
}


