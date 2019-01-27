

#ifndef __Windows_awt_Graphics
#define __Windows_awt_Graphics


//===========================================================
//===========================================================
#include "../_windows.h"
class Color;
class Font;
class FontMetrics;
class Image;
class Polygon;
class ImageObserver;
class String;
template<class T> class PointerObject;
//===========================================================
//===========================================================
class Graphics
{
private:
    friend class Component;
    
protected:
    HDC _hdc;
    Graphics();
    
public:
    virtual ~Graphics() =0;
    
    virtual void translate(int x, int y) =0;
    virtual PointerObject<Color> getColor() =0;
    virtual void setColor(Color& c) =0;
    virtual void setPaintMode() =0;
    virtual void setXORMode(Color& c1) =0;
    
    virtual PointerObject<Font> getFont() =0;
    virtual void setFont(Font& font) =0;
    virtual PointerObject<FontMetrics> getFontMetrics();
    
    virtual void drawLine(int x1, int y1, int x2, int y2) =0;
    virtual void fillRect(int x, int y, int width, int height) =0;
    virtual void drawRect(int x, int y, int width, int height);
    virtual void drawOval(int x, int y, int width, int height) =0;
    virtual void fillOval(int x, int y, int width, int height) =0;
    virtual void drawPolygon(int xPoints[], int yPoints[], int nPoints) =0;
    virtual void drawPolygon(Polygon& p);
    virtual void fillPolygon(int xPoints[], int yPoints[], int nPoints) =0;
    virtual void fillPolygon(Polygon& p);
    
    virtual void drawString(String& string, int x, int y) =0;
    
    virtual bool drawImage(
        Image& img,
        int x,
        int y,
        ImageObserver& observer) =0;
    virtual bool drawImage(
        Image& img,
        int x,
        int y,
        int width,
        int height,
        ImageObserver& observer) =0;
    
    //void drawString(String& string, int x, int y, int width, int height);
    //void drawPixel(int x, int y);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Graphics

