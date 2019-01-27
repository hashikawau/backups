#include "iostream.h"
//#include <d3dx9.h>
//#include <direct.h>
//#include <cwchar>


class A
{
public:
    virtual void showA1()
    {
        cout << "A1\n";
    }
    virtual void showA2()
    {
        cout << "A2\n";
    }
};
class B
{
public:
    virtual void showB1()
    {
        cout << "B1\n";
    }
    virtual void showB2()
    {
        cout << "B2\n";
    }
};

class C: public A, public B
{
public:
    virtual void showA1()
    {
        cout << "A1---------------C\n";
    }
    virtual void showA2()
    {
        cout << "A2---------------C\n";
    }
    virtual void showB1()
    {
        cout << "B1---------------C\n";
    }
    virtual void showB2()
    {
        cout << "B2---------------C\n";
    }
};



void main()
{
    A* a = new C();
    a->showA1();
    a->showA2();
    cout << endl;
    
    B* b = new C();
    b->showB1();
    b->showB2();
    cout << endl;
    
    void* va = dynamic_cast<void*>(a);
    static_cast<A*>(va)->showA1();
    static_cast<A*>(va)->showA2();
    cout << endl;
    
    void* vb = dynamic_cast<void*>(b);
    b = static_cast<B*>(vb);//->showB1();
    //b = static_cast<B*>(vb)->showB2();
    b->showB1();
    b->showB2();
    cout << endl;
    
    
    va = dynamic_cast<void*>(a);
    dynamic_cast<A*>(static_cast<A*>(va))->showA1();
    dynamic_cast<A*>(static_cast<A*>(va))->showA2();
    cout << endl;
    
    vb = dynamic_cast<void*>(b);
    dynamic_cast<B*>(static_cast<B*>(vb))->showB1();
    dynamic_cast<B*>(static_cast<B*>(vb))->showB2();
    cout << endl;
    
    
    
    
    
}