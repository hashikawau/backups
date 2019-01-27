

#ifndef __Windows_awt_TextComponent
#define __Windows_awt_TextComponent


//===========================================================
//===========================================================
#include "Component.h"
#include "../cpp/PointerObject.h"
class Graphics;
class TextListener;
class String;
class StringBuffer;
//===========================================================
//===========================================================
class TextComponent: public Component
{
private:
    class Listener;
    friend class Listener;
    static Listener* _listener;
    
    static const int CARET_WIDTH;
    
protected:
    PointerObject<StringBuffer> _text;
    PointerObject<TextListener> _textListener;
    
    int _selectionStart;
    int _selectionEnd;
    bool _isEditable;
    int _caretPosition;
    
    int _caretRowPosition;
    int _caretColumnPosition;
    int _caretHeight;
    int _rows;
    int _columns;
    void adjustCaretPosition(int position);
    void adjustCaretPosition(int row, int column);
    void insertText(
        int startRow,
        int startColumn,
        String& inserted);
    void deleteText(
        int startRow,
        int startColumn,
        int endRow,
        int endtColumn);
    void insertText(
        StringBuffer& source,
        int index,
        String& inserted);
    void deleteText(
        StringBuffer& source,
        int start,
        int end);
    void setCaretPosition(
        int row,
        int column);
    
public:
    TextComponent();
    virtual ~TextComponent();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
    void addTextListener(TextListener& l);
    void removeTextListener(TextListener& l);
    
    int getCaretPosition();
    virtual String getText();
    virtual String getSelectedText();
    int getSelectionEnd();
    int getSelectionStart();
    
    virtual void select(int selectionStart, int selectionEnd);
    virtual void selectAll();
    
    virtual void setCaretPosition(int position);
    virtual void setText(String& text);
    virtual void setSelectionEnd(int selectionEnd);
    virtual void setSelectionStart(int selectionStart);
    
    bool isEditable();
    void setEditable(bool b);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_TextComponent

