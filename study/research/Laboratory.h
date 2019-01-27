

#ifndef __Windows_research_Laboratory
#define __Windows_research_Laboratory

#include "windows\lang\String.h"
#include <windows.h>

//===========================================================
//===========================================================
class Laboratory
{
protected:
    double* _state;
    double* _input;
    double _dt;
    double _elapsedTime;
    
    virtual void next();
    virtual void determineInput();
    virtual const String print();
    
public:
    Laboratory();
    Laboratory(const Laboratory&);
    Laboratory& operator=(const Laboratory&);
    virtual ~Laboratory();
    
    const String calculate(int numstep);
};
//===========================================================
//===========================================================
Laboratory::Laboratory():
    _state(0),
    _input(0),
    _dt(1),
    _elapsedTime(0)
{}
Laboratory::~Laboratory()
{
    delete [] _state;
    delete [] _input;
}
//===========================================================
//===========================================================
void Laboratory::next(){}
void Laboratory::determineInput(){}
const String Laboratory::print(){ return String(""); }
//===========================================================
//===========================================================
const String Laboratory::calculate(int numstep)
{
    int elapsedTime = GetTickCount();
    
    determineInput();
    for(int i=0; i< numstep; ++i){
        next();
    }
    _elapsedTime += _dt *numstep;
    
    return print();
}
//===========================================================
//===========================================================
/*
void Laboratory::putForward(int numstep)
{
    if(_stateeq){
        _stateeq->calcState(numstep, _state, _input);
    }
}
void Laboratory::determineInput()
{
    if(_cu){
        _cu->calcInput(_state, _input);
    }
}
void Laboratory::printOutput(Variable& output)
{
    if(_outputeq){
        _outputeq->calcOutput(output, _state, _input);
    }
}
*/
//===========================================================
//===========================================================


#endif //ifndef __Windows_research_Laboratory

