

#ifndef __Windows_awt_Image
#define __Windows_awt_Image


//===========================================================
//===========================================================
#include "../_windows.h"
#include "Graphics.h"
#include "../cpp/PointerObject.h"
class Color;
class Font;
class FontMetrics;
class Image;
class Polygon;
class ImageObserver;
class String;
//===========================================================
//===========================================================
class Image
{
private:
    class ImageGraphics;
    
protected:
    int _width;
    int _height;
    PointerObject<Graphics> _graphics;
    
public:
    Image(int width, int height, HWND hwnd, HBITMAP hbitmap =0);
    virtual ~Image();
    PointerObject<Graphics> getGraphics();
    int getWidth(ImageObserver& observer);
    int getHeight(ImageObserver& observer);
};
//===========================================================
//===========================================================
class Image::ImageGraphics: public Graphics
{
private:
    friend class Image;
    
public:
    HWND _hwnd;
    //HDC _hdc;
    //Color _color;
    bool _xormode;
    
    int _width;
    int _height;
    HBITMAP _hbitmap;
    BYTE* _bits;
    BITMAPINFO _info;
    
    
public:
    ImageGraphics(int width, int height, HWND hwnd, HBITMAP hbitmap =0);
    virtual ~ImageGraphics();
    virtual void translate(int x, int y);
    virtual PointerObject<Color> getColor();
    virtual void setColor(Color& c);
    virtual void setPaintMode();
    virtual void setXORMode(Color& c1);
    
    virtual PointerObject<Font> getFont();
    virtual void setFont(Font& font);
    virtual PointerObject<FontMetrics> getFontMetrics();
    
    virtual void drawLine(int x1, int y1, int x2, int y2);
    virtual void drawRect(int x, int y, int width, int height);
    virtual void fillRect(int x, int y, int width, int height);
    virtual void drawOval(int x, int y, int width, int height);
    virtual void fillOval(int x, int y, int width, int height);
    virtual void drawPolygon(int xPoints[], int yPoints[], int nPoints);
    virtual void drawPolygon(Polygon& p);
    virtual void fillPolygon(int xPoints[], int yPoints[], int nPoints);
    virtual void fillPolygon(Polygon& p);
    virtual void drawString(String& string, int x, int y);
    
    virtual bool drawImage(
        Image& img,
        int x,
        int y,
        ImageObserver& observer);
    virtual bool drawImage(
        Image& img,
        int x,
        int y,
        int width,
        int height,
        ImageObserver& observer);
    
    void drawPixel(int x, int y);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Image

