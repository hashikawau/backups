

//===========================================================
//===========================================================
#include "_awt.h"
#include "_lang.h"
#include "_util.h"
//===========================================================
//===========================================================
class Test:
    public Component
{
private:
    class Listener;
    friend class Listener;
    static Listener* _listener;
    
    int _mouseX;
    int _mouseY;
    
    int _id;
    String string;
    
public:
    Test(int id);
    ~Test();
    virtual void update(Graphics& g);
};
//===========================================================
//===========================================================

//===========================================================
//===========================================================
class Test::Listener:
    public ComponentListener,
    public FocusListener,
    public KeyListener,
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
    
    virtual void focusGained(FocusEvent& e);
    virtual void focusLost(FocusEvent& e);
    
    virtual void keyTyped(KeyEvent& e);
    virtual void keyPressed(KeyEvent& e);
    virtual void keyReleased(KeyEvent& e);
    
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
Test::Listener* Test::_listener =0;
Test::Test(int id)
{
    if(!_listener){
        _listener = new Test::Listener();
    }
    addComponentListener(*_listener);
    addFocusListener(*_listener);
    addKeyListener(*_listener);
    addMouseListener(*_listener);
    addMouseMotionListener(*_listener);
    addMouseWheelListener(*_listener);
    
    _mouseX =0;
    _mouseY =0;
    
    _id = id;
    
    //cout << "setsize" << endl;
    setSize(300, 200);
    setLocation(0, 200 *_id);
    setVisible(true);
}
Test::~Test(){}
void Test::update(Graphics& g)
{
    g.setColor(Color::white);
    g.fillRect(0, 0, getWidth(), getHeight());
    g.setColor(Color::black);
    g.drawRect(0, 0, getWidth(), getHeight());
    g.drawString(String(_id), 2, 2);
    g.drawString(string, 2, 20);
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
Test::Listener::Listener(){}
Test::Listener::~Listener(){}
//===========================================================
//===========================================================
void Test::Listener::componentShown(ComponentEvent& e)
{
    cout << "    componentShown" << endl;
    Test& t = static_cast<Test&>(e.getComponent());
    //cout << t.getWidth() << ", " << t.getHeight() << endl;
    t.repaint();
}
void Test::Listener::componentHidden(ComponentEvent& e)
{
    cout << "    componentHidden" << endl;
    Test& t = static_cast<Test&>(e.getComponent());
    //cout << t.getWidth() << ", " << t.getHeight() << endl;
    t.repaint();
}
void Test::Listener::componentResized(ComponentEvent& e)
{
    cout << "    componentResized";
    cout << "=> ";
    
    Test& t = static_cast<Test&>(e.getComponent());
    cout << t.getX() << ", " << t.getY() << " - ";
    cout << t.getWidth() << ", " << t.getHeight() << endl;
}
void Test::Listener::componentMoved(ComponentEvent& e)
{
    cout << "    componentMoved";
    cout << "=> ";
    
    Test& t = static_cast<Test&>(e.getComponent());
    cout << t.getX() << ", " << t.getY() << " - ";
    cout << t.getWidth() << ", " << t.getHeight() << endl;
}
//===========================================================
//===========================================================
void Test::Listener::focusGained(FocusEvent& e)
{
    cout << "    focusGained" << endl;
    Test& t = static_cast<Test&>(e.getComponent());
}
void Test::Listener::focusLost(FocusEvent& e)
{
    cout << "    focusLost" << endl;
    Test& t = static_cast<Test&>(e.getComponent());
}
//===========================================================
//===========================================================
void Test::Listener::keyTyped(KeyEvent& e)
{
    cout << "    keyTyped" << endl;
    Test& t = static_cast<Test&>(e.getComponent());
    t.string = String(e.getKeyChar());
    t.repaint();
}
void Test::Listener::keyPressed(KeyEvent& e)
{
    cout << "    keyPressed" << endl;
    Test& t = static_cast<Test&>(e.getComponent());
}
void Test::Listener::keyReleased(KeyEvent& e)
{
    cout << "    keyReleased" << endl;
    Test& t = static_cast<Test&>(e.getComponent());
}
//===========================================================
//===========================================================
void Test::Listener::mouseClicked(MouseEvent& e)
{
    cout << "    mouseClicked" << endl;
    Test& t = static_cast<Test&>(e.getComponent());
    //t.setCursor(Cursor(Cursor::TEXT_CURSOR));
}
void Test::Listener::mouseEntered(MouseEvent& e)
{
    cout << "    mouseEntered" << endl;
}
void Test::Listener::mouseExited(MouseEvent& e)
{
    cout << "    mouseExited" << endl;
}
void Test::Listener::mousePressed(MouseEvent& e)
{
    cout << "    mousePressed" << endl;
    
    int mx = e.getX();
    int my = e.getY();
    Test& t = static_cast<Test&>(e.getComponent());
    t._mouseX = mx;
    t._mouseY = my;
    
    int n=4;
    if(mx >= n && mx <= t.getWidth() -n
        && my >= n && my <= t.getHeight() -n)
    {
        t.setCursor(Cursor(Cursor::MOVE_CURSOR));
    }
}
void Test::Listener::mouseReleased(MouseEvent& e)
{
    cout << "    mouseReleased" << endl;
    Test& t = static_cast<Test&>(e.getComponent());
    t.setCursor(Cursor(Cursor::DEFAULT_CURSOR));
}
void Test::Listener::mouseDragged(MouseEvent& e)
{
    cout << "    mouseDragged" << endl;
    
    int mx = e.getX();
    int my = e.getY();
    Test& t = static_cast<Test&>(e.getComponent());
    int cw = t.getWidth();
    int ch = t.getHeight();
    
    if(t._id %2){
        return;
    }
    
    int type = (*t.getCursor()).getType();
    switch(type){
        case Cursor::MOVE_CURSOR:
            t.setLocation(
                t.getX() +mx -t._mouseX,
                t.getY() +my -t._mouseY);
            break;
        
        case Cursor::N_RESIZE_CURSOR:
            t.setBounds(
                t.getX(),
                t.getY() +my -t._mouseY,
                cw,
                ch -(my -t._mouseY));
            break;
        
        case Cursor::S_RESIZE_CURSOR:
            t.setSize(
                cw,
                ch +my -t._mouseY);
            t._mouseY = my;
            break;
        
        case Cursor::W_RESIZE_CURSOR:
            t.setBounds(
                t.getX() +mx -t._mouseX,
                t.getY(),
                cw -(mx -t._mouseX),
                ch);
            break;
        
        case Cursor::E_RESIZE_CURSOR:
            t.setSize(
                cw +mx -t._mouseX,
                ch);
            t._mouseX = mx;
            break;
        
        case Cursor::SW_RESIZE_CURSOR:
            t.setBounds(
                t.getX() +mx -t._mouseX,
                t.getY(),
                cw -(mx -t._mouseX),
                ch +my -t._mouseY);
            t._mouseY = my;
            break;
        
        case Cursor::NE_RESIZE_CURSOR:
            t.setBounds(
                t.getX(),
                t.getY() +my -t._mouseY,
                cw +mx -t._mouseX,
                ch -(my -t._mouseY));
            t._mouseX = mx;
            break;
        
        case Cursor::SE_RESIZE_CURSOR:
            t.setSize(
                cw +mx -t._mouseX,
                ch +my -t._mouseY);
            t._mouseX = mx;
            t._mouseY = my;
            break;
        
        case Cursor::NW_RESIZE_CURSOR:
            t.setBounds(
                t.getX() +mx -t._mouseX,
                t.getY() +my -t._mouseY,
                cw -(mx -t._mouseX),
                ch -(my -t._mouseY));
            break;
        
        default:
            break;
    }
    t.repaint();
}
void Test::Listener::mouseMoved(MouseEvent& e)
{
    int mx = e.getX();
    int my = e.getY();
    cout << "    mouseMoved";
    cout << " = ";
    cout << mx << ", " << my << endl;
    
    Test& t = static_cast<Test&>(e.getComponent());
    int cw = t.getWidth();
    int ch = t.getHeight();
    int n = 4;
    if(mx < n){
        if(my < n){
            t.setCursor(Cursor(Cursor::NW_RESIZE_CURSOR));
        }else
        if(my > ch -n){
            t.setCursor(Cursor(Cursor::SW_RESIZE_CURSOR));
        }else{
            t.setCursor(Cursor(Cursor::W_RESIZE_CURSOR));
        }
    }else
    if(mx > cw -n){
        if(my < n){
            t.setCursor(Cursor(Cursor::NE_RESIZE_CURSOR));
        }else
        if(my > ch -n){
            t.setCursor(Cursor(Cursor::SE_RESIZE_CURSOR));
        }else{
            t.setCursor(Cursor(Cursor::E_RESIZE_CURSOR));
        }
    }else{
        if(my < n){
            t.setCursor(Cursor(Cursor::N_RESIZE_CURSOR));
        }else
        if(my > ch -n){
            t.setCursor(Cursor(Cursor::S_RESIZE_CURSOR));
        }else{
            t.setCursor(Cursor(Cursor::DEFAULT_CURSOR));
        }
    }
}
void Test::Listener::mouseWheelMoved(MouseWheelEvent& e)
{
    Component& c = e.getComponent();
    cout << "    mouseWheelMoved" << endl;
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
    Test& test0 = *new Test(0);
    Test& test1 = *new Test(1);
    cout << endl;
    
    //Sleep(1000);
    //cout << "set false" << endl;
    //test.setVisible(false);
    //test.repaint();
    
    //Sleep(1000);
    //cout << "set true" << endl;
    //test.setVisible(true);
    //test.repaint();
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}
//===========================================================
//===========================================================

