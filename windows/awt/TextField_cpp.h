

#ifndef __Windows_awt_TextField_cpp
#define __Windows_awt_TextField_cpp


//===========================================================
//===========================================================
#include "TextField.h"
#include "Font.h"
#include "event/ActionEvent.h"
#include "../lang/String.h"
#include "../cpp/PointerObject.h"
//===========================================================
//===========================================================
class TextField::TextFieldListener: public KeyListener
{
public:
    virtual ~TextFieldListener();
    virtual void keyPressed(KeyEvent& e);
    virtual void keyReleased(KeyEvent& e);
    virtual void keyTyped(KeyEvent& e);
};
//===========================================================
//===========================================================
TextField::TextFieldListener* TextField::_listener = 0;
//===========================================================
//===========================================================
TextField::TextFieldListener::~TextFieldListener(){}
void TextField::TextFieldListener::keyPressed(KeyEvent& e)
{
    TextField* source = static_cast<TextField*>(e.getSource());
    //source = dynamic_cast<TextComponent*>(source);
    if(!source->_isEditable){ return; }
    
    wchar_t key = e.getKeyChar();
    
    switch(key)
    {
        case VK_LEFT:
            source->setCaretPosition(source->_caretPosition -1);
            break;
            
        case VK_RIGHT:
            source->setCaretPosition(source->_caretPosition +1);
            break;
            
        case VK_BACK:
            if(source->_caretPosition > 0
                && source->_text)
            {
                //source->_text->deleteCharAt(source->_caretPosition -1);
                StringBuffer* str = *source->_text.get();
                source->deleteText(
                    *str,
                    source->_caretPosition -1,
                    source->_caretPosition);
                /*
                source->setText(
                    str->deleteCharAt(
                        source->_caretPosition -1
                    ).substring(0)
                );
                */
                source->setCaretPosition(source->_caretPosition -1);
                //source->repaint();
            }
            break;
            
        case VK_DELETE:
            if(source->_caretPosition < source->getText().length()
                && source->_text)
            {
                //source->_text->deleteCharAt(source->_caretPosition);
                StringBuffer* str = *source->_text.get();
                source->deleteText(
                    *str,
                    source->_caretPosition,
                    source->_caretPosition +1);
                /*
                source->setText(
                    str->deleteCharAt(
                        source->_caretPosition
                    ).substring(0)
                );
                */
                source->setCaretPosition(source->_caretPosition);
                //source->repaint();
            }
            break;
            
        default:
            break;
    }
    source->repaint();
}
void TextField::TextFieldListener::keyReleased(KeyEvent& e){}
void TextField::TextFieldListener::keyTyped(KeyEvent& e)
{
    TextField* source = static_cast<TextField*>(e.getSource());
    if(!source->_isEditable){ return; }
    
    wchar_t key = e.getKeyChar();
    
    switch(key)
    {
        case (wchar_t)0x0008:    //BackSpace
            break;
            
        case (wchar_t)0x000D:    //Enter
            if(source->_actionListener)
            {
                ActionEvent e(static_cast<int>(source));
                source->_actionListener->actionPerformed(e);
            }
            break;
            
        default:
            if(source->_text)
            {
                //source->_text->insert(source->_caretPosition, String(key));
                StringBuffer* str = *source->_text.get();
                
                source->insertText(
                    *str,
                    source->_caretPosition,
                    String(key));
                /*
                source->setText(
                    str->insert(
                        source->_caretPosition,
                        String(key)
                    ).substring(0)
                );
                */
                source->setCaretPosition(source->getCaretPosition() +1);
            }
            break;
    }
    source->repaint();
}
//===========================================================
//===========================================================
void TextField::constructor(String& text, int columns)
{
    _rows = 1;
    setText(text);
    setColumns(columns);
    if(!_listener){
        _listener = new TextFieldListener();
    }
    addKeyListener(*_listener);
}
//===========================================================
//===========================================================
TextField::TextField()
{
    constructor(String(""), 1);
}
TextField::TextField(int columns)
{
    constructor(String(""), columns);
}
TextField::TextField(String& text)
{
    constructor(text, text.length());
}
TextField::TextField(String& text, int columns)
{
    constructor(text, columns);
}
TextField::~TextField()
{
}
//===========================================================
//===========================================================
//void TextField::paint(Graphics &g)
//{
//    TextComponent::paint(g);
//}
void TextField::addActionListener(ActionListener& l)
{
    _actionListener.add(&l);
}
void TextField::removeActionListener(ActionListener& l)
{
    _actionListener.remove(&l);
}
//===========================================================
//===========================================================
int TextField::getColumns()
{
    return _columns;
}
void TextField::setColumns(int columns)
{
    _columns = columns?
        columns:
        1;
    
    //Graphics g(_hwnd);
    //FontMetrics fm = g.getFontMetrics();
    PointerObject<FontMetrics> fm = getFontMetrics(getFont());
    int width = _columns * fm->getWidth();
    int height = fm->getHeight();
    setSize(width, height);
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_TextField_cpp

