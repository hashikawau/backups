#include <iostream.h>
#include <typeinfo.h>
#include "header\tens2_header.h"

template<class T> class tt
{
    T itt;
    static tt<T>* ptt;
    static int numtt;
public:
    tt()
    {
        itt = 5;
        if( !numtt )
        {
            numtt++;
            ptt = new tt [3];
        }
    }
    
    void show(T n)
    {
        
        for( int i=0; i< 3; i++ )
        {
            cout << ptt[i].itt;
            ptt[i].itt += n;
        }
        cout << "  ";
        for( int i=0; i< 3; i++ )
        {
            cout << ptt[i].itt;
        }
        cout << endl;
        
    }
    
    
    template<class T, class T2>
    friend tt<T>& operator+( tt<T>& tt1, T2 t2val );
    
    template<class T>
    friend tt<T>& operator+( int i, tt<T>& tt1 );
    
    template<class T>
    friend ostream& operator<<( ostream& stream, tt<T>& tt1 );
    
    template<class T>
    friend T f(tt<T>& tt1);
};
template<class T>
tt<T>* tt<T>::ptt;

template<class T>
int tt<T>::numtt;

template<class T>
T f( tt<T>& tt1 ){ return tt1.itt; }

template<class T, class T2>
tt<T>& operator+( tt<T>& tt1, T2 t2val )
{   
    tt1.itt += (T)t2val;
    return tt1;
}

template<class T>
tt<T>& operator+( int i, tt<T>& tt1 )
{   
    tt1.itt += i;    
    return tt1;
}

template<class T>
ostream& operator<<( ostream& stream, tt<T>& tt1 )
{
    cout << tt1.itt;
    return stream;
}

int g()
{
    int n = 8;
    int* pn;
    int** ppn;
    
    pn = new int [3];
    cout << pn << "  ";
    
    ppn = new int* [3];
    cout << ppn << "  ";
    
    for( int i=0; i< 3; i++ )
    {
        ppn[i] = &pn[i];
        cout << ppn[i] << "  ";
    }
    
    cout << endl;
    
    delete [] ppn;
    delete [] pn;
    
    return n;
}

int main()
{    
    /*
    Matrix<int> dm;
    //Matrix<int> dm2;
    dm.readMatrix("datatens", 4, 4);
    //dm2.readMatrix("datatens2", 4, 4);
    
    cout << dm[0];
    cout << dm;
    dm = dm(0,0,4,4)=dm(0,0,2,2);
    cout << dm;
    
    //cout << dm;
    //cout << dm2+2+3+3+2;
    //cout << dm2*2;
    //dm%=0.3;
    //cout << dm[0];
    //cout << dm2(0);
    
    //dm(0) = dm(1);
    
    //cout << dm*2;
    //cout << dm2(0);
    //cout << 2.0*dm;
    */
    
    /*
    tt<int> t1;
    cout << t1 << endl;
    4+t1;
    cout << t1 << endl;
    cout << f(t1);
    */
    
    int* ppi[4];
    int* pi;
    
    for( int j=0; j< 3; j++ )
    {
        cout << "\npi\n";
        for( int i=0; i< 4; i++ )
        {
            pi = new int [5];
            for( int k=0; k< 5; k++ )
            {
                cout << &pi[k] << "  ";
            }
            ppi[i] = pi;
            cout << endl;
        }
        cout << "\nppi\n";
        for( int i=0; i< 4; i++ )
        {
            //cout << ppi[i] << "  " << *ppi[i] << endl;
            delete ppi[i];
        }
    }
    
    return 0;
}

