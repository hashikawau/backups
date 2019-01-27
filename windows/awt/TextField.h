

#ifndef __Windows_awt_TextField
#define __Windows_awt_TextField


//===========================================================
//===========================================================
#include "TextComponent.h"
#include "../cpp/PointerObject.h"
class String;
class ActionListener;
//===========================================================
//===========================================================
class TextField: public TextComponent
{
private:
    static class TextFieldListener;
    /*
    class Listener: public KeyListener
    {
    public:
        virtual ~Listener();
        virtual void keyPressed(KeyEvent& e);
        virtual void keyReleased(KeyEvent& e);
        virtual void keyTyped(KeyEvent& e);
    };
    */
    friend class TextFieldListener;
    
    static TextFieldListener* _listener;
    void constructor(String& text, int columns);
    
protected:
    PointerObject<ActionListener> _actionListener;
    
public:
    TextField();
    explicit TextField(int columns);
    explicit TextField(String& text);
    TextField(String& text, int columns);
    virtual ~TextField();
    //virtual void paint(Graphics& g);
    //virtual void setText(const String& text);
    
    void addActionListener(ActionListener& l);
    void removeActionListener(ActionListener& l);
    int getColumns();
    void setColumns(int columns);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_TextField

