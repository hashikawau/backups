

//===========================================================
//===========================================================

#include <iostream>
#include "../base/math/ODE.h"
#include "../base/math/ODE_cpp.h"

#include <math.h>
using namespace std;
//===========================================================
//===========================================================
class F1: public Function
{
public:
    virtual double getValue(double x[]);
};
double F1::getValue(double x[])
{
    return x[1] /x[0];//f(x, y) = y / x
}
//===========================================================
//===========================================================
class F2: public Function
{
public:
    virtual double getValue(double x[]);
};
double F2::getValue(double x[])
{
    return x[1];//f(x, y) = y
}
//===========================================================
//===========================================================
class F3: public Function
{
public:
    virtual double getValue(double x[]);
};
class F4: public Function
{
public:
    virtual double getValue(double x[]);
};
double F3::getValue(double x[])
{
    return x[2];//f(x, y1, y2) = y2
}
double F4::getValue(double x[])
{
    return -2 *x[1] +3 *x[2];//f(x, y1, y2) = -2 *y1 + 3 *y2
}
//===========================================================
//===========================================================
int main()
{
    cout << "Hello" << endl;
    
    F1 f1;
    /*
    double h = M_PI_2 /99;
    double x;
    for(int i=0; i< 100; ++i){
        x = i *h;
        cout << i *h << "  " << f1.getValue(&x) << endl;
    }
    */
    /*
    double h = -0.01;
    double x[2];
    x[0] = 2;
    x[1] = 4;
    for(int i=0; i< 100; ++i){
        DE::runge_kutta_4(f1, x, h);
        cout << x[0] << "  " << x[1] << endl;
    }
    */
    
    /*
    F2 f2;
    double h = 0.5;
    double x[2];
    x[0] = 0;
    x[1] = 1;
    for(int i=0; i< 100; ++i){
        DE::runge_kutta_4(f2, x, h);
        cout << x[0] << "  " << x[1] << "  " << exp((i+1) *h) << endl;
    }
    */
    
    F3 f3;
    F4 f4;
    Function* f0[2];
    f0[0] = new F3();
    f0[1] = new F4();
    double h = 0.1;
    double x[3];
    x[0] = 0;
    x[1] = 4;
    x[2] = 5;
    for(int i=0; i< 100; ++i){
        ODE::runge_kutta_4(2, f0, x, h);
        cout << x[0] << "  " << x[1] << "  " << x[2] << "  ";
        cout << exp((i+1) *h *2) +3 *exp((i+1) *h) << endl;
    }
    
    
    
    
    
    return 0;
}
//===========================================================
//===========================================================

