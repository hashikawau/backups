

#ifndef __Windows_awt_Container_cpp
#define __Windows_awt_Container_cpp


//===========================================================
//===========================================================
#include "Container.h"
#include "Color.h"
#include "Component.h"
#include "Graphics.h"
#include "FlowLayout.h"
#include "../lang/Math.h"
//===========================================================
//===========================================================
class Container::ListenersOfContainer:
    public ComponentListener
{
public:
    virtual void componentHidden(ComponentEvent& e);
    virtual void componentMoved(ComponentEvent& e);
    virtual void componentResized(ComponentEvent& e);
    virtual void componentShown(ComponentEvent& e);
};
//===========================================================
//===========================================================
Container::ListenersOfContainer* Container::_listener =0;
//===========================================================
//===========================================================
Container::Container()
{
    //setLayout(*new FlowLayout());
    if(!_listener){
        _listener = new Container::ListenersOfContainer();
    }
    addComponentListener(*_listener);
}
Container::~Container(){}
//===========================================================
//===========================================================
void Container::update(Graphics& g)
{
    g.setColor(getBackground());
    g.fillRect(0, 0, getWidth(), getHeight());
    g.setColor(Color::black);
    paint(g);
}
void Container::paint(Graphics& g)
{
    if(_child){
        //paint on this container's DC
        //PointerObject<Graphics> g = getGraphics();
        //POINT p;
        //p.x = getX();
        //p.y = getY();
        //ScreenToClient(_hwnd, &p);
        //g->translate(p.x, p.y);
        
        for(Component** c
            = _child.get();
            *c;
            ++c)
        {
            (**c).update((**c).getGraphics());
            //paint on this container's DC
            //int x = (**c).getX();
            //int y = (**c).getY();
            //(*g).translate(x, y);
            //(**c).update(*g);
            //g->translate(-x, -y);
        }
    }
}
//===========================================================
//===========================================================
void Container::setBounds(int x, int y, int width, int height)
{
    Component::setBounds(x, y, width, height);
    if(_layoutManager){
        _layoutManager->layoutContainer(*this);
    }
}
void Container::setSize(int width, int height)
{
    Component::setSize(width, height);
    if(_layoutManager){
        _layoutManager->layoutContainer(*this);
    }
}
//===========================================================
//===========================================================
void Container::add(Component& child)
{
    _child.addFirst(&child);
    if(_layoutManager){
        _layoutManager->addLayoutComponent(String(""), child);
    }
    
    HWND hwnd = child._hwnd;
    SetWindowLong(hwnd, GWL_STYLE, WS_CHILD | WS_VISIBLE);
    SetParent(hwnd, _hwnd);
    
    if(_containerListener){
        /*
        ContainerEvent e(*this, child);
        for(ContainerListener** l
            = _containerListener.get();
            *l;
            ++l)
        {
            (**l).componentAdded(e);
        }
        */
        
        processContainerEvent(
            ContainerEvent(
                *this,
                ContainerEvent::COMPONENT_ADDED,
                child));
    }
}
void Container::add(Component& child, int index)
{
    _child.add(&child, index);
    if(_layoutManager){
        _layoutManager->addLayoutComponent(String(""), child);
    }
    
    HWND hwnd = child._hwnd;
    SetWindowLong(hwnd, GWL_STYLE, WS_CHILD | WS_VISIBLE);
    SetParent(hwnd, _hwnd);
    
    if(_containerListener){
        /*
        ContainerEvent e(*this, child);
        for(ContainerListener** l
            = _containerListener.get();
            *l;
            ++l)
        {
            (**l).componentAdded(e);
        }
        */
        processContainerEvent(
            ContainerEvent(
                *this,
                ContainerEvent::COMPONENT_ADDED,
                child));
    }
}
//===========================================================
//===========================================================
void Container::setComponentZOrder(Component& comp, int index)
{
    int size = _child.size();
    if(index <0 || index >=size){
        return;
    }
    
    if(static_cast<int>(&comp) == 0){
        return;
    }
    
    if(this != &comp.getParent()){
        return;
    }
    
    PointerObject<Component> p = &comp;
    _child.remove(&comp);
    _child.add(&comp, index);
    
    SetWindowPos(
        comp._hwnd,
        index == 0?
            HWND_TOP:
            (*_child[index -1])._hwnd,
        0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW | SWP_NOSENDCHANGING);
}
//===========================================================
//===========================================================
void Container::removeAll()
{
    for(Component** c
        = _child.get();
        *c;
        ++c)
    {
        if(_containerListener){
            /*
            ContainerEvent e(*this, **c);
            for(ContainerListener** l
                = _containerListener.get();
                *l;
                ++l)
            {
                (**l).componentRemoved(e);
            }
            */
            processContainerEvent(
                ContainerEvent(
                    *this,
                    ContainerEvent::COMPONENT_REMOVED,
                    **c));
        }
        
        if(_layoutManager){
            _layoutManager->removeLayoutComponent(**c);
        }
        //HWND hwnd = (**c).gethwnd();
        //SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        //SetParent(hwnd, 0);
    }
    
    _child = 0;
    
}
//===========================================================
//===========================================================
void Container::remove(Component& comp)
{
    if(_child.remove(&comp)){
        if(_containerListener){
            /*
            ContainerEvent e(*this, comp);
            for(ContainerListener** l
                = _containerListener.get();
                *l;
                ++l)
            {
                (**l).componentRemoved(e);
            }
            */
            processContainerEvent(
                ContainerEvent(
                    *this,
                    ContainerEvent::COMPONENT_REMOVED,
                    comp));
        }
        if(_layoutManager){
            _layoutManager->removeLayoutComponent(comp);
        }
        //HWND hwnd = (**c).gethwnd();
        //SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    }
}
//===========================================================
//===========================================================
Component& Container::getComponent(int num)
{
    if(num<0 || num>=_child.size()){
        throw ArrayIndexOutOfBoundsException();
    }
    
    Component** c = const_cast<PointerObject<Component>&>(_child).get();
    return *c[num];
    //if(num<0 || num>=_child.size()){ throw ArrayIndexOutOfBoundsException(); }
    //return *static_cast<Component*>(_child[num]);
}
Component** Container::getComponents()
{
//    Component** c = const_cast<PointerObject<Component>&>(_child).get();
    return _child.get();
}
//===========================================================
//===========================================================
void Container::processContainerEvent(ContainerEvent& e)
{
    int id = e.getID();
    switch(id){
        case ContainerEvent::COMPONENT_ADDED:
            for(ContainerListener** l = _containerListener.get(); *l; ++l){
                (**l).componentAdded(e);
            }
            break;
        
        case ContainerEvent::COMPONENT_REMOVED:
            for(ContainerListener** l = _containerListener.get(); *l; ++l){
                (**l).componentRemoved(e);
            }
            break;
        
        default:
            break;
    };
}
//===========================================================
//===========================================================
/*
const Component& Container::getComponentAt(const int x, const int y) const
{
    POINT po;
    po.x = x;
    po.y = y;
    
    HWND hwnd = ChildWindowFromPoint(_hwnd, po);
    if(hwnd == _hwnd)
    {
        return NULL;
    }
    else
    {
        wchar_t szClassName[sizeof(int)*8+1];
        GetClassNameW(hwnd, szClassName, sizeof(int)*8+1);
        return (Component*)_wtoi(szClassName);
    }
    
}
*/
//===========================================================
//===========================================================
int Container::getComponentCount()
{
    return _child.size();
}
//===========================================================
//===========================================================
void Container::addContainerListener(ContainerListener& l)
{
    _containerListener.addFirst(&l);
}
void Container::removeContainerListener(ContainerListener& l)
{
    _containerListener.remove(&l);
}
//===========================================================
//===========================================================
LayoutManager& Container::getLayout()
{
    return *_layoutManager;
}
void Container::setLayout(LayoutManager& mgr)
{
    _layoutManager = &mgr;
}
//===========================================================
//===========================================================
void Container::ListenersOfContainer::componentHidden(ComponentEvent& e){}
void Container::ListenersOfContainer::componentMoved(ComponentEvent& e){}
void Container::ListenersOfContainer::componentResized(ComponentEvent& e)
{
    Container* c = static_cast<Container*>(&e.getComponent());
    LayoutManager* lm= &c->getLayout();
    if(lm){
        lm->layoutContainer(*c);
    }
}
void Container::ListenersOfContainer::componentShown(ComponentEvent& e){}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Container_cpp

