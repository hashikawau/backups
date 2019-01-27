

#ifndef __Windows_awt_event_ActionEvent
#define __Windows_awt_event_ActionEvent

using namespace std;

#include "../AWTEvent.h"


class ActionEvent: public AWTEvent
{
public:
    static const int SHIFT_MASK;
    static const int CTRL_MASK;
    static const int META_MASK;
    static const int ALT_MASK;

private:
    string _command;
    int _modifiers;
    long long int _when;

public:
    ActionEvent(Object& source, int id, const string& command);
    ActionEvent(Object& source, int id, const string& command, int modifiers);
    ActionEvent(Object& source, int id, const string& command,
        long long int when, int modiriers);
    explicit ActionEvent(int source);
    virtual ~ActionEvent();
    string getActionCommand();
    long long int getWhen();
    int getModifiers();
};


class AdjustmentEvent: public AWTEvent
{
public:
    static const int BLOCK_DECREMENT;
    static const int BLOCK_INCREMENT;
    static const int TRACK;
    static const int UNIT_DECREMENT;
    static const int UNIT_INCREMENT;

private:
    int _type;
    int _value;

public:
    AdjustmentEvent(
        int source,
        int type,
        int value);
    virtual ~AdjustmentEvent();
    int getAdjustmentType();
    int getValue();
};


class Component;
class ComponentEvent: public AWTEvent
{
public:
    static const int COMPONENT_FIRST;
    static const int COMPONENT_LAST;
    static const int COMPONENT_MOVED;
    static const int COMPONENT_RESIZED;
    static const int COMPONENT_SHOWN;
    static const int COMPONENT_HIDDEN;

public:
    explicit ComponentEvent(const Component& source);

    ComponentEvent(Component& source, int id);
    virtual ~ComponentEvent();
    Component& getComponent();
};


class Container;
class ContainerEvent: public ComponentEvent
{
public:
    static const int CONTAINER_FIRST;
    static const int CONTAINER_LAST;
    static const int COMPONENT_ADDED;
    static const int COMPONENT_REMOVED;

private:
    Component* _child;

public:
    ContainerEvent(const Component& source, const Component& child);

    ContainerEvent(Component& source, int id, Component& child);
    virtual ~ContainerEvent();
    Container& getContainer();
    Component& getChild();
};


class FocusEvent: public ComponentEvent
{
public:
    static const int FOCUS_FIRST;
    static const int FOCUS_LAST;
    static const int FOCUS_GAINED;
    static const int FOCUS_LOST;

private:
    bool _temporary;
    Component* _opposite;

public:
    FocusEvent(const Component& source, const Component& opposite);

    //FocusEvent(Component& source, int id);
    //FocusEvent(Component& source, int id, bool temporary);
    FocusEvent(
        Component& source, int id, bool temporary, Component& opposite);
    virtual ~FocusEvent();
    bool isTemporary();
    Component& getOppositeComponent();
};


class HierarchyEvent;


class InputMethodEvent;


class InputEvent: public ComponentEvent
{
public:
    //static const int SHIFT_MASK;
    //static const int CTRL_MASK;
    //static const int META_MASK;
    //static const int ALT_MASK;
    //static const int BUTTON1_MASK;
    //static const int BUTTON2_MASK;
    //static const int BUTTON3_MASK;
    static const int ALT_GRAPH_MASK;
    static const int SHIFT_DOWN_MASK;
    static const int CTRL_DOWN_MASK;
    static const int META_DOWN_MASK;
    static const int ALT_DOWN_MASK;
    static const int ALT_GRAPH_DOWN_MASK;
    static const int BUTTON1_DOWN_MASK;
    static const int BUTTON2_DOWN_MASK;
    static const int BUTTON3_DOWN_MASK;

private:
    long long _when;
    int _modifiers;

public:
    explicit InputEvent(const Component& source);

    InputEvent(Component& source, int id, long long when, int modifiers);
    virtual ~InputEvent() =0;
    bool isShiftDown();
    bool isControlDown();
    bool isAltDown();
    long long getWhen();
    int getModifiersEx();
};


class InvocationEvent;


class ItemEvent;


