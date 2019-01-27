

#include "awt\Frame.h"
#include "awt\ScrollBar.h"


//===========================================================
//===========================================================
class Test:
    public Frame
{
    class Listener:
        public AdjustmentListener
    {
    private:
        int _indexrgb;
    public:
        virtual void adjustmentValueChanged(AdjustmentEvent& e);
    };
friend class Listener;
    static Listener* _listener;

private:
    int _width;
    int _height;
    int _numrow;
    int _numcol;
    int _bkcolor;
    String _string;
    int _count;
    Scrollbar** _rgb;
    
public:
    Test(int count =0);
    ~Test();
    virtual void paint(Graphics& g);
    void teststart();
};
static Test::Listener* Test::_listener = new Test::Listener();
//===========================================================
//===========================================================
void Test::Listener::adjustmentValueChanged(AdjustmentEvent& e)
{
    Scrollbar& sb = *static_cast<Scrollbar*>(e.getSource());
    Test& test = *const_cast<Test*>(&sb.getParent());
    if(test._rgb){
        int background = 0
            | test._rgb[0]->getValue()
            | test._rgb[1]->getValue() <<8
            | test._rgb[2]->getValue() <<16;
        test.setBackground(Color(background));
        test.repaint();
    }
}
//===========================================================
//===========================================================
Test::Test(int count):
    _width(80),
    _height(20),
    _numrow(10),
    _numcol(5),
    _bkcolor(0x00FFFFFF),
    _string(static_cast<int>(this)),
    _count(count),
    _rgb(0)
{}
Test::~Test()
{
    delete [] _rgb;
}
//===========================================================
//===========================================================
void Test::paint(Graphics& g)
{
    Frame::paint(g);
}
void Test::teststart()
{
    _rgb = new Scrollbar* [3];
    Listener* l = new Listener();
    for(int i=0; i< 3; ++i)
    {
        _rgb[i] = new Scrollbar(
            Scrollbar::HORIZONTAL,
            0, 10, 0, 265);
        _rgb[i]->addAdjustmentListener(*l);
        add(*_rgb[i]);
    }
    
    setBounds(30, 30, 300, 300);
    setVisible(true);
}
//===========================================================
//===========================================================
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR lpCmdLine,
                   int nCmdShow)
{
    wchar_t programname[MAX_PATH +1];
    GetModuleFileNameW(0, programname, MAX_PATH);
    Test test;
    test.teststart();
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}
