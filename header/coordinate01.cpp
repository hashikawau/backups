#include <math.h>
#include <iostream.h>
#include <iomanip.h>

template<class T=double> class Vector
{
protected:
    T aVector[2];
    T aIni[2];
    int degrees;//0.00 - 360 : 36000
    
public:
    Vector( T t0 = 0, T t1 = 0 )
    {
        aVector[0] = aIni[0] = t0;
        aVector[1] = aIni[1] = t1;
        degrees = 0;
    }
    
    void rotation(double deg)
    {
        degrees += (int)(100*deg);
        degrees %= 36000;
        long double rad = M_PI*degrees/18000;
        aVector[0] = aIni[0]*cos(rad) - aIni[1]*sin(rad);
        aVector[1] = aIni[0]*sin(rad) + aIni[1]*cos(rad);
    }
    
    void translation( T t0, T t1 )
    {
        aVector[0] += t0;
        aVector[1] += t1;
    }
    void translation( Vector ax )
    {
        translation( ax.aVector[0], ax.aVector[1] );
    }
    
    void show()
    {
        cout << aVector[0] << endl;
        cout << aVector[1] << endl;
    }
};

template<class T=double> class Coordinate
{
    Vector<T> aAxis[2];
    
public:
    
    Coordinate( T t00, T t01, T t10, T t11 )
    {
        aAxis[0] = Vector<T>( t00, t01 );
        aAxis[1] = Vector<T>( t10, t11 );
    }
    
    ~Coordinate()
    {
        cout << "destractor\n";
    }
    
    void rotation(long double deg)
    {
        aAxis[0].rotation(deg);
        aAxis[1].rotation(deg);
    }
    
    void show()
    {
        cout << "aAxis[0]: " << endl;
        aAxis[0].show();
        cout << "aAxis[1]: " << endl;
        aAxis[1].show();
    }
};

int main()
{
    /*
    Vector<> e1(1, 0);
    Vector<> e2(1, 0);
    e1.show();
    e1.translation(e2);
    e1.show();
    e1.rotation(720);
    e1.show();
    e1.rotation(90);
    e1.show();
    e1.rotation(90);
    e1.show();
    e1.rotation(90);
    e1.show();
    e1.rotation(90);
    e1.show();
    e1.rotation(90);
    e1.show();
    e1.rotation(90);
    e1.show();
    e1.rotation(90);
    e1.show();
    */
    
    /*
    int m = 3;
    int n = 4;
    int p = 2;
    int i, j, k;
    int **a, **b, **c;
    a = new int *[m];
    for( i=0; i<m; i++ )
    {
        a[i] = new int [p];
        for( j=0; j<p; j++ )
        {
            a[i][j] = i+j;
            cout << &a[i][j] << endl;
        }
        delete a[i];
    }
    delete a;
    a = new int *[m];
    for( i=0; i<m; i++ )
    {
        a[i] = new int [p];
        for( j=0; j<p; j++ )
        {
            cout << &a[i][j] << endl;
        }
        delete a[i];
    }
    delete a;
    */
    /*
    int *a;
    a = new int;
    *a = 9;
    cout << a << "  " << *a << endl;
    delete [] a;
    */
    
    /*
    char c = 'v';
    wchar_t wc = '‚ ';
    cout << wc << endl;
    */
    
    
    Coordinate<> *a1;
    a1 = new Coordinate<>( 1.5, 0, 0, 1 );
    a1->show();
    a1->rotation(180);
    a1->show();
    delete a1;
    cout << "finished\n";
    
    
    return 0;
}