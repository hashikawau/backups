#include <iostream.h>
#include <math.h>

template < class T = long double > class Tensor
{
    T  *paElements;
    int iNumElements;
    
public:
    Tensor( int num )
    {
        iNumElements = num;
        paElements = new T[iNumElements];
        for( int i = 0; i < iNumElements; i++ ){ *(paElements + i) = 0; }
    }
    
    Tensor( T t01, T t02 )
    {
        iNumElements = 2;
        paElements = new T[iNumElements];
        paElements[0] = t01;
        paElements[1] = t02;
    }
    
    Tensor( T t01, T t02, T t03 )
    {
        iNumElements = 3;
        paElements = new T[iNumElements];
        paElements[0] = t01;
        paElements[1] = t02;
        paElements[2] = t03;
    }
    
    ~Tensor()
    {
        if(paElements)
        {
            //cout << paElements[1] << "destructor\n";
            delete [] paElements;
        }
    }
    
    T &set( int num ){ return *(paElements + num); }
    
    T get( int num ){ return *(paElements + num); }
    
    void trans( int num, T t01 )
    {
        *(paElements+num) += t01;
        show();
    }
    
    void trans( Tensor &tensor01 )
    {
        if( iNumElements == tensor01.iNumElements )
        {
            for( int i = 0; i < iNumElements; i++ )
            {
                *(paElements+i) += *(tensor01.paElements+i);
            }
            show();
        }
        else
        {
            cout << "Translation failed\n";
        }
    }
    
    void rot( double radian )
    {
        T *temp;
        temp = new T[iNumElements];
        for( int i = 0; i < iNumElements; i++ ){ *(temp+i) = *(paElements+i); }
        
        paElements[0] = cos(radian)*temp[0] - sin(radian)*temp[1];
        paElements[1] = sin(radian)*temp[0] + cos(radian)*temp[1];
        
        delete [] temp;
        
        show();
    }
    
    void show()
    {
        for( int i = 0; i < iNumElements; i++ ){ cout << get(i) << endl; }
        cout << endl;
    }
};

int study()
{
    Tensor<> a(2.3, 9);
    a.show();
    a.set(0) = 5;
    a.show();
    
    Tensor<> b(1, 1);
    b.show();
    b.rot(M_PI_2);
    b.trans(0, 10);
    a.show();
    b.trans(a);
    a.show();
    
    return 0;
}