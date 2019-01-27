

//#include "util\LinkedList.h"
//#include "_lang.h"
//#include "awt\Label.h"
//#include "awt\TextField.h"
#include "awt\Frame.h"
#include "awt\FileDialog.h"
#include "io\File.h"
#include "io\FileOutputStream.h"
#include "io\FileInputStream.h"
#include "awt\Menu.h"


/*
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
*/

class MenuFile: public Menu
{
public:
    class MenuNew: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e){}
        };
    public:
        MenuNew(): MenuItem(String("&New"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuNew(){}
    };
    class MenuOpen: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e)
            {
                MenuOpen& m
                    = *static_cast<MenuOpen*>(e.getSource());
                MenuComponent* mc
                    = dynamic_cast<MenuComponent*>(&m.getParent());
                if(!mc){ return; }
                
                Frame* f
                    = static_cast<Frame*>(&mc->getParent());
                    //= dynamic_cast<Frame*>(&mc->getParent());
                //if(!f){ throw int(); }
                
                FileDialog fd(*f, L"Open File");
                fd.setVisible(true);
                //String filename
                //    = String(fd.getDirectory())
                //    +String(fd.getFile());
            }
        };
    public:
        MenuOpen(): MenuItem(String("&Open"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuOpen(){}
    };
    class MenuSave: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e){}
        };
    public:
        MenuSave(): MenuItem(String("&Save"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuSave(){}
    };
    class MenuSaveAs: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e)
            {
                MenuSaveAs& m
                    = *static_cast<MenuSaveAs*>(e.getSource());
                MenuComponent* mc
                    = dynamic_cast<MenuComponent*>(&m.getParent());
                if(!mc){ return; }
                
                Frame* f
                    = static_cast<Frame*>(&mc->getParent());
                    //= dynamic_cast<Frame*>(&mc->getParent());
                //if(!f){ throw int(); }
                
                FileDialog fd(*f, L"Save As", FileDialog::SAVE);
                fd.setVisible(true);
                //String filename
                //    = String(fd.getDirectory())
                //    +String(fd.getFile());
            }
        };
    public:
        MenuSaveAs(): MenuItem(String("Save &As..."))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuSaveAs(){}
    };
    class MenuExit: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e){}
        };
    public:
        MenuExit(): MenuItem(String("&Exit"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuExit(){}
    };
    MenuFile(): Menu(L"&File")
    {
        add(*new MenuNew());
        add(*new MenuOpen());
        addSeparator();
        add(*new MenuSave());
        add(*new MenuSaveAs());
        addSeparator();
        add(*new MenuExit());
    }
};
class MenuEdit: public Menu
{
public:
    class MenuCut: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e){}
        };
    public:
        MenuCut(): MenuItem(String("Cu&t"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuCut(){}
    };
    class MenuCopy: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e)
            {
                MenuCopy& m
                    = *static_cast<MenuCopy*>(e.getSource());
            }
        };
    public:
        MenuCopy(): MenuItem(String("&Copy"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuCopy(){}
    };
    class MenuPaste: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e){}
        };
    public:
        MenuPaste(): MenuItem(String("&Paste"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuPaste(){}
    };
    class MenuDelete: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e)
            {
                MenuDelete& m
                    = *static_cast<MenuDelete*>(e.getSource());
            }
        };
    public:
        MenuDelete(): MenuItem(String("&Delete"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuDelete(){}
    };
    MenuEdit(): Menu(L"&Edit")
    {
        addSeparator();
        add(*new MenuCut());
        add(*new MenuCopy());
        add(*new MenuPaste());
        add(*new MenuDelete());
        addSeparator();
    }
};
/*
class TestMenuBar: public MenuBar
{
private:
    MenuFile _menufile;
    
public:
    TestMenuBar()
    {
        add(_menufile);
    }
};
*/

