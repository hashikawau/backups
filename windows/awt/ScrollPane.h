



#ifndef __Windows_awt_ScrollPane
#define __Windows_awt_ScrollPane


#include "Container.h"
#include "Scrollbar.h"
#include "FlowLayout.h"


//===========================================================
//===========================================================
class ScrollPane :public Container
{
public:
    class Listener:
        public FocusListener,
        public AdjustmentListener,
        public LayoutManager
    {
    public:
        virtual ~Listener();
        virtual void focusGained(FocusEvent& e);
        virtual void focusLost(FocusEvent& e);
        virtual void adjustmentValueChanged(AdjustmentEvent& e);
        virtual void addLayoutComponent(
            String& name,
            Component& comp);
        virtual void layoutContainer(Container& parent);
        virtual void removeLayoutComponent(Component& comp);
    };
    //static ScrollPane::Listener* _listener;
    friend class ScrollPane::Listener;
    friend class PointerObject<ScrollPane::Listener>;
    static PointerObject<ScrollPane::Listener> _listener;

private:
    void constructor(
        Component* view,
        int vsbPolicy,
        int hsbPolicy);
protected:
    Component* _compView;
    Scrollbar* _sbVertical;
    Scrollbar* _sbHorizontal;
    int _vsbPolicy;
    int _hsbPolicy;
    int _scrollPositionX;
    int _scrollPositionY;
    //void addImpl(Component &comp);
    
public:
    ScrollPane();
    explicit ScrollPane(Component& view);
    ScrollPane(int vsbPolicy, int hsbPolicy);
    ScrollPane(
        Component& view,
        int vsbPolicy,
        int hsbPolicy);
    virtual ~ScrollPane();
    virtual void add(Component& view);
    virtual void paint(Graphics& g);
    
    static const int SCROLLBARS_AS_NEEDED;
    static const int SCROLLBARS_ALWAYS;
    static const int SCROLLBARS_NEVER;
};
//ScrollPane::Listener* ScrollPane::_listener = new ScrollPane::Listener();
PointerObject<ScrollPane::Listener> ScrollPane::_listener(new ScrollPane::Listener());
const int ScrollPane::SCROLLBARS_AS_NEEDED =0;
const int ScrollPane::SCROLLBARS_ALWAYS    =1;
const int ScrollPane::SCROLLBARS_NEVER     =2;
//===========================================================
//===========================================================
ScrollPane::Listener::~Listener(){}
void ScrollPane::Listener::focusGained(FocusEvent& e)
{
    Component* source = static_cast<Component*>(e.getSource());
    
    if(ScrollPane* source2 = dynamic_cast<ScrollPane*>(source)){
        if(source2->_compView){
            source2->_compView->requestFocus();
        }
    }else
    if(Scrollbar* source2 = dynamic_cast<Scrollbar*>(source)){
        if(ScrollPane* parent = dynamic_cast<ScrollPane*>(&source2->getParent())){
            parent->requestFocus();
            //if(parent->_compView){
            //    parent->_compView->requestFocus();
            //}
        }
    }
}
void ScrollPane::Listener::focusLost(FocusEvent& e){}
void ScrollPane::Listener::adjustmentValueChanged(AdjustmentEvent& e)
{
    Scrollbar* sbar = static_cast<Scrollbar*>(e.getSource());
    ScrollPane* spane = static_cast<ScrollPane*>(&sbar->getParent());
    if(!spane->_compView){ return; }
    
    //Graphics& g = spane->_compView->getGraphics();
    if(sbar->getOrientation() == Scrollbar::HORIZONTAL){
        spane->_scrollPositionX = -e.getValue();
    }else{
    //if(sbar->getOrientation() == Scrollbar::HORIZONTAL){
        spane->_scrollPositionY = -e.getValue();
    }
    spane->_compView->setLocation(
        spane->_scrollPositionX,
        spane->_scrollPositionY);
    spane->update(spane->_compView->getGraphics());
}
void ScrollPane::Listener::addLayoutComponent(
    String& name,
    Component& comp){}
