

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


//===========================================================
//===========================================================
class DigitalClock:
    public Frame,
    public Thread
{
private:
    PointerObject<Image> _imageWork;
    const Graphics* _graphicsWork;
    int _count;
    
public:
    DigitalClock(const String& str);
    virtual ~DigitalClock();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
    virtual void run();
};
//===========================================================
//===========================================================
DigitalClock::DigitalClock(const String& str): Frame(str), _count(0)
{
    setBounds(0, 250, 300, 100);
    setBackground(Color(SystemColor::desktop));
    setVisible(true);
    
    _imageWork = createImage(getWidth(), getHeight());
    _graphicsWork = &(_imageWork->getGraphics());
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
        g.drawImage(*_imageWork, 0, 0, *this);
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
        
        _graphicsWork->fillRect(0, 0, getWidth(), getHeight());
        _graphicsWork->drawString(time.substring(0), 5, 5);
        repaint();
        
        //_count += 1;
        Thread::sleep(100);
    }
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
    DigitalClock digitalclock(GetCommandLineW());
    digitalclock.start();
    
    
    while(GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return msg.wParam;
}
//===========================================================
//===========================================================


