


#ifndef __Windows_awt_Canvas
#define __Windows_awt_Canvas



#include "Component.h"

//===========================================================
//===========================================================
class Canvas: public Component
{
private:
    
protected:
    
public:
    Canvas();
    virtual ~Canvas();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
};
//===========================================================
//===========================================================
Canvas::Canvas()
{
    setBackground(Color(0xFFFFFF));
}
Canvas::~Canvas(){}
//===========================================================
//===========================================================
void Canvas::update(Graphics& g)
{
    g.setColor(getBackground());
    g.fillRect(0, 0, getWidth(), getHeight());
    g.setColor(Color(0x00));
    paint(g);
}
void Canvas::paint(Graphics& g){}
//===========================================================
//===========================================================




#endif //ifndef __Windows_awt_Canvas

