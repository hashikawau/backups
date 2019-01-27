

#ifndef __Windows_awt_Menu
#define __Windows_awt_Menu


//===========================================================
//===========================================================
#include "../_windows.h"
//#include "../lang/String.h"
//#include "../util/LinkedList.h"
//#include "../cpp/PointerObject.h"
#include <vector>
#include <memory>
using namespace std;
class ActionListener;
//===========================================================
//===========================================================
class MenuContainer
{
public:
    MenuContainer();
    virtual ~MenuContainer() =0;
};
//===========================================================
//===========================================================
class MenuItem;
class MenuComponent
{
private:
    friend class MenuItem;
    static int _count;
    
protected:
    HMENU _hmenu;
    MenuContainer* _parent;
    const int _id;
    
public:
    MenuComponent();
    //MenuComponent(const MenuComponent& mc);
    virtual ~MenuComponent() =0;
    
    MenuContainer& getParent();
    
    int getid();
};
//===========================================================
//===========================================================
class Menu;
class MenuItem: public MenuComponent
{
private:
    friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    friend class Menu;
    
protected:
    static vector<MenuItem*> _menuItemList;
    string _label;
    shared_ptr<ActionListener> _actionListener;
    
public:
    MenuItem(const string& label ="");
    virtual ~MenuItem();
    void addActionListener(ActionListener& l);
    string getLabel();
    void setLabel(string& label);
    bool isEnabled();
    void setEnabled(bool b);
};
//===========================================================
//===========================================================
class MenuBar;
class Menu: public MenuContainer, public MenuItem
{
private:
    friend class MenuBar;
    
public:
    //Menu();
    Menu(const string& label ="");
    virtual ~Menu();
    MenuItem& add(MenuItem& m);
    void addSeparator();
};
//===========================================================
//===========================================================
class Frame;
class MenuBar: public MenuContainer, public MenuComponent
{
private:
    friend class Frame;
    
public:
    MenuBar();
    virtual ~MenuBar();
    Menu& add(Menu& m);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Menu

