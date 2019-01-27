

#ifndef __Windows_awt_Window
#define __Windows_awt_Window


//===========================================================
//===========================================================
#include "Container.h"
#include "cpp/PointerObject.h"
class WindowListener;
class WindowFocusListener;
class WindowStateListener;
//===========================================================
//===========================================================
class Window: public Container
{
private:
protected:
    PointerObject<WindowListener> _windowListener;
    PointerObject<WindowFocusListener> _windowFocusListener;
    PointerObject<WindowStateListener> _windowStateListener;
    
public:
    Window();
    virtual ~Window();
    void addWindowListener(WindowListener& l);
    void addWindowFocusListener(WindowFocusListener& l);
    void addWindowStateListener(WindowStateListener& l);
    void removeWindowListener(WindowListener& l);
    void removeWindowFocusListener(WindowFocusListener& l);
    void removeWindowStateListener(WindowStateListener& l);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Window

