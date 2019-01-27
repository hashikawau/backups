

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
class DigitalClock:
    public Frame,
    public Thread,
    public MouseMotionListener
{
private:
    PointerObject<Image> _imageWork;
    const Graphics* _graphicsWork;
    
    int _centerX;
    int _centerY;
    int _radius;
    
    int _markX;
    int _markY;
    int _distanceX;
    int _distanceY;
    
public:
    DigitalClock(const String& str);
    virtual ~DigitalClock();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
    virtual void run();
    virtual void mouseMoved(MouseEvent& e);
    virtual void mouseDragged(MouseEvent& e);
};
//===========================================================
//===========================================================
DigitalClock::DigitalClock(const String& str): Frame(str)
{
    setBounds(0, 250, 300, 350);
    setBackground(Color(SystemColor::desktop));
    setVisible(true);
    
    _centerX = 300 /2;
    _centerY = 300 /2;
    _radius = 0.8 *150;
    _imageWork = createImage(getWidth(), getHeight());
    _graphicsWork = &(_imageWork->getGraphics());
    
    _markX =0;
    _markY =0;
    _distanceX =0;
    _distanceY =0;
    addMouseMotionListener(*this);
    
    repaint();
    
    start();
}
DigitalClock::~DigitalClock()
{
    delete _graphicsWork;
}
//===========================================================
//===========================================================
void DigitalClock::update(Graphics& g)
{
    paint(g);
}
void DigitalClock::paint(Graphics& g)
{
    if(_imageWork){
        g.drawImage(*_imageWork, _distanceX, _distanceY, *this);
    }
}
//===========================================================
//===========================================================
void DigitalClock::run()
{
    while(1){
        
        PointerObject<Calendar> calendar = Calendar::getInstance();
        int hour = calendar->get(Calendar::HOUR_OF_DAY);
        int hour1 = hour /10;
        int hour2 = hour %10;
        int minute = calendar->get(Calendar::MINUTE);
        int minute1 = minute /10;
        int minute2 = minute %10;
        int second = calendar->get(Calendar::SECOND);
        int second1 = second /10;
        int second2 = second %10;
        int millisecond = calendar->get(Calendar::MILLISECOND);
        int millisecond1 = millisecond /100;
        int millisecond2 = millisecond %100 /10;
        int millisecond3 = millisecond %10;
        
        StringBuffer time(10);
        time += String(hour1);
        time += String(hour2);
        time += String(" : ");
        time += String(minute1);
        time += String(minute2);
        time += String(" : ");
        time += String(second1);
        time += String(second2);
        time += String(" : ");
        time += String(millisecond1);
        //time += String(millisecond2);
        //time += String(millisecond3);
        
        _graphicsWork->setColor(Color(0x00FFFF));
        _graphicsWork->fillRect(0, 0, getWidth(), getHeight());
        
        _graphicsWork->setColor(Color(0xFF00FF));
        _graphicsWork->drawString(time.substring(0), 100, 300);
        
        double radian;
        
        for(int i=0; i< 360; i+= 6){
            
            radian = i *Math::PI /180;
            
            int x1 = _centerX + static_cast<int>(_radius *Math::sin(radian));
            int y1 = _centerY - static_cast<int>(_radius *Math::cos(radian));
            
            int radius2;
            if(i %30 == 0){
                radius2 = _radius - 8;
            }else{
                radius2 = _radius - 2;
            }
            
            int x2 = _centerX + static_cast<int>(radius2 *Math::sin(radian));
            int y2 = _centerY - static_cast<int>(radius2 *Math::cos(radian));
            
            _graphicsWork->drawLine(x1, y1, x2, y2);
        }
        
        double sin;
        double cos;
        int arrayX[3];
        int arrayY[3];
        
        
        radian = (hour %12 *30 + minute *0.5) *Math::PI /180;
        sin = Math::sin(radian);
        cos = Math::cos(radian);
        arrayX[0] = _centerX + static_cast<int>(0.6 *_radius *sin);
        arrayY[0] = _centerY - static_cast<int>(0.6 *_radius *cos);
        arrayX[1] = _centerX + static_cast<int>(0.05 *_radius *cos);
        arrayY[1] = _centerY + static_cast<int>(0.05 *_radius *sin);
        arrayX[2] = _centerX - static_cast<int>(0.05 *_radius *cos);
        arrayY[2] = _centerY - static_cast<int>(0.05 *_radius *sin);
        _graphicsWork->setColor(Color(0xFF0000));
        _graphicsWork->drawPolygon(arrayX, arrayY, 3);
        _graphicsWork->fillOval(
            arrayX[0] - 0.025 *_radius,
            arrayY[0] - 0.025 *_radius,
            0.05 *_radius,
            0.05 *_radius);
        
        radian = minute *6 *Math::PI /180;
        //radian = (minute *6 + second *0.1) *Math::PI /180;
        sin = Math::sin(radian);
        cos = Math::cos(radian);
        arrayX[0] = _centerX + static_cast<int>(0.8 *_radius *sin);
        arrayY[0] = _centerY - static_cast<int>(0.8 *_radius *cos);
        arrayX[1] = _centerX + static_cast<int>(0.05 *_radius *cos);
        arrayY[1] = _centerY + static_cast<int>(0.05 *_radius *sin);
        arrayX[2] = _centerX - static_cast<int>(0.05 *_radius *cos);
        arrayY[2] = _centerY - static_cast<int>(0.05 *_radius *sin);
        _graphicsWork->setColor(Color(0xFF0000));
        _graphicsWork->fillPolygon(arrayX, arrayY, 3);
        _graphicsWork->fillOval(
            arrayX[0] - 0.025 *_radius,
            arrayY[0] - 0.025 *_radius,
            0.05 *_radius,
            0.05 *_radius);
        
        
        
        radian = second *6 *Math::PI /180;
        //radian = (second *6 + millisecond *0.006) *Math::PI /180;
        int sx = _centerX + static_cast<int>(0.9 *_radius *Math::sin(radian));
        int sy = _centerY - static_cast<int>(0.9 *_radius *Math::cos(radian));
        _graphicsWork->setColor(Color(0x00FF00));
        _graphicsWork->drawLine(_centerX, _centerY, sx, sy);
        _graphicsWork->fillOval(
            _centerX - 0.05 *_radius,
            _centerY - 0.05 *_radius,
            0.1 *_radius,
            0.1 *_radius);
        
        repaint();
        Thread::sleep(100);
    }
}
//===========================================================
//===========================================================
void DigitalClock::mouseMoved(MouseEvent& e)
{
    _markX = e.getX() -_distanceX;
    _markY = e.getY() -_distanceY;
}
void DigitalClock::mouseDragged(MouseEvent& e)
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
    DigitalClock* digitalclock = new DigitalClock(GetCommandLineW());
    
    
    while(GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return msg.wParam;
}
//===========================================================
//===========================================================


