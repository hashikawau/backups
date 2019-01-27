

#ifndef __Windows_awt_Toolkit
#define __Windows_awt_Toolkit


//===========================================================
//===========================================================
#include "../_windows.h"
class Image;
class Clipboard;
class String;
template<class T> class PointerObject;
//===========================================================
//===========================================================
class Toolkit
{
private:
    HWND _hwnd;
    
public:
    Toolkit(HWND hwnd);
    virtual ~Toolkit();
    PointerObject<Clipboard> getSystemClipboard();
    PointerObject<Image> getImage(String& filename);
};
//===========================================================
//============================================================


#endif //ifndef __Windows_awt_Toolkit

