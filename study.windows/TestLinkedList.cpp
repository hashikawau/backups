

#include <iostream.h>
#include "windows\util\LinkedList.h"

class A
{
public:
    virtual void show(){ cout << "A\n"; }
};
class C
{
private:
class B: public A
{
    virtual void show(){ cout << "B\n"; }
}_b;
public:
    A& back(){ return _b; }
};


int main()
{
    int num =10;
    LinkedList<int> l1;
    for(int i=0; i< num; ++i)
    {
        l1.addLast(i);
    }
    
    
    for(ListIterator<int>& i1 = l1.listIterator(0); i1.hasNext();)
    {
        cout << i1.next() << endl;
    }
    
    return 0;
}


