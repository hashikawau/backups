

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
            virtual void actionPerformed(ActionEvent& e);
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
class TestFrame: public Frame
{
    class Listener:
        public KeyListener
    {
    public:
        virtual void keyPressed(KeyEvent& e){}
        virtual void keyReleased(KeyEvent& e){}
        virtual void keyTyped(KeyEvent& e)
        {
            //debug += String(e.getKeyChar());
        }
    };
public:
    PointerObject<Image> _image;
    PointerObject<Image> _imageWork;
    const Graphics* _graphicsWork;
    
public:
    TestFrame(const String& str): Frame(str)
    {
        MenuBar& mb = *new MenuBar();
        setMenuBar(mb);
        
        mb.add(*new MenuFile());
        mb.add(*new MenuEdit());
        
        ScrollPane& sp = *new ScrollPane();
        
        //sp.add(*new Label(String("abc             \n\n\n\n\n\n\ndfgh\n\n\n\n\n\n\n\n\n\n\n\ndhjkl\n\n\n\n\n\n\n\n\n\n\n")));
        //sp.add(*new Label(String("abc             \n\n\n\n\n\n\ndfgh\n\n\n\n\n\n\n\n\n\n\n\ndhjkl\n\n\n\n\n\n\n\n\n\n\n")));
        sp.setSize(200, 100);
        add(sp);
        
        
        ScrollPane& sp2 = *new ScrollPane(*new Label(String("lkjhgfddwgd\n\n\n\n\n\n\ndfgh\n\n\n\n\n\n\n\n\n\n\n\ndhjkl\n\n\n\n\n\n\n\n\n\n\n")));
        sp2.add(*new Label(String("abc             \n\n\n\n\n\n\ndfgh\n\n\n\n\n\n\n\n\n\n\n\ndhjkl\n\n\n\n\n\n\n\n\n\n\n")));
        Label* label = new Label(String("ijk"));
        label->setSize(200, 300);
        sp2.add(*label);
        sp2.setSize(100, 150);
        add(sp2);
        
        //setLayout(*new FlowLayout(FlowLayout::LEFT));
        //Label* l = new Label(String("abc"));
        add(*new Label(String("ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
        add(*new Label(String("defgh")));
        add(*new Label(String("ijklmnop")));
        add(*new Label(String("qrstuvwxyz")));
        
        addKeyListener(*new Listener());
        
        
        add(*new Button(String("Button1")));
        
        
    }
    virtual ~TestFrame(){}
    void teststart()
    {
        setBounds(0, 250, 600, 300);
        setBackground(Color(SystemColor::desktop));
        setVisible(true);
        
        _imageWork = createImage(getWidth(), getHeight());
        _graphicsWork = &(_imageWork->getGraphics());
        
        Frame::paint(*const_cast<Graphics*>(_graphicsWork));
        _graphicsWork->translate(10, 10);
        _graphicsWork->drawOval(0, 0, getWidth(), getHeight());
    }
    virtual void update(Graphics& g)
    {
        paint(g);
    }
    virtual void paint(Graphics& g)
    {
        /*
        Frame::paint(g);
        g.translate(10, 10);
        g.drawOval(0, 0, getWidth(), getHeight());
        */
        
        
        if(_image){
            g.drawImage(*_image, 0, 0, *this);
        }else
        if(_imageWork){
            g.drawImage(*_imageWork, 0, 0, *this);
        }
    }
    
};



void MenuFile::MenuOpen::Listener::actionPerformed(ActionEvent& e)
{
    MenuOpen* m
        = static_cast<MenuOpen*>(e.getSource());
    MenuFile* mc
        = static_cast<MenuFile*>(&m->getParent());
    if(!mc){ return; }
    
    MenuBar* mb
        = static_cast<MenuBar*>(&mc->getParent());
    
    Frame* f
        = dynamic_cast<Frame*>(&mb->getParent());
    
    
    
    
    FileDialog fd(*f, L"Open File");
    fd.setVisible(true);
    String filename
        = String(fd.getDirectory())
        +String(fd.getFile());
    
    static_cast<TestFrame*>(f)->_image
        = f->getToolkit()->getImage(filename);
    f->repaint();
}






int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow)
{
    //wchar_t programname[MAX_PATH +1];
    //GetModuleFileNameW(0, programname, MAX_PATH);
    TestFrame test(GetCommandLineW());
    test.teststart();
    
    
    while(GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return msg.wParam;
}
