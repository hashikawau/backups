

#include <iostream.h>


class Base
{
public:
    int a;
    Base(): a(0){}
    virtual void show(){ cout << a << endl; }
};
class Derived: public Base
{
public:
    int b;
    Derived(): b(4){}
    virtual void show(){ cout << a << " " << b << endl; }
};
class Derived2: public Base
{
public:
    int c;
    Derived2(): c(5){}
    virtual void show(){ cout << a << " " << c << endl; }
};


int main()
{
    Base b1;
    Derived d1;
    Derived2 dd1;
    
    b1.show();
    d1.show();
    dd1.show();
    
    Base& b2 = d1;
    b2.show();
    
    b2 = reinterpret_cast<Base&>(dd1);
    b2.show();
    
    try{
        Derived& d2 = dynamic_cast<Derived&>(b2);
        d2.show();
    }catch(...){ cout << "Derived\n"; }
    
    try{
        Derived2& dd2 = dynamic_cast<Derived2&>(b2);
        dd2.show();
    }catch(...){ cout << "Derived2\n"; }
    
    
    
    return 0;
}

