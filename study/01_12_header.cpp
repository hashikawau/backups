#include <iostream.h>
//#include "01_12_header.h"

template<class T> class Test
{
    T   tt;
    int test1;
    
public:
    Test();
    ~Test();
};

template<class T>
Test<T>::Test()
{
    test1 = 0;
    cout << "Constructor  ";
    cout << test1 << endl;
}


template<class T>
Test<T>::~Test()
{
    cout << "Destructor\n";
}

