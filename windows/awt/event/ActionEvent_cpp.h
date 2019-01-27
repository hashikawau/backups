

#ifndef __Windows_awt_event_ActionEvent_cpp
#define __Windows_awt_event_ActionEvent_cpp


//===========================================================
//===========================================================
#include "ActionEvent.h"
#include "../AWTEvent.h"
#include "../../_windows.h"
//===========================================================
//===========================================================
const int ActionEvent::SHIFT_MASK =1;
const int ActionEvent::CTRL_MASK  =2;
const int ActionEvent::META_MASK  =4;
const int ActionEvent::ALT_MASK   =8;
//===========================================================
//===========================================================
ActionEvent::ActionEvent(
    Object& source, int id, String& command):
    AWTEvent(source, id),
    _command(command),
    _when(0),
    _modifiers(0)
{}
ActionEvent::ActionEvent(
    Object& source, int id, String& command, int modifiers):
    AWTEvent(source, id),
    _command(command),
    _when(0),
    _modifiers(modifiers)
{}
ActionEvent::ActionEvent(
    Object& source, int id, String& command,
    long long int when, int modifiers):
    AWTEvent(source, id),
    _command(command),
    _when(when),
    _modifiers(modifiers)
{}
ActionEvent::ActionEvent(int source): AWTEvent(source){}
ActionEvent::~ActionEvent(){}
//===========================================================
//===========================================================
String& ActionEvent::getActionCommand()
{
    return _command;
}
long long int ActionEvent::getWhen()
{
    //MMRESULT timeGetSystemTime(LPMMTIME pmmt, UINT cbmmt);
    //VOID GetLocalTime(LPSYSTEMTIME lpSystemTime);
    //VOID GetSystemTime(LPSYSTEMTIME lpSystemTime);
    //typedef struct _SYSTEMTIME{
    //    WORD wYear
    //    WORD wMonth
    //    WORD wDayOfWeek
    //    WORD wDay
    //    WORD wHour
    //    WORD wMinute
    //    WORD wSecond
    //    WORD wMilliseconds
    //} SYSTEMTIME;
    //return timeGetTime();
    return _when;
}
int ActionEvent::getModifiers()
{
    return _modifiers;
}
//===========================================================
//===========================================================
const int AdjustmentEvent::UNIT_INCREMENT  = 1;
const int AdjustmentEvent::UNIT_DECREMENT  = 2;
const int AdjustmentEvent::BLOCK_DECREMENT = 3;
const int AdjustmentEvent::BLOCK_INCREMENT = 4;
const int AdjustmentEvent::TRACK           = 5;
//===========================================================
//===========================================================
AdjustmentEvent::AdjustmentEvent(
    int source,
    int type,
    int value): 
    AWTEvent(source),
    _type(type),
    _value(value)
{}
AdjustmentEvent::~AdjustmentEvent(){}
int AdjustmentEvent::getAdjustmentType()
{
    return _type;
}
int AdjustmentEvent::getValue()
{
    return _value;
}
//===========================================================
//===========================================================
const int ComponentEvent::COMPONENT_FIRST   =100;
const int ComponentEvent::COMPONENT_LAST    =103;
const int ComponentEvent::COMPONENT_MOVED   =100;
const int ComponentEvent::COMPONENT_RESIZED =101;
const int ComponentEvent::COMPONENT_SHOWN   =102;
const int ComponentEvent::COMPONENT_HIDDEN  =103;
//===========================================================
//===========================================================
ComponentEvent::ComponentEvent(Component& source, int id):
    AWTEvent(source, id)
{}
ComponentEvent::ComponentEvent(const Component& source):
    AWTEvent(static_cast<int>(&source))
{}
ComponentEvent::~ComponentEvent(){}
Component& ComponentEvent::getComponent()
{
    //return *static_cast<Component*>(_source__);
    return static_cast<Component&>(*_source);
}
//===========================================================
//===========================================================
const int ContainerEvent::CONTAINER_FIRST   =300;
const int ContainerEvent::CONTAINER_LAST    =301;
const int ContainerEvent::COMPONENT_ADDED   =300;
const int ContainerEvent::COMPONENT_REMOVED =301;
//===========================================================
//===========================================================
ContainerEvent::ContainerEvent(
    const Component& source,
    const Component& child):
    ComponentEvent(source),
    _child(const_cast<Component*>(&child))
{}

