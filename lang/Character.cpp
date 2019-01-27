

#ifndef __Windows_lang_Character_cpp
#define __Windows_lang_Character_cpp


//===========================================================
//===========================================================
#include "Character.h"
//===========================================================
//===========================================================
Character::Character(){}
Character::~Character(){}
//===========================================================
//===========================================================
bool Character::isDigit(wchar_t wc)
{
    bool isdigit = false;
    if(static_cast<unsigned short>(wc) >= static_cast<unsigned short>(L'0'))
    {
        if(static_cast<unsigned short>(wc) <= static_cast<unsigned short>(L'9'))
        {
            isdigit = true;
        }
    }
    return isdigit;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_Character_cpp

