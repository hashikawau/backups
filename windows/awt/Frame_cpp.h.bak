

#ifndef __Windows_awt_Frame_cpp
#define __Windows_awt_Frame_cpp


//===========================================================
//===========================================================
#include "Frame.h"
#include "../_windows.h"
#include "Menu.h"
#include "../lang/String.h"
#include "../cpp/PointerObject.h"
//===========================================================
//===========================================================
Frame::Frame(String& title)
{
    SetWindowTextW(_hwnd, title.toCharArray());
    SetWindowLong(_hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
    setLayout(*new FlowLayout());
}
Frame::~Frame(){}
//===========================================================
//===========================================================
void Frame::setTitle(String& title)
{
    SetWindowTextW(_hwnd, title.toCharArray());
}
//===========================================================
//===========================================================
MenuBar& Frame::getMenuBar()
{
    return *_menuBar;
}
void Frame::setMenuBar(MenuBar& mb)
{
    _menuBar = &mb;
    HMENU hmenu = _menuBar?
        _menuBar->_hmenu:
        0;
    SetMenu(_hwnd, hmenu);
    _menuBar->_parent = this;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Frame_cpp

