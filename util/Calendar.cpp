
#ifndef __Windows_util_Calendar_cpp
#define __Windows_util_Calendar_cpp


//===========================================================
//===========================================================
#include "Calendar.h"
#include "../cpp/PointerObject.h"
//===========================================================
//===========================================================
const int Calendar::HOUR        =10;
const int Calendar::HOUR_OF_DAY =11;
const int Calendar::MINUTE      =12;
const int Calendar::SECOND      =13;
const int Calendar::MILLISECOND =14;
//===========================================================
//===========================================================
Calendar::Calendar()
{
    GetLocalTime(&_systemTime);
}
Calendar::~Calendar(){}
//===========================================================
//===========================================================
PointerObject<Calendar> Calendar::getInstance()
{
    return PointerObject<Calendar>(new Calendar());
}
//===========================================================
//===========================================================
int Calendar::get(int field) const
{
    int value =-1;
    
    switch(field){
        case Calendar::HOUR:
            value = _systemTime.wHour %12;
            break;
            
        case Calendar::HOUR_OF_DAY:
            value = _systemTime.wHour;
            break;
            
        case Calendar::MINUTE:
            value = _systemTime.wMinute;
            break;
            
        case Calendar::SECOND:
            value = _systemTime.wSecond;
            break;
            
        case Calendar::MILLISECOND:
            value = _systemTime.wMilliseconds;
            break;
            
        default:
            break;
            
    }
    return value;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_util_Calendar_cpp

