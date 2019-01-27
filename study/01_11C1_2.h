#include <iostream.h>

template<class T> class C1;

template<class T>
inline void C1<T>::show3(int n)
{
    show2(n);
}