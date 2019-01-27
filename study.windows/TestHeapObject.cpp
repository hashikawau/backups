

#include <iostream.h>
#include "windows\cpp\HeapObject.h"

class testHeapObject: public HeapObject
{
private:
    
protected:
    virtual testHeapObject& clone() const { return *new testHeapObject(*this); }
    
public:
    testHeapObject(testHeapObject* p =0): HeapObject(p){}
    testHeapObject(testHeapObject* p =0): HeapObject(p){}
    ~testHeapObject(){}
};

class testHeapObject2: public testHeapObject{};

//void f(const Hea


class A
{
int ii[34];
protected:
    A(){}
    virtual ~A() =0;
    A(const A& a){cout << "A=A\n";}
public:
    void show(){cout << "A\n";}
    A& operator=(const A& a){cout << "A=A\n";return *this;}
    static void operator delete(void* pointer)
    {
        cout << "delete A\n";
        ::delete(pointer);
    }
};
A::~A(){}
class B: public A
{
public:
    //virtual B& operator=(const A& b){cout << "B=A\n";return *this;}
    B& operator=(const B& b){cout << "B=B\n";return *this;}
    void show(){cout << "B\n";}
    static void operator delete(void* pointer)
    {
        cout << "delete B\n";
        ::delete(pointer);
    }
};
class C: public B
{
public:
    C& operator=(const C& b){cout << "C=C\n";return *this;}
    void show(){cout << "C\n";}
    static void operator delete(void* pointer)
    {
        cout << "delete C\n";
        ::delete(pointer);
    }
    operator void*(){return dynamic_cast<void*>(this);}
};

void listshow()
{
    int size = HeapObject::_listAddress.size();
    cout << "size  " << size << "  " ;
    cout << HeapObject::_listRefcount.size() << endl;
    for(int i=0; i< size; ++i)
    {
        cout << HeapObject::_listAddress[i];
        cout << "  ";
        cout << HeapObject::_listRefcount[i];
        cout << endl;
    }
}

int main()
{
    testHeapObject tho1;
    listshow();
    
    testHeapObject tho2;
    tho2 = tho1;
    listshow();
    
    
    return 0;
}

