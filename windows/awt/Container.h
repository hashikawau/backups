

#ifndef __Windows_awt_Container
#define __Windows_awt_Container


//===========================================================
//===========================================================
#include <memory>
#include "Component.h"
//#include "../cpp/PointerObject.h"
class ContainerListener;
class LayoutManager;
//===========================================================
//===========================================================
class Container: public Component
{
private:
    class ListenersOfContainer;
    static ListenersOfContainer* _listener;
    
protected:
    PointerObject<Component> _child;
    PointerObject<ContainerListener> _containerListener;
    PointerObject<LayoutManager> _layoutManager;
    
    void processContainerEvent(ContainerEvent& e);
    
public:
    Container();
    virtual ~Container();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
    
    virtual void setBounds(int x, int y, int width, int height);
    virtual void setSize(int width, int height);
    virtual void add(Component& child);
    virtual void add(Component& child, int index);
    void setComponentZOrder(Component& comp, int index);
    void removeAll();
    void remove(Component& comp);
    void addContainerListener(ContainerListener& l);
    void removeContainerListener(ContainerListener& l);
    Component& getComponent(int num);
    Component** getComponents();
    //const Component& getComponentAt(const int x, const int y) const;
    int getComponentCount();
    LayoutManager& getLayout();
    void setLayout(LayoutManager& mgr);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Container

