

#ifndef _base_math_analysis_calculus_ODE
#define _base_math_analysis_calculus_ODE


//===========================================================
//===========================================================
class Function;

//===========================================================
//===========================================================
class ODE
{
public:
    static void runge_kutta_4(
        Function& f,
        double vars[],
        double interval);
    static void runge_kutta_4(
        int numy,
        Function* f[],
        double vars[],
        double interval);
    
};
//===========================================================
//===========================================================


#endif //ifndef _base_math_analysis_calculus_ODE

