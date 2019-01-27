

#ifndef __Windows_awt_TextArea_cpp
#define __Windows_awt_TextArea_cpp


//===========================================================
//===========================================================
#include "TextArea.h"
#include "Font.h"
#include "event/ActionEvent.h"
#include "../lang/StringBuffer.h"
//===========================================================
//===========================================================
class TextArea::TextAreaListener: public KeyListener
{
public:
    virtual ~TextAreaListener();
    virtual void keyPressed(KeyEvent& e);
    virtual void keyReleased(KeyEvent& e);
    virtual void keyTyped(KeyEvent& e);
};
//===========================================================
//===========================================================
TextArea::TextAreaListener* TextArea::_listener =0;
//===========================================================
//===========================================================
void TextArea::constructor(String& text, int rows, int columns)
{
    setText(text);
    setRows(rows);
    setColumns(columns);
    setSize(_minimumWidth, _minimumHeight);
    if(!_listener){
        _listener = new TextAreaListener();
    }
    addKeyListener(*_listener);
}
//===========================================================
//===========================================================
TextArea::TextArea()
{
    constructor(String(""), 0, 0);
}
TextArea::TextArea(int rows, int columns)
{
    constructor(String(""), rows, columns);
}
TextArea::TextArea(String& text)
{
    constructor(text, 0, 0);
}
TextArea::TextArea(String& text, int rows, int columns)
{
    constructor(text, rows, columns);
}
TextArea::~TextArea()
{
}
//===========================================================
//===========================================================
void TextArea::paint(Graphics &g)
{
    TextComponent::paint(g);
    //g.drawString(_text->substring(0), 2, 2, getWidth(), getHeight());
}
//===========================================================
//===========================================================
//const String TextArea::getText()
//{
//    return TextComponent::getText();
//}
void TextArea::setText(String& text)
{
    _text.clear();
    _minimumWidth =0;
    _minimumHeight =0;
    TextComponent::setText(text);
    /*
    int maxStringWidth = 0;
    int count = 0;
    int lineCount = 1;
    bool isNewLine = false;
    
    Graphics g(_hwnd);
    FontMetrics fm = g.getFontMetrics();
    wchar_t* offset = _label.toCharArray();
    
    for(int i=0; _label[i] != L'\0'; ++i)
    {
        if(isNewLine)
        {
            ++lineCount;
            isNewLine = false;
            offset = &_label[i];
        }
        
        if(_label[i] == L'\n')
        {
            isNewLine = true;
            int stringwidth = fm.stringWidth(String(offset, 0, count));
            maxStringWidth = (maxStringWidth > stringwidth)? maxStringWidth: stringwidth;
            count = 0;
        }
        else
        {
            ++count;
        }
    }
    int stringwidth = fm.stringWidth(String(offset, 0, count));
    maxStringWidth = (maxStringWidth > stringwidth)? maxStringWidth: stringwidth;
    */
}
//===========================================================
//===========================================================    
void TextArea::append(String& string)
{
    TextComponent::insertText(0x7FFFFFFF, 0x7FFFFFFF, string);
}
void TextArea::insert(String& string, int position)
{
    TextComponent::adjustCaretPosition(position);
    TextComponent::insertText(_caretRowPosition, _caretColumnPosition, string);
}
void TextArea::replaceRange(String& string, int start, int end)
{
    TextComponent::adjustCaretPosition(end);
    int endRow = _caretRowPosition;
    int endColumn = _caretColumnPosition;
    TextComponent::adjustCaretPosition(start);
    TextComponent::deleteText(
        _caretRowPosition,
        _caretColumnPosition,
        endRow,
        endColumn);
    TextComponent::insertText(_caretRowPosition, _caretColumnPosition, string);
}
//===========================================================
//===========================================================
int TextArea::getColumns()
{
    return _columns;
}
int TextArea::getRows()
{
    return _rows;
}
void TextArea::setColumns(int columns)
{
    _columns = columns;
    //Graphics g(_hwnd);
    //PointerObject<FontMetrics> fm = getFontMetrics(getFont());
    _minimumWidth = getFontMetrics(getFont())->getWidth() * _columns;
}
void TextArea::setRows(int rows)
{
    _rows = rows;
    //Graphics g(_hwnd);
    //FontMetrics fm = g.getFontMetrics();
    _minimumHeight = getFontMetrics(getFont())->getHeight() * _rows;
}
//===========================================================
//===========================================================
TextArea::TextAreaListener::~TextAreaListener(){}
void TextArea::TextAreaListener::keyPressed(KeyEvent& e)
{
    TextArea* source = static_cast<TextArea*>(e.getSource());
    if(!source->_isEditable){ return; }
    
    wchar_t key = e.getKeyChar();
    int row = source->_caretRowPosition;
    int column = source->_caretColumnPosition;
    
    switch(key)
    {
        case VK_LEFT:
            row += column <=0?
                -1:
                0;
            column = column >0?
                column -1:
                row <0?
                    column:
                    0x7FFFFFFF;
            source->setCaretPosition(row, column);
            break;
            
        case VK_UP:
            source->setCaretPosition(
                source->_caretRowPosition -1,
                source->_caretColumnPosition);
            break;
            
        case VK_RIGHT:
            StringBuffer** s = source->_text.get();
            int length = s[row]->length();
            row += column >=length?
                1:
                0;
            column = column <length?
                column +1:
                !s[row]?
                    column:
                    0;
            source->setCaretPosition(row, column);
            break;
            
        case VK_DOWN:
            source->setCaretPosition(
                source->_caretRowPosition +1,
                source->_caretColumnPosition);
            break;
            
        case VK_BACK:
            if(source->_text)
            {
                StringBuffer** s = source->_text.get();
                
                if(column <=0){
                    if(row >0){
                        column = s[row -1]->length();
                        source->insertText(
                            row -1,
                            column,
                            s[row]->substring(0));
                        source->_text.remove(s[row]);
                        
                        row += -1;
                    }
                }else
                {
                    //source->deleteText(*s[row], column -1, column);
                    source->deleteText(row, column -1, row, column);
                    column += -1;
                }
                source->setCaretPosition(row, column);
            }
            break;
            
        case VK_DELETE:
            if(source->_text)
            {
                StringBuffer** s = source->_text.get();
                int length = s[row]->length();
                
                if(column >=length){
                    if(s[row +1]){
                        source->insertText(
                            row,
                            column,
                            s[row +1]->substring(0));
                        source->_text.remove(s[row +1]);
                    }
                }else
                {
                    //source->deleteText(*s[row], column, column +1);
                    source->deleteText(row, column, row, column +1);
                }
                source->setCaretPosition(row, column);
                
//debug+=String("row  ")+String(source->_caretRowPosition)+String("  ");
//debug+=String("column  ")+String(source->_caretColumnPosition)+String("\n");
            }
            break;
            
        default:
            break;
    }
}
void TextArea::TextAreaListener::keyReleased(KeyEvent& e)
{
}
void TextArea::TextAreaListener::keyTyped(KeyEvent& e)
{
    TextArea* source = static_cast<TextArea*>(e.getSource());
    if(!source->_isEditable){ return; }
    
    wchar_t key = e.getKeyChar();
    int row = source->_caretRowPosition;
    int column = source->_caretColumnPosition;
    
    switch(key)
    {
        case (wchar_t)0x0008:    //BackSpace
            break;
            
        case (wchar_t)0x000D:    //Enter
            if(source->_text)
            {
                source->insertText(
                    row,
                    column,
                    String("\n"));
                source->setCaretPosition(row +1, 0);
            }
            break;
            
        default:
            if(e.isControlDown()){ break; }
            if(source->_text)
            {
                source->insertText(
                    row,
                    column,
                    String(key));
                source->setCaretPosition(row, column +1);
                //source->setCaretPosition(source->_caretRowPosition, source->_caretColumnPosition);
            }
            break;
    }
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_TextArea_cpp

