

#ifndef __Windows_cpp_Joystick
#define __Windows_cpp_Joystick


//===========================================================
//===========================================================
#include "../_windows.h"


//===========================================================
//===========================================================
class Joystick
{
private:
    JOYINFOEX _joyinfoex;
    int _error;
    
public:
    Joystick(int id);
    ~Joystick();
    bool isValid();
    unsigned int getX();
    unsigned int getY();
    unsigned int getZ();
    unsigned int getR();
    unsigned int getU();
    unsigned int getV();
    unsigned int getButtons();
    unsigned int getButtonNumber();
    unsigned int getPOV();
    
    static unsigned int getXmin(int id);
    static unsigned int getXmax(int id);
    static unsigned int getYmin(int id);
    static unsigned int getYmax(int id);
    static unsigned int getZmin(int id);
    static unsigned int getZmax(int id);
    static unsigned int getRmin(int id);
    static unsigned int getRmax(int id);
    static unsigned int getUmin(int id);
    static unsigned int getUmax(int id);
    static unsigned int getVmin(int id);
    static unsigned int getVmax(int id);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_cpp_Joystick

