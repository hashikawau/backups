

#ifndef __Windows_lang_Math_cpp
#define __Windows_lang_Math_cpp


//===========================================================
//===========================================================
#include "Math.h"
#include <stdlib.h>
#include <windows.h>
//===========================================================
//===========================================================
const double Math::E =2.718281828459045;
const double Math::PI =3.141592653589793;
//===========================================================
//===========================================================
Math::Math(){}
Math::~Math(){}
//===========================================================
//===========================================================
double Math::signum(double d)
{
    return d == 0?
        0:
        d > 0?
            1.0:
            -1.0;
}
//===========================================================
//===========================================================
double Math::sqrt(double a)
{
    if(a < 0){ return 0/(1.-1.); }
    if(a == 0){ return 0; }
    const double EPSILON =1e-3;
    double value =1;
    double emax  =0;
    double temp  =0;
    double c = a <1?
        a:
        1;
    do{
        temp = (value *value +a) /2 /value;
        emax = Math::abs((temp -value) / c);
        value = temp;
    }while(emax > EPSILON);
    
    return value;
}
//===========================================================
//===========================================================
double Math::pow(double a, double b)
{
    //if(a < 0){ return 0/(1.-1.); }
    if(Math::abs(b) >1e9){ b = Math::signum(b) *1e9; }
    const double EPSILON =1e-3;
    double value =1;
    double power =static_cast<int>(b);
    double cval  =1 + (b -power) *Math::log(Math::abs(a));
    double emax  =0;
    double temp  =0;
    do{
        temp = value *(cval - Math::log(value));
        emax = Math::abs((temp -value));
        value = temp;
    }while(emax > EPSILON);
    
    temp=1;
    for(int i=0; i< Math::abs(power); ++i){
        temp *= a;
    }
    value = power >0?
        value *temp:
        value /temp;
    
    return value;
}
//===========================================================
//===========================================================
double Math::sin(double a)
{
    const int COUNT =1000;
    double value =0;
    
    
    for(int i= COUNT; i> 0; i-= 2 ){
        value += 1;
        value *= a *a;
        value /= (i+1)*i;
        
        i -= 2;
        
        value -= 1;
        value *= a *a;
        value /= (i+1)*i;
    }
    value += 1;
    value *= a;
    
    return value;
}
double Math::cos(double a)
{
    const int COUNT =1000;
    double value =0;
    
    
    for(int i= COUNT; i> 0; i-= 2 ){
        value += 1;
        value *= a *a;
        value /= i*(i-1);
        
        i -= 2;
        
        value -= 1;
        value *= a *a;
        value /= i*(i-1);
    }
    value += 1;
    
    
    return value;
}
double Math::tan(double a)
{
    return Math::sin(a) / Math::cos(a);
}
//===========================================================
//===========================================================
double Math::atan(double a)
{
    const int COUNT =1000000;
    double value =0;
    
    double arg = Math::abs(a) >1?
        1 /a:
        a;
    
    for(int i= COUNT; i> 0; i-= 2 )
    {
        value += 1/static_cast<double>(i+1);
        value *= arg *arg;
        
        i -= 2;
        
        value -= 1/static_cast<double>(i+1);
        value *= arg *arg;
    }
    value += 1;
    value *= arg;
    
    if(Math::abs(a) >1){
        value = Math::signum(a) *Math::PI /2 - value;
    }
    
    return value;
}
//===========================================================
//===========================================================
double Math::exp(double a)
{
    if(a == 0){ return 1; }
    if(Math::abs(a) >1e9){ a = Math::signum(a) *1e9; }
    
    const int COUNT =20;
    double value =0;
    int    power = static_cast<int>(a);
    double arg   = a -power;
    
    for(int i= COUNT; i> 0; --i )
    {
        value += 1;
        value *= arg /i;
    }
    value += 1;
    
    double temp =1;
    for(int i=0; i< Math::abs(power); ++i){
        if(temp >=1./(1.-1.)){ break; }
        temp *= Math::E;
    }
    value = power >0?
        value *temp:
        value /temp;
    
    return value;
}
double Math::log(double a)
{
    if(a <= 0){ return -1/(1.-1.); }
    if(a == 1){ return 0; }
    
    const int COUNT =1000000;
    double value =0;
    int    power =0;
    
    while(a < 1){
        a *=2;
        --power;
    }
    while(a > 2){
        a /=2;
        ++power;
    }
    
    double arg = 1 -a;
    for(int i= COUNT; i> 0; --i )
    {
        value += 1. /i;
        value *= arg;
    }
    value = -value + power * 0.6931471805599452862;
    
    return value;
}
//===========================================================
//===========================================================
double Math::toDegrees(double angrad)
{
    return angrad *180 /Math::PI;
}
double Math::toRadians(double angdeg)
{
    return angdeg *Math::PI /180;
}
//===========================================================
//===========================================================
double Math::random()
{
    srand(timeGetTime());
    return static_cast<double>(rand()) / RAND_MAX;
}
//===========================================================
//===========================================================
double Math::abs(double a)
{
    return a >= 0?
        a:
        -a;
}
int Math::abs(int a)
{
    return a >= 0?
        a:
        -a;
}
//===========================================================
//===========================================================
double Math::max(double a, double b)
{
    return a > b?
        a:
        b;
}
int Math::max(int a, int b)
{
    return a > b?
        a:
        b;
}
double Math::min(double a, double b)
{
    return a < b?
        a:
        b;
}
int Math::min(int a, int b)
{
    return a < b?
        a:
        b;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_Math_cpp

