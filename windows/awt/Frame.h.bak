

#ifndef __Windows_awt_Frame
#define __Windows_awt_Frame


//===========================================================
//===========================================================
#include "Window.h"
#include "../cpp/PointerObject.h"
class String;
class MenuBar;
//===========================================================
//===========================================================
class Frame: public Window
{
private:
    friend class FileDialog;
protected:
    PointerObject<MenuBar> _menuBar;
    
public:
    Frame(String& title = String(L""));
    virtual ~Frame();
    
    void setTitle(String& title);
    MenuBar& getMenuBar();
    void setMenuBar(MenuBar& mb);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Frame

