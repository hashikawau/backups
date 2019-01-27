

#ifndef __Windows_awt_Color
#define __Windows_awt_Color


//===========================================================
//===========================================================
#include "../_windows.h"
//===========================================================
//===========================================================
class Color
{
public:
    static Color white;
    static Color lightGray;
    static Color gray;
    static Color darkGray;
    static Color black;
    static Color red;
    static Color pink;
    static Color orange;
    static Color yellow;
    static Color green;
    static Color magenta;
    static Color cyan;
    static Color blue;
    
protected:
    int _rgb;
    
public:
    explicit Color(int rgb =0);
    Color(int r, int g, int b, int a =0xFF);
    virtual ~Color();
    int getRGB() const;
};
//===========================================================
//===========================================================
class SystemColor: public Color
{
public:
    static SystemColor desktop;
    static SystemColor activeCaption;
    static SystemColor activeCaptionText;
    static SystemColor activeCaptionBorder;
    static SystemColor inactiveCaption;
    static SystemColor inactiveCaptionText;
    static SystemColor inactiveCaptionBorder;
    static SystemColor window;
    static SystemColor windowBorder;
    static SystemColor windowText;
    static SystemColor menu;
    static SystemColor menuText;
    static SystemColor text;
    static SystemColor textText;
    static SystemColor textHighlight;
    static SystemColor textHighlightText;
    static SystemColor textInactiveText;
    
public:
    SystemColor(int rgb);
    virtual ~SystemColor();
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Color

