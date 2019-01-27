

#include "windows\awt\Frame.h"
#include "windows\awt\Button.h"
#include "windows\lang\String.h"

#include <iostream.h>

#include "windows\lang\Thread.h"
#include "windows\cpp\3d\utils\universe\SimpleUniverse.h"





//===========================================================
//===========================================================

//===========================================================
//===========================================================
class TransformGroup
{
private:
    
    
public:
    
};
//===========================================================
//===========================================================
        
//===========================================================
//===========================================================
class TestSimpleUniverse:
    public Frame,
    public ActionListener,
    public Thread
{
private:
    Button* _button;
    
public:
    TestSimpleUniverse(const String& str);
    virtual void paint(Graphics& g);
    virtual void actionPerformed(ActionEvent& e);
    virtual void run();
    
    void teststart();
};
//===========================================================
//===========================================================
TestSimpleUniverse::TestSimpleUniverse(const String& str): Frame(str)
{
    _button = new Button(String("Add Ball"));
    _button->addActionListener(*this);
    add(*_button);
}
//===========================================================
//===========================================================
void TestSimpleUniverse::paint(Graphics& g)
{
    g.setColor(Color(0));
    
}
//===========================================================
//===========================================================
void TestSimpleUniverse::actionPerformed(ActionEvent& e)
{
    
}
//===========================================================
//===========================================================
void TestSimpleUniverse::run()
{
    while(1){
        repaint();
        sleep(100);
    }
}
//===========================================================
//===========================================================
void TestSimpleUniverse::teststart()
{
    setBounds(0, 250, 600, 300);
    setVisible(true);
    start();
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR lpCmdLine,
                   int nCmdShow)
{
    TestSimpleUniverse test(GetCommandLineW());
    test.teststart();
    
    while(GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return msg.wParam;
}
//===========================================================
//===========================================================
