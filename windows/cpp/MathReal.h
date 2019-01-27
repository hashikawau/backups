

#ifndef __Windows_cpp_MathReal
#define __Windows_cpp_MathReal


#include "windows\cpp\MathNumber.h"


//===========================================================
//===========================================================
class MathReal: public MathNumber
{
private:
    void reduce() const;
    
protected:
    long long int _numerator;
    long long int _denominator;
    
public:
    explicit MathReal(const String& number);
    MathReal();
    MathReal(const int numerator, const int denominator =1);
    MathReal(const double real);
    virtual ~MathReal();
    virtual const String getNumber() const;
    
    const int getInt() const;
    const double getDouble() const;
    
    MathReal& operator=(const MathReal& object);
    MathReal& operator+=(const MathReal& object);
    MathReal& operator-=(const MathReal& object);
    MathReal& operator*=(const MathReal& object);
    MathReal& operator/=(const MathReal& object);
    MathReal& operator%=(const MathReal& object);
    MathReal& operator++();
    MathReal& operator--();
    const MathReal operator++(int notused);
    const MathReal operator--(int notused);
    const MathReal operator-() const;
    
friend const MathReal operator+(const MathReal& object1, const MathReal& object2);
friend const MathReal operator-(const MathReal& object1, const MathReal& object2);
friend const MathReal operator*(const MathReal& object1, const MathReal& object2);
friend const MathReal operator/(const MathReal& object1, const MathReal& object2);
friend const MathReal operator%(const MathReal& object1, const MathReal& object2);
friend const bool operator==(const MathReal& object1, const MathReal& object2);
friend const bool operator!=(const MathReal& object1, const MathReal& object2);
friend const bool operator<(const MathReal& object1, const MathReal& object2);
friend const bool operator<=(const MathReal& object1, const MathReal& object2);
friend const bool operator>(const MathReal& object1, const MathReal& object2);
friend const bool operator>=(const MathReal& object1, const MathReal& object2);
};
//===========================================================
//===========================================================
void MathReal::reduce() const
{
    if(!_denominator){
        //const_cast<int>(_denominator) = 1;
        throw MathFunctionException();
    }
    if(_denominator < 0){
        const_cast<int>(_denominator) = -_denominator;
        const_cast<int>(_numerator) = -_numerator;
    }
    
    int& min = _numerator >= _denominator?
        const_cast<int>(_numerator):
        const_cast<int>(_denominator);
    int& max = _numerator < _denominator?
        const_cast<int>(_numerator):
        const_cast<int>(_denominator);
    
    int i=2;
    while(i <= min){
        if(!((min %i) | (max %i))){
            min /= i;
            max /= i;
            continue;
        }
        ++i;
    }
    
    cout << "reduce  " << getDouble() << " = " << _numerator << " / " << _denominator << endl;
}
//===========================================================
//===========================================================
MathReal::MathReal(const String& number){}
MathReal::MathReal(): _numerator(0), _denominator(1){}
MathReal::MathReal(const int numerator, const int denominator):
    _numerator(numerator), _denominator(denominator)
{
    reduce();
}
MathReal::MathReal(const double real)
{
    _denominator = 1000;
    double d = _denominator *real;
    _numerator = static_cast<int>(d >0? d +0.5: d -0.5);
    reduce();
}
MathReal::~MathReal(){}
const String MathReal::getNumber() const
{
    return String(_numerator) +String(" / ") +String(_denominator);
}
const int MathReal::getInt() const
{
    long double temp = static_cast<double>(_numerator)
        / static_cast<double>(_denominator);
    return  temp + (temp >0? 0.5: -0.5);
}
const double MathReal::getDouble() const
{
    return static_cast<double>(_numerator)
        / static_cast<double>(_denominator);
}
//===========================================================
//===========================================================
MathReal& MathReal::operator=(const MathReal& object)
{
    if(this != &object){
        _numerator = object._numerator;
        _denominator = object._denominator;
    }
    return *this;
}
MathReal& MathReal::operator+=(const MathReal& object)
{
    _numerator
        = _numerator * object._denominator
        + _denominator * object._numerator;
    _denominator *= object._denominator;
    reduce();
    return *this;
}
MathReal& MathReal::operator-=(const MathReal& object)
{
    _numerator
        = _numerator * object._denominator
        - _denominator * object._numerator;
    _denominator *= object._denominator;
    reduce();
    return *this;
}
MathReal& MathReal::operator*=(const MathReal& object)
{
    _numerator *= object._numerator;
    _denominator *= object._denominator;
    reduce();
    return *this;
}
MathReal& MathReal::operator/=(const MathReal& object)
{
    _numerator *= object._denominator;
    _denominator *= object._numerator;
    reduce();
    return *this;
}
MathReal& MathReal::operator%=(const MathReal& object)
{
    MathReal quotient = *this /object;
    *this = MathReal(
        *this - object *static_cast<int>(quotient.getDouble()));
    return *this;
}
MathReal& MathReal::operator++()
{
    _numerator += _denominator;
    return *this;
}
MathReal& MathReal::operator--()
{
    _numerator -= _denominator;
    return *this;
}
//===========================================================
//===========================================================
const MathReal MathReal::operator++(int notused)
{
    _numerator += _denominator;
    return MathReal();
}
const MathReal MathReal::operator--(int notused)
{
    _numerator -= _denominator;
    return MathReal();
}
const MathReal MathReal::operator-() const
{
    return MathReal(-_numerator, _denominator);
}
//===========================================================
//===========================================================
const MathReal operator+(const MathReal& object1, const MathReal& object2)
{
    return MathReal(
        object1._numerator * object2._denominator
            + object1._denominator * object2._numerator,
        object1._denominator * object2._denominator);
}
const MathReal operator-(const MathReal& object1, const MathReal& object2)
{
    return MathReal(
        object1._numerator * object2._denominator
            - object1._denominator * object2._numerator,
        object1._denominator * object2._denominator);
}
const MathReal operator*(const MathReal& object1, const MathReal& object2)
{
    return MathReal(
        object1._numerator * object2._numerator,
        object1._denominator * object2._denominator);
}
const MathReal operator/(const MathReal& object1, const MathReal& object2)
{
    return MathReal(
        object1._numerator * object2._denominator,
        object1._denominator * object2._numerator);
}
const MathReal operator%(const MathReal& object1, const MathReal& object2)
{
    MathReal quotient = object1 /object2;
    return MathReal(
        object1 - object2 *static_cast<int>(quotient.getDouble()));
}
//===========================================================
//===========================================================
const bool operator==(const MathReal& object1, const MathReal& object2)
{
    return object1._numerator == object2._numerator
        && object1._denominator == object2._denominator?
        true:
        false;
}
const bool operator!=(const MathReal& object1, const MathReal& object2)
{
    return object1._numerator == object2._numerator
        && object1._denominator == object2._denominator?
        false:
        true;
}
const bool operator<(const MathReal& object1, const MathReal& object2)
{
    return object1.getDouble() < object2.getDouble()?
        true:
        false;
}
const bool operator<=(const MathReal& object1, const MathReal& object2)
{
    return object1.getDouble() <= object2.getDouble()?
        true:
        false;
}
const bool operator>(const MathReal& object1, const MathReal& object2)
{
    return object1.getDouble() > object2.getDouble()?
        true:
        false;
}
const bool operator>=(const MathReal& object1, const MathReal& object2)
{
    return object1.getDouble() >= object2.getDouble()?
        true:
        false;
}
//===========================================================
//===========================================================

#endif //ifndef __Windows_cpp_MathReal