class TestFrame: public Frame//, public Thread
{
private:
    int _numTTF;
    //TestTextField* _ttf;
    //Label _label;
    //FileDialog* _fd;
    //File* _file;
    //LinkedList<int> _list;
    //TestMenuBar _testmenubar;
    //MenuBar _menubar;
    //MenuFile _menufile;
    //Menu* _menufile;
    //MenuItem* _menufileopen;
    //MenuFileOpen mfo;
    
public:
    TestFrame(const String& str): _numTTF(4), Frame(str)//, _file(0)//, _fd(0)
    {
        /*
        _ttf = new TestTextField[_numTTF];
        for(int i=0; i< _numTTF; ++i)
        {
            _ttf[i].setLocation(2, 2 +20*i);
            add(_ttf[i]);
        }
        */
        //_label.setLocation(100, 2);
        //_label.setBackground(Color(0xFFFFFF));
        //add(_label);
        //_fd = NULL;
        MenuBar& mb = *new MenuBar();
        setMenuBar(mb);
        //_menufile = new Menu(L"File");
        //_menubar.add(*_menufile);
        
        //_menufileopen = new MenuItem(L"Open");
        //_menufileopen->addActionListener(mfo);
        //_menufile->add(*_menufileopen);
        
        //MenuFile* mf = new MenuFile();
        mb.add(*new MenuFile());
        mb.add(*new MenuEdit());
        
        
        
        //setMenuBar(_testmenubar);
        /*
        Menu menu(L"File");
        menu.add(MenuItem(L"New"));
        menu.add(MenuItem(L"Open"));
        menu.add(MenuItem(L"Save"));
        
        MenuBar menubar;
        setMenuBar(menubar);
        
        Menu history(L"History");
        history.add(MenuItem(L"1_"));
        history.add(MenuItem(L"2_"));
        history.add(MenuItem(L"3_"));
        
        menubar.add(menu);
        menu.add(history);
        //tmb = new TestMenuBar();
        
        //setMenuBar(TestMenuBar());
        
        //menubar.add(Menu(L"Edit"));
        //menubar.add(Menu(L"Find"));
        //setMenuBar(menubar);
        */
    }
    ~TestFrame()
    {
        //delete [] _ttf;
        //delete _fd;
        //delete _file;
    }
    void teststart()
    {
        setBounds(0, 250, 600, 300);
        setVisible(true);
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
debugDisplay.clear();
debugDisplay.setformat(DebugDisplay::HEX);
debugDisplay << debug.substring(0);
        /*
        if(source == static_cast<int>(&_ttf[0]))
        {
            FileDialog fd(*this, L"Load File");
            fd.setVisible(true);
            String filename = String(fd.getDirectory()) +String(fd.getFile());
            if(filename.length() != 0){
                _ttf[0].setText(filename);
            }
        }
        if(source == static_cast<int>(&_ttf[1])){
            //FileInputStream fis(File(_ttf[0].getText()));
            String filename = String(_ttf[0].getText());
            String text = String(_ttf[1].getText());
            if(filename.length() != 0){
                if(text.length() != 0){
                    FileOutputStream fos(filename, true);
                    int length = text.length();
                    char byte[length *2];
                    for(int i=0; i< length; ++i)
                    {
                        byte[i *2] = static_cast<char>(text[i] >>8);
                        byte[i *2 +1] = static_cast<char>(text[i]);
                    }
                    fos.write(byte, 0, length *2);
                }
                FileInputStream fis(filename);
                int i;
                char byte[2];
                while((i=fis.read(byte, 0, 2)) == 2)
                {
                    wchar_t wc = (byte[0] <<8) ^ (byte[1]);
                    //debugDisplay << String((wchar_t)wc);
                    debugDisplay << (int)wc << String(L"\n");
                }
                
            }
        }
        */
        /*
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
        /*
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
        */
    }
    
};
/*
void TestTextField::actionPerformed(ActionEvent& e)
{
    static_cast<TestFrame*>(&getParent())->getAction(e.getSource(), getText());
}
*/

int WINAPI wWinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPWSTR lpCmdLine,
                   int nCmdShow)
{
    wchar_t programname[MAX_PATH +1];
    GetModuleFileNameW(0, programname, MAX_PATH);
    TestFrame test(GetCommandLineW());
    test.teststart();
    //test.setVisible(true);
    //test.start();
    
    while(GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return msg.wParam;
}
