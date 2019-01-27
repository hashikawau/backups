

#include "windows\awt\Frame.h"
#include "windows\awt\Button.h"
#include "windows\lang\String.h"

#include <iostream.h>

#include "windows\lang\Thread.h"



//===========================================================
//===========================================================
class TestThread;
class BoundingBall: public Thread
{
    friend class TestThread;
private:
    static const int _MAXBALL;
    static int _numball;
    static int _firstindex;
    static int _count;
    static BoundingBall** _array;
    int _id;
    int _x;
    int _y;
    
public:
    BoundingBall();
    ~BoundingBall();
    virtual void run();
    
    static BoundingBall** getArray();
    static int getMaxball();
    static int getNumball();
    int getX();
    int getY();
};
static const int BoundingBall::_MAXBALL =20;
static int BoundingBall::_numball =0;
static int BoundingBall::_firstindex =0;
static int BoundingBall::_count =0;
static BoundingBall** BoundingBall::_array =
    new BoundingBall* [BoundingBall::_MAXBALL];
//===========================================================
//===========================================================
BoundingBall::BoundingBall()
{
    _id=_count++ %_MAXBALL;
    _x = 0;
    _y = (_firstindex +_numball) %_MAXBALL;
    _array[_y] = this;
    ++_numball;
    start();
}
BoundingBall::~BoundingBall()
{
    --_numball;
    ++_firstindex;
    _array[_y] =0;
}
//===========================================================
//===========================================================
void BoundingBall::run()
{
    for(int i=0; i< 20; ++i){
        //cout<<_y<<"  "<<(_x++)<<endl;
        ++_x;
        sleep(100);
    }
    delete this;
}
//===========================================================
//===========================================================
static BoundingBall** BoundingBall::getArray()
{
    return _array +_firstindex;
}
static int BoundingBall::getMaxball()
{
    return _MAXBALL;
}
static int BoundingBall::getNumball()
{
    return _numball;
}
int BoundingBall::getX()
{
    return _x;
}
int BoundingBall::getY()
{
    return _y;
}
//===========================================================
//===========================================================
        
//===========================================================
//===========================================================
class TestThread:
    public Frame,
    public ActionListener,
    public Thread
{
private:
    Button* _button;
    
public:
    TestThread(const String& str);
    virtual void paint(Graphics& g);
    virtual void actionPerformed(ActionEvent& e);
    virtual void run();
    
    void teststart();
};
//===========================================================
//===========================================================
TestThread::TestThread(const String& str): Frame(str)
{
    _button = new Button(String("Add Ball"));
    _button->addActionListener(*this);
    add(*_button);
}
//===========================================================
//===========================================================
void TestThread::paint(Graphics& g)
{
    g.setColor(Color(0));
    for(
        int i= BoundingBall::_firstindex;
        i< BoundingBall::_firstindex +BoundingBall::_numball;
        ++i)
    {
        int x = (*BoundingBall::_array[i %BoundingBall::_MAXBALL])._x *20;
        int y = (*BoundingBall::_array[i %BoundingBall::_MAXBALL])._y *10;
        g.drawLine(0, y, x, y);
    }
}
//===========================================================
//===========================================================
void TestThread::actionPerformed(ActionEvent& e)
{
    BoundingBall* b = new BoundingBall();
    //BoundingBall b1;
    //b1.start();
}
//===========================================================
//===========================================================
void TestThread::run()
{
    while(1){
        repaint();
        sleep(100);
    }
}
//===========================================================
//===========================================================
void TestThread::teststart()
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
    TestThread test(GetCommandLineW());
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
