

#ifndef __Windows_awt_Button_cpp
#define __Windows_awt_Button_cpp


//===========================================================
//===========================================================
#include "Button.h"
#include "Color.h"
#include "Component.h"
#include "Font.h"
#include "Graphics.h"
#include "event/ActionEvent.h"
#include "../lang/Math.h"
#include "../cpp/PointerObject.h"
//===========================================================
//===========================================================
class Button::Listener: public MouseListener
{
public:
    virtual void mouseClicked(MouseEvent& e);
    virtual void mouseEntered(MouseEvent& e);
    virtual void mouseExited(MouseEvent& e);
    virtual void mousePressed(MouseEvent& e);
    virtual void mouseReleased(MouseEvent& e);
};
//===========================================================
//===========================================================

//===========================================================
//===========================================================
static Button::Listener* Button::_listener =0;
static int Button::_pressedButton =0;
static int Button::_enteredButton =0;
//===========================================================
//===========================================================
Button::Button(String& label)
{
    setBackground(SystemColor::activeCaptionBorder);
    setLabel(label);
    setActionCommand(label);
    
    if(!_listener){
        _listener = new Listener();
    }
    addMouseListener(*_listener);
}
Button::~Button(){}
//===========================================================
//===========================================================
void Button::paint(Graphics& g)
{
    int width  = getWidth();
    int height = getHeight();
    
    PointerObject<FontMetrics> fm = g.getFontMetrics();
    //FontMetrics fm = g.getFontMetrics();
    int x = (getWidth() - fm->stringWidth(_label)) /2;
    int y = (getHeight() - fm->getHeight()) /2;
    
    g.setColor(getBackground());
    g.fillRect(0, 0, width, height);
    
    if(_pressedButton == static_cast<int>(this)
        && _enteredButton == _pressedButton)
    {
        g.setColor(SystemColor::inactiveCaption);
        g.drawRect(0, 0, width, height);
    }else{
        g.setColor(SystemColor::window);
        g.fillRect(0, 0, width, 1);
        g.fillRect(0, 0, 1, height);
        g.setColor(SystemColor::inactiveCaption);
        g.fillRect(0, height -2, width, 2);
        g.fillRect(width -2, 0, 2, height);
    }
    
    g.setColor(Color::black);
    g.drawString(_label, x, y);
}
//===========================================================
//===========================================================
void Button::addActionListener(ActionListener& l)
{
    _actionListener.add(&l);
}
void Button::removeActionListener(ActionListener& l)
{
    _actionListener.remove(&l);
}
//===========================================================
//===========================================================
void Button::setActionCommand(String& command)
{
    SetWindowTextW(_hwnd, command.toCharArray());
}
void Button::setLabel(String& label)
{
    _label = label;
    
    //Graphics g(_hwnd);
    PointerObject<FontMetrics> fm = getFontMetrics(getFont());
    
    int width  = Math::max(getWidth(), fm->stringWidth(_label));
    int height = Math::max(getHeight(), fm->getHeight());
    setSize(width, height);
}
String Button::getLabel()
{
    return String(_label);
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
void Button::Listener::mouseClicked(MouseEvent& e)
{
    int sourceAdress = e.getSource();
    Button* source = static_cast<Button*>(sourceAdress);
    
    if(source->_actionListener
        && Button::_pressedButton == sourceAdress)
    {
        ActionEvent e(sourceAdress);
        for(ActionListener** l
            = source->_actionListener.get();
            *l;
            ++l)
        {
            (**l).actionPerformed(e);
        }
    }
    source->repaint();
}
void Button::Listener::mouseEntered(MouseEvent& e)
{
    int sourceAdress
        = Button::_enteredButton
        = e.getSource();
    Button* source = static_cast<Button*>(sourceAdress);
    source->repaint();
}
void Button::Listener::mouseExited(MouseEvent& e)
{
    int sourceAdress = e.getSource();
    Button* source = static_cast<Button*>(sourceAdress);
    _enteredButton = 0;
    source->repaint();
}
void Button::Listener::mousePressed(MouseEvent& e)
{
    int sourceAdress
        = Button::_pressedButton
        = e.getSource();
    Button* source = static_cast<Button*>(sourceAdress);
    source->repaint();
}
void Button::Listener::mouseReleased(MouseEvent& e)
{
    int sourceAdress = e.getSource();
    Button* source = static_cast<Button*>(sourceAdress);
    Button::_pressedButton = 0;
    source->repaint();
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Button_cpp

