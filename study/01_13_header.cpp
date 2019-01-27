#include <iostream.h>
#include "01_13.h"

Test2::Test2()
{
    cout << "con  Test2\n";
}
Test2::~Test2()
{
    cout << "decon  Test2\n";
}

template<class T>
Test<T>::Test<T>()
{
    t1 = 3;
    cout << t1 << endl;
}

template<class T>
Test<T>::~Test()
{
    cout << "deconstructor\n";
}

template<class T>
void Test<T>::show()
{
    cout << t1 << endl;
}


void f(int in)
{
    cout << in << endl;
}

template<>
void temf(int in)
{
    cout << in << endl;
}

template<class T>
void temf(T in)
{
    cout << in << endl;
}

