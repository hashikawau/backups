


#ifndef __Windows_research_Variable
#define __Windows_research_Variable


#include <iostream.h>
#include <fstream.h>


//===========================================================
//===========================================================
class Variable
{
private:
    int _length;
    double* _value;
    
public:
    explicit Variable(int length =0);
    Variable(const Variable& object);
    Variable& operator=(const Variable& object);
    ~Variable();
    
    int length();
    double* array();
    
    void setLength(int length);
};
//===========================================================
//===========================================================
Variable::Variable(int length):
    _length(length),
    _value(new double [length])
{}
Variable::Variable(const Variable& object)
{
    _length = object._length;
    _value = new double [_length];
    for(int i=0; i< _length; ++i){
        _value[i] = object._value[i];
    }
}
/*
Variable& Variable::operator=(const Variable& object)
{
    delete [] _value;
    
    _length = object._length;
    _value = new double [_length];
    for(int i=0; i< _length; ++i){
        _value[i] = object._value[i];
    }
    
    return *this;
}
*/
Variable::~Variable()
{
    delete [] _value;
    _value =0;
}
//===========================================================
//===========================================================
int Variable::length()
{
    return _length;
}
double* Variable::array()
{
    return _value;
}
//===========================================================
//===========================================================
void Variable::setLength(int length)
{
    delete [] _value;
    _length = length;
    _value = new double [_length];
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_research_Variable

