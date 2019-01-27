

#ifndef __Windows_awt_Menu_cpp
#define __Windows_awt_Menu_cpp


//===========================================================
//===========================================================
#include "Menu.h"
#include "../_windows.h"
#include "event/ActionEvent.h"
#include "../util/LinkedList.h"
#include "../cpp/PointerObject.h"
#include "event/ActionEvent_cpp.h"
#include "../util/LinkedList_cpp.h"
#include "../cpp/PointerObject_cpp.h"
//===========================================================
//===========================================================
//#include "windows\util\LinkedList.h"
//===========================================================
//===========================================================
MenuContainer::MenuContainer(){}
MenuContainer::~MenuContainer(){}
//===========================================================
//===========================================================
int MenuComponent::_count =0;
//===========================================================
//===========================================================
MenuComponent::MenuComponent(): _parent(0), _id(_count++)
{
    _hmenu = CreateMenu();
    
    MENUITEMINFOW mii;
    ZeroMemory(&mii, sizeof(mii));
    mii.cbSize = sizeof(mii);
    mii.fMask  = MIIM_ID;
    mii.wID    = _id;
    SetMenuItemInfoW(_hmenu, 0, true, &mii);
}
MenuComponent::~MenuComponent(){}
//===========================================================
//===========================================================
MenuContainer& MenuComponent::getParent()
{
    return *_parent;
}
int MenuComponent::getid()
{
    return _id;
}
//===========================================================
//===========================================================
LinkedList<MenuItem*> MenuItem::_menuItemList;
//===========================================================
//===========================================================
MenuItem::MenuItem(const String& label): _label(label)
{
    _menuItemList.addLast(this);
}
MenuItem::~MenuItem(){}
//===========================================================
//===========================================================
void MenuItem::addActionListener(ActionListener& l)
{
    _actionListener.addFirst(&l);
}
String MenuItem::getLabel()
{
    return _label;
}
void MenuItem::setLabel(String& label)
{
    _label = label;
}
//===========================================================
//===========================================================
Menu::Menu(const String& label): MenuItem(label){}
Menu::~Menu(){}
MenuItem& Menu::add(MenuItem& m)
{
    String str = m.getLabel();
    MENUITEMINFO mii;
    //ZeroMemory(&mii, sizeof(mii));
    mii.cbSize     = sizeof(mii);
    mii.fMask      = dynamic_cast<Menu*>(&m)?
        MIIM_TYPE | MIIM_SUBMENU:
        MIIM_TYPE;
    mii.fType      = MFT_STRING;
    mii.hSubMenu   = m._hmenu;
    mii.dwTypeData = const_cast<wchar_t*>(str.toCharArray());
    mii.cch        = str.length();
    InsertMenuItem(_hmenu, -1, TRUE, &mii);
    m._parent = this;
    
    mii.fMask = MIIM_ID;
    mii.wID   = m.getid();
    SetMenuItemInfoW(_hmenu, GetMenuItemCount(_hmenu)-1, true, &mii);
    
    return m;
}
void Menu::addSeparator()
{
    MenuItem m(String("-"));
    String str = m.getLabel();
    MENUITEMINFO mii;
    //ZeroMemory(&mii, sizeof(mii));
    mii.cbSize     = sizeof(mii);
    mii.fMask      = MIIM_TYPE;
    mii.fType      = MFT_SEPARATOR;
    mii.dwTypeData = const_cast<wchar_t*>(str.toCharArray());
    mii.cch        = str.length();
    InsertMenuItem(_hmenu, -1, true, &mii);
    m._parent = this;
    
    mii.fMask = MIIM_ID;
    mii.wID   = m.getid();
    SetMenuItemInfoW(_hmenu, GetMenuItemCount(_hmenu) -1, true, &mii);
}
//===========================================================
//===========================================================
bool MenuItem::isEnabled()
{
    return !(
        GetMenuState(
            dynamic_cast<MenuComponent&>(getParent())._hmenu,
            getid(),
            MF_BYCOMMAND)
        & (MF_DISABLED | MF_GRAYED));
}
void MenuItem::setEnabled(bool b)
{
    int state = b?
        MF_BYCOMMAND | MF_ENABLED:
        MF_BYCOMMAND | MF_GRAYED;
    EnableMenuItem(
        dynamic_cast<MenuComponent&>(getParent())._hmenu,
        getid(),
        state);
}
//===========================================================
//===========================================================
MenuBar::MenuBar(){}
MenuBar::~MenuBar(){}
Menu& MenuBar::add(Menu& m)
{
    String str = m.getLabel();
    MENUITEMINFO mii;
    ZeroMemory(&mii, sizeof(mii));
    mii.cbSize     = sizeof(mii);
    mii.fMask      = MIIM_TYPE | MIIM_SUBMENU;
    mii.fType      = MFT_STRING;
    mii.hSubMenu   = m._hmenu;
    mii.dwTypeData = const_cast<wchar_t*>(m.getLabel().toCharArray());
    mii.cch        = str.length();
    InsertMenuItem(_hmenu, -1, TRUE, &mii);
    m._parent = this;
    
    mii.fMask = MIIM_ID;
    mii.wID   = m.getid();
    SetMenuItemInfoW(_hmenu, GetMenuItemCount(_hmenu) -1, true, &mii);
    
    return m;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Menu_cpp

