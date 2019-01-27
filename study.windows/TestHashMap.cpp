

#include <iostream.h>
#include "windows\util\HashMap.h"


class A
{
public:
    int _a;
    A(): _a(2){}
    virtual void show(){ cout << "A  " << _a << endl; }
};
class B: public A
{
public:
    int _b;
    B(): _b(4){}
    virtual void show(){ cout << "B  " << _b << endl; }
};

//void f(const PointerObject<A>& poa){ poa->show(); }

int main()
{
    HashMap<int, int> hm1;
    for(int i=0; i< 2; ++i)
    {
        for(int j=0; j< 10; ++j)
        {
            hm1.put( i*10+j, 9);
        }
    }
    
    
    return 0;
}