void ScrollPane::Listener::layoutContainer(Container& parent)
{
    ScrollPane* sp = dynamic_cast<ScrollPane*>(&parent);
//debug+=String("ScrollPane  ")+String((int)sp)+String("\n");
    if(!sp){ return; }
    int parentWidth  = sp->getWidth();
    int parentHeight = sp->getHeight();
    int viewWidth  =0;
    int viewHeight =0;
    if(sp->_compView){
        viewWidth  = sp->_compView->getWidth();
        viewHeight = sp->_compView->getHeight();
        sp->_compView->setLocation(1, 1);
    }
    int vsbWidth = sp->_sbVertical?
        sp->_sbVertical->getWidth():
        0;
    int hsbHeight = sp->_sbHorizontal?
        sp->_sbHorizontal->getHeight():
        0;
    bool isVsbNecessary
        = (viewHeight > parentHeight)
        | (sp->_vsbPolicy == ScrollPane::SCROLLBARS_ALWAYS)
        & (sp->_vsbPolicy != ScrollPane::SCROLLBARS_NEVER);
    bool isHsbNecessary
        = (viewWidth > parentWidth)
        | (sp->_hsbPolicy == ScrollPane::SCROLLBARS_ALWAYS)
        & (sp->_hsbPolicy != ScrollPane::SCROLLBARS_NEVER);
    
    //int _vsbPolicy;
    //int _hsbPolicy;
    
    parentWidth += isVsbNecessary?
        -vsbWidth:
        0;
    parentHeight += isHsbNecessary?
        -hsbHeight:
        0;
    
    if(!isVsbNecessary && viewHeight > parentHeight){
        parentWidth += -vsbWidth;
        isVsbNecessary = true;
    }
    if(!isHsbNecessary && viewWidth > parentWidth){
        parentHeight += -hsbHeight;
        isHsbNecessary = true;
    }
    //isVsbNecessary = _vsbPolicy == SCROLLBARS_ALWAYS?;
    //isHsbNecessary = _hsbPolicy;
    if(sp->_sbVertical){
        if(isVsbNecessary){
            sp->_sbVertical->setBounds(
                parentWidth,
                0,
                vsbWidth,
                parentHeight);
            sp->_sbVertical->setValues(
                0,
                parentHeight,
                0,
                viewHeight);
            sp->_sbVertical->setUnitIncrement(parentHeight/10);
            sp->_sbVertical->setBlockIncrement(parentHeight/2);
        }
        sp->_sbVertical->setVisible(isVsbNecessary);
    }
    if(sp->_sbHorizontal){
        if(isHsbNecessary){
            sp->_sbHorizontal->setBounds(
                0,
                parentHeight,
                parentWidth,
                hsbHeight);
            sp->_sbHorizontal->setValues(
                0,
                parentWidth,
                0,
                viewWidth);
            sp->_sbHorizontal->setUnitIncrement(parentWidth/10);
            sp->_sbHorizontal->setBlockIncrement(parentWidth/2);
        }
        sp->_sbHorizontal->setVisible(isHsbNecessary);
    }
}
void ScrollPane::Listener::removeLayoutComponent(Component& comp){}
//===========================================================
//===========================================================
void ScrollPane::constructor(
    Component* view,
    int vsbPolicy,
    int hsbPolicy)
{
    _sbVertical = new Scrollbar(Scrollbar::VERTICAL);
    _sbHorizontal = new Scrollbar(Scrollbar::HORIZONTAL);
    _sbVertical->addAdjustmentListener(*_listener);
    _sbHorizontal->addAdjustmentListener(*_listener);
    _sbVertical->addFocusListener(*_listener);
    _sbHorizontal->addFocusListener(*_listener);
    setLayout(*_listener);
    addFocusListener(*_listener);
    
    _compView =0;
    if(view){
        Container::add(*view);
        _compView = const_cast<Component*>(view);
    }
    Container::add(*_sbVertical);
    Container::add(*_sbHorizontal);
    
    _vsbPolicy = vsbPolicy;
    _hsbPolicy = hsbPolicy;
    _scrollPositionX =0;
    _scrollPositionY =0;
    
    setBackground(Color::white);
}
//===========================================================
//===========================================================
ScrollPane::ScrollPane()
{
    constructor(0, SCROLLBARS_AS_NEEDED, SCROLLBARS_AS_NEEDED);
}
ScrollPane::ScrollPane(Component& view)
{
    constructor(&view, SCROLLBARS_AS_NEEDED, SCROLLBARS_AS_NEEDED);
}
ScrollPane::ScrollPane(int vsbPolicy, int hsbPolicy)
{
    constructor(0, vsbPolicy, hsbPolicy);
}
ScrollPane::ScrollPane(
    Component& view,
    int vsbPolicy,
    int hsbPolicy)
{
    constructor(&view, vsbPolicy, hsbPolicy);
}
ScrollPane::~ScrollPane(){}
//void ScrollPane::addImpl(Component &comp){}
//===========================================================
//===========================================================
void ScrollPane::add(Component& view)
{
    if(!&view){ return; }
    if(_compView){
        Container::remove(*_compView);
    }
    Container::add(view, 0);
    _compView = const_cast<Component*>(&view);
    if(_layoutManager){
        _layoutManager->layoutContainer(*this);
    }
    
    /*
    SetWindowPos(
        _compView->_hwnd,
        HWND_BOTTOM,
        0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE);
    */
}
//===========================================================
//===========================================================
void ScrollPane::paint(Graphics& g)
{
    if(_compView){
        //g.translate(_scrollPositionX, _scrollPositionY);
        _compView->update(_compView->getGraphics());
    }
    _sbVertical->update(_sbVertical->getGraphics());
    _sbHorizontal->update(_sbHorizontal->getGraphics());
    
    /*
    {
        Graphics g(_sbVertical->_hwnd);
        _sbVertical->update(g);
    }
    
    {
        Graphics g(_sbHorizontal->_hwnd);
        _sbHorizontal->update(g);
    }
    */
    
    g.setColor(Color(0x00));
    g.drawRect(0, 0, getWidth(), getHeight());
}

//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_ScrollPane




