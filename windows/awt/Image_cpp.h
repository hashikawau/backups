

#ifndef __Windows_awt_Image_cpp
#define __Windows_awt_Image_cpp


//===========================================================
//===========================================================
#include "Image.h"
#include "../_windows.h"
#include "Color.h"
#include "Font.h"
#include "Graphics.h"
#include "Polygon.h"
#include "image/ImageObserver.h"
#include "../cpp/PointerObject.h"
#include "../lang/String.h"
//===========================================================
//===========================================================
Image::Image(int width, int height, HWND hwnd, HBITMAP hbitmap)
{
    _width = width;
    _height = height;
    _graphics = new ImageGraphics(_width, _height, hwnd, hbitmap);
}
Image::~Image(){}
//===========================================================
//===========================================================
PointerObject<Graphics> Image::getGraphics()
{
    return _graphics;
}
int Image::getWidth(ImageObserver& observer)
{
    return _width;
}
int Image::getHeight(ImageObserver& observer)
{
    return _height;
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
Image::ImageGraphics::ImageGraphics(
    int width, int height, HWND hwnd, HBITMAP hbitmap)
{
    _width = width;
    _height = height;
    //_hwnd = hwnd;
    HDC hdcTemp = GetDC(hwnd);
    ReleaseDC(hwnd, hdcTemp);
    
    //_fontMetrics = new FontMetrics(_hdc);
    _xormode = false;
    SelectObject(_hdc, CreateSolidBrush(0x00000000));
    SelectObject(_hdc, CreatePen(PS_SOLID, 1, 0x00000000));
    
    ZeroMemory(&_info, sizeof(_info));
    _info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    _info.bmiHeader.biWidth = width;
    _info.bmiHeader.biHeight = -height;
    _info.bmiHeader.biPlanes = 1;
    _info.bmiHeader.biBitCount = 32;
    _hbitmap = CreateDIBSection(
        0,
        &_info,
        DIB_RGB_COLORS,
        static_cast<void**>(&_bits),
        0,
        0);
    //cout << "hbitmap  " << _hbitmap << endl;
    //cout << "bits     " << _bits << endl;
    SelectObject(_hdc, _hbitmap);
}
Image::ImageGraphics::~ImageGraphics()
{
    DeleteDC(_hdc);
    DeleteObject(_hbitmap);
}
//===========================================================
//===========================================================
void Image::ImageGraphics::translate(int x, int y)
{
    OffsetViewportOrgEx(_hdc, x, y, NULL);
}
//===========================================================
//===========================================================
PointerObject<Color> Image::ImageGraphics::getColor()
{
    LOGBRUSH logbrush;
    GetObject(
        GetCurrentObject(_hdc, OBJ_BRUSH),
        sizeof(logbrush),
        &logbrush);
    
    return PointerObject<Color>(
        new Color(logbrush.lbColor));
}
void Image::ImageGraphics::setColor(Color& c)
{
    //_color = c;
    SetTextColor(_hdc, 0x00FFFFFF & c.getRGB());
    DeleteObject(
        SelectObject(_hdc, CreateSolidBrush(0x00FFFFFF & c.getRGB())));
    DeleteObject(
        SelectObject(_hdc, CreatePen(PS_SOLID, 1, 0x00FFFFFF & c.getRGB())));
}
//===========================================================
//===========================================================
void Image::ImageGraphics::setPaintMode()
{
    _xormode = false;
    SetROP2(_hdc, R2_COPYPEN);
}
void Image::ImageGraphics::setXORMode(Color& c1)
{
    _xormode = true;
    SetROP2(_hdc, R2_XORPEN);
}
//===========================================================
//===========================================================
PointerObject<Font> Image::ImageGraphics::getFont()
{
    Font* font = new Font(String(""), 0, 0);
    
    GetObject(
        GetCurrentObject(_hdc, OBJ_FONT),
        sizeof(*font),
        font);
    return PointerObject<Font>(font);
}
void Image::ImageGraphics::setFont(Font& font)
{
    DeleteObject(
        SelectObject(_hdc, CreateFontIndirectW(&font)));
}
PointerObject<FontMetrics> Image::ImageGraphics::getFontMetrics()
{
    return PointerObject<FontMetrics>(new FontMetrics(_hdc));
}
//===========================================================
//===========================================================
void Image::ImageGraphics::drawLine(int x1, int y1, int x2, int y2)
{
    MoveToEx(_hdc, x1, y1, NULL);
    LineTo(_hdc, x2, y2);
}
//===========================================================
//===========================================================
void Image::ImageGraphics::fillRect(
    int x, int y, int width, int height)
{
    Rectangle(_hdc, x, y, x +width, y +height);
}
void Image::ImageGraphics::drawRect(
    int x, int y, int width, int height)
{
    //DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
    HBRUSH hb = SelectObject(_hdc, GetStockObject(NULL_BRUSH));
    Rectangle(_hdc, x, y, x +width, y +height);
    SelectObject(_hdc, hb);
}
//===========================================================
//===========================================================
void Image::ImageGraphics::drawOval(
    int x,
    int y,
    int width,
    int height)
{
    HBRUSH hb = SelectObject(_hdc, GetStockObject(NULL_BRUSH));
    Ellipse(_hdc, x, y, x +width, y +height);
    SelectObject(_hdc, hb);
}
void Image::ImageGraphics::fillOval(
    int x, int y, int width, int height)
{
    Ellipse(_hdc, x, y, x +width, y +height);
}
//===========================================================
//===========================================================
void Image::ImageGraphics::drawPolygon(
    int xPoints[],
    int yPoints[],
    int nPoints)
{
    POINT points[nPoints];
    for(int i= 0; i< nPoints -1; ++i){
        points[i].x = xPoints[i+1];
        points[i].y = yPoints[i+1];
    }
    points[nPoints -1].x = xPoints[0];
    points[nPoints -1].y = yPoints[0];
    MoveToEx(_hdc, xPoints[0], yPoints[0], NULL);
    PolylineTo(_hdc , points , nPoints);
}
void Image::ImageGraphics::drawPolygon(Polygon& p)
{
    drawPolygon(p.xpoints, p.ypoints, p.npoints);
}
void Image::ImageGraphics::fillPolygon(
    int xPoints[], int yPoints[], int nPoints)
{
    POINT points[nPoints];
    for(int i= 0; i< nPoints; ++i){
        points[i].x = xPoints[i];
        points[i].y = yPoints[i];
    }
    int np[] = {nPoints};
    
    SetPolyFillMode(_hdc , WINDING);
    PolyPolygon(_hdc, points, np, 1);
}
void Image::ImageGraphics::fillPolygon(Polygon& p)
{
    fillPolygon(p.xpoints, p.ypoints, p.npoints);
}
//===========================================================
//===========================================================
void Image::ImageGraphics::drawString(
    String& string, int x, int y)
{
    SetBkMode(_hdc, TRANSPARENT);
    ExtTextOutW(
        _hdc,
        x,
        y,
        ETO_CLIPPED,
        NULL,
        string.toCharArray(),
        string.length(),
        NULL);
}
//===========================================================
//===========================================================
bool Image::ImageGraphics::drawImage(
        Image& img,
        int x,
        int y,
        ImageObserver& observer)
{
    observer.imageUpdate(
        img,
        ImageObserver::ALLBITS,
        x, y,
        img.getWidth(observer), img.getHeight(observer));
    
    return true;
}
bool Image::ImageGraphics::drawImage(
        Image& img,
        int x,
        int y,
        int width,
        int height,
        ImageObserver& observer)
{
    observer.imageUpdate(
        img,
        ImageObserver::ALLBITS,
        x, y,
        width, height);
        
    return true;
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
void Image::ImageGraphics::drawPixel(int x, int y)
{
    int* b = const_cast<int*>(_bits);
    int c =0;
        //_color.getRGB() & 0x0000FF00
        //| (_color.getRGB() & 0x00FF0000) >>16
        //| (_color.getRGB() & 0x000000FF) <<16;
    for(int i=0; i< 600; ++i){
        *b = c;
        b += 601;
    }
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Image_cpp

