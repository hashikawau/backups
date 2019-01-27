

#ifndef __Windows_lang_System_cpp
#define __Windows_lang_System_cpp


//===========================================================
//===========================================================
#include "System.h"
#include <windows.h>
//===========================================================
//===========================================================
System::System(){}
System::~System(){}
//===========================================================
//===========================================================
long long int System::currentTimeMillis()
{
    //MMRESULT timeGetSystemTime(LPMMTIME pmmt, UINT cbmmt);
    //VOID GetLocalTime(LPSYSTEMTIME lpSystemTime);
    //VOID GetSystemTime(LPSYSTEMTIME lpSystemTime);
    //typedef struct _SYSTEMTIME{
    //    WORD wYear
    //    WORD wMonth
    //    WORD wDayOfWeek
    //    WORD wDay
    //    WORD wHour
    //    WORD wMinute
    //    WORD wSecond
    //    WORD wMilliseconds
    //} SYSTEMTIME;
    return GetTickCount();
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_System_cpp

