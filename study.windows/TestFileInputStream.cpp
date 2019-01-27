

#include "util\LinkedList.h"
#include "_lang.h"
#include "awt\Label.h"
#include "awt\TextField.h"
#include "awt\Frame.h"
#include "awt\FileDialog.h"
#include "io\File.h"
#include "io\FileInputStream.h"



class TestFrame;
class TestTextField: public TextField, public ActionListener
{
private:
    
public:
    TestTextField(): TextField(30)
    {
        addActionListener(*this);
    }
    
    virtual void actionPerformed(ActionEvent& e);
    
    
};

class TestFrame: public Frame//, public Thread
{
private:
    int _numTTF;
    TestTextField* _ttf;
    //Label _label;
    //FileDialog* _fd;
    //File* _file;
    LinkedList<int> _list;
    
public:
    TestFrame(const String& str): _numTTF(4), Frame(str)//, _file(0)//, _fd(0)
    {
        setBounds(0, 250, 600, 300);
        setBackground(Color(0x000088));
        _ttf = new TestTextField[_numTTF];
        for(int i=0; i< _numTTF; ++i)
        {
            _ttf[i].setLocation(2, 2 +20*i);
            add(_ttf[i]);
        }
        //_label.setLocation(100, 2);
        //_label.setBackground(Color(0xFFFFFF));
        //add(_label);
        //_fd = NULL;
    }
    ~TestFrame()
    {
        delete [] _ttf;
        //delete _fd;
        //delete _file;
    }
    
    /*
    virtual void run()
    {
        while(1)
        {
            //_label.setText(_ttf[0].number() +_ttf[1].number());
            
            //repaint(false);
            
            //sleep(100);
        }
    }
    */
    
    void getAction(const int source, const String& text)
    {
        if(source == static_cast<int>(&_ttf[0]))
        {
            FileDialog fd(*this, L"Load File");
            fd.setVisible(true);
            String filename = String(fd.getDirectory()) +String(fd.getFile());
            if(filename.length() != 0){
                _ttf[0].setText(filename);
                File fl(filename);
                FileInputStream fis(fl);
                int size = fl.length();
                
                char byte[size+1];
                byte[size] = L'\0';
                fis.read(byte, 0, size);
                debugDisplay.clear();
                debugDisplay.setformat(DebugDisplay::HEX);
                debugDisplay << String(byte);
            }
            
            //debugDisplay.clear();
            //debugDisplay.setformat(DebugDisplay::HEX);
            //int i;
            //while((i=fis.read()) != -1)
            //{
            //    debugDisplay << (int)i << String(L"\n");
            //}
            
        }
        /*
        if(source == static_cast<int>(&_ttf[1])){
            //FileInputStream fis(File(_ttf[0].getText()));
            _ttf[1].setText(String((int)FileInputStream(File(_ttf[0].getText())).read()));
        }
        
        if(source == static_cast<int>(&_ttf[2]))
        {
            File f(_ttf[0].getText());
            _ttf[1].setText(String((int)f.length()) +String(L"  ") +String((int)f.lastModified().dwLowDateTime) +String(L"  ") +String((int)f.lastModified().dwHighDateTime));
            if(f.exists())
            {
                if(f.isDirectory())
                    _ttf[2].setText(L"is directory");
                else
                if(f.isFile())
                    _ttf[2].setText(L"is file");
                else
                    _ttf[2].setText(L"error");
            }
            else
            {
                _ttf[2].setText(L"not exist");
            }
            if(f.isHidden())
                _ttf[2].setText(_ttf[2].getText() +L"  and is hidden");
            else
                _ttf[2].setText(_ttf[2].getText() +L"  and is not hidden");
            
        }
        if(source == static_cast<int>(&_ttf[3])){
            File f(_ttf[0].getText());
            switch(Integer::parseInt(_ttf[3].getText()))
            {
                case 1:
                    if(bool b = f.delete_()){
                            _ttf[3].setText(String(L"deleted  ")
                            +String(b));
                    }else{
                        _ttf[3].setText(String(b));
                    }
                    break;
                case 2:
                    if(bool b = f.createNewFile()){
                        _ttf[3].setText(
                            String(L"file created  ")
                            +String(b));
                    }else{
                        _ttf[3].setText(String(b));
                    }
                    break;
                case 3:
                    if(bool b = f.mkdir()){
                        _ttf[3].setText(
                            String(L"directory created  ")
                            +String(b));
                    }else{
                        _ttf[3].setText(String(b));
                    }
                    break;
                default:
                    _ttf[3].setText(String(L"a"));
                    break;
            }
        }
        */
        //if(source == static_cast<int>(&_ttf[4]))
        //    { _ttf[4].setText(String(_file->delete_())); }
        //if(source == static_cast<int>(&_ttf[5])){}
        
        repaint();
        
        //debugDisplay << String(L"\n");
        //debugDisplay.clear();
        try{
            debugDisplay << String(L"First  ") + String(static_cast<int>(&_list.getFirst())) + L"\n";
            debugDisplay << String(L"Last   ") + String(static_cast<int>(&_list.getLast())) + L"\n";
        }catch(...){}
        int listArray[100];
        _list.toArray(listArray);
        for(int i=0; i< _list.size(); ++i)
        {
            debugDisplay << String(i) + L"  ";
            debugDisplay << String(static_cast<int>(&_list[i])) + L"  ";
            debugDisplay << String(static_cast<int>(_list[i])) + L"\n";
        }
        
    }
    
};

void TestTextField::actionPerformed(ActionEvent& e)
{
    static_cast<TestFrame*>(&getParent())->getAction(e.getSource(), getText());
}

int WINAPI wWinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPWSTR lpCmdLine,
                   int nCmdShow)
{
    wchar_t programname[MAX_PATH +1];
    GetModuleFileNameW(0, programname, MAX_PATH);
    TestFrame test(programname);
    test.setVisible(true);
    //test.start();
    
    while(GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return msg.wParam;
}
