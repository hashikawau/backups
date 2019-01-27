

#ifndef __Windows_cpp_MathFunction
#define __Windows_cpp_MathFunction


#include "windows\cpp\MathReal.h"


//===========================================================
//===========================================================
class MathVector
{
private:
    PointerObject<MathReal> _arrayReal;
    
public:
void show();
    
    
    
public:
    MathVector(const String& vector);
    MathVector();
    MathVector(const PointerObject<MathReal>& arrayReal);
    virtual ~MathVector();
    virtual const String getNumber() const;
    
    void append(const MathReal& object);
    void insert(const MathReal& real, const int index);
};
void MathVector::show()
{
    cout << "MathVector.show()\n";
    if(_arrayReal){
        for(MathReal** real
            = _arrayReal.get();
            *real;
            ++real)
        {
            cout << (**real).getDouble() << endl;
        }
    }
}
//===========================================================
//===========================================================
//MathVector::MathVector(const String& vector){}
MathVector::MathVector(){}
MathVector::MathVector(const PointerObject<MathReal>& arrayReal)
{
    _arrayReal = arrayReal;
}
MathVector::~MathVector(){}
const String MathVector::getNumber() const
{
    return String();
}
//===========================================================
//===========================================================
void MathVector::append(const MathReal& object)
{
    _arrayReal.addLast(new MathReal(object));
}
void MathVector::insert(const MathReal& real, const int index)
{
    
}
//===========================================================
//===========================================================
/*
class MathMatrix: public MathNumber
{
private:
    PointerObject<MathMatrix> _arrayMatrix;
    
public:
    MathMatrix();
    virtual ~MathMatrix();
    virtual MathNumber& getNumber();
};
MathMatrix::MathMatrix(){}
MathMatrix::~MathMatrix(){}
MathNumber& MathMatrix::getNumber()
{
    return *this;
}
*/
//===========================================================
//===========================================================
class MathFunction
{
public:
    MathFunction();
    virtual ~MathFunction() =0;
};
MathFunction::MathFunction(){}
MathFunction::~MathFunction(){}
//===========================================================
//===========================================================
//class 
//===========================================================
//===========================================================


#endif //ifndef __Windows_cpp_MathFunction


