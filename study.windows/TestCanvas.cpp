

#include "windows\awt\Frame.h"
#include "windows\lang\String.h"
#include "windows\awt\Label.h"
#include "windows\awt\Button.h"
#include "windows\awt\Canvas.h"


//===========================================================
//===========================================================
class DerivedCanvas:
    public Canvas,
    public MouseListener
{
private:
    int _startx;
    int _starty;
    int _endx;
    int _endy;
    int _length;
    
public:
    DerivedCanvas();
    virtual ~DerivedCanvas();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
    
    virtual void mouseClicked(MouseEvent& e);
    virtual void mouseEntered(MouseEvent& e);
    virtual void mouseExited(MouseEvent& e);
    virtual void mousePressed(MouseEvent& e);
    virtual void mouseReleased(MouseEvent& e);
};
//===========================================================
//===========================================================
DerivedCanvas::DerivedCanvas()
{
    _startx =_starty =_endx =_endy =1;
    _length = 10;
}
DerivedCanvas::~DerivedCanvas(){}
//===========================================================
//===========================================================
void DerivedCanvas::update(Graphics& g)
{
    Canvas::update(g);
    //paint(g);
}
void DerivedCanvas::paint(Graphics& g)
{
    g.setColor(Color(0x00));
    _length = 1;
    int grad = 10;
    for(int i=0; i< 1000; ++i){
        
        g.setColor(Color(0x00));
        //g.fillRect(_length *(grad *i), _length *i, _length, _length);
        g.drawPixel(_length *(grad *i), _length *i);
        
        for(int j=1; j< grad-1; ++j){
            g.setColor(Color(0x00));
            //g.fillRect(_length *(grad *i +j), _length *i, _length, _length);
            g.drawPixel(_length *(grad *i +j), _length *i);
        }
        
        g.setColor(Color(0x00));
        //g.fillRect(_length *(grad *i +grad -1), _length *i, _length, _length);
        g.drawPixel(_length *(grad *i +grad -1), _length *i);
        //g.fillRect(_length *(grad *(i +1) -1), _length *(i+1), _length, _length);
    }
    //g.drawPixel(_startx, _starty);
    //g.drawLine(_startx, _starty, _endx, _endy);
    g.drawLine(0, 100, 1000*grad, 1000 +100);
}
//===========================================================
//===========================================================
void DerivedCanvas::mouseClicked(MouseEvent& e)
{
    Canvas::update(getGraphics());
}
void DerivedCanvas::mouseEntered(MouseEvent& e){}
void DerivedCanvas::mouseExited(MouseEvent& e){}
void DerivedCanvas::mousePressed(MouseEvent& e)
{
    _startx = _endx = e.getX();
    _starty = _endy = e.getY();
    repaint();
    
}
void DerivedCanvas::mouseReleased(MouseEvent& e)
{
    _endx = e.getX();
    _endy = e.getY();
    repaint();
}
//===========================================================
//===========================================================
class TestCanvas: public Frame, public ActionListener
{
private:
    const int NUM;
    Label* _display;
    Button** _command;
    
public:
    TestCanvas(const String& string =String(L"")): Frame(string), NUM(1)
    {
        DerivedCanvas *dc = new DerivedCanvas();
        dc->addMouseListener(*dc);
        dc->setSize(400, 400);
        //dc->setVisible(true);
        add(*dc);
        
        
        //_display = new Label();
        
        Color color(0xFF0000);
    setBackground(color);
        //Container* container = new Container();
        //container->add(*new Label(String("RESULT  ")));
        //container->add(*_display);
        //add(*container);
        //add(*new Label(String("RESULT  ")));
        //container->setSize(200, 20);
    //container->setBackground(color);
        
        /*
        _command = new Button* [NUM];
        for(int i=0; i< NUM; ++i){
            _command[i] = new Button(String(i));
            _command[i]->setSize(40, 40);
            _command[i]->addActionListener(*this);
            add(*_command[i]);
        }
        */
    }
    ~TestCanvas()
    {
        //delete _command;
    }
    
    void teststart()
    {
        setSize(500, 450);
        setVisible(true);
        //repaint();
    }
    
    virtual void actionPerformed(ActionEvent& e)
    {
        Button* b = static_cast<Button*>(e.getSource());
        _display->setText(b->getLabel());
        _display->repaint();
        
        //cout << "Button  " << b->getX() << " , " << b->getY() << endl;
    }
};
//===========================================================
//===========================================================
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow)
{
    //wchar_t programname[MAX_PATH +1];
    //GetModuleFileNameW(0, programname, MAX_PATH);
    //TestButton test(programname);
    TestCanvas test(GetCommandLineW());
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



