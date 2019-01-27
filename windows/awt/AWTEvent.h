

#ifndef __Windows_awt_AWTEvent
#define __Windows_awt_AWTEvent


//===========================================================
//===========================================================
#include "../../util/EventObject.h"
//===========================================================
//===========================================================
class AWTEvent: public EventObject
{
public:
    static const long long COMPONENT_EVENT_MASK;
    static const long long CONTAINER_EVENT_MASK;
    static const long long FOCUS_EVENT_MASK;
    static const long long KEY_EVENT_MASK;
    static const long long MOUSE_EVENT_MASK;
    static const long long MOUSE_MOTION_EVENT_MASK;
    static const long long WINDOW_EVENT_MASK;
    static const long long ACTION_EVENT_MASK;
    static const long long ADJUSTMENT_EVENT_MASK;
    static const long long ITEM_EVENT_MASK;
    static const long long TEXT_EVENT_MASK;
    static const long long INPUT_METHOD_EVENT_MASK;
    static const long long PAINT_EVENT_MASK;
    static const long long INVOCATION_EVENT_MASK;
    static const long long HIERARCHY_EVENT_MASK;
    static const long long HIERARCHY_BOUNDS_EVENT_MASK;
    static const long long MOUSE_WHEEL_EVENT_MASK;
    static const long long WINDOW_STATE_EVENT_MASK;
    static const long long WINDOW_FOCUS_EVENT_MASK;
    static const int  RESERVED_ID_MAX;
    
protected:
    int _id;
    
public:
    explicit AWTEvent(unsigned int source);
    AWTEvent(Object& source, int id);
    virtual ~AWTEvent() =0;
    int getID();
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_AWTEvent

