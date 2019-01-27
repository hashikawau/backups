

#ifndef __Windows_awt_windowProcedure_cpp
#define __Windows_awt_windowProcedure_cpp


//===========================================================
//===========================================================
#include "../_lang.h"
#include "event/ActionEvent.h"
#include "Menu.h"
#include "Window.h"
#include "event/ActionEvent_cpp.h"
//===========================================================
//===========================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    wchar_t szClassName[sizeof(int)*8+1];
    GetClassNameW(hwnd, szClassName, sizeof(int)*8+1);
    
    Component* comp = static_cast<Component*>(_wtoi(szClassName));
    
    static Component* compMouseOn =0;
    
    cout << "0x";
    cout << Integer::toHexString(static_cast<int>(hwnd));
    cout << " @0x";
    cout << Integer::toHexString(static_cast<int>(comp));
    cout << " -";
    switch(msg)
    {
        //===========================================================
        case WM_WINDOWPOSCHANGED:
        {
            cout << "WM_WINDOWPOSCHANGED" << endl;
            
            if(comp->_componentListener){
                WINDOWPOS& wp = *static_cast<WINDOWPOS*>(lParam);
                
                if(wp.flags & SWP_SHOWWINDOW){
                    (*comp).processComponentEvent(
                        ComponentEvent(
                            *comp,
                            ComponentEvent::COMPONENT_SHOWN));
                    return 0;
                }
                if(wp.flags & SWP_HIDEWINDOW){
                    (*comp).processComponentEvent(
                        ComponentEvent(
                            *comp,
                            ComponentEvent::COMPONENT_HIDDEN));
                    return 0;
                }
                if(!(wp.flags & SWP_NOSIZE)){
                    (*comp).processComponentEvent(
                        ComponentEvent(
                            *comp,
                            ComponentEvent::COMPONENT_RESIZED));
                }
                if(!(wp.flags & SWP_NOMOVE)){
                    (*comp).processComponentEvent(
                        ComponentEvent(
                            *comp,
                            ComponentEvent::COMPONENT_MOVED));
                }
            }
            
            return 0;
        }
        
        //===========================================================
        case WM_SETFOCUS:
        case WM_KILLFOCUS:
        {
            if(msg == WM_SETFOCUS){
                cout << "WM_SETFOCUS" << endl;
            }else
            if(msg == WM_KILLFOCUS){
                cout << "WM_KILLFOCUS" << endl;
            }
            
            int id =0;
            if(msg == WM_SETFOCUS){
                id = FocusEvent::FOCUS_GAINED;
            }else
            if(msg == WM_KILLFOCUS){
                id = FocusEvent::FOCUS_LOST;
            }
            
            if(comp->_focusListener){
                GetClassNameW((HWND)wParam, szClassName, sizeof(int)*8+1);
                (*comp).processFocusEvent(
                    FocusEvent(
                        *comp, id,
                        false,
                        *static_cast<Component*>(_wtoi(szClassName))));
            }
            return 0;
        }
        
        //===========================================================
        case WM_PAINT:
        {
            //PAINTSTRUCT ps;
            //BeginPaint(hwnd, &ps);
            
            //Graphics g(comp->_hwnd);
            //int time = timeGetTime();
            
            cout << "WM_PAINT" << endl;
            
            ValidateRect(hwnd, NULL);
            comp->update((*comp).getGraphics());
            
            //cout << "time - " << timeGetTime() - time << endl;
            
            //EndPaint(hwnd, &ps);
            return 0;
        }
        
        //===========================================================
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            if(msg == WM_KEYDOWN){
                cout << "WM_KEYDOWN" << endl;
            }else
            if(msg == WM_SYSKEYDOWN){
                cout << "WM_SYSKEYDOWN" << endl;
            }
            
            if((*comp)._keyListener){
                int id = KeyEvent::KEY_PRESSED;
                long long when = timeGetTime();
                int modifiers
                    = 0
                    //+ wParam & MK_LBUTTON? InputEvent::BUTTON1_DOWN_MASK: 0
                    //+ wParam & MK_RBUTTON? InputEvent::BUTTON2_DOWN_MASK: 0
                    //+ wParam & MK_MBUTTON? InputEvent::BUTTON3_DOWN_MASK: 0
                    + wParam & MK_SHIFT? InputEvent::SHIFT_DOWN_MASK: 0
                    + wParam & MK_CONTROL? InputEvent::CTRL_DOWN_MASK: 0
                    + GetAsyncKeyState(VK_MENU)
                        & 0x8000? InputEvent::ALT_DOWN_MASK: 0;
                
                (*comp).processKeyEvent(
                    KeyEvent(
                        *comp, id, when, modifiers,
                        wParam, KeyEvent::CHAR_UNDEFINED,
                        KeyEvent::KEY_LOCATION_STANDARD));
            }
            return 0;
        }
        
        //===========================================================
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            if(msg == WM_KEYUP){
                cout << "WM_KEYUP" << endl;
            }else
            if(msg == WM_SYSKEYUP){
                cout << "WM_SYSKEYUP" << endl;
            }
            
            if((*comp)._keyListener){
                int id = KeyEvent::KEY_RELEASED;
                long long when = timeGetTime();
                int modifiers
                    = 0
                    //+ wParam & MK_LBUTTON? InputEvent::BUTTON1_DOWN_MASK: 0
                    //+ wParam & MK_RBUTTON? InputEvent::BUTTON2_DOWN_MASK: 0
                    //+ wParam & MK_MBUTTON? InputEvent::BUTTON3_DOWN_MASK: 0
                    + wParam & MK_SHIFT? InputEvent::SHIFT_DOWN_MASK: 0
                    + wParam & MK_CONTROL? InputEvent::CTRL_DOWN_MASK: 0
                    + GetAsyncKeyState(VK_MENU)
                        & 0x8000? InputEvent::ALT_DOWN_MASK: 0;
                
                (*comp).processKeyEvent(
                    KeyEvent(
                        *comp, id, when, modifiers,
                        KeyEvent::VK_UNDEFINED, KeyEvent::CHAR_UNDEFINED,
                        KeyEvent::KEY_LOCATION_UNKNOWN));
            }
            return 0;
        }
        
        //===========================================================
        case WM_CHAR:
        case WM_SYSCHAR:
        {
            if(msg == WM_CHAR){
                cout << "WM_CHAR" << endl;
            }else
            if(msg == WM_SYSCHAR){
                cout << "WM_SYSCHAR" << endl;
            }
            
            if((*comp)._keyListener){
                int id = KeyEvent::KEY_TYPED;
                long long when = timeGetTime();
                int modifiers
                    = 0
                    //+ wParam & MK_LBUTTON? InputEvent::BUTTON1_DOWN_MASK: 0
                    //+ wParam & MK_RBUTTON? InputEvent::BUTTON2_DOWN_MASK: 0
                    //+ wParam & MK_MBUTTON? InputEvent::BUTTON3_DOWN_MASK: 0
                    + wParam & MK_SHIFT? InputEvent::SHIFT_DOWN_MASK: 0
                    + wParam & MK_CONTROL? InputEvent::CTRL_DOWN_MASK: 0
                    + GetAsyncKeyState(VK_MENU)
                        & 0x8000? InputEvent::ALT_DOWN_MASK: 0;
                
                (*comp).processKeyEvent(
                    KeyEvent(
                        *comp, id, when, modifiers,
                        KeyEvent::VK_UNDEFINED, wParam,
                        KeyEvent::KEY_LOCATION_STANDARD));
            }
            return 0;
        }
        
        //===========================================================
        case WM_MOUSEMOVE:
        {
            cout << "WM_MOUSEMOVE" << endl;
            
            int id =0;
            long long when = timeGetTime();
            int modifiers
                = 0
                + wParam & MK_LBUTTON? InputEvent::BUTTON1_DOWN_MASK: 0
                + wParam & MK_RBUTTON? InputEvent::BUTTON2_DOWN_MASK: 0
                + wParam & MK_MBUTTON? InputEvent::BUTTON3_DOWN_MASK: 0
                + wParam & MK_SHIFT? InputEvent::SHIFT_DOWN_MASK: 0
                + wParam & MK_CONTROL? InputEvent::CTRL_DOWN_MASK: 0
                + GetAsyncKeyState(VK_MENU)
                    & 0x8000? InputEvent::ALT_DOWN_MASK: 0;
            int x = static_cast<short>(LOWORD(lParam));
            int y = static_cast<short>(HIWORD(lParam));
            POINT p;
            GetCursorPos(&p);
            int xAbs = p.x;
            int yAbs = p.y;
            int clickCount =0;
            bool popupTrigger =false;
            int button = MouseEvent::NOBUTTON;
            
            if((*comp)._mouseMotionListener){
                id = modifiers & 0x1C00?
                    MouseEvent::MOUSE_DRAGGED:
                    MouseEvent::MOUSE_MOVED;
                (*comp).processMouseMotionEvent(
                    MouseEvent(
                        *comp, id, when, modifiers,
                        x, y, xAbs, yAbs,
                        clickCount, popupTrigger,
                        button));
            }
            
            if(comp != compMouseOn){
                if(compMouseOn && (*compMouseOn)._mouseListener){
                    id = MouseEvent::MOUSE_EXITED;
                    (*compMouseOn).processMouseEvent(
                        MouseEvent(
                            *compMouseOn, id, when, modifiers,
                            x, y, xAbs, yAbs,
                            clickCount, popupTrigger,
                            button));
                }
                if((*comp)._mouseListener){
                    id = MouseEvent::MOUSE_ENTERED;
                    (*comp).processMouseEvent(
                        MouseEvent(
                            *comp, id, when, modifiers,
                            x, y, xAbs, yAbs,
                            clickCount, popupTrigger,
                            button));
                }
            }
            compMouseOn = comp;
            return 0;
        }
        
        //===========================================================
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        {
            if(msg == WM_LBUTTONDOWN){
                cout << "WM_LBUTTONDOWN" << endl;
            }else
            if(msg == WM_RBUTTONDOWN){
                cout << "WM_RBUTTONDOWN" << endl;
            }else
            if(msg == WM_MBUTTONDOWN){
                cout << "WM_MBUTTONDOWN" << endl;
            }
            //SetActiveWindow(hwnd);
            //SetFocus(hwnd);
            SetCapture(hwnd);
            
            int id = MouseEvent::MOUSE_PRESSED;
            long long when = timeGetTime();
            int modifiers
                = 0
                + wParam & MK_LBUTTON? InputEvent::BUTTON1_DOWN_MASK: 0
                + wParam & MK_RBUTTON? InputEvent::BUTTON2_DOWN_MASK: 0
                + wParam & MK_MBUTTON? InputEvent::BUTTON3_DOWN_MASK: 0
                + wParam & MK_SHIFT? InputEvent::SHIFT_DOWN_MASK: 0
                + wParam & MK_CONTROL? InputEvent::CTRL_DOWN_MASK: 0
                + GetAsyncKeyState(VK_MENU)
                    & 0x8000? InputEvent::ALT_DOWN_MASK: 0;
            int x = static_cast<short>(LOWORD(lParam));
            int y = static_cast<short>(HIWORD(lParam));
            POINT p;
            GetCursorPos(&p);
            int xAbs = p.x;
            int yAbs = p.y;
            int clickCount =1;
            bool popupTrigger =false;
            int button =0;
            if(msg == WM_LBUTTONDOWN){
                button = MouseEvent::BUTTON1;
            }else
            if(msg == WM_RBUTTONDOWN){
                button = MouseEvent::BUTTON1;
            }else
            if(msg == WM_MBUTTONDOWN){
                button = MouseEvent::BUTTON1;
            }
            
            if((*comp)._mouseListener){
                (*comp).processMouseEvent(
                    MouseEvent(
                        *comp, id, when, modifiers,
                        x, y, xAbs, yAbs,
                        clickCount, popupTrigger,
                        button));
            }
            return 0;
        }
        
        //===========================================================
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        {
            if(msg == WM_LBUTTONUP){
                cout << "WM_LBUTTONUP" << endl;
            }else
            if(msg == WM_RBUTTONUP){
                cout << "WM_RBUTTONUP" << endl;
            }else
            if(msg == WM_MBUTTONUP){
                cout << "WM_MBUTTONUP" << endl;
            }
            
            int id = MouseEvent::MOUSE_RELEASED;
            long long when = timeGetTime();
            int modifiers
                = 0
                + wParam & MK_LBUTTON? InputEvent::BUTTON1_DOWN_MASK: 0
                + wParam & MK_RBUTTON? InputEvent::BUTTON2_DOWN_MASK: 0
                + wParam & MK_MBUTTON? InputEvent::BUTTON3_DOWN_MASK: 0
                + wParam & MK_SHIFT? InputEvent::SHIFT_DOWN_MASK: 0
                + wParam & MK_CONTROL? InputEvent::CTRL_DOWN_MASK: 0
                + GetAsyncKeyState(VK_MENU)
                    & 0x8000? InputEvent::ALT_DOWN_MASK: 0;
            int x = static_cast<short>(LOWORD(lParam));
            int y = static_cast<short>(HIWORD(lParam));
            POINT p;
            GetCursorPos(&p);
            int xAbs = p.x;
            int yAbs = p.y;
            int clickCount =1;
            bool popupTrigger =false;
            int button =0;
            if(msg == WM_LBUTTONUP){
                button = MouseEvent::BUTTON1;
            }else
            if(msg == WM_RBUTTONUP){
                button = MouseEvent::BUTTON1;
            }else
            if(msg == WM_MBUTTONUP){
                button = MouseEvent::BUTTON1;
            }
            
            if(!(modifiers & 0x1C00)){
                ReleaseCapture();
            }
            
            if((*comp)._mouseListener){
                (*comp).processMouseEvent(
                    MouseEvent(
                        *comp, id, when, modifiers,
                        x, y, xAbs, yAbs,
                        clickCount, popupTrigger,
                        button));
            }
            
            RECT r;
            GetWindowRect(hwnd, &r);
            if(true
                && xAbs >= r.left
                && yAbs >= r.top
                && xAbs <= r.right
                && yAbs <= r.bottom)
            {
                id = MouseEvent::MOUSE_CLICKED;
                if((*comp)._mouseListener){
                    (*comp).processMouseEvent(
                        MouseEvent(
                            *comp, id, when, modifiers,
                            x, y, xAbs, yAbs,
                            clickCount, popupTrigger,
                            button));
                }
            }
            return 0;
        }
        
        //===========================================================
        case WM_MOUSEWHEEL:
        {
            cout << "WM_MOUSEWHEEL" << endl;
            
            if(comp->_mouseWheelListener){
                int id = MouseEvent::MOUSE_WHEEL;
                long long when = timeGetTime();
                int modifiers = 0;
                int xAbs = static_cast<short>(LOWORD(lParam));
                int yAbs = static_cast<short>(HIWORD(lParam));
                RECT r;
                GetWindowRect(hwnd, &r);
                int x = xAbs - r.left;
                int y = yAbs - r.top;
                int clickCount =1;
                bool popupTrigger =false;
                int scrollType = MouseWheelEvent::WHEEL_UNIT_SCROLL;
                int scrollAmount = 2;
                int wheelRotation = static_cast<short>(HIWORD(wParam))/120;
                
                (*comp).processMouseWheelEvent(
                    MouseWheelEvent(
                        *comp,
                        id,
                        when,
                        modifiers,
                        x,
                        y,
                        xAbs,
                        yAbs,
                        clickCount,
                        popupTrigger,
                        scrollType,
                        scrollAmount,
                        wheelRotation));
            }
            return 0;
        }
        
        //===========================================================
        case WM_COMMAND:
        {
            cout << "WM_COMMAND" << endl;
            
            int menuID = wParam & 0x0000FFFF;
            MenuItem* mi =0;
            for(ListIterator<MenuItem*>& it
                = MenuItem::_menuItemList.listIterator(0);
                it.hasNext() && !mi;
                )
            {
                MenuItem* temp = it.next();
                if(temp->getid() == menuID){
                    mi = temp;
                }
            }
            if(mi){
                if(mi->_actionListener){
                    for(ActionListener** l
                        = mi->_actionListener.get();
                        *l;
                        ++l)
                    {
                        (**l).actionPerformed(
                            ActionEvent(static_cast<int>(mi)));
                    }
                }
            }
            return 0;
        }
        
        //===========================================================
        case WM_SETCURSOR:
        {
            cout << "WM_SETCURSOR" << endl;
            //SetCursor((*comp->getCursor())._hcursor);
            return 1;
        }
        
        //===========================================================
        case WM_DESTROY:
        {
            cout << "WM_DESTROY" << endl;
            if(dynamic_cast<Window*>(comp)){
                PostQuitMessage(0);
            }
            return 0;
        }
        
        //===========================================================
        case WM_NULL:
            cout << "WM_NULL" << endl;
            break;
        case WM_ACTIVATE:
            cout << "WM_ACTIVATE" << endl;
            break;
        case WM_ENABLE:
            cout << "WM_ENABLE" << endl;
            break;
        case WM_SETREDRAW:
            cout << "WM_SETREDRAW" << endl;
            break;
        case WM_SETTEXT:
            cout << "WM_SETTEXT" << endl;
            break;
        case WM_GETTEXT:
            cout << "WM_GETTEXT" << endl;
            break;
        case WM_GETTEXTLENGTH:
            cout << "WM_GETTEXTLENGTH" << endl;
            break;
        case WM_CLOSE:
            cout << "WM_CLOSE" << endl;
            break;
        case WM_QUERYENDSESSION:
            cout << "WM_QUERYENDSESSION" << endl;
            break;
        case WM_QUIT:
            cout << "WM_QUIT" << endl;
            break;
        case WM_QUERYOPEN:
            cout << "WM_QUERYOPEN" << endl;
            break;
        case WM_SYSCOLORCHANGE:
            cout << "WM_SYSCOLORCHANGE" << endl;
            break;
        case WM_ENDSESSION:
            cout << "WM_ENDSESSION" << endl;
            break;
        case WM_WININICHANGE:
            cout << "WM_WININICHANGE" << endl;
            break;
        //case WM_SETTINGCHANGE:
        //    cout << "WM_SETTINGCHANGE" << endl;
        //    break;
        case WM_DEVMODECHANGE:
            cout << "WM_DEVMODECHANGE" << endl;
            break;
        case WM_ACTIVATEAPP:
            cout << "WM_ACTIVATEAPP" << endl;
            break;
        case WM_FONTCHANGE:
            cout << "WM_FONTCHANGE" << endl;
            break;
        case WM_TIMECHANGE:
            cout << "WM_TIMECHANGE" << endl;
            break;
        case WM_CANCELMODE:
            cout << "WM_CANCELMODE" << endl;
            break;
        case WM_MOUSEACTIVATE:
            cout << "WM_MOUSEACTIVATE" << endl;
            break;
        case WM_CHILDACTIVATE:
            cout << "WM_CHILDACTIVATE" << endl;
            break;
        case WM_QUEUESYNC:
            cout << "WM_QUEUESYNC" << endl;
            break;
        case WM_GETMINMAXINFO:
            cout << "WM_GETMINMAXINFO" << endl;
            break;
        case WM_PAINTICON:
            cout << "WM_PAINTICON" << endl;
            break;
        case WM_ICONERASEBKGND:
            cout << "WM_ICONERASEBKGND" << endl;
            break;
        case WM_NEXTDLGCTL:
            cout << "WM_NEXTDLGCTL" << endl;
            break;
        case WM_SPOOLERSTATUS:
            cout << "WM_SPOOLERSTATUS" << endl;
            break;
        case WM_DRAWITEM:
            cout << "WM_DRAWITEM" << endl;
            break;
        case WM_MEASUREITEM:
            cout << "WM_MEASUREITEM" << endl;
            break;
        case WM_DELETEITEM:
            cout << "WM_DELETEITEM" << endl;
            break;
        case WM_VKEYTOITEM:
            cout << "WM_VKEYTOITEM" << endl;
            break;
        case WM_CHARTOITEM:
            cout << "WM_CHARTOITEM" << endl;
            break;
        case WM_SETFONT:
            cout << "WM_SETFONT" << endl;
            break;
        case WM_GETFONT:
            cout << "WM_GETFONT" << endl;
            break;
        case WM_SETHOTKEY:
            cout << "WM_SETHOTKEY" << endl;
            break;
        case WM_GETHOTKEY:
            cout << "WM_GETHOTKEY" << endl;
            break;
        case WM_QUERYDRAGICON:
            cout << "WM_QUERYDRAGICON" << endl;
            break;
        case WM_COMPAREITEM:
            cout << "WM_COMPAREITEM" << endl;
            break;
        case WM_COMPACTING:
            cout << "WM_COMPACTING" << endl;
            break;
        case WM_COMMNOTIFY:
            cout << "WM_COMMNOTIFY" << endl;
            break;
        case WM_POWER:
            cout << "WM_POWER" << endl;
            break;
        case WM_COPYDATA:
            cout << "WM_COPYDATA" << endl;
            break;
        case WM_CANCELJOURNAL:
            cout << "WM_CANCELJOURNAL" << endl;
            break;
        case WM_NOTIFY:
            cout << "WM_NOTIFY" << endl;
            break;
        case WM_INPUTLANGCHANGEREQUEST:
            cout << "WM_INPUTLANGCHANGEREQUEST" << endl;
            break;
        case WM_INPUTLANGCHANGE:
            cout << "WM_INPUTLANGCHANGE" << endl;
            break;
        case WM_TCARD:
            cout << "WM_TCARD" << endl;
            break;
        case WM_HELP:
            cout << "WM_HELP" << endl;
            break;
        case WM_USERCHANGED:
            cout << "WM_USERCHANGED" << endl;
            break;
        case WM_NOTIFYFORMAT:
            cout << "WM_NOTIFYFORMAT" << endl;
            break;
        //case WM_CONTEXTMENU:
        //    cout << "WM_CONTEXTMENU" << endl;
        //    break;
        case WM_CONTEXTMENU:
            cout << "WM_CONTEXTMENU" << endl;
            break;
        case WM_STYLECHANGING:
            cout << "WM_STYLECHANGING" << endl;
            break;
        case WM_STYLECHANGED:
            cout << "WM_STYLECHANGED" << endl;
            break;
        case WM_DISPLAYCHANGE:
            cout << "WM_DISPLAYCHANGE" << endl;
            break;
        case WM_GETICON:
            cout << "WM_GETICON" << endl;
            break;
        case WM_SETICON:
            cout << "WM_SETICON" << endl;
            break;
        case WM_NCCREATE:
            cout << "WM_NCCREATE" << endl;
            break;
        case WM_NCDESTROY:
            cout << "WM_NCDESTROY" << endl;
            break;
        case WM_NCCALCSIZE:
            cout << "WM_NCCALCSIZE" << endl;
            break;
        case WM_NCPAINT:
            cout << "WM_NCPAINT" << endl;
            break;
        case WM_NCACTIVATE:
            cout << "WM_NCACTIVATE" << endl;
            break;
        case WM_GETDLGCODE:
            cout << "WM_GETDLGCODE" << endl;
            break;
        
        case WM_IME_STARTCOMPOSITION:
            cout << "WM_IME_STARTCOMPOSITION" << endl;
            break;
        case WM_IME_ENDCOMPOSITION:
            cout << "WM_IME_ENDCOMPOSITION" << endl;
            break;
        case WM_IME_COMPOSITION:
            cout << "WM_IME_COMPOSITION" << endl;
            break;
        //case WM_IME_KEYLAST:
        //    cout << "WM_IME_KEYLAST" << endl;
        //    break;
        
        case WM_INITDIALOG:
            cout << "WM_INITDIALOG" << endl;
            break;
        case WM_SYSCOMMAND:
            cout << "WM_SYSCOMMAND" << endl;
            break;
        case WM_TIMER:
            cout << "WM_TIMER" << endl;
            break;
        case WM_HSCROLL:
            cout << "WM_HSCROLL" << endl;
            break;
        case WM_VSCROLL:
            cout << "WM_VSCROLL" << endl;
            break;
        case WM_INITMENU:
            cout << "WM_INITMENU" << endl;
            break;
        case WM_INITMENUPOPUP:
            cout << "WM_INITMENUPOPUP" << endl;
            break;
        case WM_MENUSELECT:
            cout << "WM_MENUSELECT" << endl;
            break;
        case WM_MENUCHAR:
            cout << "WM_MENUCHAR" << endl;
            break;
        case WM_ENTERIDLE:
            cout << "WM_ENTERIDLE" << endl;
            break;
        case WM_PARENTNOTIFY:
            cout << "WM_PARENTNOTIFY" << endl;
            break;
        case WM_ENTERMENULOOP:
            cout << "WM_ENTERMENULOOP" << endl;
            break;
        case WM_EXITMENULOOP:
            cout << "WM_EXITMENULOOP" << endl;
            break;
        case WM_NEXTMENU:
            cout << "WM_NEXTMENU" << endl;
            break;
        case WM_CAPTURECHANGED:
            cout << "WM_CAPTURECHANGED" << endl;
            break;
        case WM_POWERBROADCAST:
            cout << "WM_POWERBROADCAST" << endl;
            break;
        case WM_DEVICECHANGE:
            cout << "WM_DEVICECHANGE" << endl;
            break;
        
        case WM_IME_SETCONTEXT:
            cout << "WM_IME_SETCONTEXT" << endl;
            break;
        case WM_IME_NOTIFY:
            cout << "WM_IME_NOTIFY" << endl;
            break;
        case WM_IME_CONTROL:
            cout << "WM_IME_CONTROL" << endl;
            break;
        case WM_IME_COMPOSITIONFULL:
            cout << "WM_IME_COMPOSITIONFULL" << endl;
            break;
        case WM_IME_SELECT:
            cout << "WM_IME_SELECT" << endl;
            break;
        case WM_IME_CHAR:
            cout << "WM_IME_CHAR" << endl;
            break;
        case WM_IME_KEYDOWN:
            cout << "WM_IME_KEYDOWN" << endl;
            break;
        case WM_IME_KEYUP:
            cout << "WM_IME_KEYUP" << endl;
            break;
        
        case WM_MDICREATE:
            cout << "WM_MDICREATE" << endl;
            break;
        case WM_MDIDESTROY:
            cout << "WM_MDIDESTROY" << endl;
            break;
        case WM_MDIACTIVATE:
            cout << "WM_MDIACTIVATE" << endl;
            break;
        case WM_MDIRESTORE:
            cout << "WM_MDIRESTORE" << endl;
            break;
        case WM_MDINEXT:
            cout << "WM_MDINEXT" << endl;
            break;
        case WM_MDIMAXIMIZE:
            cout << "WM_MDIMAXIMIZE" << endl;
            break;
        case WM_MDITILE:
            cout << "WM_MDITILE" << endl;
            break;
        case WM_MDICASCADE:
            cout << "WM_MDICASCADE" << endl;
            break;
        case WM_MDIICONARRANGE:
            cout << "WM_MDIICONARRANGE" << endl;
            break;
        case WM_MDIGETACTIVE:
            cout << "WM_MDIGETACTIVE" << endl;
            break;
        
        case WM_MDISETMENU:
            cout << "WM_MDISETMENU" << endl;
            break;
        case WM_DROPFILES:
            cout << "WM_DROPFILES" << endl;
            break;
        case WM_MDIREFRESHMENU:
            cout << "WM_MDIREFRESHMENU" << endl;
            break;
        case WM_CUT:
            cout << "WM_CUT" << endl;
            break;
        case WM_COPY:
            cout << "WM_COPY" << endl;
            break;
        case WM_PASTE:
            cout << "WM_PASTE" << endl;
            break;
        case WM_CLEAR:
            cout << "WM_CLEAR" << endl;
            break;
        case WM_UNDO:
            cout << "WM_UNDO" << endl;
            break;
        case WM_RENDERFORMAT:
            cout << "WM_RENDERFORMAT" << endl;
            break;
        case WM_RENDERALLFORMATS:
            cout << "WM_RENDERALLFORMATS" << endl;
            break;
        case WM_DESTROYCLIPBOARD:
            cout << "WM_DESTROYCLIPBOARD" << endl;
            break;
        case WM_DRAWCLIPBOARD:
            cout << "WM_DRAWCLIPBOARD" << endl;
            break;
        case WM_PAINTCLIPBOARD:
            cout << "WM_PAINTCLIPBOARD" << endl;
            break;
        case WM_VSCROLLCLIPBOARD:
            cout << "WM_VSCROLLCLIPBOARD" << endl;
            break;
        case WM_SIZECLIPBOARD:
            cout << "WM_SIZECLIPBOARD" << endl;
            break;
        case WM_ASKCBFORMATNAME:
            cout << "WM_ASKCBFORMATNAME" << endl;
            break;
        case WM_CHANGECBCHAIN:
            cout << "WM_CHANGECBCHAIN" << endl;
            break;
        case WM_HSCROLLCLIPBOARD:
            cout << "WM_HSCROLLCLIPBOARD" << endl;
            break;
        case WM_QUERYNEWPALETTE:
            cout << "WM_QUERYNEWPALETTE" << endl;
            break;
        case WM_PALETTEISCHANGING:
            cout << "WM_PALETTEISCHANGING" << endl;
            break;
        case WM_PALETTECHANGED:
            cout << "WM_PALETTECHANGED" << endl;
            break;
        case WM_HOTKEY:
            cout << "WM_HOTKEY" << endl;
            break;
        case WM_PRINT:
            cout << "WM_PRINT" << endl;
            break;
        case WM_PRINTCLIENT:
            cout << "WM_PRINTCLIENT" << endl;
            break;
        case WM_APP:
            cout << "WM_APP" << endl;
            break;
        
        //===========================================================
        case WM_CREATE:
            cout << "WM_CREATE" << endl;
            return 0;
        case WM_MOVE:
            cout << "WM_MOVE" << endl;
            return 0;
        case WM_SIZE:
            cout << "WM_SIZE" << endl;
            return 0;
        case WM_ERASEBKGND:
            cout << "WM_ERASEBKGND" << endl;
            return 0;
        case WM_SHOWWINDOW:
            cout << "WM_SHOWWINDOW" << endl;
            return 0;
        case WM_WINDOWPOSCHANGING:
            cout << "WM_WINDOWPOSCHANGING" << endl;
            return 0;
        case WM_SIZING:
            cout << "WM_SIZING" << endl;
            return 0;
        case WM_MOVING:
            cout << "WM_MOVING" << endl;
            return 0;
        case WM_ENTERSIZEMOVE:
            cout << "WM_ENTERSIZEMOVE" << endl;
            return 0;
        case WM_EXITSIZEMOVE:
            cout << "WM_EXITSIZEMOVE" << endl;
            return 0;
        
        //===========================================================
        //case WM_KEYFIRST:
        //    cout << "WM_KEYFIRST" << endl;
        //    break;
        case WM_DEADCHAR:
            cout << "WM_DEADCHAR" << endl;
            break;
        case WM_SYSDEADCHAR:
            cout << "WM_SYSDEADCHAR" << endl;
            break;
        //case WM_KEYLAST:
        //    cout << "WM_KEYLAST" << endl;
        //    break;
        
        //===========================================================
        case WM_NCMOUSEMOVE:
            cout << "WM_NCMOUSEMOVE" << endl;
            return 0;
        case WM_NCLBUTTONDOWN:
            cout << "WM_NCLBUTTONDOWN" << endl;
            return 0;
        case WM_NCLBUTTONUP:
            cout << "WM_NCLBUTTONUP" << endl;
            return 0;
        case WM_NCLBUTTONDBLCLK:
            cout << "WM_NCLBUTTONDBLCLK" << endl;
            return 0;
        case WM_NCRBUTTONDOWN:
            cout << "WM_NCRBUTTONDOWN" << endl;
            return 0;
        case WM_NCRBUTTONUP:
            cout << "WM_NCRBUTTONUP" << endl;
            return 0;
        case WM_NCRBUTTONDBLCLK:
            cout << "WM_NCRBUTTONDBLCLK" << endl;
            return 0;
        case WM_NCMBUTTONDOWN:
            cout << "WM_NCMBUTTONDOWN" << endl;
            return 0;
        case WM_NCMBUTTONUP:
            cout << "WM_NCMBUTTONUP" << endl;
            return 0;
        case WM_NCMBUTTONDBLCLK:
            cout << "WM_NCMBUTTONDBLCLK" << endl;
            return 0;
        
        case WM_LBUTTONDBLCLK:
            cout << "WM_LBUTTONDBLCLK" << endl;
            return 0;
        case WM_RBUTTONDBLCLK:
            cout << "WM_RBUTTONDBLCLK" << endl;
            return 0;
        case WM_MBUTTONDBLCLK:
            cout << "WM_MBUTTONDBLCLK" << endl;
            return 0;
        
        //===========================================================
        case WM_NCHITTEST:
            cout << "WM_NCHITTEST" << endl;
            return 1;
        
        default:
        {
            cout << Integer::toHexString(msg) << endl;
            break;
        }
    }
    
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_windowProcedure_cpp