class KeyEvent: public InputEvent
{
public:
    static const wchar_t CHAR_UNDEFINED;
    static const int KEY_FIRST;
    static const int KEY_LAST;
    static const int KEY_TYPED;
    static const int KEY_PRESSED;
    static const int KEY_RELEASED;
    static const int KEY_LOCATION_UNKNOWN;
    static const int KEY_LOCATION_STANDARD;
    static const int KEY_LOCATION_LEFT;
    static const int KEY_LOCATION_RIGHT;
    static const int KEY_LOCATION_NUMPAD;

    static const int VK_UNDEFINED;
    //static const int VK_CANCEL;

    static const int VK_BACK_SPACE;
    //static const int VK_TAB;

    //static const int VK_CLEAR;

    //static const int VK_SHIFT;
    //static const int VK_CONTROL;
    static const int VK_ALT;
    //static const int VK_PAUSE;
    static const int VK_CAPS_LOCK;

    //static const int VK_ESCAPE;

    //static const int VK_SPACE;
    static const int VK_PAGE_UP;
    static const int VK_PAGE_DOWN;
    //static const int VK_END;
    //static const int VK_HOME;
    //static const int VK_LEFT;
    //static const int VK_UP;
    //static const int VK_RIGHT;
    //static const int VK_DOWN;

    static const int VK_0;
    static const int VK_1;
    static const int VK_2;
    static const int VK_3;
    static const int VK_4;
    static const int VK_5;
    static const int VK_6;
    static const int VK_7;
    static const int VK_8;
    static const int VK_9;

    static const int VK_A;
    static const int VK_B;
    static const int VK_C;
    static const int VK_D;
    static const int VK_E;
    static const int VK_F;
    static const int VK_G;
    static const int VK_H;
    static const int VK_I;
    static const int VK_J;
    static const int VK_K;
    static const int VK_L;
    static const int VK_M;
    static const int VK_N;
    static const int VK_O;
    static const int VK_P;
    static const int VK_Q;
    static const int VK_R;
    static const int VK_S;
    static const int VK_T;
    static const int VK_U;
    static const int VK_V;
    static const int VK_W;
    static const int VK_X;
    static const int VK_Y;
    static const int VK_Z;

private:
    int _keyCode;
    wchar_t _keyChar;
    int _keyLocation;

public:
    KeyEvent(const Component& source, wchar_t keyChar);

    KeyEvent(
        Component& source, int id, long long when, int modifiers,
        int keyCode, wchar_t keyChar, int keyLocation);
    virtual ~KeyEvent();
    int getKeyCode();
    wchar_t getKeyChar();
    int getKeyLocation();

    //static String getKeyText(int keyCode);
    //static String getKeyModifiersText(int modifiers);

    //bool isActionKey();
};


class MouseEvent: public InputEvent
{
public:
    static const int BUTTON1;
    static const int BUTTON2;
    static const int BUTTON3;
    static const int NOBUTTON;
    static const int MOUSE_FIRST;
    static const int MOUSE_LAST;
    static const int MOUSE_CLICKED;
    static const int MOUSE_PRESSED;
    static const int MOUSE_RELEASED;
    static const int MOUSE_MOVED;
    static const int MOUSE_ENTERED;
    static const int MOUSE_EXITED;
    static const int MOUSE_DRAGGED;
    static const int MOUSE_WHEEL;

private:
    int _x;
    int _y;
    int _xAbs;
    int _yAbs;
    int _clickCount;
    bool _popupTrigger;
    int _button;

public:
    MouseEvent(
        const Component& source,
        int x,
        int y,
        int button);

    MouseEvent(
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
        int button);
    virtual ~MouseEvent();
    int getXOnScreen();
    int getYOnScreen();
    int getX();
    int getY();
    int getClickCount();
    int getButton();
    bool isPopupTrigger();
};


class MouseWheelEvent: public MouseEvent
{
public:
    static const int WHEEL_BLOCK_SCROLL;
    static const int WHEEL_UNIT_SCROLL;

private:
    int _scrollType;
    int _scrollAmount;
    int _wheelRotation;

public:
    MouseWheelEvent(
        const Component& source,
        int x,
        int y,
        int button,
        int wheelRotation);