ContainerEvent::ContainerEvent(
    Component& source,
    int id,
    Component& child):
    ComponentEvent(source, id),
    _child(&child)
{}
ContainerEvent::~ContainerEvent(){}
Container& ContainerEvent::getContainer()
{
    return *static_cast<Container*>(_source);
}
Component& ContainerEvent::getChild()
{
    return *_child;
}
//===========================================================
//===========================================================
const int FocusEvent::FOCUS_FIRST   =104;
const int FocusEvent::FOCUS_LAST    =105;
const int FocusEvent::FOCUS_GAINED  =104;
const int FocusEvent::FOCUS_LOST    =105;
//===========================================================
//===========================================================
FocusEvent::FocusEvent(
    const Component& source,
    const Component& opposite):
    ComponentEvent(source),
    _opposite(const_cast<Component*>(&opposite))
{}

FocusEvent::FocusEvent(
    Component& source,
    int id,
    bool temporary,
    Component& opposite):
    ComponentEvent(source, id),
    _temporary(temporary),
    _opposite(&opposite)
{}
FocusEvent::~FocusEvent(){}
bool FocusEvent::isTemporary()
{
    return _temporary;
}
Component& FocusEvent::getOppositeComponent()
{
    return *_opposite;
}
//===========================================================
//===========================================================
//const int InputEvent::SHIFT_MASK          =1;
//const int InputEvent::CTRL_MASK           =2;
//const int InputEvent::META_MASK           =4;
//const int InputEvent::ALT_MASK            =8;
//const int InputEvent::BUTTON1_MASK        =16;
//const int InputEvent::BUTTON2_MASK        =8;
//const int InputEvent::BUTTON3_MASK        =4;
const int InputEvent::ALT_GRAPH_MASK      =32;
const int InputEvent::SHIFT_DOWN_MASK     =64;
const int InputEvent::CTRL_DOWN_MASK      =128;
const int InputEvent::META_DOWN_MASK      =256;
const int InputEvent::ALT_DOWN_MASK       =512;
const int InputEvent::ALT_GRAPH_DOWN_MASK =8192;
const int InputEvent::BUTTON1_DOWN_MASK   =1024;
const int InputEvent::BUTTON2_DOWN_MASK   =2048;
const int InputEvent::BUTTON3_DOWN_MASK   =4096;
//===========================================================
//===========================================================
InputEvent::InputEvent(const Component& source): ComponentEvent(source){}

InputEvent::InputEvent(
    Component& source,
    int id,
    long long when,
    int modifiers):
    ComponentEvent(source, id),
    _when(when),
    _modifiers(modifiers)
{}
InputEvent::~InputEvent(){}
bool InputEvent::isShiftDown()
{
    return _modifiers & ALT_DOWN_MASK;
}
bool InputEvent::isControlDown()
{
    return _modifiers & CTRL_DOWN_MASK;
}
bool InputEvent::isAltDown()
{
    return _modifiers & ALT_DOWN_MASK;
}
long long InputEvent::getWhen()
{
    return _when;
    //return timeGetTime();
}
int InputEvent::getModifiersEx()
{
    return _modifiers;
}
//===========================================================
//===========================================================
const wchar_t KeyEvent::CHAR_UNDEFINED    =65535;
const int KeyEvent::KEY_FIRST             =400;
const int KeyEvent::KEY_LAST              =402;
const int KeyEvent::KEY_TYPED             =400;
const int KeyEvent::KEY_PRESSED           =401;
const int KeyEvent::KEY_RELEASED          =402;
const int KeyEvent::KEY_LOCATION_UNKNOWN  =0;
const int KeyEvent::KEY_LOCATION_STANDARD =1;
const int KeyEvent::KEY_LOCATION_LEFT     =2;
const int KeyEvent::KEY_LOCATION_RIGHT    =3;
const int KeyEvent::KEY_LOCATION_NUMPAD   =4;
//===========================================================
//===========================================================
KeyEvent::KeyEvent(
    const Component& source,
    wchar_t keyChar):
    InputEvent(source),
    _keyChar(keyChar)
{}

