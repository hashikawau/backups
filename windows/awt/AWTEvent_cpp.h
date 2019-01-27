

#ifndef __Windows_awt_AWTEvent_cpp
#define __Windows_awt_AWTEvent_cpp


//===========================================================
//===========================================================
#include "AWTEvent.h"
#include "../util/EventObject.h"
#include "../util/EventObject_cpp.h"
//===========================================================
//===========================================================
const long long AWTEvent::COMPONENT_EVENT_MASK        =1;
const long long AWTEvent::CONTAINER_EVENT_MASK        =2;
const long long AWTEvent::FOCUS_EVENT_MASK            =4;
const long long AWTEvent::KEY_EVENT_MASK              =8;
const long long AWTEvent::MOUSE_EVENT_MASK            =16;
const long long AWTEvent::MOUSE_MOTION_EVENT_MASK     =32;
const long long AWTEvent::WINDOW_EVENT_MASK           =64;
const long long AWTEvent::ACTION_EVENT_MASK           =128;
const long long AWTEvent::ADJUSTMENT_EVENT_MASK       =256;
const long long AWTEvent::ITEM_EVENT_MASK             =512;
const long long AWTEvent::TEXT_EVENT_MASK             =1024;
const long long AWTEvent::INPUT_METHOD_EVENT_MASK     =2048;
const long long AWTEvent::PAINT_EVENT_MASK            =8192;
const long long AWTEvent::INVOCATION_EVENT_MASK       =16384;
const long long AWTEvent::HIERARCHY_EVENT_MASK        =32768;
const long long AWTEvent::HIERARCHY_BOUNDS_EVENT_MASK =65536;
const long long AWTEvent::MOUSE_WHEEL_EVENT_MASK      =131072;
const long long AWTEvent::WINDOW_STATE_EVENT_MASK     =262144;
const long long AWTEvent::WINDOW_FOCUS_EVENT_MASK     =524288;
const int  AWTEvent::RESERVED_ID_MAX =1999;
//===========================================================
//===========================================================
AWTEvent::AWTEvent(unsigned int source): EventObject(source){}
AWTEvent::AWTEvent(Object& source, int id):
    EventObject(source),
    _id(id)
{}
AWTEvent::~AWTEvent(){}
int AWTEvent::getID()
{
    return _id;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_AWTEvent_cpp

