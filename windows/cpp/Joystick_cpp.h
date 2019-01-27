

#ifndef __Windows_cpp_Joystick_cpp
#define __Windows_cpp_Joystick_cpp


//===========================================================
//===========================================================
#include "Joystick.h"
#include "../_windows.h"


//===========================================================
//===========================================================
Joystick::Joystick(int id)
{
    _joyinfoex.dwSize = sizeof(JOYINFOEX);
    _joyinfoex.dwFlags = JOY_RETURNALL;
    _error = joyGetPosEx(id, &_joyinfoex);
}
Joystick::~Joystick(){}
//===========================================================
//===========================================================
bool Joystick::isValid()
{
    return _error == 0?
        true:
        false;
}
//===========================================================
//===========================================================
unsigned int Joystick::getX(){return _joyinfoex.dwXpos;}
unsigned int Joystick::getY(){return _joyinfoex.dwYpos;}
unsigned int Joystick::getZ(){return _joyinfoex.dwZpos;}
unsigned int Joystick::getR(){return _joyinfoex.dwRpos;}
unsigned int Joystick::getU(){return _joyinfoex.dwUpos;}
unsigned int Joystick::getV(){return _joyinfoex.dwVpos;}
unsigned int Joystick::getButtons(){return _joyinfoex.dwButtons;}
unsigned int Joystick::getButtonNumber(){return _joyinfoex.dwButtonNumber;}
unsigned int Joystick::getPOV(){return _joyinfoex.dwPOV;}
//===========================================================
//===========================================================
unsigned int Joystick::getXmin(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wXmin;
}
unsigned int Joystick::getXmax(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wXmax;
}
unsigned int Joystick::getYmin(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wRmin;
}
unsigned int Joystick::getYmax(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wRmax;
}
unsigned int Joystick::getZmin(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wRmin;
}
unsigned int Joystick::getZmax(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wRmax;
}
unsigned int Joystick::getRmin(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wRmin;
}
unsigned int Joystick::getRmax(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wRmax;
}
unsigned int Joystick::getUmin(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wRmin;
}
unsigned int Joystick::getUmax(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wRmax;
}
unsigned int Joystick::getVmin(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wRmin;
}
unsigned int Joystick::getVmax(int id)
{
    JOYCAPSW joycapsw;
    joyGetDevCapsW(id, &joycapsw, sizeof(JOYCAPSW));
    return joycapsw.wRmax;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_cpp_Joystick_cpp

