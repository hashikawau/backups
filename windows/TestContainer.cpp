

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
    
    int _id;
    
public:
    TestComponent(int id);
    ~TestComponent();
    virtual void paint(Graphics& g);
};
//===========================================================
//===========================================================
class TestComponent::Listener:
    public ComponentListener,
    public MouseListener,
    public MouseMotionListener,
    public MouseWheelListener
{
public:
    Listener();
    virtual ~Listener();
    virtual void componentHidden(ComponentEvent& e);
    virtual void componentMoved(ComponentEvent& e);
    virtual void componentResized(ComponentEvent& e);
    virtual void componentShown(ComponentEvent& e);
    
    virtual void mouseClicked(MouseEvent& e);
    virtual void mouseEntered(MouseEvent& e);
    virtual void mouseExited(MouseEvent& e);
    virtual void mousePressed(MouseEvent& e);
    virtual void mouseReleased(MouseEvent& e);
    
    virtual void mouseDragged(MouseEvent& e);
    virtual void mouseMoved(MouseEvent& e);
    
    virtual void mouseWheelMoved(MouseWheelEvent& e);
};
//===========================================================
//===========================================================

//===========================================================
//===========================================================
TestComponent::Listener* TestComponent::_listener =0;
//===========================================================
//===========================================================
TestComponent::TestComponent(int id)
{
    _id = id;
    if(!_listener){
        _listener = new TestComponent::Listener();
    }
    addComponentListener(*_listener);
    addMouseListener(*_listener);
    addMouseMotionListener(*_listener);
    addMouseWheelListener(*_listener);
}
TestComponent::~TestComponent(){}
void TestComponent::paint(Graphics& g)
{
    g.setColor(Color::white);
    g.fillRect(0, 0, getWidth(), getHeight());
    g.setColor(Color::black);
    g.drawRect(0, 0, getWidth(), getHeight());
    g.drawString(String(_id), 2, 2);
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
    class Listener;
    friend class Listener;
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
class Test::Listener: public ContainerListener
{
public:
    Listener();
    ~Listener();
    virtual void componentAdded(ContainerEvent& e);
    virtual void componentRemoved(ContainerEvent& e);
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
    setLayout(*static_cast<LayoutManager*>(0));
    addContainerListener(*new Listener());
    
    int num = 12;
    
    for(int i=0; i< num; ++i){
        Component& c = *new TestComponent(Math::abs(i -num +1));
        c.setBounds(
            10 +20 *i,
            10 +20 *i,
            100,
            50);
        add(c);
    }
    
    setSize(500, 600);
    setVisible(true);
    
    //start();
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
Test::Listener::Listener(){}
Test::Listener::~Listener(){}
void Test::Listener::componentAdded(ContainerEvent& e)
{
    cout << "    componentAdded" << endl;
}
void Test::Listener::componentRemoved(ContainerEvent& e)
{
    cout << "    componentRemoved" << endl;
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
void TestComponent::Listener::mouseClicked(MouseEvent& e){}
void TestComponent::Listener::mouseEntered(MouseEvent& e){}
void TestComponent::Listener::mouseExited(MouseEvent& e){}
void TestComponent::Listener::mousePressed(MouseEvent& e)
{
    Component& c = e.getComponent();
    c.getParent().setComponentZOrder(c, 0);
    c.getParent().repaint();
    //cout << "pressed" << endl;
}
void TestComponent::Listener::mouseReleased(MouseEvent& e)
{
    Component& c = e.getComponent();
    c.getParent().setComponentZOrder(c, c.TestComponent::_id);
    c.getParent().repaint();
    //cout << "released" << endl;
}
void TestComponent::Listener::mouseDragged(MouseEvent& e){}
void TestComponent::Listener::mouseMoved(MouseEvent& e){}
void TestComponent::Listener::mouseWheelMoved(MouseWheelEvent& e){}
//===========================================================
//===========================================================