    MouseWheelEvent(
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
        int wheelRotation);
    virtual ~MouseWheelEvent();
    int getScrollAmount();
    int getWheelRotation();
};


class PaintEvent;


class TextEvent: public AWTEvent
{
public:
    explicit TextEvent(int source);
    virtual ~TextEvent();
};


class Window;
class WindowEvent: public ComponentEvent
{
public:
    explicit WindowEvent(const Component& source);
    virtual ~WindowEvent();
    Window& getWindow();
};





class ActionListener: public EventListener
{
public:
    ActionListener();
    virtual ~ActionListener() =0;
    virtual void actionPerformed(ActionEvent& e) =0;
};


class AdjustmentListener: public EventListener
{
public:
    AdjustmentListener();
    virtual ~AdjustmentListener() =0;
    virtual void adjustmentValueChanged(AdjustmentEvent& e) =0;
};


class AWTEventListener: public EventListener
{
public:
    AWTEventListener();
    virtual ~AWTEventListener() =0;
    virtual void eventDispatched(AWTEvent& e) =0;
};


class ComponentListener: public EventListener
{
public:
    ComponentListener();
    virtual ~ComponentListener() =0;
    virtual void componentHidden(ComponentEvent& e) =0;
    virtual void componentMoved(ComponentEvent& e) =0;
    virtual void componentResized(ComponentEvent& e) =0;
    virtual void componentShown(ComponentEvent& e) =0;
};


class ContainerListener: public EventListener
{
public:
    ContainerListener();
    virtual ~ContainerListener() =0;
    virtual void componentAdded(ContainerEvent& e) =0;
    virtual void componentRemoved(ContainerEvent& e) =0;
};


class FocusListener: public EventListener
{
public:
    FocusListener();
    virtual ~FocusListener() =0;
    virtual void focusGained(FocusEvent& e) =0;
    virtual void focusLost(FocusEvent& e) =0;
};


class HierarchyBoundsListener: public EventListener
{
public:
    HierarchyBoundsListener();
    virtual ~HierarchyBoundsListener() =0;
    virtual void ancestorMoved(HierarchyEvent& e) =0;
    virtual void ancestorResized(HierarchyEvent& e) =0;
};


class HierarchyListener: public EventListener
{
public:
    HierarchyListener();
    virtual ~HierarchyListener() =0;
    virtual void hierarchyChanged(HierarchyEvent& e) =0;
};


class InputMethodListener: public EventListener
{
public:
    InputMethodListener();
    virtual ~InputMethodListener() =0;
    virtual void caretPositionChanged(InputMethodEvent& e) =0;
    virtual void inputMethodTextChanged(InputMethodEvent& e) =0;
};


class Itemlistener: public EventListener
{
public:
    Itemlistener();
    virtual ~Itemlistener() =0;
    virtual void itemStateChanged(ItemEvent& e) =0;
};


class KeyListener: public EventListener
{
public:
    KeyListener();
    virtual ~KeyListener() =0;
    virtual void keyPressed(KeyEvent& e) =0;
    virtual void keyReleased(KeyEvent& e) =0;
    virtual void keyTyped(KeyEvent& e) =0;
};


class MouseListener: public EventListener
{
public:
    MouseListener();
    virtual ~MouseListener() =0;
    virtual void mouseClicked(MouseEvent& e) =0;
    virtual void mousePressed(MouseEvent& e) =0;
    virtual void mouseReleased(MouseEvent& e) =0;
    virtual void mouseEntered(MouseEvent& e) =0;
    virtual void mouseExited(MouseEvent& e) =0;
};


class MouseMotionListener: public EventListener
{
public:
    MouseMotionListener();
    virtual ~MouseMotionListener() =0;
    virtual void mouseDragged(MouseEvent& e) =0;
    virtual void mouseMoved(MouseEvent& e) =0;
};


class MouseWheelListener: public EventListener
{
public:
    MouseWheelListener();
    virtual ~MouseWheelListener() =0;
    virtual void mouseWheelMoved(MouseWheelEvent& e) =0;
};


class TextListener: public EventListener
{
public:
    TextListener();
    virtual ~TextListener() =0;
    virtual void textValueChanged(TextEvent& e) =0;
};


