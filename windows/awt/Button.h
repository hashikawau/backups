

#ifndef __Windows_awt_Button
#define __Windows_awt_Button


//===========================================================
//===========================================================
#include "Component.h"
#include "../lang/String.h"
#include "../cpp/PointerObject.h"
class Graphics;
class ActionListener;
//===========================================================
//===========================================================
class Button: public Component
{
private:
    class Listener;
    friend class Button::Listener;
    static Listener* _listener;
    static int _pressedButton;
    static int _enteredButton;
    
protected:
    String _label;
    PointerObject<ActionListener> _actionListener;
    
public:
    explicit Button(String& label =String(L""));
    virtual ~Button();
    virtual void paint(Graphics& g);
    
    void addActionListener(ActionListener& l);
    void removeActionListener(ActionListener& l);
    void setActionCommand(String& command);
    
    void setLabel(String& label);
    String getLabel();
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Button

