

#include "windows\awt\Frame.h"
#include "windows\lang\String.h"
#include "windows\awt\Label.h"
#include "windows\awt\Button.h"


//===========================================================
//===========================================================
class TestButton: public Frame, public ActionListener
{
private:
    const int NUM;
    Label* _display;
    Button** _command;
    
public:
    TestButton(const String& string =String(L"")): Frame(string), NUM(100)
    {
        _display = new Label();
        
        Color color(0xFF0000);
    setBackground(color);
        Container* container = new Container();
        container->add(*new Label(String("RESULT  ")));
        container->add(*_display);
        add(*container);
        //add(*new Label(String("RESULT  ")));
        container->setSize(200, 20);
    container->setBackground(color);
        
        _command = new Button* [NUM];
        for(int i=0; i< NUM; ++i){
            _command[i] = new Button(String(i));
            _command[i]->setSize(40, 40);
            _command[i]->addActionListener(*this);
            add(*_command[i]);
        }
    }
    ~TestButton()
    {
        delete _command;
    }
    
    void teststart()
    {
        setSize(200, 300);
        setVisible(true);
    }
    
    virtual void actionPerformed(ActionEvent& e)
    {
        Color color[30];
        color[0] = SystemColor::desktop;
        color[1] = SystemColor::activeCaption;
        color[2] = SystemColor::activeCaptionText;
        color[3] = SystemColor::activeCaptionBorder;
        color[4] = SystemColor::inactiveCaption;
        color[5] = SystemColor::inactiveCaptionText;
        color[6] = SystemColor::inactiveCaptionBorder;
        color[7] = SystemColor::window;
        color[8] = SystemColor::windowBorder;
        color[9] = SystemColor::windowText;
        color[10] = SystemColor::menu;
        color[11] = SystemColor::menuText;
        color[12] = SystemColor::text;
        color[13] = SystemColor::textText;
        color[14] = SystemColor::textHighlight;
        color[15] = SystemColor::textHighlightText;
        color[16] = SystemColor::textInactiveText;
        
        color[17] = Color::white;
        color[18] = Color::lightGray;
        color[19] = Color::gray;
        color[20] = Color::darkGray;
        color[21] = Color::black;
        color[22] = Color::red;
        color[23] = Color::pink;
        color[24] = Color::orange;
        color[25] = Color::yellow;
        color[26] = Color::green;
        color[27] = Color::magenta;
        color[28] = Color::cyan;
        color[29] = Color::blue;
        
        Button* b = static_cast<Button*>(e.getSource());
        int number = Integer::parseInt(b->getLabel());
        //Container& c = const_cast<Container&>(b->getParent());
        //c.setBackground(color[number %17]);
        this->setBackground(color[number %30]);
        
        //_display->setText(b->getLabel());
        //c.repaint();
        _display->setText(String(color[number %30].getRGB()));
        this->repaint();
        //_display->repaint();
        
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
    TestButton test(GetCommandLineW());
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



