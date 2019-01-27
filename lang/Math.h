

#ifndef __Windows_lang_Math
#define __Windows_lang_Math


//===========================================================
//===========================================================
#include <math.h>
#undef max
#undef min
//===========================================================
//===========================================================
class Math
{
public:
    static const double E;
    static const double PI;
    
private:
    Math();
    ~Math();
    
public:
    static double signum(double d);
    
    //static const double pow(double a, double b);
    static double sqrt(double a);
    static double pow(double a, double b);
    
    static double sin(double a);
    static double cos(double a);
    static double tan(double a);
    
    static double atan(double a);
    
    static double exp(double a);
    static double log(double a);
    
    static double toDegrees(double angrad);
    static double toRadians(double angdeg);
    
    static double random();
    
    static double abs(double a);
    static int abs(int a);
    static double max(double a, double b);
    static int max(int a, int b);
    static double min(double a, double b);
    static int min(int a, int b);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_Math

