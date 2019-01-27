

#ifndef __Windows_awt_Component
#define __Windows_awt_Component


//===========================================================
//===========================================================
#include "../_windows.h"
#include "Point.h"
#include "Menu.h"
#include "image/ImageObserver.h"
#include "../cpp/PointerObject.h"
#include "../lang/Object.h"
class Color;
class Cursor;
class Font;
class FontMetrics;
class Graphics;
class Image;
class Toolkit;
class ComponentListener;
class FocusListener;
class KeyListener;
class MouseListener;
class MouseMotionListener;
class MouseWheelListener;
//===========================================================
//===========================================================
class Component:
    public Object,
    public ImageObserver,
    public MenuContainer
{
private:
    friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    friend class Container;
    
    class __Component_Graphics;

protected:
    HWND _hwnd;
    
    PointerObject<Dimension> _preferredSize;
    PointerObject<Dimension> _minimumSize;
    PointerObject<Dimension> _maximumSize;
    PointerObject<Cursor> _cursor;
    
    PointerObject<ComponentListener> _componentListener;
    PointerObject<FocusListener> _focusListener;
    PointerObject<KeyListener> _keyListener;
    PointerObject<MouseListener> _mouseListener;
    PointerObject<MouseMotionListener> _mouseMotionListener;
    PointerObject<MouseWheelListener> _mouseWheelListener;
    
    Component();
    Component(const Component& component);
    
    void processComponentEvent(ComponentEvent& e);
    void processFocusEvent(FocusEvent& e);
    void processKeyEvent(KeyEvent& e);
    void processMouseEvent(MouseEvent& e);
    void processMouseMotionEvent(MouseEvent& e);
    void processMouseWheelEvent(MouseWheelEvent& e);
    
public:
    virtual ~Component() =0;
    
    Container& getParent();
    //PointerObject<Container> getParent();
    
    PointerObject<Toolkit> getToolkit();
    PointerObject<Point> getMousePosition();
    void setVisible(bool b);
    
    PointerObject<Color> getBackground();
    void setBackground(Color& c);
    
    PointerObject<Font> getFont();
    
    PointerObject<Point> getLocation();
    PointerObject<Point> getLocationOnScreen();
    void setLocation(int x, int y);
    
    PointerObject<Dimension> getSize();
    virtual void setSize(int width, int height);
    
    virtual void setBounds(int x, int y, int width, int height);
    
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setPreferredSize(Dimension& preferredSize);
    PointerObject<Dimension> getPreferredSize();
    void setMinimumSize(Dimension& minimumSize);
    PointerObject<Dimension> getMinimumSize();
    void setMaximumSize(Dimension& maximumSize);
    PointerObject<Dimension> getMaximumSize();
    
    //virtual void doLayout();
    //virtual void validate();
    //virtual void invalidate();
    
    PointerObject<Graphics> getGraphics();
    PointerObject<FontMetrics> getFontMetrics(Font& font);
    
    PointerObject<Cursor> getCursor();
    void setCursor(Cursor& cursor);
    
    virtual void paint(Graphics& g);
    virtual void update(Graphics& g);
    void repaint();
    void repaint(int x, int y, int width, int height);
    
    virtual bool imageUpdate(
        Image& img,
        int infoflags,
        int x,
        int y,
        int width,
        int height);
    PointerObject<Image> createImage(int width, int height);
    
    bool contains(int x, int y);
    Component& getComponentAt(int x, int y);
    
    void addComponentListener(ComponentListener& l);
    void addFocusListener(FocusListener& l);
    void addKeyListener(KeyListener& l);
    void addMouseListener(MouseListener& l);
    void addMouseMotionListener(MouseMotionListener& l);
    void addMouseWheelListener(MouseWheelListener& l);
    void removeComponentListener(ComponentListener& l);
    void removeFocusListener(FocusListener& l);
    void removeKeyListener(KeyListener& l);
    void removeMouseListener(MouseListener& l);
    void removeMouseMotionListener(MouseMotionListener& l);
    void removeMouseWheelListener(MouseWheelListener& l);
    
    void requestFocus();
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Component

