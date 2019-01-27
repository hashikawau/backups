

#ifndef __Windows_awt_Toolkit_cpp
#define __Windows_awt_Toolkit_cpp


//===========================================================
//===========================================================
#include "Toolkit.h"
#include "../_windows.h"
#include "Image.h"
#include "datatransfer/Clipboard.h"
#include "../cpp/PointerObject.h"
//===========================================================
//===========================================================
Toolkit::Toolkit(HWND hwnd): _hwnd(hwnd){}
Toolkit::~Toolkit(){}
//===========================================================
//===========================================================
PointerObject<Clipboard> Toolkit::getSystemClipboard()
{
    return PointerObject<Clipboard>(new Clipboard(_hwnd));
}
//===========================================================
//===========================================================
PointerObject<Image> Toolkit::getImage(String& filename)
{
    HBITMAP hbitmap = static_cast<HBITMAP>(LoadImage(
        0,
        filename.toCharArray(),
        IMAGE_BITMAP,
        0,
        0,
        LR_LOADFROMFILE));
    
    Image* image =0;
    if(hbitmap){
        BITMAP bitmap;
        GetObject(hbitmap, sizeof(BITMAP), &bitmap);
        image = new Image(bitmap.bmWidth, bitmap.bmHeight, _hwnd, hbitmap);
    }
    
    return PointerObject<Image>(image);
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Toolkit_cpp

