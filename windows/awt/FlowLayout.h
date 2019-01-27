


#ifndef __Windows_awt_FlowLayout
#define __Windows_awt_FlowLayout



#include "Container.h"

class String;
class Component;
class Container;
//===========================================================
//===========================================================
class LayoutManager
{
public:
    virtual ~LayoutManager() =0;
    virtual void addLayoutComponent(String& name, Component& comp) =0;
    virtual void layoutContainer(Container& parent) =0;
    virtual void removeLayoutComponent(Component& comp) =0;
};
LayoutManager::~LayoutManager(){}
//===========================================================
//===========================================================
class FlowLayout: public LayoutManager
{
private:
    //PointerObject<Component> _poChild;
    int _align;
    int _hgap;
    int _vgap;
    int getHorizontalStart(
        int containerWidth,
        int rowWidth);
protected:
public:
    explicit FlowLayout(int align =CENTER);
    FlowLayout(int align, int hgap, int vgap);
    virtual ~FlowLayout();
    virtual void addLayoutComponent(String& name, Component& comp);
    virtual void layoutContainer(Container& parent);
    virtual void removeLayoutComponent(Component& comp);
    
    static const int LEFT;
    static const int CENTER;
    static const int RIGHT;
    static const int LEADING;
    static const int TRAILING;
};
const int FlowLayout::LEFT     =0;
const int FlowLayout::CENTER   =1;
const int FlowLayout::RIGHT    =2;
const int FlowLayout::LEADING  =3;
const int FlowLayout::TRAILING =4;
//===========================================================
//===========================================================
int FlowLayout::getHorizontalStart(
    int containerWidth,
    int rowWidth)
{
    int horizontalStart;
    switch(_align){
        case LEFT:
            horizontalStart = _hgap;
            break;
        case RIGHT:
            horizontalStart
                = -_hgap +(containerWidth - rowWidth);
            break;
        case CENTER:
        default:
            horizontalStart
                = _hgap +(containerWidth - rowWidth)/2.;
            break;
    }
    return horizontalStart;
}
//===========================================================
//===========================================================
FlowLayout::FlowLayout(int align):
    _align(align),
    _hgap(5),
    _vgap(5){}
FlowLayout::FlowLayout(int align, int hgap, int vgap):
    _align(align),
    _hgap(hgap),
    _vgap(vgap){}
FlowLayout::~FlowLayout(){}
void FlowLayout::addLayoutComponent(String& name, Component& comp)
{
    //_poChild.addFirst(&comp);
}
//===========================================================
//===========================================================
void FlowLayout::layoutContainer(Container& parent)
{
    int containerWidth = parent.getWidth();
    Component** child = const_cast<Container*>(&parent)->getComponents();
    int verticalStart = _vgap;
    int maxHeight =0;
    int rowStartNum =0;
    int rowWidth =_hgap;
    for(int i=0; ;++i)
    {
        if(child[i]){
            int childWidth = child[i]->getWidth();
            int temp = rowWidth +childWidth +_hgap;
            if(temp >= containerWidth){
                int horizontalStart
                    = getHorizontalStart(containerWidth, rowWidth);
                
                for(int j=rowStartNum; j< i; ++j)
                {
                    child[j]->setLocation(horizontalStart, verticalStart);
                    horizontalStart += child[j]->getWidth() +_hgap;
                }
                
//debug +=String("containerWidth, rowWidth   ")
//    +String(containerWidth) +String("  ")
//    +String(temp) +String("\n");
                
                if(i){
                    verticalStart += maxHeight +_vgap;
                }
                maxHeight =0;
                rowStartNum =i;
                rowWidth = childWidth + 2*_hgap;
            }else{
                rowWidth = temp;
            }
            
            int height = child[i]->getHeight();
            maxHeight = height > maxHeight?
                height:
                maxHeight;
            
        }else{
            int horizontalStart
                = getHorizontalStart(containerWidth, rowWidth);
            for(int j=rowStartNum; j< i; ++j)
            {
                child[j]->setLocation(horizontalStart, verticalStart);
                horizontalStart += child[j]->getWidth() +_hgap;
            }
            
            break;
        }
//cout << child[i]->getX() << "  " << child[i]->getY() << endl;
        
    }
//debug +=String("paint()  ") +String(count) +String("\n");
    const_cast<Container*>(&parent)->repaint();
}
void FlowLayout::removeLayoutComponent(Component& comp)
{
    //_poChild.remove(&comp);
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================




#endif //ifndef __Windows_awt_FlowLayout

