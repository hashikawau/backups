

#ifndef __Windows_awt_Scrollbar_cpp
#define __Windows_awt_Scrollbar_cpp


//===========================================================
//===========================================================
#include "Scrollbar.h"
#include "Color.h"
#include "Component.h"
#include "Graphics.h"
#include "event/ActionEvent.h"
#include "../cpp/PointerObject.h"
//===========================================================
//===========================================================
class Scrollbar::Listener:
    public KeyListener,
    public MouseListener,
    public MouseMotionListener,
    public MouseWheelListener
{
public:
    virtual void keyPressed(KeyEvent &e);
    virtual void keyReleased(KeyEvent &e);
    virtual void keyTyped(KeyEvent &e);
    virtual void mouseClicked(MouseEvent &e);
    virtual void mouseEntered(MouseEvent &e);
    virtual void mouseExited(MouseEvent &e);
    virtual void mousePressed(MouseEvent &e);
    virtual void mouseReleased(MouseEvent &e);
    virtual void mouseDragged(MouseEvent &e);
    virtual void mouseMoved(MouseEvent &e);
    virtual void mouseWheelMoved(MouseWheelEvent& e);
    static int _mousePosition;
    static int _initialValue;
};
//===========================================================
//===========================================================

//===========================================================
//===========================================================
int Scrollbar::Listener::_mousePosition =0;
int Scrollbar::Listener::_initialValue =0;
Scrollbar::Listener* Scrollbar::_listener =0;
const int Scrollbar::INIT_SIZE            =15;
const int Scrollbar::INIT_MINIMUM_SIZE    =5;
const int Scrollbar::INIT_VALUE           =0;
const int Scrollbar::INIT_VISIBLE         =10;
const int Scrollbar::INIT_MINIMUM         =0;
const int Scrollbar::INIT_MAXIMUM         =100;
const int Scrollbar::INIT_UNIT_INCREMENT  =1;
const int Scrollbar::INIT_BLOCK_INCREMENT =10;
const int Scrollbar::HORIZONTAL = 0;
const int Scrollbar::VERTICAL   = 1;
//===========================================================
//===========================================================
void Scrollbar::constructor(
    int orientation,
    int value,
    int visible,
    int minimum,
    int maximum)
{
    setBackground(Color(0x00DDDDDD));
    
    setOrientation(orientation);
    setValues(value, visible, minimum, maximum);
    _unitIncrement  =1;
    _blockIncrement =10;
    
    if(_orientation == VERTICAL){
        setSize(INIT_SIZE, _maximum -_minimum);
    }else
    if(_orientation == HORIZONTAL){
        setSize(_maximum -_minimum, INIT_SIZE);
    }
    
    if(!_listener){
        _listener = new Scrollbar::Listener();
    }
    addKeyListener(*_listener);
    addMouseListener(*_listener);
    addMouseMotionListener(*_listener);
    addMouseWheelListener(*_listener);
}
//===========================================================
//===========================================================
Scrollbar::Scrollbar()
{
    constructor(
        VERTICAL,
        INIT_VALUE,
        INIT_VISIBLE,
        INIT_MINIMUM,
        INIT_MAXIMUM);
}
Scrollbar::Scrollbar(int orientation)
{
    constructor(
        orientation,
        INIT_VALUE,
        INIT_VISIBLE,
        INIT_MINIMUM,
        INIT_MAXIMUM);
}
Scrollbar::Scrollbar(
    int orientation,
    int value,
    int visible,
    int minimum,
    int maximum)
{
    constructor(
        orientation,
        value,
        visible,
        minimum,
        maximum);
}
Scrollbar::~Scrollbar(){}
//===========================================================
//===========================================================
void Scrollbar::update(Graphics &g)
{
    paint(g);
}
void Scrollbar::paint(Graphics &g)
{
    int width = getWidth();
    int height = getHeight();
    g.setColor(getBackground());
    g.fillRect(0, 0, width, height);
    
    g.setColor(SystemColor::activeCaptionBorder);
    if(_orientation == VERTICAL){
        double ratio = static_cast<double>(height -2 *width)
            /(_maximum -_minimum);
        double visible = _visible *ratio +1;
        if(visible < INIT_MINIMUM_SIZE){
            visible = INIT_MINIMUM_SIZE;
            ratio = static_cast<double>(height -2 *width -visible)
                /(_maximum -_minimum -_visible);
        }
        
        g.fillRect(
            0,
            width +(_value -_minimum) *ratio,
            width,
            visible);
        g.fillRect(0, 0, width, width);
        g.fillRect(0, height -width, width, width);
        
        g.setColor(SystemColor::window);
        g.fillRect(
            0,
            width +(_value -_minimum) *ratio,
            width,
            1);
        g.fillRect(
            0,
            width +(_value -_minimum) *ratio,
            1,
            visible);
        g.fillRect(0, 0, width, 1);
        g.fillRect(0, 0, 1, width);
        g.fillRect(0, height -width, width, 1);
        g.fillRect(0, height -width, 1, width);
        
        g.setColor(SystemColor::inactiveCaption);
        g.fillRect(
            0,
            width +(_value -_minimum) *ratio +visible -2,
            width,
            2);
        g.fillRect(
            width -2,
            width +(_value -_minimum) *ratio,
            2,
            visible);
        
        g.fillRect(0, width -2, width, 2);
        g.fillRect(width -2, 0, 2, width);
        
        g.fillRect(0, height -2, width, 2);
        g.fillRect(width -2, height -width, 2, width);
    }else
    if(_orientation == HORIZONTAL){
        double ratio = static_cast<double>(width -2 *height)
            /(_maximum -_minimum);
        double visible = _visible *ratio +1;
        if(visible < INIT_MINIMUM_SIZE){
            visible = INIT_MINIMUM_SIZE;
            ratio = static_cast<double>(width -2 *height -visible)
                /(_maximum -_minimum -_visible);
        }
        
        g.fillRect(
            height +(_value -_minimum) *ratio,
            0,
            visible,
            height);
        g.fillRect(0, 0, height, height);
        g.fillRect(width -height, 0, height, height);
        
        g.setColor(SystemColor::window);
        g.fillRect(
            height +(_value -_minimum) *ratio,
            0,
            visible,
            1);
        g.fillRect(
            height +(_value -_minimum) *ratio,
            0,
            1,
            height);
        g.fillRect(0, 0, height, 1);
        g.fillRect(0, 0, 1, height);
        g.fillRect(width -height, 0, height, 1);
        g.fillRect(width -height, 0, 1, height);
        
        g.setColor(SystemColor::inactiveCaption);
        g.fillRect(
            height +(_value -_minimum) *ratio,
            height -2,
            visible,
            2);
        g.fillRect(
            height +(_value -_minimum) *ratio +visible -2,
            0,
            2,
            height);
        
        g.fillRect(0, height -2, height, 2);
        g.fillRect(height -2, 0, 2, height);
        
        g.fillRect(width -height, height -2, height, 2);
        g.fillRect(width -2, 0, 2, height);
    }
}
//===========================================================
//===========================================================
void Scrollbar::addAdjustmentListener(AdjustmentListener &l)
{
    _adjustmentListener.add(&l);
}
void Scrollbar::removeAdjustmentListener(AdjustmentListener &l)
{
    _adjustmentListener.remove(&l);
}
//===========================================================
//===========================================================
int Scrollbar::getOrientation(){ return _orientation; }
int Scrollbar::getValue(){ return _value; }
//===========================================================
//===========================================================
void Scrollbar::setBlockIncrement(int v)
{
    _blockIncrement = v;
}
void Scrollbar::setUnitIncrement(int v)
{
    _unitIncrement = v;
}
//===========================================================
//===========================================================
void Scrollbar::setOrientation(int orientation)
{
    if(orientation == VERTICAL){
        _orientation = VERTICAL;
    }else
    if(orientation == HORIZONTAL){
        _orientation = HORIZONTAL;
    }else{
        throw IllegalArgumentException();
    }
}
//===========================================================
//===========================================================
void Scrollbar::setValue(int newValue)
{
    _value = newValue < _minimum?
        _minimum:
        newValue > _maximum -_visible?
            _maximum -_visible:
            newValue;
}
//===========================================================
//===========================================================
void Scrollbar::setVisibleAmount(int newAmount)
{
    if(newAmount <= _maximum -_minimum){
        if(newAmount >0){
            setValues(_value, newAmount, _minimum, _maximum);
        }
    }
}
//===========================================================
//===========================================================
void Scrollbar::setMinimum(int newMinimum)
{
    if(newMinimum < _maximum){
        setValues(_value, _visible, newMinimum, _maximum);
    }
}
void Scrollbar::setMaximum(int newMaximum)
{
    if(newMaximum > _minimum){
        setValues(_value, _visible, _minimum, newMaximum);
    }
}
//===========================================================
//===========================================================
void Scrollbar::setValues(
    int value,
    int visible,
    int minimum,
    int maximum)
{
    if(maximum > minimum){
        _maximum = maximum;
        _minimum = minimum;
    }else
    if(maximum < minimum){
        _maximum = minimum;
        _minimum = maximum;
    }else
    if(maximum == minimum){
        _maximum = maximum +1;
        _minimum = minimum;
    }
    
    int difference = _maximum -_minimum;
    _visible = visible <= difference?
        visible:
        difference;
    
    _value = value < _minimum?
        _minimum:
        value > _maximum -_visible?
            _maximum -_visible:
            value;
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
void Scrollbar::Listener::keyPressed(KeyEvent &e)
{
    Scrollbar& sb = *static_cast<Scrollbar*>(e.getSource());
    int type;
    
    switch(e.getKeyChar())
    {
        case VK_PRIOR:
            sb.setValue(sb._value -sb._blockIncrement);
            type = AdjustmentEvent::BLOCK_DECREMENT;
            break;
            
        case VK_NEXT:
            sb.setValue(sb._value +sb._blockIncrement);
            type = AdjustmentEvent::BLOCK_INCREMENT;
            break;
            
        case VK_HOME:
            return;
            
        case VK_END:
            return;
            
        case VK_LEFT:
            sb.setValue(sb._value -sb._unitIncrement);
            type = AdjustmentEvent::UNIT_DECREMENT;
            break;
             
        case VK_UP:
            sb.setValue(sb._value -sb._unitIncrement);
            type = AdjustmentEvent::UNIT_DECREMENT;
            break;
            
        case VK_RIGHT:
            sb.setValue(sb._value +sb._unitIncrement);
            type = AdjustmentEvent::UNIT_INCREMENT;
            break;
            
        case VK_DOWN:
            sb.setValue(sb._value +sb._unitIncrement);
            type = AdjustmentEvent::UNIT_INCREMENT;
            break;
             
        default:
            return;
    }
    
    if(sb._adjustmentListener){
        AdjustmentEvent e(
            static_cast<int>(&sb),
            type,
            sb._value
        );
        for(AdjustmentListener** l
            = sb._adjustmentListener.get();
            *l;
            ++l)
        {
            (**l).adjustmentValueChanged(e);
        }
    }
    
    //Graphics g(sb._hwnd);
    sb.repaint();
}
void Scrollbar::Listener::keyReleased(KeyEvent &e)
{
}
void Scrollbar::Listener::keyTyped(KeyEvent &e)
{
}
//===========================================================
//===========================================================
void Scrollbar::Listener::mouseClicked(MouseEvent &e)
{
}
void Scrollbar::Listener::mouseEntered(MouseEvent &e)
{
}
void Scrollbar::Listener::mouseExited(MouseEvent &e)
{
}
void Scrollbar::Listener::mousePressed(MouseEvent &e)
{
    Scrollbar& sb = *static_cast<Scrollbar*>(e.getSource());
    int prevalue = sb._value;
    int type =0;
    int position;
    int parallel;
    int orthogonal;
    if(sb._orientation == Scrollbar::VERTICAL){
        position = e.getY();
        parallel   = sb.getHeight();
        orthogonal = sb.getWidth();
    }else
    if(sb._orientation == Scrollbar::HORIZONTAL){
        position = e.getX();
        parallel   = sb.getWidth();
        orthogonal = sb.getHeight();
    }
    
    double ratio = static_cast<double>(parallel -2*orthogonal)
        /static_cast<double>(sb._maximum -sb._minimum);
    //int visible = sb._visible *ratio >= Scrollbar::INIT_MINIMUM_SIZE?
    //    sb._visible *ratio:
    //    Scrollbar::INIT_MINIMUM_SIZE;
    double visible = sb._visible *ratio;
    if( visible < Scrollbar::INIT_MINIMUM_SIZE){
        visible = Scrollbar::INIT_MINIMUM_SIZE;
        ratio = (parallel -2*orthogonal -visible)
            /static_cast<double>(sb._maximum -sb._minimum -sb._visible);
    }
    if(position < orthogonal){
        sb.setValue(sb._value -sb._unitIncrement);
        type = AdjustmentEvent::UNIT_DECREMENT;
    }else
    if(position > parallel -orthogonal){
        sb.setValue(sb._value +sb._unitIncrement);
        type = AdjustmentEvent::UNIT_INCREMENT;
    }else
    if(position < orthogonal +(sb._value -sb._minimum) *ratio){
        sb.setValue(sb._value -sb._blockIncrement);
        type = AdjustmentEvent::BLOCK_DECREMENT;
    }else
    if(position > orthogonal +(sb._value -sb._minimum) *ratio +visible){
        sb.setValue(sb._value +sb._blockIncrement);
        type = AdjustmentEvent::BLOCK_INCREMENT;
    }else{
        _mousePosition = e.getButton() == MouseEvent::BUTTON1?
            position:
            0;
        _initialValue = sb._value;
    }
    
    if(prevalue != sb._value){
        if(sb._adjustmentListener){
            AdjustmentEvent e(
                static_cast<int>(&sb),
                type,
                sb._value
            );
            for(AdjustmentListener** l
                = sb._adjustmentListener.get();
                *l;
                ++l)
            {
                (**l).adjustmentValueChanged(e);
            }
        }
    }
    
    //Graphics g(sb._hwnd);
    //sb.update(g);
    sb.repaint();
}
void Scrollbar::Listener::mouseReleased(MouseEvent &e)
{
    _mousePosition = 0;
    _initialValue = 0;
    Scrollbar& sb = *static_cast<Scrollbar*>(e.getSource());
    sb.repaint();
}
//===========================================================
//===========================================================
void Scrollbar::Listener::mouseDragged(MouseEvent &e)
{
    if(_mousePosition){
        Scrollbar& sb = *static_cast<Scrollbar*>(e.getSource());
        int prevalue = sb._value;
        int position;
        int parallel;
        int orthogonal;
        if(sb._orientation == Scrollbar::VERTICAL){
            position = e.getY();
            parallel   = sb.getHeight();
            orthogonal = sb.getWidth();
        }else
        if(sb._orientation == Scrollbar::HORIZONTAL){
            position = e.getX();
            parallel   = sb.getWidth();
            orthogonal = sb.getHeight();
        }
        
        double ratio = static_cast<double>(parallel -2*orthogonal)
            /static_cast<double>(sb._maximum -sb._minimum);
        double visible = sb._visible *ratio;
        if( visible < Scrollbar::INIT_MINIMUM_SIZE){
            visible = Scrollbar::INIT_MINIMUM_SIZE;
            ratio = (parallel -2*orthogonal -visible)
                /static_cast<double>(sb._maximum -sb._minimum -sb._visible);
        }
        sb.setValue(_initialValue +(position -_mousePosition)/ratio);
        
        if(prevalue != sb._value){
            if(sb._adjustmentListener){
                AdjustmentEvent e(
                    static_cast<int>(&sb),
                    AdjustmentEvent::TRACK,
                    sb._value
                );
                for(AdjustmentListener** l
                    = sb._adjustmentListener.get();
                    *l;
                    ++l)
                {
                    (**l).adjustmentValueChanged(e);
                }
            }
        }
        
        //Graphics g(sb._hwnd);
        //sb.update(g);
        sb.repaint();
    }
}
void Scrollbar::Listener::mouseMoved(MouseEvent &e){}
void Scrollbar::Listener::mouseWheelMoved(MouseWheelEvent& e)
{
    Scrollbar& sb = *static_cast<Scrollbar*>(e.getSource());
    int scroll = e.getWheelRotation() *e.getScrollAmount();
    sb.setValue(sb._value -scroll);
    
    if(sb._adjustmentListener){
        int type = scroll <0?
            AdjustmentEvent::UNIT_INCREMENT:
            AdjustmentEvent::UNIT_DECREMENT;
        AdjustmentEvent e(
            static_cast<int>(&sb),
            type,
            sb._value
        );
        for(AdjustmentListener** l
            = sb._adjustmentListener.get();
            *l;
            ++l)
        {
            (**l).adjustmentValueChanged(e);
        }
    }
    
    //Graphics g(sb._hwnd);
    //sb.update(g);
    sb.repaint();
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Scrollbar_cpp

