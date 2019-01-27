

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
class ScrollMessage:
    public Frame,
    public Thread
{
private:
    PointerObject<Image> _imageWork;
    const Graphics* _graphicsWork;
    
    int _markX;
    int _markY;
    
public:
    ScrollMessage(const String& str);
    virtual ~ScrollMessage();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
    virtual void run();
};
//===========================================================
//===========================================================
ScrollMessage::ScrollMessage(const String& str): Frame(str)
{
    setBounds(0, 250, 300, 350);
    setBackground(Color(SystemColor::desktop));
    setVisible(true);
    
    _imageWork = createImage(getWidth(), getHeight());
    _graphicsWork = &(_imageWork->getGraphics());
    
    _graphicsWork->setColor(Color(0x000000));
    _graphicsWork->fillRect(0, 0, getWidth(), getHeight());
    _graphicsWork->setColor(Color(0xFFFFFF));
    _graphicsWork->drawString(String("abcdef"), 2, 2);
    _graphicsWork->drawString(String("ghijklmn"), 2, 20);
    _graphicsWork->drawString(String("opqstuvwxyz"), 2, 40);
    
    _markX =0;
    _markY =0;
    
    repaint();
    
    start();
}
ScrollMessage::~ScrollMessage()
{
    delete _graphicsWork;
}
//===========================================================
//===========================================================
void ScrollMessage::update(Graphics& g)
{
    paint(g);
}
void ScrollMessage::paint(Graphics& g)
{
    if(_imageWork){
        g.drawImage(*_imageWork, _markX, getHeight() - _markY, *this);
    }
}
//===========================================================
//===========================================================
void ScrollMessage::run()
{
    while(1){
        
        _markX += 0;
        _markY += 2;
        
        _markX %= getWidth();
        _markY %= getHeight();
        
        repaint();
        Thread::sleep(50);
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
    ScrollMessage* scrollmessage = new ScrollMessage(GetCommandLineW());
    
    
    while(GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return msg.wParam;
}
//===========================================================
//===========================================================


