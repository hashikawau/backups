

#ifndef __Windows_awt_Label_cpp
#define __Windows_awt_Label_cpp


//===========================================================
//===========================================================
#include "Label.h"
#include "Color.h"
#include "Component.h"
#include "Font.h"
#include "Graphics.h"
#include "../lang/String.h"
//===========================================================
//===========================================================
Label::Label(String& label)
{
    setBackground(Color(0xFFFFFF));
    setText(label);
}
Label::~Label(){}
//===========================================================
//===========================================================
void Label::update(Graphics& g)
{
    g.setColor(getBackground());
    g.fillRect(0, 0, getWidth(), getHeight());
    paint(g);
}
void Label::paint(Graphics& g)
{
    g.setColor(Color(0x00));
    g.drawString(_label, 0, 0);
}
//===========================================================
//===========================================================
void Label::setText(String& label)
{
    _label = label;
    
    //Graphics g(_hwnd);
    //FontMetrics fm = g.getFontMetrics();
    PointerObject<FontMetrics> fm = getFontMetrics(getFont());
    
    int width = fm->stringWidth(_label);
    int height = fm->getHeight();
    setSize(width, height);
}
String Label::getText()
{
    return String(_label);
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Label_cpp

