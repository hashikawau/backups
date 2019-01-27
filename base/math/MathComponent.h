

#ifndef _base_math_MathComponent
#define _base_math_MathComponent


//===========================================================
//===========================================================
#include "../../base/PointerObject.h"
class String;
//===========================================================
//===========================================================
class MathComponent
{
protected:
public:
    MathComponent();
    virtual ~MathComponent() =0;
};
//===========================================================
//===========================================================
class MathFunction: public MathComponent
{
protected:
    
public:
    MathFunction();
    virtual ~MathFunction() =0;
    virtual String getSymbol() =0;
    virtual double getValue() =0;
    virtual bool isVariable() =0;
    //virtual PointerObject<MathFunction> differentiate() =0;
    virtual void set(MathFunction& function) =0;
};
//===========================================================
//===========================================================





//===========================================================
//===========================================================


#endif //ifndef _base_math_MathComponent

