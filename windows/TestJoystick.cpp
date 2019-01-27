

//===========================================================
//===========================================================
#include "_awt.h"
#include "_lang.h"
#include "_util.h"
#include "cpp/Joystick.h"
#include "cpp/Joystick_cpp.h"
//===========================================================
//===========================================================
class TestComponent:
    public Component
{
private:
    class Listener;
    friend class Listener;
    static Listener* _listener;
    
    Color _color;
    String _string;
    
public:
    TestComponent(Color& color, String& string);
    ~TestComponent();
    virtual void paint(Graphics& g);
};
//===========================================================
//===========================================================
class TestComponent::Listener:
    public ComponentListener,
    public MouseWheelListener
{
public:
    Listener();
    virtual ~Listener();
    virtual void componentHidden(ComponentEvent& e);
    virtual void componentMoved(ComponentEvent& e);
    virtual void componentResized(ComponentEvent& e);
    virtual void componentShown(ComponentEvent& e);
    
    virtual void mouseWheelMoved(MouseWheelEvent& e);
};
//===========================================================
//===========================================================

//===========================================================
//===========================================================
TestComponent::Listener* TestComponent::_listener =0;
//===========================================================
//===========================================================
TestComponent::TestComponent(Color& color, String& string)
{
    _color = color;
    _string = string;
    if(!_listener){
        _listener = new TestComponent::Listener();
    }
    addComponentListener(*_listener);
}
TestComponent::~TestComponent(){}
void TestComponent::paint(Graphics& g)
{
    g.setColor(_color);
    g.fillRect(0, 0, getWidth(), getHeight());
    g.setColor(Color(~_color.getRGB()));
    g.drawRect(0, 0, getWidth(), getHeight());
    g.drawString(_string, 2, 2);
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
TestComponent::Listener::Listener(){}
TestComponent::Listener::~Listener(){}
void TestComponent::Listener::componentHidden(ComponentEvent& e)
{
    cout << "component hidden" << endl;
}
void TestComponent::Listener::componentMoved(ComponentEvent& e)
{
    cout << "component moved" << endl;
}
void TestComponent::Listener::componentResized(ComponentEvent& e)
{
    cout << "component resized" << endl;
}
void TestComponent::Listener::componentShown(ComponentEvent& e)
{
    cout << "component shown" << endl;
}
void TestComponent::Listener::mouseWheelMoved(MouseWheelEvent& e)
{
    Component& c = e.getComponent();
    
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
class Test:
    public Frame,
    public Thread
{
private:
    PointerObject<Component> _component;
    
public:
    Test(String& string);
    ~Test();
    virtual void update(Graphics& g);
    virtual void run();
    void teststart();
};
//===========================================================
//===========================================================
Test::Test(String& string): Frame(string){}
Test::~Test(){}
void Test::update(Graphics& g)
{
    Frame::update(g);
    /*
    POINT p;
    p.x = getX();
    p.y = getY();
    ScreenToClient(_hwnd, &p);
    cout << p.x << ", " << p.y << endl;
    SetViewportOrgEx(g._hdc, p.x, p.y, &p);
    SetWindowOrgEx(g._hdc, p.x, p.y, &p);
    cout << p.x << ", " << p.y << "============" << endl;
    //cout << endl;
    */
}
void Test::run()
{
    //cout << Joystick::getRmax(0) << " --- " << endl;
    unsigned int diff = Joystick::getXmax(0) - Joystick::getXmin(0);
    unsigned int width = 1000;
    unsigned int height = 600;
    //cout << joySetCapture(_hwnd, 0, 1, false) << endl;
    
    while(1){
        
        Joystick j(0);
        unsigned int buttons = j.getButtons();
        unsigned int numbutton = j.getButtonNumber();
        if(numbutton >= 8){
            //DestroyWindow(_hwnd);
        }
        int x = j.getX() *width /diff;
        int y = j.getY() *height /diff;
        //SetCursorPos(x, y);
        
        //HWND hwnd = GetForegroundWindow();
        POINT point;
        point.x = x;
        point.y = y;
        HWND hwnd = WindowFromPoint(point);
        RECT rect;
        GetWindowRect(hwnd, &rect);
        short newx = x -rect.left;
        short newy = y -rect.top;
        //cout << numbutton << ", ";
        //cout << Integer::toBinaryString(buttons);// << endl;
        //cout << hwnd << endl;
        if(buttons != 0 && hwnd != 0){
            PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, newy<<16 | newx);
            PostMessage(hwnd, WM_LBUTTONUP, 0, newy<<16 | newx);
        }
        
        sleep(10);
    }
}
void Test::teststart()
{
    setLayout(*static_cast<LayoutManager*>(0));
    
    int num = 30;
    Color colors[30];
    String strings[30];
    
    strings[0] = String("white");
    strings[1] = String("lightGray");
    strings[2] = String("gray");
    strings[3] = String("darkGray");
    strings[4] = String("black");
    strings[5] = String("red");
    strings[6] = String("pink");
    strings[7] = String("orange");
    strings[8] = String("yellow");
    strings[9] = String("green");
    strings[10] = String("magenta");
    strings[11] = String("cyan");
    strings[12] = String("blue");
    strings[13] = String("desktop");
    strings[14] = String("activeCaption");
    strings[15] = String("activeCaptionText");
    strings[16] = String("activeCaptionBorder");
    strings[17] = String("inactiveCaption");
    strings[18] = String("inactiveCaptionText");
    strings[19] = String("inactiveCaptionBorder");
    strings[20] = String("window");
    strings[21] = String("windowBorder");
    strings[22] = String("windowText");
    strings[23] = String("menu");
    strings[24] = String("menuText");
    strings[25] = String("text");
    strings[26] = String("textText");
    strings[27] = String("textHighlight");
    strings[28] = String("textHighlightText");
    strings[29] = String("textInactiveText");
    
    colors[0] = Color::white;
    colors[1] = Color::lightGray;
    colors[2] = Color::gray;
    colors[3] = Color::darkGray;
    colors[4] = Color::black;
    colors[5] = Color::red;
    colors[6] = Color::pink;
    colors[7] = Color::orange;
    colors[8] = Color::yellow;
    colors[9] = Color::green;
    colors[10] = Color::magenta;
    colors[11] = Color::cyan;
    colors[12] = Color::blue;
    colors[13] = SystemColor::desktop;
    colors[14] = SystemColor::activeCaption;
    colors[15] = SystemColor::activeCaptionText;
    colors[16] = SystemColor::activeCaptionBorder;
    colors[17] = SystemColor::inactiveCaption;
    colors[18] = SystemColor::inactiveCaptionText;
    colors[19] = SystemColor::inactiveCaptionBorder;
    colors[20] = SystemColor::window;
    colors[21] = SystemColor::windowBorder;
    colors[22] = SystemColor::windowText;
    colors[23] = SystemColor::menu;
    colors[24] = SystemColor::menuText;
    colors[25] = SystemColor::text;
    colors[26] = SystemColor::textText;
    colors[27] = SystemColor::textHighlight;
    colors[28] = SystemColor::textHighlightText;
    colors[29] = SystemColor::textInactiveText;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //_component = new TestComponent [10];
    for(int i=0; i< num; ++i){
        _component.addLast(
            new TestComponent(colors[i], strings[i]));
        _component[i]->setBounds(
            100 *(i %3),
            50 *(i /3),
            100,
            50);
        add(*_component[i]);
    }
    
    setSize(500, 600);
    setVisible(true);
    
    start();
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow)
{
    Test test(String(GetCommandLineW()));
    test.teststart();
    
    
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}
//===========================================================
//===========================================================

