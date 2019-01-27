

#include <iostream.h>
#include "windows\cpp\PointerObject.h"

class S{};
class T{};
class U{};


class A
{
public:
    int _a;
    A(): _a(2){}
    virtual ~A(){ cout << "destructor A\n"; }
    virtual void showA(){ cout << "A  " << _a << endl; }
};
class B
{
public:
    int _b;
    B(): _b(4){}
    virtual ~B(){ cout << "destructor B\n"; }
    virtual void showB(){ cout << "B  " << _b << endl; }
};
//void f(const PointerObject<A>& poa){ poa->show(); }

class C//: public A, public B
{
public:
    PointerObject<A> _poca;
    PointerObject<B> _pocb;
    C(): _poca(new A()), _pocb(new B()){}
    virtual ~C(){ cout << "destructor C\n"; }
    //void addA(A* p){ _poa.addFirst(p); }
    //void addB(B* p){ _pob.addFirst(p); }
    virtual void showA(){ cout << "C  A123" << endl; }
    virtual void showB(){ cout << "C  B123" << endl; }
};

class D: public A
{
public:
    PointerObject<A> _poda;
    PointerObject<B> _podb;
    PointerObject<C> _podc;
    D(): _poda(new A()), _podb(new B()), _podc(new C()){}
    virtual ~D(){ cout << "destructor D\n"; }
    //void addA(A* p){ _poa.addFirst(p); }
    //void addB(B* p){ _pob.addFirst(p); }
    virtual void showA(){ cout << "C  A123" << endl; }
    virtual void showB(){ cout << "C  B123" << endl; }
};

class E: public D, public B
{
public:
    PointerObject<A> _poea;
    PointerObject<B> _poeb;
    PointerObject<C> _poec;
    PointerObject<D> _poed;
    E(): _poea(new D()), _poeb(new B()), _poec(new C()), _poed(new D()){}
    virtual ~E(){ cout << "destructor E\n"; }
    //void addA(A* p){ _poa.addFirst(p); }
    //void addB(B* p){ _pob.addFirst(p); }
    virtual void showA(){ cout << "C  A123" << endl; }
    virtual void showB(){ cout << "C  B123" << endl; }
};




int main()
{
    for(int i=0; i< 10; ++i)
    {
        //PointerObject<D> poc(new E());
        //poc->addA(new D());
        //poc->addB(new D());
    }
    PointerObject<D> poc(new E());
    cout << "before clear()\n";
    poc.clear();
    cout << "after  clear()\n";
    
    
    
try{
    /*
    A* a1 = new A();
    B* b1 = new B();
    C* c1 = new C();
    //PointerObject<A> poa1(c1);
    PointerObject<B> pob1;
    if(pob1){ cout << "true" << endl; }
    if(!pob1){ cout << "false" << endl; }
    
    pob1.add(c1);
    pob1.add(c1);
    pob1.add(b1);
    
    
    for(B** b= pob1.get(); *b; ++b)
    {
        //cout << (int)(*b) << "  " << (int)b << endl;
    }
    pob1.remove(b1);
    for(B** b= pob1.get(); *b; ++b)
    {
        //cout << (int)(*b) << "  " << (int)b << endl;
    }
    */
    //pob1.add(c1);
    //pob1->showB();
    //(*pob1).showB();
    /*
    pob1.add(c1);
    pob1.remove(c1);
    pob1.add(c1);
    pob1.add(c1);
    pob1.add(c1);
    pob1.remove(c1);
    */
    
    
    
    /*
    pob1 = new B();
    
    
    
    
    
    poa1->showA();
    pob1->showB();
    
    
    for(int i=0; i< 10; ++i)
    {
        //PointerObject<A> poa(poa1);
        //PointerObject<B> pob;
        //pob = pob1;
        //PointerObject<C> poc(new C());
    }
    */
    
    
    /*
    for(int i=0; i< 10; ++i)
    {
        B* b = new C();
        cout << b << endl;
        delete dynamic_cast<void*>(b);
    }
    */
    
    
    
    
    
    
}catch(...)
{
    cout << "Exception" << endl;
}
    
    /*
    A a1;
    PointerObject<A> poa1 = new A();
    PointerObject<A> poa2;
    poa1->show();
    poa1 = new B();
    poa1->show();
    poa2 = poa1;
    poa2->show();
    poa1 = new A();
//showlist();
    poa2 = new A();
//showlist();
    poa1 = new B();
//showlist();
    poa2 = new B();
//showlist();
    cout << endl;
    
    poa1 = new A();
//showlist();
    poa2 = new A();
//showlist();
    poa1 = new B();
//showlist();
    poa2 = new B();
//showlist();
    //cout << poa1.get() << endl;
    //cout << poa2.get() << endl;
    //PointerObject<B> pob(new B());
    //poa->show();
    
    //poa=pob;
    //poa->show();
    
    //f(pob);
    */
    
    return 0;
}

