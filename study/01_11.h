
#include "01_11C1_1.h"
#include "01_11C1_2.h"

int f(int x)
{
    return x;
}

template<class T=int> class C1
{
    T   tc1;
    int ic1;
public:
    C1();
    void show();
    void swap(C1<T>);
    void show2(int n=0);
    void show3(int n=5);
    
};