KeyEvent::KeyEvent(
    Component& source,
    int id,
    long long when,
    int modifiers,
    int keyCode,
    wchar_t keyChar,
    int keyLocation):
    InputEvent(source, id, when, modifiers),
    _keyCode(keyCode),
    _keyChar(keyChar),
    _keyLocation(keyLocation)
{}
KeyEvent::~KeyEvent(){}
int KeyEvent::getKeyCode()
{
    return _keyCode;
}
wchar_t KeyEvent::getKeyChar()
{
    return _keyChar;
}
int KeyEvent::getKeyLocation()
{
    return _keyLocation;
}
//===========================================================
//===========================================================
const int MouseEvent::NOBUTTON =0;
const int MouseEvent::BUTTON1  =1;
const int MouseEvent::BUTTON2  =2;
const int MouseEvent::BUTTON3  =3;
const int MouseEvent::MOUSE_FIRST    =500;
const int MouseEvent::MOUSE_LAST     =507;
const int MouseEvent::MOUSE_CLICKED  =500;
const int MouseEvent::MOUSE_PRESSED  =501;
const int MouseEvent::MOUSE_RELEASED =502;
const int MouseEvent::MOUSE_MOVED    =503;
const int MouseEvent::MOUSE_ENTERED  =504;
const int MouseEvent::MOUSE_EXITED   =505;
const int MouseEvent::MOUSE_DRAGGED  =506;
const int MouseEvent::MOUSE_WHEEL    =507;
//===========================================================
//===========================================================
MouseEvent::MouseEvent(
    const Component& source,
    int x,
    int y,
    int button):
    InputEvent(source),
    _x(x),
    _y(y),
    _button(button)
{}

MouseEvent::MouseEvent(
    Component& source,
    int id,
    long long when,
    int modifiers,
    int x,
    int y,
    int xAbs,
    int yAbs,
    int clickCount,
    bool popupTrigger,
    int button):
    InputEvent(source, id, when, modifiers),
    _x(x),
    _y(y),
    _xAbs(xAbs),
    _yAbs(yAbs),
    _clickCount(clickCount),
    _popupTrigger(popupTrigger),
    _button(button)
{}
MouseEvent::~MouseEvent(){}
int MouseEvent::getXOnScreen()
{
    return _xAbs;
}
int MouseEvent::getYOnScreen()
{
    return _yAbs;
}
int MouseEvent::getX()
{
    return _x;
}
int MouseEvent::getY()
{
    return _y;
}
int MouseEvent::getClickCount()
{
    return _clickCount;
}
int MouseEvent::getButton()
{
    return _button;
}
bool MouseEvent::isPopupTrigger()
{
    return _popupTrigger;
}
//===========================================================
//===========================================================
const int MouseWheelEvent::WHEEL_BLOCK_SCROLL =1;
const int MouseWheelEvent::WHEEL_UNIT_SCROLL  =0;
//===========================================================
//===========================================================
MouseWheelEvent::MouseWheelEvent(
    const Component& source,
    int x,
    int y,
    const int button,
    int wheelRotation):
    MouseEvent(source, x, y, button),
    _wheelRotation(wheelRotation)
{}

