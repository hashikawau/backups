

#ifndef __Windows_awt_Color_cpp
#define __Windows_awt_Color_cpp


//===========================================================
//===========================================================
#include "Color.h"
#include "../_windows.h"
//===========================================================
//===========================================================
Color Color::white     = Color(0xFFFFFF);
Color Color::lightGray = Color(0xD3D3D3);
Color Color::gray      = Color(0x808080);
Color Color::darkGray  = Color(0xA9A9A9);
Color Color::black     = Color(0x000000);
Color Color::red       = Color(0x0000FF);
Color Color::pink      = Color(0xCBC0FF);
Color Color::orange    = Color(0x00A5FF);
Color Color::yellow    = Color(0x00FFFF);
Color Color::green     = Color(0x008000);
Color Color::magenta   = Color(0xFF00FF);
Color Color::cyan      = Color(0xFFFF00);
Color Color::blue      = Color(0xFF0000);
//===========================================================
//===========================================================
Color::Color(int rgb): _rgb(0xFFFFFF &rgb){}
Color::Color(int r, int g, int b, int a):
    _rgb(a<<24 | (0xFF & b)<<16 | (0xFF & g)<<8 | (0xFF & r))
{}
Color::~Color(){}
//===========================================================
//===========================================================
int Color::getRGB() const
{
    return _rgb;
}
//===========================================================
//===========================================================
SystemColor SystemColor::desktop
    = SystemColor(GetSysColor(COLOR_DESKTOP));
SystemColor SystemColor::activeCaption
    = SystemColor(GetSysColor(COLOR_ACTIVECAPTION));
SystemColor SystemColor::activeCaptionText
    = SystemColor(GetSysColor(COLOR_CAPTIONTEXT));
SystemColor SystemColor::activeCaptionBorder
    = SystemColor(GetSysColor(COLOR_ACTIVEBORDER));
SystemColor SystemColor::inactiveCaption
    = SystemColor(GetSysColor(COLOR_INACTIVECAPTION));
SystemColor SystemColor::inactiveCaptionText
    = SystemColor(GetSysColor(COLOR_INACTIVECAPTIONTEXT));
SystemColor SystemColor::inactiveCaptionBorder
    = SystemColor(GetSysColor(COLOR_INACTIVEBORDER));
SystemColor SystemColor::window
    = SystemColor(GetSysColor(COLOR_WINDOW));
SystemColor SystemColor::windowBorder
    = SystemColor(GetSysColor(COLOR_WINDOWFRAME));
SystemColor SystemColor::windowText
    = SystemColor(GetSysColor(COLOR_WINDOWTEXT));
SystemColor SystemColor::menu
    = SystemColor(GetSysColor(COLOR_MENU));
SystemColor SystemColor::menuText
    = SystemColor(GetSysColor(COLOR_MENUTEXT));
SystemColor SystemColor::text
    = SystemColor(GetSysColor(COLOR_BTNFACE));
SystemColor SystemColor::textText
    = SystemColor(GetSysColor(COLOR_BTNTEXT));
SystemColor SystemColor::textHighlight
    = SystemColor(GetSysColor(COLOR_HIGHLIGHT));
SystemColor SystemColor::textHighlightText
    = SystemColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
SystemColor SystemColor::textInactiveText
    = SystemColor(GetSysColor(COLOR_GRAYTEXT));
//===========================================================
//===========================================================
SystemColor::SystemColor(int rgb): Color(rgb){}
SystemColor::~SystemColor(){}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Color_cpp

