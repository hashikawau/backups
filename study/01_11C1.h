#include <iostream.h>

template<class T> class C1;

template<>
inline C1<int>::C1()
{
    ic1 = 1;
    tc1 = 10;
    show();
}
template<>
inline C1<char>::C1()
{
    ic1 = 100;
    tc1 = 't';
    show();
}
template<class T>
inline C1<T>::C1()
{
    ic1 = 9;
    tc1 = 90;
    show();
}


template<>
inline void C1<int>::show()
{
    cout << "C1<int>  " << ic1 << "  " << tc1 << endl;
}
template<>
inline void C1<char>::show()
{
    cout << "C1<char>  " << ic1 << "  " << tc1 << endl;
}

template<class T>
inline void C1<T>::show()
{
    cout << "C1<T>  " << ic1 << "  " << tc1 << endl;
}

template<class T>
inline void C1<T>::swap(C1 c2)
{
    C1<T> temp;
    temp = *this;
    this->ic1 = c2.ic1;
    c2.ic1 = temp.ic1;
}

template<class T>
inline void C1<T>::show2(int n)
{
    cout << "show  " << n << endl;
}

template<class T>
inline void C1<T>::show3(int n)
{
    show2(n);
}