

#ifndef __Windows_awt_Component_cpp
#define __Windows_awt_Component_cpp


//===========================================================
//===========================================================
#include "Component.h"
#include "../_windows.h"
#include "Color.h"
#include "Cursor.h"
#include "Font.h"
#include "Graphics.h"
#include "Image.h"
#include "Menu.h"
#include "Point.h"
#include "Polygon.h"
#include "Toolkit.h"
#include "event/ActionEvent.h"
#include "image/ImageObserver.h"
#include "../cpp/PointerObject.h"
#include "../lang/Math.h"
#include "../lang/String.h"
//===========================================================
//===========================================================
class Component::__Component_Graphics: public Graphics
{
private:
    friend class Component;
    
    HWND _hwnd;
    //HDC _hdc;
    //Color _color;
    bool _xormode;
    
public:
    __Component_Graphics(HWND hwnd);
    virtual ~__Component_Graphics();
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
};
//===========================================================
//===========================================================

//===========================================================
//===========================================================
Component::Component():
    _preferredSize(new Dimension(1, 1)),
    _minimumSize(new Dimension(0, 0)),
    _maximumSize(new Dimension(
        static_cast<unsigned short>(-1),
        static_cast<unsigned short>(-1)))
{
    wchar_t szClassName[sizeof(int)*8+1];
    wsprintfW(szClassName, L"%d", (int)(this));
    static WNDCLASSW wndclass;
    wndclass.style         = 0;//CS_DBLCLKS;
    wndclass.lpfnWndProc   = WndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = GetModuleHandle(0);
    wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor       = NULL;//LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wndclass.lpszClassName = szClassName;
    RegisterClassW(&wndclass);
    
    _hwnd = CreateWindowW(
        szClassName,
        NULL,
        WS_POPUP,//WS_OVERLAPPEDWINDOW,// | WS_DISABLED,
        0,
        0,
        0,
        0,
        NULL,
        NULL,
        GetModuleHandle(0),
        NULL
    );
    _cursor = new Cursor(Cursor::DEFAULT_CURSOR);
    SetCursor(LoadCursor(NULL, IDC_ARROW));
    
    //ShowWindow(_hwnd, SW_HIDE);
}
Component::~Component()
{
    ShowWindow(_hwnd, SW_HIDE);
    DestroyWindow(_hwnd);
}
//===========================================================
//===========================================================
Container& Component::getParent()
{
    Container* parent =0;
    HWND hwndParent = GetParent(_hwnd);//GetWindow(_hwnd, GW_OWNER);
    if(hwndParent){
        wchar_t szClassName[sizeof(int)*8+1];
        GetClassNameW(hwndParent, szClassName, sizeof(int)*8+1);
        parent = static_cast<Container*>(_wtoi(szClassName));
    }
    return *parent;
}
//PointerObject<Container> Component::getParent(){}
//===========================================================
//===========================================================
PointerObject<Toolkit> Component::getToolkit()
{
    return PointerObject<Toolkit>(new Toolkit(_hwnd));
}
//===========================================================
//===========================================================
PointerObject<Point> Component::getMousePosition()
{
    POINT mp;
    GetCursorPos(&mp);
    RECT cr;
    GetWindowRect(_hwnd, &cr);
    int x = mp.x -cr.left;
    int y = mp.y -cr.top;
    if(x <0 || mp.x >cr.right || y <0 || mp.y >cr.bottom){
        return PointerObject<Point>();
    }
    return PointerObject<Point>(new Point(x, y));
}
//===========================================================
//===========================================================
void Component::setVisible(bool b)
{
    //DrawMenuBar(_hwnd);
    //ShowWindow(_hwnd, b);
    //UpdateWindow(_hwnd);
    
    unsigned int visible = b?
        SWP_SHOWWINDOW:
        SWP_HIDEWINDOW;
    //SetWindowPos(
    //    _hwnd, NULL,
    //    0, 0, 0, 0,
    //    b? SWP_SHOWWINDOW: SWP_HIDEWINDOW
    //    | SWP_NOSENDCHANGING | SWP_NOREDRAW | SWP_NOZORDER
    //    | SWP_NOSIZE | SWP_NOMOVE);
    //DrawMenuBar(_hwnd);
    //InvalidateRect(_hwnd, NULL, false);
    //UpdateWindow(_hwnd);
    
    //cout <<"setvisible()  " << getWidth() << " , " << getHeight() << endl;
    RECT rect;
    GetWindowRect(_hwnd, &rect);
    SetWindowPos(
        _hwnd,
        NULL,
        rect.left,
        rect.top,
        rect.right -rect.left,
        rect.bottom -rect.top,
        visible | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOSENDCHANGING);
    //UpdateWindow(_hwnd);
}
//===========================================================
//===========================================================
PointerObject<Color> Component::getBackground()
{
    HBRUSH hbrush = static_cast<HBRUSH>(
        GetClassLong(_hwnd, GCL_HBRBACKGROUND));
    LOGBRUSH logbrush;
    GetObject(hbrush, sizeof(logbrush), &logbrush);
    
    return PointerObject<Color>(
        new Color(static_cast<int>(logbrush.lbColor)));
}
void Component::setBackground(Color& c)
{
    /*
    HGDIOBJ newHGDIOBJ = CreateSolidBrush(0x00FFFFFF & c.getRGB());
    HGDIOBJ preHGDIOBJ
        = static_cast<HGDIOBJ>(
        SetClassLong(
            _hwnd,
            GCL_HBRBACKGROUND,
            static_cast<long>(newHGDIOBJ)));
    DeleteObject(preHGDIOBJ);
    */
    DeleteObject(
        static_cast<HGDIOBJ>(
        SetClassLong(
            _hwnd,
            GCL_HBRBACKGROUND,
            static_cast<int>(
            CreateSolidBrush(0x00FFFFFF & c.getRGB())))));
}
//===========================================================
//===========================================================
PointerObject<Font> Component::getFont()
{
    HDC hdc = GetDC(_hwnd);
    Font* font = new Font(String(""), 0, 0);
    GetObject(
        GetCurrentObject(hdc, OBJ_FONT),
        sizeof(*font),
        font);
    ReleaseDC(_hwnd, hdc);
    return PointerObject<Font>(font);
}
//===========================================================
//===========================================================
PointerObject<Point> Component::getLocation()
{
    RECT rect;
    int parentx =0;
    int parenty =0;
    HWND hwndParent = GetParent(_hwnd);
    if(hwndParent){
        GetWindowRect(hwndParent, &rect);
        parentx = rect.left;
        parenty = rect.top;
    }
    GetWindowRect(_hwnd, &rect);
    return PointerObject<Point>(
        new Point(rect.left -parentx, rect.top -parenty));
}
PointerObject<Point> Component::getLocationOnScreen()
{
    RECT rect;
    GetWindowRect(_hwnd, &rect);
    return PointerObject<Point>(new Point(rect.left, rect.top));
}
void Component::setLocation(int x, int y)
{
    SetWindowPos(
        _hwnd, NULL,
        x, y, 0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOSENDCHANGING);
}
//===========================================================
//===========================================================
PointerObject<Dimension> Component::getSize()
{
    RECT rect;
    GetWindowRect(_hwnd, &rect);
    return PointerObject<Dimension>(
        new Dimension(rect.right -rect.left, rect.bottom -rect.top));
}
void Component::setSize(int width, int height)
{
    PointerObject<Dimension> min = getMinimumSize();
    PointerObject<Dimension> max = getMaximumSize();
    width = width < (*min).width?
        (*min).width:
        width > (*max).width?
            (*max).width:
            width;
    height = height < (*min).height?
        (*min).height:
        height > (*max).height?
            (*max).height:
            height;
    SetWindowPos(
        _hwnd, NULL,
        0, 0, width, height,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOSENDCHANGING);
}
//===========================================================
//===========================================================
void Component::setBounds(int x, int y, int width, int height)
{
    PointerObject<Dimension> min = getMinimumSize();
    PointerObject<Dimension> max = getMaximumSize();
    width = width < (*min).width?
        (*min).width:
        width > (*max).width?
            (*max).width:
            width;
    height = height < (*min).height?
        (*min).height:
        height > (*max).height?
            (*max).height:
            height;
    SetWindowPos(
        _hwnd, NULL,
        x, y, width, height,
        SWP_NOZORDER | SWP_NOREDRAW | SWP_NOSENDCHANGING);
}
//===========================================================
//===========================================================
int Component::getX()
{
    RECT rect;
    
    int parentx =0;
    HWND hwndParent = GetParent(_hwnd);
    if(hwndParent){
        GetWindowRect(hwndParent, &rect);
        parentx = rect.left;
    }
    
    GetWindowRect(_hwnd, &rect);
    return rect.left -parentx;
}
int Component::getY()
{
    RECT rect;
    
    int parenty =0;
    HWND hwndParent = GetParent(_hwnd);
    if(hwndParent){
        GetWindowRect(hwndParent, &rect);
        parenty = rect.top;
    }
    
    GetWindowRect(_hwnd, &rect);
    return rect.top -parenty;
}
//===========================================================
//===========================================================
int Component::getWidth()
{
    RECT rect;
    GetClientRect(_hwnd, &rect);
    return rect.right -rect.left;
}
int Component::getHeight()
{
    RECT rect;
    GetClientRect(_hwnd, &rect);
    return rect.bottom -rect.top;
}
//===========================================================
//===========================================================
void Component::setPreferredSize(Dimension& preferredSize)
{
    _preferredSize = PointerObject<Dimension>(new Dimension(preferredSize));
}
PointerObject<Dimension> Component::getPreferredSize()
{
    return _preferredSize;
}
void Component::setMinimumSize(Dimension& minimumSize)
{
    _minimumSize = PointerObject<Dimension>(new Dimension(minimumSize));
}
PointerObject<Dimension> Component::getMinimumSize()
{
    return _minimumSize;
}
void Component::setMaximumSize(Dimension& maximumSize)
{
    _maximumSize = PointerObject<Dimension>(new Dimension(maximumSize));
}
PointerObject<Dimension> Component::getMaximumSize()
{
    return _maximumSize;
}
//===========================================================
//===========================================================
PointerObject<Graphics> Component::getGraphics()
{
    return PointerObject<Graphics>(new __Component_Graphics(_hwnd));
}
PointerObject<FontMetrics> Component::getFontMetrics(Font& font)
{
    return PointerObject<FontMetrics>(new FontMetrics(_hwnd, font));
}
//===========================================================
//===========================================================
PointerObject<Cursor> Component::getCursor()
{
    return _cursor;
}
void Component::setCursor(Cursor& cursor)
{
    _cursor = new Cursor(cursor);
    HCURSOR hcursor =0;
    switch(cursor.getType()){
        case Cursor::CUSTOM_CURSOR:
            hcursor = LoadCursor(NULL, IDC_NO);
            //SetCursor(LoadCursor(NULL, IDC_NO));
            break;
        
        case Cursor::DEFAULT_CURSOR:
            hcursor = LoadCursor(NULL, IDC_ARROW);
            //SetCursor(LoadCursor(NULL, IDC_ARROW));
            break;
        
        case Cursor::CROSSHAIR_CURSOR:
            hcursor = LoadCursor(NULL, IDC_CROSS);
            //SetCursor(LoadCursor(NULL, IDC_CROSS));
            break;
        
        case Cursor::TEXT_CURSOR:
            hcursor = LoadCursor(NULL, IDC_IBEAM);
            //SetCursor(LoadCursor(NULL, IDC_IBEAM));
            break;
        
        case Cursor::WAIT_CURSOR:
            hcursor = LoadCursor(NULL, IDC_WAIT);
            //SetCursor(LoadCursor(NULL, IDC_WAIT));
            break;
        
        case Cursor::SW_RESIZE_CURSOR:
        case Cursor::NE_RESIZE_CURSOR:
            hcursor = LoadCursor(NULL, IDC_SIZENESW);
            //SetCursor(LoadCursor(NULL, IDC_SIZENESW));
            break;
        
        case Cursor::SE_RESIZE_CURSOR:
        case Cursor::NW_RESIZE_CURSOR:
            hcursor = LoadCursor(NULL, IDC_SIZENWSE);
            //SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
            break;
        
        case Cursor::N_RESIZE_CURSOR:
        case Cursor::S_RESIZE_CURSOR:
            hcursor = LoadCursor(NULL, IDC_SIZENS);
            //SetCursor(LoadCursor(NULL, IDC_SIZENS));
            break;
        
        case Cursor::W_RESIZE_CURSOR:
        case Cursor::E_RESIZE_CURSOR:
            hcursor = LoadCursor(NULL, IDC_SIZEWE);
            //SetCursor(LoadCursor(NULL, IDC_SIZEWE));
            break;
        
        case Cursor::HAND_CURSOR:
            hcursor = LoadCursor(NULL, IDC_APPSTARTING);
            //SetCursor(LoadCursor(NULL, IDC_APPSTARTING));
            break;
        
        case Cursor::MOVE_CURSOR:
            hcursor = LoadCursor(NULL, IDC_SIZEALL);
            //SetCursor(LoadCursor(NULL, IDC_SIZEALL));
            break;
        
        default:
            break;
    }
    //DestroyCursor(static_cast<HCURSOR>(
    //    SetClassLong(_hwnd, GCL_HCURSOR, static_cast<int>(hcursor))));
    //SetCursor(LoadCursor(NULL, hcursor));
    SetCursor((*_cursor)._hcursor);
}
//===========================================================
//===========================================================
void Component::paint(Graphics& g){}
void Component::update(Graphics& g)
{
    g.setColor(Color::black);
    paint(g);
}
//===========================================================
//===========================================================
void Component::repaint()
{
    InvalidateRect(_hwnd, NULL, false);
    //UpdateWindow(_hwnd);
}
void Component::repaint(int x, int y, int width, int height)
{
    RECT rect;
    rect.left   = x;
    rect.top    = y;
    rect.right  = x +width;
    rect.bottom = y +height;
    InvalidateRect(_hwnd, &rect, false);
}
//===========================================================
//===========================================================
bool Component::imageUpdate(
    Image& img,
    int infoflags,
    int x,
    int y,
    int width,
    int height)
{
    int destX = Math::max(0, x);
    int destY = Math::max(0, y);
    int srcX = -Math::min(0, x);
    int srcY = -Math::min(0, y);
    int newWidth = Math::min(getWidth(), x+width) - Math::max(0, x);
    int newHeight = Math::min(getHeight(), y+height) - Math::max(0, y);
    //PointerObject<Graphics> g = getGraphics();
    int rop = //g->_xormode?
        //SRCINVERT:
        SRCCOPY;
    BitBlt(
        getGraphics()->_hdc,
        destX,
        destY,
        newWidth,
        newHeight,
        img.getGraphics()->_hdc,
        srcX,
        srcY,
        rop);
    
    return 1;
}
//===========================================================
//===========================================================
PointerObject<Image> Component::createImage(int width, int height)
{
    return PointerObject<Image>(new Image(width, height, _hwnd));
}
//===========================================================
//===========================================================
bool Component::contains(int x, int y)
{
    POINT po;
    po.x = x;
    po.y = y;
    
    if(WindowFromPoint(po) == _hwnd){
        return true;
    }else{
        return false;
    }
}
//===========================================================
//===========================================================
Component& Component::getComponentAt(int x, int y)
{
    wchar_t szClassName[sizeof(int)*8+1];
    POINT po;
    po.x = x;
    po.y = y;
    
    GetClassNameW(
        WindowFromPoint(po),
        szClassName,
        sizeof(int)*8+1);
    return *static_cast<Component*>(_wtoi(szClassName));
}
//===========================================================
//===========================================================
void Component::addComponentListener(ComponentListener& l)
{
    _componentListener.addFirst(&l);
}
void Component::removeComponentListener(ComponentListener& l)
{
    _componentListener.remove(&l);
}
//===========================================================
//===========================================================
void Component::addFocusListener(FocusListener& l)
{
    _focusListener.addFirst(&l);
}
void Component::removeFocusListener(FocusListener& l)
{
    _focusListener.remove(&l);
}
//===========================================================
//===========================================================
void Component::addKeyListener(KeyListener& l)
{
    _keyListener.addFirst(&l);
}
void Component::removeKeyListener(KeyListener& l)
{
    _keyListener.remove(&l);
}
//===========================================================
//===========================================================
void Component::addMouseListener(MouseListener& l)
{
    _mouseListener.addFirst(&l);
}
void Component::removeMouseListener(MouseListener& l)
{
    _mouseListener.remove(&l);
}
//===========================================================
//===========================================================
void Component::addMouseMotionListener(MouseMotionListener& l)
{
    _mouseMotionListener.addFirst(&l);
}
void Component::removeMouseMotionListener(MouseMotionListener& l)
{
    _mouseMotionListener.remove(&l);
}
//===========================================================
//===========================================================
void Component::addMouseWheelListener(MouseWheelListener& l)
{
    _mouseWheelListener.addFirst(&l);
}
void Component::removeMouseWheelListener(MouseWheelListener& l)
{
    _mouseWheelListener.remove(&l);
}
//===========================================================
//===========================================================
void Component::processComponentEvent(ComponentEvent& e)
{
    int id = e.getID();
    switch(id){
        case ComponentEvent::COMPONENT_MOVED:
            for(ComponentListener** l = _componentListener.get(); *l; ++l){
                (**l).componentMoved(e);
            }
            break;
        
        case ComponentEvent::COMPONENT_RESIZED:
            for(ComponentListener** l = _componentListener.get(); *l; ++l){
                (**l).componentResized(e);
            }
            break;
        
        case ComponentEvent::COMPONENT_SHOWN:
            for(ComponentListener** l = _componentListener.get(); *l; ++l){
                (**l).componentShown(e);
            }
            break;
        
        case ComponentEvent::COMPONENT_HIDDEN:
            for(ComponentListener** l = _componentListener.get(); *l; ++l){
                (**l).componentHidden(e);
            }
            break;
        
        default:
            break;
    };
}
//===========================================================
//===========================================================
void Component::processFocusEvent(FocusEvent& e)
{
    int id = e.getID();
    switch(id){
        case FocusEvent::FOCUS_GAINED:
            for(FocusListener** l = _focusListener.get(); *l; ++l){
                (**l).focusGained(e);
            }
            break;
        
        case FocusEvent::FOCUS_LOST:
            for(FocusListener** l = _focusListener.get(); *l; ++l){
                (**l).focusLost(e);
            }
            break;
        
        default:
            break;
    };
}
//===========================================================
//===========================================================
void Component::processKeyEvent(KeyEvent& e)
{
    int id = e.getID();
    switch(id){
        case KeyEvent::KEY_TYPED:
            for(KeyListener** l = _keyListener.get(); *l; ++l){
                (**l).keyTyped(e);
            }
            break;
        
        case KeyEvent::KEY_PRESSED:
            for(KeyListener** l = _keyListener.get(); *l; ++l){
                (**l).keyPressed(e);
            }
            break;
        
        case KeyEvent::KEY_RELEASED:
            for(KeyListener** l = _keyListener.get(); *l; ++l){
                (**l).keyReleased(e);
            }
            break;
        
        default:
            break;
    };
}
//===========================================================
//===========================================================
void Component::processMouseEvent(MouseEvent& e)
{
    int id = e.getID();
    switch(id){
        case MouseEvent::MOUSE_CLICKED:
            for(MouseListener** l = _mouseListener.get(); *l; ++l){
                (**l).mouseClicked(e);
            }
            break;
        
        case MouseEvent::MOUSE_PRESSED:
            for(MouseListener** l = _mouseListener.get(); *l; ++l){
                (**l).mousePressed(e);
            }
            break;
        
        case MouseEvent::MOUSE_RELEASED:
            for(MouseListener** l = _mouseListener.get(); *l; ++l){
                (**l).mouseReleased(e);
            }
            break;
        
        case MouseEvent::MOUSE_ENTERED:
            for(MouseListener** l = _mouseListener.get(); *l; ++l){
                (**l).mouseEntered(e);
            }
            break;
        
        case MouseEvent::MOUSE_EXITED:
            for(MouseListener** l = _mouseListener.get(); *l; ++l){
                (**l).mouseExited(e);
            }
            break;
        
        default:
            break;
    };
}
//===========================================================
//===========================================================
void Component::processMouseMotionEvent(MouseEvent& e)
{
    int id = e.getID();
    switch(id){
        case MouseEvent::MOUSE_MOVED:
            for(MouseMotionListener** l = _mouseMotionListener.get(); *l; ++l){
                (**l).mouseMoved(e);
            }
            break;
        
        case MouseEvent::MOUSE_DRAGGED:
            for(MouseMotionListener** l = _mouseMotionListener.get(); *l; ++l){
                (**l).mouseDragged(e);
            }
            break;
        
        default:
            break;
    };
}
//===========================================================
//===========================================================
void Component::processMouseWheelEvent(MouseWheelEvent& e)
{
    int id = e.getID();
    switch(id){
        case MouseEvent::MOUSE_WHEEL:
            for(MouseWheelListener** l = _mouseWheelListener.get(); *l; ++l){
                (**l).mouseWheelMoved(e);
            }
            break;
        
        default:
            break;
    };
}
//===========================================================
//===========================================================
void Component::requestFocus()
{
    SetFocus(_hwnd);
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
Component::__Component_Graphics::__Component_Graphics(HWND hwnd)//: Graphics(hwnd)
{
    
    _hwnd = hwnd;
    _hdc = GetDC(hwnd);
    //_color = Color(0x00);
    _xormode = false;
    
    SelectObject(_hdc, GetStockObject(NULL_BRUSH));
    SelectObject(_hdc, GetStockObject(NULL_PEN));
    
    /*
    LOGFONTW logfont;
    GetObject(GetStockObject(SYSTEM_FONT), sizeof(logfont), &logfont);
    SelectObject(_hdc, CreateFontIndirectW(&logfont));
    SelectObject(_hdc, CreateSolidBrush(NULL_BRUSH));
    //SelectObject(_hdc, GetStockObject(NULL_BRUSH));
    SelectObject(_hdc, CreatePen(PS_SOLID, 1, 0x00));
    */
}
Component::__Component_Graphics::~__Component_Graphics()
{
    DeleteObject(SelectObject(_hdc, GetStockObject(SYSTEM_FONT)));
    DeleteObject(SelectObject(_hdc, GetStockObject(NULL_BRUSH)));
    DeleteObject(SelectObject(_hdc, GetStockObject(BLACK_PEN)));
    ReleaseDC(_hwnd, _hdc);
}
//===========================================================
//===========================================================
//===========================================================
//===========================================================
void Component::__Component_Graphics::translate(int x, int y)
{
    OffsetViewportOrgEx(_hdc, x, y, NULL);
}
//===========================================================
//===========================================================
PointerObject<Color> Component::__Component_Graphics::getColor()
{
    LOGBRUSH logbrush;
    GetObject(
        GetCurrentObject(_hdc, OBJ_BRUSH),
        sizeof(logbrush),
        &logbrush);
    
    return PointerObject<Color>(
        new Color(static_cast<int>(logbrush.lbColor)));
}
void Component::__Component_Graphics::setColor(Color& c)
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
void Component::__Component_Graphics::setPaintMode()
{
    _xormode = false;
    SetROP2(_hdc, R2_COPYPEN);
}
void Component::__Component_Graphics::setXORMode(Color& c1)
{
    _xormode = true;
    SetROP2(_hdc, R2_XORPEN);
}
//===========================================================
//===========================================================
PointerObject<Font> Component::__Component_Graphics::getFont()
{
    Font* font = new Font(String(""), 0, 0);
    
    GetObject(
        GetCurrentObject(_hdc, OBJ_FONT),
        sizeof(*font),
        font);
    return PointerObject<Font>(font);
}
void Component::__Component_Graphics::setFont(Font& font)
{
    DeleteObject(
        SelectObject(_hdc, CreateFontIndirectW(&font)));
}
PointerObject<FontMetrics> Component::__Component_Graphics::getFontMetrics()
{
    return PointerObject<FontMetrics>(new FontMetrics(_hdc));
}
//===========================================================
//===========================================================
void Component::__Component_Graphics::drawLine(
    int x1,
    int y1,
    int x2,
    int y2)
{
    MoveToEx(_hdc, x1, y1, NULL);
    LineTo(_hdc, x2, y2);
}
//===========================================================
//===========================================================
void Component::__Component_Graphics::fillRect(
    int x,
    int y,
    int width,
    int height)
{
    Rectangle(_hdc, x, y, x +width, y +height);
}
void Component::__Component_Graphics::drawRect(
    int x,
    int y,
    int width,
    int height)
{
    HBRUSH hb = SelectObject(_hdc, GetStockObject(NULL_BRUSH));
    Rectangle(_hdc, x, y, x +width, y +height);
    SelectObject(_hdc, hb);
}
//===========================================================
//===========================================================
void Component::__Component_Graphics::drawOval(
    int x,
    int y,
    int width,
    int height)
{
    HBRUSH hb = SelectObject(_hdc, GetStockObject(NULL_BRUSH));
    Ellipse(_hdc, x, y, x +width, y +height);
    SelectObject(_hdc, hb);
}
void Component::__Component_Graphics::fillOval(
    int x,
    int y,
    int width,
    int height)
{
    Ellipse(_hdc, x, y, x +width, y +height);
}
//===========================================================
//===========================================================
void Component::__Component_Graphics::drawPolygon(
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
void Component::__Component_Graphics::drawPolygon(Polygon& p)
{
    drawPolygon(p.xpoints, p.ypoints, p.npoints);
}
void Component::__Component_Graphics::fillPolygon(
    int xPoints[],
    int yPoints[],
    int nPoints)
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
void Component::__Component_Graphics::fillPolygon(Polygon& p)
{
    fillPolygon(p.xpoints, p.ypoints, p.npoints);
}
//===========================================================
//===========================================================
void Component::__Component_Graphics::drawString(String& string, int x, int y)
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
bool Component::__Component_Graphics::drawImage(
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
bool Component::__Component_Graphics::drawImage(
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


#endif //ifndef __Windows_awt_Component_cpp