class WindowFocusListener: public EventListener
{
public:
    WindowFocusListener();
    virtual ~WindowFocusListener() =0;
    virtual void windowGainedFocus(WindowEvent& e) =0;
    virtual void windowLostFocus(WindowEvent& e) =0;
};


class WindowListener: public EventListener
{
public:
    WindowListener();
    virtual ~WindowListener() =0;
    virtual void windowActivated(WindowEvent& e) =0;
    virtual void windowClosed(WindowEvent& e) =0;
    virtual void windowClosing(WindowEvent& e) =0;
    virtual void windowDeactivated(WindowEvent& e) =0;
    virtual void windowDeiconified(WindowEvent& e) =0;
    virtual void windowIconified(WindowEvent& e) =0;
    virtual void windowOpened(WindowEvent& e) =0;
};


class WindowStateListener: public EventListener
{
public:
    WindowStateListener();
    virtual ~WindowStateListener() =0;
    virtual void windowStateChanged(WindowEvent& e) =0;
};





class ComponentAdapter: public ComponentListener
{
public:
    ComponentAdapter();
    virtual ~ComponentAdapter() =0;
    virtual void componentHidden(ComponentEvent& e);
    virtual void componentMoved(ComponentEvent& e);
    virtual void componentResized(ComponentEvent& e);
    virtual void componentShown(ComponentEvent& e);
};


class ContainerAdapter: public ContainerListener
{
public:
    ContainerAdapter();
    virtual ~ContainerAdapter() =0;
    virtual void componentAdded(ContainerEvent& e);
    virtual void componentRemoved(ContainerEvent& e);
};


class FocusAdapter: public FocusListener
{
public:
    FocusAdapter();
    virtual ~FocusAdapter() =0;
    virtual void focusGained(FocusEvent& e);
    virtual void focusLost(FocusEvent& e);
};


class HierarchyBoundsAdapter: public HierarchyBoundsListener
{
public:
    HierarchyBoundsAdapter();
    virtual ~HierarchyBoundsAdapter() =0;
    virtual void ancestorMoved(HierarchyEvent& e);
    virtual void ancestorResized(HierarchyEvent& e);
};


class KeyAdapter: public KeyListener
{
public:
    KeyAdapter();
    virtual ~KeyAdapter() =0;
    virtual void keyPressed(KeyEvent& e);
    virtual void keyReleased(KeyEvent& e);
    virtual void keyTyped(KeyEvent& e);
};


class MouseAdapter:
    public MouseListener,
    public MouseMotionListener,
    public MouseWheelListener
{
public:
    MouseAdapter();
    virtual ~MouseAdapter() =0;
    virtual void mouseClicked(MouseEvent& e);
    virtual void mouseEntered(MouseEvent& e);
    virtual void mouseExited(MouseEvent& e);
    virtual void mousePressed(MouseEvent& e);
    virtual void mouseReleased(MouseEvent& e);
    virtual void mouseDragged(MouseEvent& e);
    virtual void mouseMoved(MouseEvent& e);
    virtual void mouseWheelMoved(MouseWheelEvent& e);
};


class MouseMotionAdapter: public MouseMotionListener
{
public:
    MouseMotionAdapter();
    virtual ~MouseMotionAdapter() =0;
    virtual void mouseDragged(MouseEvent& e);
    virtual void mouseMoved(MouseEvent& e);
};


class WindowAdapter:
    public WindowFocusListener,
    public WindowListener,
    public WindowStateListener
{
public:
    WindowAdapter();
    virtual ~WindowAdapter() =0;
    virtual void windowGainedFocus(WindowEvent& e);
    virtual void windowLostFocus(WindowEvent& e);
    virtual void windowActivated(WindowEvent& e);
    virtual void windowClosed(WindowEvent& e);
    virtual void windowClosing(WindowEvent& e);
    virtual void windowDeactivated(WindowEvent& e);
    virtual void windowDeiconified(WindowEvent& e);
    virtual void windowIconified(WindowEvent& e);
    virtual void windowOpened(WindowEvent& e);
    virtual void windowStateChanged(WindowEvent& e);
};




#endif //ifndef __Windows_awt_event_ActionEvent

