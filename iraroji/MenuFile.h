

//#include "../windows/awt/Frame.h"
//#include "../windows/awt/Label.h"
//#include "../windows/awt/Button.h"
//#include "../windows/awt/Canvas.h"
//#include "../windows/awt/ScrollPane.h"
//#include "../windows/awt/TextField.h"
//#include "../windows/lang/String.h"
//#include "../windows/lang/Math.h"
//#include "../windows/lang/Number.h"
//#include "../windows/util/LinkedList.h"
//#include "../windows/awt/FileDialog_cpp.h"

//#include <fstream>

#include "../windows/awt/FileDialog.h"
#include "../windows/awt/Menu.h"
#include "../windows/awt/event/ActionEvent.h"

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
        MenuNew(): MenuItem("&New")
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
        MenuOpen(): MenuItem("&Open")
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
        MenuSave(): MenuItem("&Save")
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
                    = *reinterpret_cast<MenuSaveAs*>(e.getSource());
                MenuComponent* mc
                    = dynamic_cast<MenuComponent*>(&m.getParent());
                if(!mc){ return; }

                Frame* f
                    = reinterpret_cast<Frame*>(&mc->getParent());
                    //= dynamic_cast<Frame*>(&mc->getParent());
                //if(!f){ throw int(); }

                FileDialog fd(*f, String(L"Save As"), FileDialog::SAVE);
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

    MenuFile(): Menu(String(L"&File"))
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

