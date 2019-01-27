

#ifndef __Windows_awt_Scrollbar
#define __Windows_awt_Scrollbar


//===========================================================
//===========================================================
#include "Component.h"
#include "../cpp/PointerObject.h"
class Graphics;
class AdjustmentListener;
//===========================================================
//===========================================================
class Scrollbar: public Component
{
private:
    int _orientation;
    int _value;
    int _visible;
    int _minimum;
    int _maximum;
    int _unitIncrement;
    int _blockIncrement;
    
    class Listener;
    friend class Scrollbar::Listener;
    static Scrollbar::Listener* _listener;
    
    static const int INIT_SIZE;
    static const int INIT_MINIMUM_SIZE;
    static const int INIT_VALUE;
    static const int INIT_VISIBLE;
    static const int INIT_MINIMUM;
    static const int INIT_MAXIMUM;
    static const int INIT_UNIT_INCREMENT;
    static const int INIT_BLOCK_INCREMENT;
    void constructor(
        int orientation,
        int value,
        int visible,
        int minimum,
        int maximum);
    
protected:
    PointerObject<AdjustmentListener> _adjustmentListener;
    
public:
    Scrollbar();
    Scrollbar(int orientation);
    Scrollbar(
        int orientation,
        int value,
        int visible,
        int minimum,
        int maximum);
    virtual ~Scrollbar();
    virtual void update(Graphics &g);
    virtual void paint(Graphics &g);
    
    void addAdjustmentListener(AdjustmentListener &l);
    void removeAdjustmentListener(AdjustmentListener &l);
    int getOrientation();
    int getValue();
    void setBlockIncrement(int v);
    void setUnitIncrement(int v);
    void setOrientation(int orientation);
    void setValue(int newValue);
    void setVisibleAmount(int newAmount);
    void setMinimum(int newMinimum);
    void setMaximum(int newMaximum);
    void setValues(
        int value,
        int visible,
        int minimum,
        int maximum);
    
    static const int HORIZONTAL;
    static const int VERTICAL;
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Scrollbar

