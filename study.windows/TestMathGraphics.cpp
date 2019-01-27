

#include "awt\Frame.h"
#include "windows\lang\String.h"
#include "windows\awt\Label.h"
#include "windows\awt\Button.h"
#include "windows\awt\TextField.h"
#include "windows\awt\TextArea.h"
#include "windows\awt\ScrollPane.h"
#include "windows\_lang.h"
#include "windows\cpp\MathGraphics.h"

//===========================================================
//===========================================================
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
                MenuOpen* m
                    = static_cast<MenuOpen*>(e.getSource());
                MenuComponent* mc
                    = dynamic_cast<MenuComponent*>(&m->getParent());
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
//===========================================================
//===========================================================
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
                /*
                MenuCopy& m
                    = *static_cast<MenuCopy*>(e.getSource());
                MenuComponent& mc
                    = *dynamic_cast<MenuComponent*>(&m.getParent());
                if(!&mc){ return; }
                
                Frame& f
                    = *static_cast<Frame*>(&mc.getParent());
                
                f.getToolkit()->getSystemClipboard()
                    ->setContents(StringSelection(debug.substring(0)));
                */
                MenuCopy& m
                    = *static_cast<MenuCopy*>(e.getSource());
                MenuComponent& mc
                    = *dynamic_cast<MenuComponent*>(&m.getParent());
                if(!&mc){ return; }
                
                Frame& f
                    = *static_cast<Frame*>(&mc.getParent());
                
                f.getToolkit()->getSystemClipboard()
                    ->setContents(StringSelection(
                        debugDisplay->getText()));
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
            virtual void actionPerformed(ActionEvent& e)
            {
                MenuPaste& m
                    = *static_cast<MenuPaste*>(e.getSource());
                MenuComponent& mc
                    = *dynamic_cast<MenuComponent*>(&m.getParent());
                if(!&mc){ return; }
                
                Frame& f
                    = *static_cast<Frame*>(&mc.getParent());
                
                wchar_t** str
                    = f.getToolkit()->getSystemClipboard()
                    ->getData(DataFlavor::stringFlavor).get();
                debug +=
                    String(str[0]);
            }
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
//===========================================================
//===========================================================
class TestTextComponent:
    public Frame,
    public ActionListener,
    public TextListener
{
private:
    static const int NUM;
    Label* _display;
    Button** _command;
    TextField* _freeCommand;
    TextArea* _log;
    MathGraphics* _graph;
    
public:
    TestTextComponent(const String& string =String(L"")): Frame(string)
    {
        MenuBar& mb = *new MenuBar();
        setMenuBar(mb);
        
        mb.add(*new MenuFile());
        mb.add(*new MenuEdit());
        
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
        _freeCommand->addTextListener(*this);
        //_freeCommand->setSize(150, 40);
        //_freeCommand->setBackground(Color(0xAA));
        add(*_freeCommand);
        //_freeCommand->setText(String(""));
        //_freeCommand->setText(String("abc"));
        
        _log = new TextArea(20, 50);
        _log->addTextListener(*this);
        ScrollPane* sp = new ScrollPane();
        sp->setSize(200, 200);
        sp->add(*_log);
        add(*sp);
    }
    ~TestTextComponent()
    {
        delete _command;
    }
    
    void teststart()
    {
        setSize(250, 350);
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
            _display->setText(
                String(Double::parseDouble(source2->getText()))
            );
            _display->repaint();
            
            Frame* f
                = static_cast<Frame*>(&source2->getParent());
            /*
            f->getToolkit()->getSystemClipboard()
                ->setContents(StringSelection(
                    debugDisplay->getText()));
            */
            wchar_t** str
                = f->getToolkit()->getSystemClipboard()
                ->getData(DataFlavor::stringFlavor).get();
            
            MemoryViewer<long double> md(Double::parseDouble(source2->getText()));
            _log->replaceRange(
                md.get(), 0, 0x7FFFFFFF
            );
            _log->repaint();
        }
        //debugDisplay << String(Double::parseDouble(getText())) + L"\n";
    }
    
    virtual void textValueChanged(TextEvent& e)
    {
        Component* source = static_cast<Component*>(e.getSource());
//debug += String((int)e.getSource()) + String("\n");
    }
};
const int TestTextComponent::NUM =10;


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow)
{
    TestTextComponent test(GetCommandLineW());
    test.teststart();
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}
