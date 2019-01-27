

#ifndef __Windows_awt_Window_cpp
#define __Windows_awt_Window_cpp


//===========================================================
//===========================================================
#include "Window.h"
#include "Color.h"
#include "event/ActionEvent.h"
#include "../cpp/PointerObject.h"
//===========================================================
//===========================================================
Window::Window()
{
    setBackground(Color::white);
}
Window::~Window(){}
//===========================================================
//===========================================================
void Window::addWindowListener(WindowListener& l)
{
    _windowListener.addFirst(&l);
}
void Window::removeWindowListener(WindowListener& l)
{
    _windowListener.remove(&l);
}
//===========================================================
//===========================================================
void Window::addWindowFocusListener(WindowFocusListener& l)
{
    _windowFocusListener.addFirst(&l);
}
void Window::removeWindowFocusListener(WindowFocusListener& l)
{
    _windowFocusListener.remove(&l);
}
//===========================================================
//===========================================================
void Window::addWindowStateListener(WindowStateListener& l)
{
    _windowStateListener.addFirst(&l);
}
void Window::removeWindowStateListener(WindowStateListener& l)
{
    _windowStateListener.remove(&l);
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Window_cpp

