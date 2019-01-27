

#ifndef _base_math_MathFunction
#define _base_math_MathFunction


//===========================================================
//===========================================================
#include "MathComponent.h"
#include "../../lang/String.h"
#include "../../lang/String_cpp.h"
#include "../../base/PointerObject.h"
//===========================================================
//===========================================================
class MathVariable: public MathFunction
{
protected:
    String _symbol;
    double _value;
    
public:
    MathVariable(String& symbol);
    MathVariable();
    virtual ~MathVariable();
    virtual String getSymbol();
    virtual double getValue();
    virtual bool isVariable();
    //virtual PointerObject<MathFunction> differentiate();
    virtual void set(MathFunction& function);
    
    void setSymbol(String& symbol);
    void setValue(double value);
};
//===========================================================
//===========================================================
/*
class MathConstant: public MathVariable
{
protected:
    //String _symbol;
    //double _value;
    
public:
    MathConstant(String& symbol, double value);
    //MathConstant(String& symbol);
    MathConstant(double value);
    MathConstant();
    virtual ~MathConstant();
    virtual String getSymbol();
    virtual double getValue();
    virtual bool isVariable();
    //virtual PointerObject<MathFunction> differentiate();
    
    //void setSymbol(String& symbol);
    //void setValue(double value);
};
*/
//===========================================================
//===========================================================
class MathSummation: public MathFunction
{
protected:
    PointerObject<MathFunction> _functions;
    
public:
    MathSummation();
    virtual ~MathSummation();
    virtual String getSymbol();
    virtual double getValue();
    virtual bool isVariable();
    //virtual PointerObject<MathFunction> differentiate() =0;
    virtual void set(MathFunction& function);
    
};
//===========================================================
//===========================================================
class MathProduct: public MathFunction
{
protected:
    PointerObject<MathFunction> _functions;
    
public:
    MathProduct();
    virtual ~MathProduct();
    virtual String getSymbol();
    virtual double getValue();
    virtual bool isVariable();
    //virtual PointerObject<MathFunction> differentiate() =0;
    virtual void set(MathFunction& function);
    
};
//===========================================================
//===========================================================
class MathExponent: public MathFunction
{
protected:
    PointerObject<MathFunction> _functions;
    
public:
    MathExponent();
    virtual ~MathExponent();
    virtual String getSymbol();
    virtual double getValue();
    virtual bool isVariable();
    //virtual PointerObject<MathFunction> differentiate() =0;
    virtual void set(MathFunction& function);
    
    void set(MathFunction& function, MathFunction& function);
    
};
//===========================================================
//===========================================================





//===========================================================
//===========================================================


#endif //ifndef _base_math_MathFunction

