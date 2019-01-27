

#ifndef __Windows_awt_TextArea
#define __Windows_awt_TextArea


//===========================================================
//===========================================================
#include "TextComponent.h"
class String;
class Graphics;
//===========================================================
//===========================================================
class TextArea: public TextComponent
{
private:
    class TextAreaListener;
    friend class TextAreaListener;
    static TextAreaListener* _listener;
    
    int _minimumWidth;
    int _minimumHeight;
    
    void constructor(String& text, int rows, int columns);
    
protected:
    
public:
    TextArea();
    TextArea(int rows, int columns);
    explicit TextArea(String& text);
    TextArea(String& text, int rows, int columns);
    virtual ~TextArea();
    virtual void paint(Graphics& g);
    //virtual void update(Graphics& g){ paint(g); }
    //virtual const String getText();
    virtual void setText(String& text);
    
    void append(String& string);
    void insert(String& string, int position);
    void replaceRange(String& string, int start, int end);
    int getColumns();
    int getRows();
    void setColumns(int columns);
    void setRows(int rows);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_TextArea

