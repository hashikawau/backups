

#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Outer
{
public:
    class Inner
    {
    public:
        T t1;
        Inner(T t);
    };

    Inner i1;

    Outer(T t);

};
template<class T>
Outer<T>::Outer(T t): i1(t)
{

}

template<class T>
Outer<T>::Inner::Inner(T t)
{
    t1 = t;
}

int f()
{
    return 3;
}
class Color1
{
private:
    int _rgb;

public:
    static const Color1 black;
    static const int white;
    Color1(int rgb=0): _rgb(rgb){}
    operator int() const{ return _rgb; }
};
const Color1 Color1::black(9);
const int Color1::white = f();

//==========================================================
//==========================================================
class A1
{
private:
protected:
    int _iii;

public:
    A1(int iii);
    virtual void show(){ cout << "A1.show()  " << _iii << endl;}
    virtual void show(const A1& a1){ cout << a1._iii << endl;}
};
A1::A1(int iii=9): _iii(iii){}
typedef A1* _A1;

const A1& fa1()
{
    A1* a1 =0;
    return *a1;
}

class A2: public A1
{
private:
    int yyy;
    double ddd;
public:
    A2(int iii =2): A1(iii){}
    virtual void show(){ cout << "A2.show()  " << A2::_iii << endl;}
    virtual void show(const A1& a1){ cout << dynamic_cast<const A2&>(a1)._iii << endl;}
};
//==========================================================
//==========================================================
template<class T>
class RCPtr
{
private:
    T* _pointer;
    int* _counter;
    void reset();
    void reset(T* pointer, int* counter);
    void show();

public:
    //RCPtr();
    explicit RCPtr(const T* pointer =0, bool disableCounter =false);
    //RCPtr(const T& pointer, int counter);
    RCPtr(const RCPtr<T>& rhs);
    ~RCPtr();
    RCPtr<T>& operator=(const T* pointer);
    RCPtr<T>& operator=(const RCPtr<T>& rhs);
    T& operator*(){ return *_pointer; }
    T* operator->(){ return _pointer; }


};
//==========================================================
template<class T>
void RCPtr<T>::reset()
{
    if(!*_counter){
        delete _pointer;
        delete _counter;
        _pointer = 0;
        _counter = 0;
    cout << "reset()  " << this << endl;
    show();
    }
}
template<class T>
void RCPtr<T>::reset(T* pointer, int* counter)
{
    if(!*_counter){
        delete _pointer;
        delete _counter;
        _pointer = pointer;
        _counter = counter;
    cout << "reset(T*, int*)  " << this << endl;
    show();
    }
}
//==========================================================
/*template<class T>
RCPtr<T>::RCPtr(): _pointer(0), _counter(new int(1))
{
    cout << "constructor\n";
    show();
}*/
template<class T>
RCPtr<T>::RCPtr(const T* pointer, bool disableCounter):
    _pointer(const_cast<T*>(pointer)),
    _counter(disableCounter? new int(2): new int(1))
{
    cout << "constructor  " << this << endl;
    show();
}
template<class T>
RCPtr<T>::RCPtr(const RCPtr<T>& rhs)
{
    if(this == &rhs){ return; }
    _pointer = rhs._pointer;
    _counter = rhs._counter;
    ++*_counter;
    cout << "copy constructor  " << this << endl;
    show();
}
template<class T>
RCPtr<T>::~RCPtr()
{
    --*_counter;
    reset();
    cout << "destructor  " << this << endl;
    show();
}
template<class T>
RCPtr<T>& RCPtr<T>::operator=(const T* pointer)
{
    --*_counter;
    reset(const_cast<T*>(pointer), new int(0));
    ++*_counter;
    cout << "asignment constructor\n";
    show();
    return *this;
}
template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr<T>& rhs)
{
    if(this == &rhs){ return *this; }
    --*_counter;
    reset(rhs._pointer, rhs._counter);
    ++*_counter;
    cout << "asignment constructor\n";
    show();
    return *this;
}
//==========================================================
//==========================================================
class P: public A1
{
private:
    RCPtr<A1> _a1;
public:
    P(A1* a1):_a1(RCPtr<A1>(a1, a1==this)){(_a1)->show();}
    virtual void show(){ cout << "P.show()  " << /*(*_a1)._iii <<*/ endl;}
    virtual void show(const A1* a1){if(this!=a1)_a1 = a1; cout << "P.show(A1&)  "  << /*(*_a1).P::_iii <<*/ endl;}
};

const int fg(){ return 4; }


int main()
{

    //cout << fg()+2 << endl;


    //RCPtr<A1> rcptr1(A1());
    //P p1(new A2());
    //p1.show(&p1);
    //P p2 = p1;

    A2* a2 = new A2();
    A1* a1 = static_cast<A1*>(a2);
//    a1->show();
    cout << a1 << endl;
    cout << a2 << endl;

    void* v = dynamic_cast<void*>(a1);
    cout << v << endl;





/*
    //LinkedList<void*> list;


    //Outer<int> o(7);
    //list.addLast(static_cast<void*>(&o));


    //cout << static_cast< Outer<int>* >(list.getFirst())->i1.t1;

    //cout << endl;
    //cout << Color1::white << endl;

    A2 a2;
    a2.show(A2(7));

    //if(&fa1() == 0) cout << "null";
    A1 a1;
    if(&fa1() ==0)
        cout << "null\n";
    //if(a1 = fa1()){ cout << "succeeded"; }
//    cout << &fa1();
*/





    return 0;
}

template<class T>
void RCPtr<T>::show()
{
    cout << "  _pointer  " << _pointer << endl;
    cout << "  _counter  " << _counter;
    if(_counter){
        cout << "  " << *_counter << endl;
    }else{
        cout << "  null pointer" << endl;
    }
}
