

#ifndef __Windows_util_EventObject_cpp
#define __Windows_util_EventObject_cpp


//===========================================================
//===========================================================
#include "EventObject.h"
#include "lang/Object.h"
//===========================================================
//===========================================================
EventObject::EventObject(Object& source):
    _source(&source),
    _source__(reinterpret_cast<void*>(&source))
{}
EventObject::~EventObject(){}
Object& EventObject::getSource() const
{
    return *_source;
}
//===========================================================
//===========================================================
EventObject::EventObject(void* source):
    _source(reinterpret_cast<Object*>(source)),
    _source__(source)
{}
void* EventObject::getSource()
{
    return _source__;
}
//===========================================================
//===========================================================
EventListener::EventListener(){}
EventListener::~EventListener(){}
//===========================================================
//===========================================================


#endif //ifndef __Windows_util_EventObject_cpp

