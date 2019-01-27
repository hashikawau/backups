

#ifndef _base_math_MathFunction_cpp
#define _base_math_MathFunction_cpp


//===========================================================
//===========================================================
#include "MathComponent.h"
#include "MathFunction.h"
#include "lang/String.h"
#include "lang/Number.h"
#include "MathComponent_cpp.h"
#include "MathFunction_cpp.h"
#include "lang/String_cpp.h"
#include "lang/Number_cpp.h"
#include "base/PointerObject.h"
#include "base/PointerObject_cpp.h"
//===========================================================
//===========================================================
/*
MathConstant::MathConstant(String& symbol, double value)
    : _symbol(symbol), _value(value)
{}
MathConstant::MathConstant(double value)
    : _symbol(String(value)), _value(value)
{}
MathConstant::MathConstant()
    : _symbol(String(0)), _value(0)
{}
MathConstant::~MathConstant(){}
//===========================================================
//===========================================================
String MathConstant::getSymbol()
{
    return _symbol;
}
double MathConstant::getValue()
{
     return _value;
}
bool MathConstant::isVariable()
{
    return false;
}
//===========================================================
//===========================================================
void MathConstant::setSymbol(String& symbol)
{
    _symbol = symbol;
}
void MathConstant::setValue(double value)
{
    _value = value;
}
*/
//===========================================================
//===========================================================


//===========================================================
//===========================================================
MathVariable::MathVariable(String& symbol)
    : _symbol(symbol)
{
    //_value(Double::parseDouble(symbol));
    _value = 0;
}
MathVariable::~MathVariable(){}
//===========================================================
//===========================================================
void MathVariable::setSymbol(String& symbol)
{
    _symbol = symbol;
}
String MathVariable::getSymbol()
{
    return _symbol;
}
double MathVariable::getValue()
{
     return _value;
}
bool MathVariable::isVariable()
{
    return true;
}
/*
PointerObject<MathFunction> MathVariable::differentiate()
{
    return PointerObject<MathFunction>(new MathVariable(String("t")));
}
*/
void MathVariable::set(MathFunction& function){}
//===========================================================
//===========================================================
void MathVariable::setValue(double value)
{
    _value = value;
}
//===========================================================
//===========================================================



//===========================================================
//===========================================================
MathSummation::MathSummation(){}
MathSummation::~MathSummation(){}
//===========================================================
//===========================================================
String MathSummation::getSymbol()
{
    if(!_functions){ return String(""); }
    
    StringBuffer str;
    str += String("( ");
    str += (*_functions[0]).getSymbol();
    for(int i=1; i< _functions.size(); ++i){
        str += String(" + ");
        str += (*_functions[i]).getSymbol();
    }
    str += String(" )");
    return str.substring(0);
}
double MathSummation::getValue()
{
     return 0;
}
bool MathSummation::isVariable()
{
    return true;
}
//===========================================================
//===========================================================
void MathSummation::set(MathFunction& function)
{
    _functions.addLast(&function);
}
//===========================================================
//===========================================================



//===========================================================
//===========================================================
MathProduct::MathProduct(){}
MathProduct::~MathProduct(){}
//===========================================================
//===========================================================
String MathProduct::getSymbol()
{
    if(!_functions){ return String(""); }
    
    StringBuffer str;
    str += (*_functions[0]).getSymbol();
    for(int i=1; i< _functions.size(); ++i){
        str += String(" ");
        str += (*_functions[i]).getSymbol();
    }
    return str.substring(0);
}
double MathProduct::getValue()
{
     return 0;
}
bool MathProduct::isVariable()
{
    return true;
}
//===========================================================
//===========================================================
void MathProduct::set(MathFunction& function)
{
    _functions.addLast(&function);
}
//===========================================================
//===========================================================



//===========================================================
//===========================================================
MathExponent::MathExponent(){}
MathExponent::~MathExponent(){}
//===========================================================
//===========================================================
String MathExponent::getSymbol()
{
    if(!_functions){ return String(""); }
    
    StringBuffer str;
    str += (*_functions[0]).getSymbol();
    str += String(" ^");
    str += (*_functions[1]).getSymbol();
    return str.substring(0);
}
double MathExponent::getValue()
{
     return 0;
}
bool MathExponent::isVariable()
{
    return true;
}
//===========================================================
//===========================================================
void MathExponent::set(MathFunction& function){}
void MathExponent::set(MathFunction& function1, MathFunction& function2)
{
    _functions.addLast(&function1);
    _functions.addLast(&function2);
}
//===========================================================
//===========================================================


//===========================================================
//===========================================================


//===========================================================
//===========================================================


#endif //ifndef _base_math_MathFunction_cpp

