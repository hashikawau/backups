

#ifndef __Windows_research_Laboratory
#define __Windows_research_Laboratory


#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
//#include <windows.h>
//#include "windows\_lang.h"
#include "windows\cpp\PointerObject.h"

#include "Variable.h"
//#include "Plate.h"
//#include "Lamp.h"
//===========================================================
//===========================================================
class StateEq
{
public:
    StateEq();
    virtual ~StateEq();
    virtual void calcState(
        int numstep,
        Variable& state,
        Variable& input) =0;
};
StateEq::StateEq(){}
StateEq::~StateEq(){}
//===========================================================
//===========================================================
class ControlUnit
{
public:
    ControlUnit();
    virtual ~ControlUnit();
    virtual void calcInput(
        Variable& state,
        Variable& input) =0;
};
ControlUnit::ControlUnit(){}
ControlUnit::~ControlUnit(){}
//===========================================================
//===========================================================
class ObservationEq
{
public:
    ObservationEq();
    virtual ~ObservationEq();
    virtual void calcOutput(
        Variable& output,
        Variable& state,
        Variable& input) =0;
};
ObservationEq::ObservationEq(){}
ObservationEq::~ObservationEq(){}
//===========================================================
//===========================================================
class Laboratory
{
private:
    Variable _state;
    Variable _input;
    PointerObject<StateEq>       _stateeq;
    PointerObject<ControlUnit>   _cu;
    PointerObject<ObservationEq> _outputeq;
    
public:
    Laboratory();
    ~Laboratory();
    
    //void setState();
    //void setInput();
    void setStateEq(const StateEq& stateeq);
    void setControlUnit(const ControlUnit& cu);
    void setObservationEq(const ObservationEq& outputeq);
    
    void putForward(int numstep);
    void determineInput();
    virtual void printOutput(Variable& output);
};
//===========================================================
//===========================================================
Laboratory::Laboratory()
{
    /*
    _plate = new Plate();
    _lamp = new Lamp [4];
    
    _plate->show(ofs);
    
    ofs.setf(ios::scientific, ios::floatfield);
    ofs.precision(3);
    for(int i=0; i< 10; ++i){
        _plate->cnMethod(100);
        _plate->showTemp(ofs);
    }
    */
}
Laboratory::~Laboratory(){}
//===========================================================
//===========================================================
void Laboratory::setStateEq(const StateEq& stateeq)
{
    _stateeq = &stateeq;
}
void Laboratory::setControlUnit(const ControlUnit& cu)
{
    _cu = &cu;
}
void Laboratory::setObservationEq(const ObservationEq& outputeq)
{
    _outputeq = &outputeq;
}
//===========================================================
//===========================================================
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
//===========================================================
//===========================================================


#endif //ifndef __Windows_research_Laboratory

