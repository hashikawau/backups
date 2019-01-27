

#ifndef __Windows_cpp_MathTerm
#define __Windows_cpp_MathTerm


#include "windows\cpp\PointerObject.h"
#include "windows\lang\Math.h"
#include "windows\lang\String.h"

#include "windows\util\LinkedList.h"



//===========================================================
//===========================================================
class MathComponent
{
public:
    MathComponent();
    virtual ~MathComponent() =0;
};
MathComponent::MathComponent(){}
MathComponent::~MathComponent(){}
//===========================================================
//===========================================================
class MathOperator: public MathComponent
{
public:
    MathOperator();
    virtual ~MathOperator() =0;
};
MathOperator::MathOperator(){}
MathOperator::~MathOperator(){}
//===========================================================
//===========================================================
class MathTerm: public MathComponent
{
public:
    MathTerm();
    virtual ~MathTerm() =0;
};
MathTerm::MathTerm(){}
MathTerm::~MathTerm(){}
//===========================================================
//===========================================================
//class 
//===========================================================
//===========================================================


#endif //ifndef __Windows_cpp_MathTerm


