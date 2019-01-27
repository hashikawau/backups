

#ifndef __Windows_lang_Object
#define __Windows_lang_Object


//===========================================================
//===========================================================
#include <windows.h>
class String;
//===========================================================
//===========================================================
class Object
{
protected:
    
public:
    Object();
    virtual ~Object();
    virtual Object* clone();
    virtual void finalize();
    virtual String toString();
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_Object

