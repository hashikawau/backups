

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
Test::Test(String& string): Frame(string)
{
    //setLayout(*static_cast<LayoutManager*>(0));
}
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
    double amplitude =30;
    
    double sum =0;
    int count =0;
    while(1){
        ++count;
        double d = amplitude *Math::random();
        sum += d;
        cout << count << ", " << d << " ==> " << sum /count << endl;
        
        sleep(100);
    }
}
void Test::teststart()
{
    int num = 30;
    
    /*
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
    */
    
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

//===========================================================
//===========================================================
TestComponent::Listener::Listener(){}
TestComponent::Listener::~Listener(){}
void TestComponent::Listener::componentHidden(ComponentEvent& e){}
void TestComponent::Listener::componentMoved(ComponentEvent& e){}
void TestComponent::Listener::componentResized(ComponentEvent& e){}
void TestComponent::Listener::componentShown(ComponentEvent& e){}
void TestComponent::Listener::mouseWheelMoved(MouseWheelEvent& e){}
//===========================================================
//===========================================================