MouseWheelEvent::MouseWheelEvent(
    Component& source,
    int id,
    long long when,
    int modifiers,
    int x,
    int y,
    int xAbs,
    int yAbs,
    int clickCount,
    bool popupTrigger,
    int scrollType,
    int scrollAmount,
    int wheelRotation):
    MouseEvent(
        source,
        id,
        when,
        modifiers,
        x,
        y,
        xAbs,
        yAbs,
        clickCount,
        popupTrigger,
        0),
    _scrollType(scrollType),
    _scrollAmount(scrollAmount),
    _wheelRotation(wheelRotation)
{}
MouseWheelEvent::~MouseWheelEvent(){}
int MouseWheelEvent::getScrollAmount()
{
    return _scrollAmount;
}
int MouseWheelEvent::getWheelRotation()
{
    return _wheelRotation;
}
//===========================================================
//===========================================================
TextEvent::TextEvent(int source): AWTEvent(source){}
TextEvent::~TextEvent(){}
//===========================================================
//===========================================================
WindowEvent::WindowEvent(const Component& source): ComponentEvent(source){}
WindowEvent::~WindowEvent(){}
Window& WindowEvent::getWindow()
{
    return *static_cast<Window*>(_source__);
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
ActionListener::ActionListener(){}
ActionListener::~ActionListener(){}
//===========================================================
//===========================================================
AdjustmentListener::AdjustmentListener(){}
AdjustmentListener::~AdjustmentListener(){}
//===========================================================
//===========================================================
AWTEventListener::AWTEventListener(){}
AWTEventListener::~AWTEventListener(){}
//===========================================================
//===========================================================
ComponentListener::ComponentListener(){}
ComponentListener::~ComponentListener(){}
//===========================================================
//===========================================================
ContainerListener::ContainerListener(){}
ContainerListener::~ContainerListener(){}
//===========================================================
//===========================================================
FocusListener::FocusListener(){}
FocusListener::~FocusListener(){}
//===========================================================
//===========================================================
HierarchyBoundsListener::HierarchyBoundsListener(){}
HierarchyBoundsListener::~HierarchyBoundsListener(){}
//===========================================================
//===========================================================
HierarchyListener::HierarchyListener(){}
HierarchyListener::~HierarchyListener(){}
//===========================================================
//===========================================================
InputMethodListener::InputMethodListener(){}
InputMethodListener::~InputMethodListener(){}
//===========================================================
//===========================================================
Itemlistener::Itemlistener(){}
Itemlistener::~Itemlistener(){}
//===========================================================
//===========================================================
KeyListener::KeyListener(){}
KeyListener::~KeyListener(){}
//===========================================================
//===========================================================
MouseListener::MouseListener(){}
MouseListener::~MouseListener(){}
//===========================================================
//===========================================================
MouseMotionListener::MouseMotionListener(){}
MouseMotionListener::~MouseMotionListener(){}
//===========================================================
//===========================================================
MouseWheelListener::MouseWheelListener(){}
MouseWheelListener::~MouseWheelListener(){}
//===========================================================
//===========================================================
TextListener::TextListener(){}
TextListener::~TextListener(){}
//===========================================================
//===========================================================
WindowFocusListener::WindowFocusListener(){}
WindowFocusListener::~WindowFocusListener(){}
//===========================================================
//===========================================================
WindowListener::WindowListener(){}
WindowListener::~WindowListener(){}
//===========================================================
//===========================================================
WindowStateListener::WindowStateListener(){}
WindowStateListener::~WindowStateListener(){}
//===========================================================
//===========================================================
ComponentAdapter::ComponentAdapter(){}
ComponentAdapter::~ComponentAdapter(){}
void ComponentAdapter::componentHidden(ComponentEvent& e){}
void ComponentAdapter::componentMoved(ComponentEvent& e){}
void ComponentAdapter::componentResized(ComponentEvent& e){}
void ComponentAdapter::componentShown(ComponentEvent& e){}
//===========================================================
//===========================================================
ContainerAdapter::ContainerAdapter(){}
ContainerAdapter::~ContainerAdapter(){}
void ContainerAdapter::componentAdded(ContainerEvent& e){}
void ContainerAdapter::componentRemoved(ContainerEvent& e){}
//===========================================================
//===========================================================
FocusAdapter::FocusAdapter(){}
FocusAdapter::~FocusAdapter(){}
void FocusAdapter::focusGained(FocusEvent& e){}
void FocusAdapter::focusLost(FocusEvent& e){}
//===========================================================
//===========================================================
HierarchyBoundsAdapter::HierarchyBoundsAdapter(){}
HierarchyBoundsAdapter::~HierarchyBoundsAdapter(){}
void HierarchyBoundsAdapter::ancestorMoved(HierarchyEvent& e){}
void HierarchyBoundsAdapter::ancestorResized(HierarchyEvent& e){}
//===========================================================
//===========================================================
KeyAdapter::KeyAdapter(){}
KeyAdapter::~KeyAdapter(){}
void KeyAdapter::keyPressed(KeyEvent& e){}
void KeyAdapter::keyReleased(KeyEvent& e){}
void KeyAdapter::keyTyped(KeyEvent& e){}
//===========================================================
//===========================================================
MouseAdapter::MouseAdapter(){}
MouseAdapter::~MouseAdapter(){}
void MouseAdapter::mouseClicked(MouseEvent& e){}
void MouseAdapter::mouseEntered(MouseEvent& e){}
void MouseAdapter::mouseExited(MouseEvent& e){}
void MouseAdapter::mousePressed(MouseEvent& e){}
void MouseAdapter::mouseReleased(MouseEvent& e){}
void MouseAdapter::mouseDragged(MouseEvent& e){}
void MouseAdapter::mouseMoved(MouseEvent& e){}
void MouseAdapter::mouseWheelMoved(MouseWheelEvent& e){}
//===========================================================
//===========================================================
MouseMotionAdapter::MouseMotionAdapter(){}
MouseMotionAdapter::~MouseMotionAdapter(){}
void MouseMotionAdapter::mouseDragged(MouseEvent& e){}
void MouseMotionAdapter::mouseMoved(MouseEvent& e){}
//===========================================================
//===========================================================
WindowAdapter::WindowAdapter(){}
WindowAdapter::~WindowAdapter(){}
void WindowAdapter::windowGainedFocus(WindowEvent& e){}
void WindowAdapter::windowLostFocus(WindowEvent& e){}
void WindowAdapter::windowActivated(WindowEvent& e){}
void WindowAdapter::windowClosed(WindowEvent& e){}
void WindowAdapter::windowClosing(WindowEvent& e){}
void WindowAdapter::windowDeactivated(WindowEvent& e){}
void WindowAdapter::windowDeiconified(WindowEvent& e){}
void WindowAdapter::windowIconified(WindowEvent& e){}
void WindowAdapter::windowOpened(WindowEvent& e){}
void WindowAdapter::windowStateChanged(WindowEvent& e){}
//===========================================================
//===========================================================


const int KeyEvent::VK_UNDEFINED  =0;
const int KeyEvent::VK_CANCEL     =3;

const int KeyEvent::VK_BACK_SPACE =8;
const int KeyEvent::VK_TAB        =9;

const int KeyEvent::VK_CLEAR      =12;
//const int KeyEvent::VK_RETURN     =13;

const int KeyEvent::VK_SHIFT      =16;
const int KeyEvent::VK_CONTROL    =17;
const int KeyEvent::VK_ALT        =18;
const int KeyEvent::VK_PAUSE      =19;
const int KeyEvent::VK_CAPS_LOCK  =20;

const int KeyEvent::VK_ESCAPE     =27;

const int KeyEvent::VK_SPACE      =32;
const int KeyEvent::VK_PAGE_UP    =33;
const int KeyEvent::VK_PAGE_DOWN  =34;
const int KeyEvent::VK_END        =35;
const int KeyEvent::VK_HOME       =36;
const int KeyEvent::VK_LEFT       =37;
const int KeyEvent::VK_UP         =38;
const int KeyEvent::VK_RIGHT      =39;
const int KeyEvent::VK_DOWN       =40;
//const int KeyEvent::VK_SELECT     =41;
//const int KeyEvent::VK_PRINT      =42;
//const int KeyEvent::VK_EXECUTE    =43;
//const int KeyEvent::VK_SNAPSHOT   =44;VK_COMMA
//const int KeyEvent::VK_INSERT     =45;VK_MINUS
//const int KeyEvent::VK_DELETE     =46;VK_PERIOD
//const int KeyEvent::VK_HELP       =47;VK_SLASH

const int KeyEvent::VK_0          =48;
const int KeyEvent::VK_1          =49;
const int KeyEvent::VK_2          =50;
const int KeyEvent::VK_3          =51;
const int KeyEvent::VK_4          =52;
const int KeyEvent::VK_5          =53;
const int KeyEvent::VK_6          =54;
const int KeyEvent::VK_7          =55;
const int KeyEvent::VK_8          =56;
const int KeyEvent::VK_9          =57;

const int KeyEvent::VK_A          =65;
const int KeyEvent::VK_B          =66;
const int KeyEvent::VK_C          =67;
const int KeyEvent::VK_D          =68;
const int KeyEvent::VK_E          =69;
const int KeyEvent::VK_F          =70;
const int KeyEvent::VK_G          =71;
const int KeyEvent::VK_H          =72;
const int KeyEvent::VK_I          =73;
const int KeyEvent::VK_J          =74;
const int KeyEvent::VK_K          =75;
const int KeyEvent::VK_L          =76;
const int KeyEvent::VK_M          =77;
const int KeyEvent::VK_N          =78;
const int KeyEvent::VK_O          =79;
const int KeyEvent::VK_P          =80;
const int KeyEvent::VK_Q          =81;
const int KeyEvent::VK_R          =82;
const int KeyEvent::VK_S          =83;
const int KeyEvent::VK_T          =84;
const int KeyEvent::VK_U          =85;
const int KeyEvent::VK_V          =86;
const int KeyEvent::VK_W          =87;
const int KeyEvent::VK_X          =88;
const int KeyEvent::VK_Y          =89;
const int KeyEvent::VK_Z          =90;
/*
const int KeyEvent::VK_LWIN       =0x5B;
const int KeyEvent::VK_RWIN       =0x5C;
const int KeyEvent::VK_APPS       =0x5D;

const int KeyEvent::VK_NUMPAD0    =0x60;
const int KeyEvent::VK_NUMPAD1    =0x61;
const int KeyEvent::VK_NUMPAD2    =0x62;
const int KeyEvent::VK_NUMPAD3    =0x63;
const int KeyEvent::VK_NUMPAD4    =0x64;
const int KeyEvent::VK_NUMPAD5    =0x65;
const int KeyEvent::VK_NUMPAD6    =0x66;
const int KeyEvent::VK_NUMPAD7    =0x67;
const int KeyEvent::VK_NUMPAD8    =0x68;
const int KeyEvent::VK_NUMPAD9    =0x69;
const int KeyEvent::VK_MULTIPLY   =0x6A;
const int KeyEvent::VK_ADD        =0x6B;
const int KeyEvent::VK_SEPARATOR  =0x6C;
const int KeyEvent::VK_SUBTRACT   =0x6D;
const int KeyEvent::VK_DECIMAL    =0x6E;
const int KeyEvent::VK_DIVIDE     =0x6F;
const int KeyEvent::VK_F1         =0x70;
const int KeyEvent::VK_F2         =0x71;
const int KeyEvent::VK_F3         =0x72;
const int KeyEvent::VK_F4         =0x73;
const int KeyEvent::VK_F5         =0x74;
const int KeyEvent::VK_F6         =0x75;
const int KeyEvent::VK_F7         =0x76;
const int KeyEvent::VK_F8         =0x77;
const int KeyEvent::VK_F9         =0x78;
const int KeyEvent::VK_F10        =0x79;
const int KeyEvent::VK_F11        =0x7A;
const int KeyEvent::VK_F12        =0x7B;
const int KeyEvent::VK_F13        =0x7C;
const int KeyEvent::VK_F14        =0x7D;
const int KeyEvent::VK_F15        =0x7E;
const int KeyEvent::VK_F16        =0x7F;
const int KeyEvent::VK_F17        =0x80;
const int KeyEvent::VK_F18        =0x81;
const int KeyEvent::VK_F19        =0x82;
const int KeyEvent::VK_F20        =0x83;
const int KeyEvent::VK_F21        =0x84;
const int KeyEvent::VK_F22        =0x85;
const int KeyEvent::VK_F23        =0x86;
const int KeyEvent::VK_F24        =0x87;

const int KeyEvent::VK_NUMLOCK    =0x90;
const int KeyEvent::VK_SCROLL     =0x91;

const int KeyEvent::VK_LSHIFT     =0xA0;
const int KeyEvent::VK_RSHIFT     =0xA1;
const int KeyEvent::VK_LCONTROL   =0xA2;
const int KeyEvent::VK_RCONTROL   =0xA3;
const int KeyEvent::VK_LMENU      =0xA4;
const int KeyEvent::VK_RMENU      =0xA5;

const int KeyEvent::VK_PROCESSKEY =0xE5;

const int KeyEvent::VK_ATTN       =0xF6;
const int KeyEvent::VK_CRSEL      =0xF7;
const int KeyEvent::VK_EXSEL      =0xF8;
const int KeyEvent::VK_EREOF      =0xF9;
const int KeyEvent::VK_PLAY       =0xFA;
const int KeyEvent::VK_ZOOM       =0xFB;
const int KeyEvent::VK_NONAME     =0xFC;
const int KeyEvent::VK_PA1        =0xFD;
const int KeyEvent::VK_OEM_CLEAR  =0xFE;
*/



#endif //ifndef __Windows_awt_event_ActionEvent_cpp

