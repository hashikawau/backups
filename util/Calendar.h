
#ifndef __Windows_util_Calendar
#define __Windows_util_Calendar


//===========================================================
//===========================================================
#include <windows.h>
template<class T> class PointerObject;
//===========================================================
//===========================================================
class Calendar
{
public:
    static const int HOUR;
    static const int HOUR_OF_DAY;
    static const int MINUTE;
    static const int SECOND;
    static const int MILLISECOND;
    
protected:
    SYSTEMTIME _systemTime;
    
public:
    Calendar();
    virtual ~Calendar();
    static PointerObject<Calendar> getInstance();
    int get(int field) const;
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_util_Calendar

