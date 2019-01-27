

#ifndef __Windows_awt_Graphics_cpp
#define __Windows_awt_Graphics_cpp


//===========================================================
//===========================================================
#include "Graphics.h"
#include "Font.h"
#include "../cpp/PointerObject.h"
//===========================================================
//===========================================================
Graphics::Graphics(){}
Graphics::~Graphics(){}
void Graphics::drawRect(int x, int y, int width, int height){}
void Graphics::drawPolygon(Polygon& p){}
void Graphics::fillPolygon(Polygon& p){}
PointerObject<FontMetrics> Graphics::getFontMetrics()
{
    return PointerObject<FontMetrics>(0);
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Graphics_cpp

