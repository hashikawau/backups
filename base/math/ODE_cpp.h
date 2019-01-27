

#ifndef _base_math_analysis_calculus_ODE_cpp
#define _base_math_analysis_calculus_ODE_cpp


//===========================================================
//===========================================================
#include "ODE.h"
#include "Function.h"

//===========================================================
//===========================================================
void ODE::runge_kutta_4(
    Function& f,
    double vars[],
    double interval)
{
    double inix = vars[0];
    double iniy = vars[1];
    double k1 = f.getValue(vars);
    
    vars[0] = inix +interval /2;
    vars[1] = iniy +k1 *interval /2;
    double k2 = f.getValue(vars);
    
    vars[1] = iniy +k2 *interval /2;
    double k3 = f.getValue(vars);
    
    vars[0] = inix +interval;
    vars[1] = iniy +k3 *interval;
    double k4 = f.getValue(vars);
    
    vars[1] = iniy + (k1 +k4 +2 *(k2 +k3)) *interval /6;
}
//===========================================================
//===========================================================
void ODE::runge_kutta_4(
    int numy,
    Function* f[],
    double vars[],
    double interval)
{
    double inix = vars[0];
    double iniy[numy];
    for(int i=0; i< numy; ++i){
        iniy[i] = vars[1 +i];
    }
    double k1[numy];
    for(int i=0; i< numy; ++i){
        k1[i] = (*f[i]).getValue(vars);
    }
    
    
    vars[0] = inix +interval /2;
    for(int i=0; i< numy; ++i){
        vars[1 +i] = iniy[i] +k1[i] *interval /2;
    }
    double k2[numy];
    for(int i=0; i< numy; ++i){
        k2[i] = (*f[i]).getValue(vars);
    }
    
    for(int i=0; i< numy; ++i){
        vars[1 +i] = iniy[i] +k2[i] *interval /2;
    }
    double k3[numy];
    for(int i=0; i< numy; ++i){
        k3[i] = (*f[i]).getValue(vars);
    }
    
    vars[0] = inix +interval;
    for(int i=0; i< numy; ++i){
        vars[1 +i] = iniy[i] +k3[i] *interval;
    }
    double k4[numy];
    for(int i=0; i< numy; ++i){
        k4[i] = (*f[i]).getValue(vars);
    }
    
    for(int i=0; i< numy; ++i){
        vars[1 +i] = iniy[i] + (k1[i] +k4[i] +2 *(k2[i] +k3[i])) *interval /6;
    }
}
//===========================================================
//===========================================================


#endif //ifndef _base_math_analysis_calculus_ODE_cpp

