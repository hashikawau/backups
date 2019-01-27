#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <new.h>
#include <typeinfo.h>
#include <math.h>
#include <vector>
#define NOMINMAX
//#include <windows.h>
//#define NOMINMAX
#undef max

#include <windows.h>
#include "header\tensor2.h"

#include "01_12_header.h"
//#include "old\tens2.h"
//#include "old\tens2_header.h"
//#include "old\storage.h"
using namespace std;


class matbase
{
public:
    int matint;
    int matint2;
};
static Storage<matbase*> storMat;

template<class T> class mat :public matbase
{
    T matT;
    Storage<mat*>* stor;
    
public:
    mat()
    {
        cout << "Con\n";
        stor = NULL;
    }
    ~mat()
    {
        cout << "DEC\n";
        if(stor)
        {
            cout << stor << endl;
            delete stor;
        }
    }
    void make()
    {
        if(!stor)
        {
            stor = new Storage<mat*>;
        }
        mat* tempmat;
        tempmat = new mat;
        cout << stor << "  " << tempmat << endl;
        stor->putItem(tempmat);
        //stor->show();
    
    }
};


enum { a, b, c } alp;

template<class T>
void f(T* pT)
{
    delete pT;
}

template<class T>
void g(T* pT)
{
    pT = new T;
    cout << pT << endl;
    
    Storage<T*> stor;
    stor.putItem(pT);
    //stor.disposeItems();

}

template<class T> class MM
{
public:
    MM(T in=0,char* ch="")
    {
        cout << "ch  ";
        cout << in;
        cout << endl;
        cout << ch;
        cout << endl;
    }
    
    ~MM()
    {
        cout << "destructor\n";
    }
    
};
long double ex(long double );
long double sn(long double );
long double cs(long double );
template<class T>
void showbit(T tbit)
{
    const int numbit = 8 *sizeof(tbit);
    char strbit[64];
    int k = 0;
    
    cout << typeid(tbit).name() << "  " << tbit << endl;
    
    for( int i=0; i< sizeof(tbit); i++ )
    {
        for( int j=0; j< 8; j++ )
        {
            switch(tbit & 0x01)
            {
                case 1:
                    strbit[k] = '1';
                    break;
                
                case 0:
                    strbit[k] = '0';
                    break;
                
                default:
                    break;
            }
            
            k++;
            tbit >>= 1;
        }
        
        strbit[k] = ' ';
        k++;
    }
    
    for( ; k> 0; k--)
    {
        cout << strbit[k-1];
    }
}
void tens2f(tens2* te)
{
    cout << typeid(te[2]).name();
}

int xyz =56;

class ijk
{
    static int numTotal;
public:
    int xyz;
    ijk()
    {
        ijk::numTotal++;
        cout << ijk::numTotal << endl;
        xyz = 9;
        //cout << xyz;
    }
};
int main()
{
    ijk iijjkk[3];
    
    /*
    cout << xyz;
    ijk ijkk;
    cout << xyz;
    
    double a = 1e-20;
    double b = 0;
    
    for( int i=0; i< 10000; i++ )
    {
        a+=b;
    }
    cout << a << endl;
    cout << b << endl;

    cout.precision(20);
    Tensor2<double> tenten1(1,1);
    tenten1 = 1;
    cout << (atan(tenten1)*180/M_PI) << endl;
    tenten1 = 1/1.7320504;
    cout << atan(tenten1)*180/M_PI ;
    
    
    double pi = M_PI;
    tenten1 = 1e-10;
    for(int i=-50; i< 50; i++ )
    {
        cout << tenten1(1,1);
        cout << endl;
    }
    */
    
    /*
    int     ipd1;
    double* pd1;
    pd1 = new double;
    ipd1 = (int)pd1;
    cout.setf(ios::dec);
    cout << (int)pd1 << endl;
    cout << ((ipd1>>16) & 0xFFFF) << endl;
    cout << (ipd1 & 0xFFFF) << endl;
    cout << (unsigned int)0xFFFFFFFF << endl;
    for( ipd1=0; ipd1<0; ipd1++ )
    {
        
    }
    cout << ipd1;
    delete pd1;
    */
    
    /*
    Tensor2<double> t2("datatens",3,3);
    Tensor2<int> t1("datatens",3,3);
    for(int i=0; i<10; i++)
    {
        t1(0,0,1,1);
        t2(0,0,2,2);
    }
    
    cout << storTensor2 << endl;
    for( int i=0; i< storTensor2; i++ )
    {
        cout << storTensor2[i] << endl;
    }
    clearStorage();
    for(int i=0; i<10; i++)
    {
        t1(0,0,1,1);
        t2(0,0,2,2);
    }
    cout << storTensor2 << endl;
    for( int i=0; i< storTensor2; i++ )
    {
        cout << storTensor2[i] << endl;
    }
    */
    
    /*
    vector<int> v1(9);
    mat<int> mmm;
    MM<int> mmmmmm(7,"uuu");
    
    enum{ a,b,c } alp;
    alp = a;
    cout << a;
    */
    
    /*
    Tensor2<double> m2("datatens",3,3), m3("datatens",2,2), m4;
    Tensor2<double>* m1;
    m3 = !m2;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout << m3(i,j) << " ";
        }
        cout << endl;
    }
    */

    /*
    int* pi;
    Storage<int*>* st1;
    Storage<int*>  st2;
    for( int i=0; i< 3; i++ )
    {
        st1 = new Storage<int*>;
        
        for( int j=0; j< 3; j++ )
        {
            pi = new int(3*i+j);
            *st1 = pi;
            st2  = pi;
        }
        cout << *st1;
        //cout << st2;
        
        for( int j=0; j< 3; j++ )
        {
            delete (*st1)[j];
            //delete st2[j];
        }
        cout << (*st1)[3];
        delete st1;
    }
    */
    
    
    /*
    mat<int>* pm;
    pm = new mat<int>;
    cout << pm << endl;
    f(pm);
    pm = new mat<int>;
    cout << pm << endl;
    f(pm);
    */
    
    /*
//    mat<int>* mat1;
    mat<int>* mat2;
    mat2 = new mat<int>;
    mat2->make();
    cout<<"--------\n";
    mat<int> mat1;
    mat1.make();
    cout<<"\n--------\n";
    mat2->make();
    mat2->make();
    delete mat2;
    
    mat2 = new mat<int>;
    mat2->make();
    mat2->make();
    mat2->make();
    delete mat2;
    */
    
    return 0;
}
long double sn(long double x)
{
    int n = 100;
    long double s = 0;
    for( int i= n; i> 0; i-=2 )
    {
        s += 1;
        s *= x*x;
        s /= (i+1)*i;
        
        i-=2;
        
        s -= 1;
        s *= x*x;
        s /= (i+1)*i;
    }
    s += 1;
    s *= x;
    
    return s;
}

long double cs(long double x)
{
    int n = 100;
    long double c = 0;
    for( int i= n; i> 0; i-=2 )
    {
        c += 1;
        c *= x*x;
        c /= i*(i-1);
        
        i-=2;
        
        c -= 1;
        c *= x*x;
        c /= i*(i-1);
    }
    c += 1;
    
    return iszero(c);
}

long double ex( long double x )
{
    int n = 1000;
    long double e = 0;
    for( int i= n; i> 0; i-- )
    {
        e += 1;
        e *= x;
        e /= i;
    }
    e += 1;
    
    return e;
}    






































