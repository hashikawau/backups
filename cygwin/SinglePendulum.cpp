

//===========================================================
//===========================================================
#include <iostream>
#include <math.h>
#include "Mathematics/DE.h"
#include "Mathematics/DE_cpp.h"

using namespace std;
//===========================================================
//===========================================================
class F10: public Function
{
public:
    virtual double getValue(double x[]);
};
class F11: public Function
{
public:
    virtual double getValue(double x[]);
};
double F10::getValue(double x[])
{
    return x[2];
}
double F11::getValue(double x[])
{
    return -sin(x[1]);
}
//===========================================================
//===========================================================
int main()
{
    Function* f0[2];
    f0[0] = new F10();
    f0[1] = new F11();
    double h = 0.1;
    double x[3];
    x[0] = 0;
    x[1] = M_PI_2;
    x[2] = 0;
    for(int i=0; i< 100; ++i){
        DE::runge_kutta_4(2, f0, x, h);
        cout << x[0] << "  " << x[1] << "  " << x[2] << "  ";
        cout << endl;
    }
    
    return 0;
}
//===========================================================
//===========================================================

