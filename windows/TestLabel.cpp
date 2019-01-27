

//===========================================================
//===========================================================
#include "_awt.h"
#include "_lang.h"
#include "_util.h"
//===========================================================
//===========================================================
class Test: public Label
{
private:
    class Listener;
    friend class Listener;
    static Listener* _listener;
    
public:
    Test();
    ~Test();
};
//===========================================================
//===========================================================
class Test::Listener:
    KeyListener
{
public:
    Listener();
    ~Listener();
    virtual void keyTyped(KeyEvent& e);
    virtual void keyPressed(KeyEvent& e);
    virtual void keyReleased(KeyEvent& e);
};
//===========================================================
//===========================================================

//===========================================================
//===========================================================
Test::Listener* Test::_listener =0;
//===========================================================
//===========================================================
Test::Test()
{
    if(!_listener){
        _listener = new Listener();
    }
    addKeyListener(*_listener);
    
    setLocation(0, 0);
    setText(String("abc"));
    setVisible(true);
    repaint();
    
    cout << getText() << endl;
}
Test::~Test(){}
//===========================================================
//===========================================================
Test::Listener::Listener(){}
Test::Listener::~Listener(){}
void Test::Listener::keyTyped(KeyEvent& e){}
void Test::Listener::keyPressed(KeyEvent& e){}
void Test::Listener::keyReleased(KeyEvent& e){}
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
    Test test();
    
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
//===========================================================
//===========================================================

