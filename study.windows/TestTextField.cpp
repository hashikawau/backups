

#include "awt\Frame.h"
#include "windows\lang\String.h"
#include "windows\awt\Label.h"
#include "windows\awt\Button.h"
#include "windows\awt\TextField.h"
#include "windows\_lang.h"


class TestTextComponentn: public Frame, public ActionListener
{
private:
    static const int NUM;
    Label* _display;
    Button** _command;
    TextField* _freeCommand;
    
public:
    TestTextComponentn(const String& string =String(L"")): Frame(string)
    {
        _display = new Label();
        
        Container* container = new Container();
        container->add(*new Label(String("RESULT  ")));
        container->add(*_display);
        add(*container);
        container->setSize(200, 20);
        
        _command = new Button* [NUM];
        for(int i=0; i< NUM; ++i){
            _command[i] = new Button(String(i));
            _command[i]->addActionListener(*this);
            add(*_command[i]);
        }
        
        _freeCommand = new TextField(5);
        _freeCommand->addActionListener(*this);
        //_freeCommand->setSize(150, 40);
        //_freeCommand->setBackground(Color(0xAA));
        add(*_freeCommand);
        //_freeCommand->setText(String(""));
        _freeCommand->setText(String("abc"));
    }
    ~TestTextComponentn()
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
        Component* source = static_cast<Component*>(e.getSource());
        if(Button* source2 = dynamic_cast<Button*>(source)){
            _display->setText(source2->getLabel());
            _display->repaint();
        }else
        if(TextField* source2 = dynamic_cast<TextField*>(source)){
            //source2
            _display->setText(
                String(Double::parseDouble(source2->getText()))
            );//source2->getLabel());
            _display->repaint();
        }
        //debugDisplay << String(Double::parseDouble(getText())) + L"\n";
    }
};
const int TestTextComponentn::NUM =10;


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow)
{
    //wchar_t programname[MAX_PATH +1];
    //GetModuleFileNameW(0, programname, MAX_PATH);
    //TestButton test(programname);
    TestTextComponentn test(GetCommandLineW());
    test.teststart();
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}
