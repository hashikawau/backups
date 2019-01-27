

#ifndef __Windows_awt_Font_cpp
#define __Windows_awt_Font_cpp


//===========================================================
//===========================================================
#include "Font.h"
#include "../lang/String.h"
//===========================================================
//===========================================================
const int Font::PLAIN  =0;
const int Font::BOLD   =1;
const int Font::ITALIC =2;
//===========================================================
//===========================================================
Font::Font(String& name, int style, int size)
{
    lfHeight         = size;
    lfWidth          = 0;
    lfEscapement     = 0;
    lfOrientation    = 0;
    lfWeight         = Font::BOLD & style? FW_BOLD: 0;
    lfItalic         = Font::ITALIC & style;
    lfUnderline      = false;
    lfStrikeOut      = false;
    lfCharSet        = SHIFTJIS_CHARSET;
    lfOutPrecision   = OUT_DEFAULT_PRECIS;
    lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    lfQuality        = DEFAULT_QUALITY ;
    lfPitchAndFamily = 0;
    lfFaceName[0]    = '\0';
}
Font::~Font(){}
int Font::getSize(){ return lfHeight;}
//===========================================================
//===========================================================
FontMetrics::FontMetrics(HDC hdc): _hdc(hdc), _hwnd(0)
{
    GetTextMetricsW(_hdc, this);
}
FontMetrics::FontMetrics(HWND hwnd, Font& font)
{
    _hwnd = hwnd;
    _hdc = GetDC(_hwnd);
    SelectObject(_hdc, CreateFontIndirectW(&font));
    GetTextMetricsW(_hdc, this);
}
FontMetrics::~FontMetrics()
{
    if(_hwnd){
        DeleteObject(SelectObject(_hdc, GetStockObject(SYSTEM_FONT)));
        ReleaseDC(_hwnd, _hdc);
    }
}
int FontMetrics::getHeight()
{
    return tmHeight;
}
int FontMetrics::getWidth()
{
    return tmAveCharWidth +8;
}
int FontMetrics::charWidth(wchar_t wc)
{
    SIZE size;
    GetTextExtentPoint32W(_hdc, &wc, 1, &size);
    return size.cx;
}
int FontMetrics::stringWidth(String& str) 
{
    SIZE size;
    GetTextExtentPoint32W(
        _hdc,
        const_cast<const wchar_t*>(str.toCharArray()),
        str.length(),
        &size);
    return size.cx;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Font_cpp

