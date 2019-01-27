

//#include "util\LinkedList.h"
//#include "_lang.h"
//#include "awt\TextField.h"
#include "awt\Frame.h"
#include "awt\FileDialog.h"
#include "io\File.h"
#include "io\FileOutputStream.h"
#include "io\FileInputStream.h"
#include "awt\datatransfer\Clipboard.h"

#include "awt\Button.h"
#include "awt\Label.h"
#include "awt\ScrollPane.h"

#include "util\Calendar.h"
#include "lang\Math.h"


//===========================================================
//===========================================================
class TestPolygon:
    public Frame,
    public Thread,
    public MouseMotionListener
{
private:
    PointerObject<Image> _imageWork;
    Graphics* _graphicsWork;
    
    PointerObject<awt::Polygon> _polygon;
    int _color;
    
    int _centerX;
    int _centerY;
    int _radius;
    
    int _markX;
    int _markY;
    int _distanceX;
    int _distanceY;
    
public:
    TestPolygon(const String& str);
    virtual ~TestPolygon();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
    virtual void run();
    virtual void mouseMoved(MouseEvent& e);
    virtual void mouseDragged(MouseEvent& e);
};
//===========================================================
//===========================================================
TestPolygon::TestPolygon(const String& str): Frame(str)
{
    setBounds(0, 250, 300, 350);
    setBackground(Color(SystemColor::desktop));
    setVisible(true);
    
    _centerX = 300 /2;
    _centerY = 300 /2;
    _radius = 0.8 *150;
    _imageWork = createImage(getWidth(), getHeight());
    _graphicsWork = &(_imageWork->getGraphics());
    _graphicsWork->setColor(Color(0x00FFFFFF));
    _graphicsWork->fillRect(0, 0, 300, 350);
    
    _polygon = new awt::Polygon();
    _polygon->addPoint(0, 100);
    _polygon->addPoint(25, 20);
    //_polygon->addPoint(50, 40);
    _polygon->addPoint(75, 20);
    _polygon->addPoint(100, 100);
    _polygon->addPoint(75, 100);
    _polygon->addPoint(50, 60);
    _polygon->addPoint(25, 100);
    _polygon->addPoint(0, 100);
    _polygon->addPoint(0, 40);
    _polygon->addPoint(100, 40);
    _polygon->addPoint(100, 100);
    _color = 0x0FFF0000;
    //_graphicsWork->fillPolygon(*_polygon);
    
    _color = 0x0000000F;
    _graphicsWork->setColor(Color(_color));
    _graphicsWork->drawString(String(_color), 20, 20);
    _color = 0x000000FF;
    _graphicsWork->setColor(Color(_color));
    _graphicsWork->drawString(String(_color), 20, 40);
    _color = 0x00000FFF;
    _graphicsWork->setColor(Color(_color));
    _graphicsWork->drawString(String(_color), 20, 60);
    _color <<= 8;
    _graphicsWork->setColor(Color(_color));
    _graphicsWork->drawString(String(_color), 20, 80);
    _color <<= 8;
    _graphicsWork->setColor(Color(_color));
    _graphicsWork->drawString(String(_color), 20, 100);
    _color <<= 8;
    _graphicsWork->setColor(Color(_color));
    _graphicsWork->drawString(String(_color), 20, 120);
    _color <<= 8;
    _graphicsWork->setColor(Color(_color));
    _graphicsWork->drawString(String(_color), 20, 140);
    _color <<= 8;
    _graphicsWork->setColor(Color(_color));
    _graphicsWork->drawString(String(_color), 20, 160);
    
    _markX =0;
    _markY =0;
    _distanceX =0;
    _distanceY =0;
    addMouseMotionListener(*this);
    
    repaint();
    
    start();
}
TestPolygon::~TestPolygon()
{
    delete _graphicsWork;
}
//===========================================================
//===========================================================
void TestPolygon::update(Graphics& g)
{
    paint(g);
}
void TestPolygon::paint(Graphics& g)
{
    if(_imageWork){
        g.drawImage(*_imageWork, _distanceX, _distanceY, *this);
    }
}
//===========================================================
//===========================================================
void TestPolygon::run()
{
    while(1){
        
        _color >>= 1;
        _color &= 0x00FFFFFF;
        if(_color < 0x0000FF){
            _color = 0xFFFF0000;
        }
        _graphicsWork->setColor(Color(!_color));
        _graphicsWork->fillRect(0, 0, 500, 500);
        _graphicsWork->setColor(Color(_color));
        _graphicsWork->fillPolygon(*_polygon);
        _graphicsWork->drawString(String(_color), 20, 100);
        
        
        repaint();
        Thread::sleep(500);
    }
}
//===========================================================
//===========================================================
void TestPolygon::mouseMoved(MouseEvent& e)
{
    _markX = e.getX() -_distanceX;
    _markY = e.getY() -_distanceY;
}
void TestPolygon::mouseDragged(MouseEvent& e)
{
    _distanceX = e.getX() -_markX;
    _distanceY = e.getY() -_markY;
    repaint();
}
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
    TestPolygon* test = new TestPolygon(GetCommandLineW());
    
    
    while(GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return msg.wParam;
}
//===========================================================
//===========================================================


