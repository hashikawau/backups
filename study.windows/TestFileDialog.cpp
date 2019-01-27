

#include "_util.h"
#include "_lang.h"
#include "awt\Label.h"
#include "awt\TextField.h"
#include "awt\Frame.h"
#include "awt\FileDialog.h"

class TestFrame;
class TestTextField: public TextField, public ActionListener
{
private:
    int _number;
    
public:
    TestTextField(): TextField(5)
    {
        _number = 0;
        setBackground(Color(0xFFFF));
        addActionListener(*this);
    }
    
    virtual void actionPerformed(ActionEvent& e);
    
    const int number() const
    {
        return _number;
    }
    
};

class TestFrame: public Frame, public Thread
{
private:
    TestTextField _ttf[2];
    Label _label;
    FileDialog* _fd;
    LinkedList<int> _list;
    
public:
    TestFrame(const String& str): Frame(str), _fd(NULL)
    {
        setBounds(0, 250, 600, 300);
        setBackground(Color(0x888888));
        for(int i=0; i< 2; ++i)
        {
            _ttf[i].setLocation(2, 2 +20*i);
            add(_ttf[i]);
        }
        _label.setLocation(100, 2);
        _label.setBackground(Color(0xFFFFFF));
        add(_label);
        
        
    }
    
    virtual void run()
    {
        while(1)
        {
            _label.setText(_ttf[0].number() +_ttf[1].number());
            
            repaint(false);
            
            sleep(100);
        }
    }
    
    void fileLoad()
    {
        //FileDialog _fd2(*this, L"Open File");
        delete _fd;
        _fd = new FileDialog(*this, L"Open File");
        
debugDisplay << String((int)System::currentTimeMillis()) + L"   " + _fd->getDirectory() + L"\n";
debugDisplay << _fd->getFile() + L"\n";
    }
    
};

void TestTextField::actionPerformed(ActionEvent& e)
{
    _number = Integer::parseInt(getText());
debugDisplay << String(_number) + L"\n";
static_cast<TestFrame*>(&getParent())->fileLoad();
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR lpCmdLine,
                   int nCmdShow)
{
    wchar_t programname[MAX_PATH +1];
    GetModuleFileNameW(0, programname, MAX_PATH);
    TestFrame test(programname);
    test.setVisible(true);
    test.start();
    
    while(GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return msg.wParam;
}
