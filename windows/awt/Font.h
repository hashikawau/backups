

#ifndef __Windows_awt_Font
#define __Windows_awt_Font


//===========================================================
//===========================================================
#include "../_windows.h"
class String;
//===========================================================
//===========================================================
class Font: protected LOGFONTW
{
public:
    static const int PLAIN;
    static const int BOLD;
    static const int ITALIC;
    
public:
    Font(String& name, int style, int size);
    ~Font();
    int getSize();
};
//===========================================================
//===========================================================
class FontMetrics: protected TEXTMETRICW
{
private:
    friend BOOL WINAPI GetTextMetricsW(HDC, TEXTMETRICW);
    
public:
    HDC _hdc;
    HWND _hwnd;
    //int getAscent();
    //int getDescent();
    FontMetrics(HDC hdc);
    FontMetrics(HWND hwnd, Font& font);
    virtual ~FontMetrics();
    virtual int getHeight();
    virtual int getWidth();
    virtual int charWidth(wchar_t wc);
    virtual int stringWidth(String& str);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Font

