

#ifndef __Windows_awt_TextComponent_cpp
#define __Windows_awt_TextComponent_cpp


//===========================================================
//===========================================================
#include "TextComponent.h"
#include "Color.h"
#include "Component.h"
#include "Font.h"
#include "Graphics.h"
#include "event/ActionEvent.h"
#include "../lang/String.h"
#include "../lang/StringBuffer.h"
//===========================================================
//===========================================================
class TextComponent::Listener:
    public FocusListener,
    public KeyListener,
    public MouseListener,
    public MouseMotionListener
{
public:
    virtual ~Listener();
    virtual void focusGained(FocusEvent& e);
    virtual void focusLost(FocusEvent& e);
    virtual void keyPressed(KeyEvent& e);
    virtual void keyReleased(KeyEvent& e);
    virtual void keyTyped(KeyEvent& e);
    virtual void mouseClicked(MouseEvent& e);
    virtual void mouseEntered(MouseEvent& e);
    virtual void mouseExited(MouseEvent& e);
    virtual void mousePressed(MouseEvent& e);
    virtual void mouseReleased(MouseEvent& e);
    virtual void mouseDragged(MouseEvent& e);
    virtual void mouseMoved(MouseEvent& e);
};
//===========================================================
//===========================================================

//===========================================================
//===========================================================
TextComponent::Listener* TextComponent::_listener =0;
const int TextComponent::CARET_WIDTH =2;
//===========================================================
//===========================================================
TextComponent::Listener::~Listener(){}
void TextComponent::Listener::focusGained(FocusEvent& e)
{
    TextComponent* source = static_cast<TextComponent*>(e.getSource());
    CreateCaret(
        source->_hwnd,
        NULL,
        TextComponent::CARET_WIDTH,
        source->_caretHeight);
    ShowCaret(source->_hwnd);
    source->setCaretPosition(source->_caretPosition);
}
void TextComponent::Listener::focusLost(FocusEvent& e)
{
    //HideCaret(static_cast<TextComponent*>(e.getSource())->_hwnd);
    DestroyCaret();
    static_cast<TextComponent*>(e.getSource())->repaint();
}
void TextComponent::Listener::keyPressed(KeyEvent& e){}
void TextComponent::Listener::keyReleased(KeyEvent& e){}
void TextComponent::Listener::keyTyped(KeyEvent& e){}
void TextComponent::Listener::mouseClicked(MouseEvent& e){}
void TextComponent::Listener::mouseEntered(MouseEvent& e){}
void TextComponent::Listener::mouseExited(MouseEvent& e){}
void TextComponent::Listener::mousePressed(MouseEvent& e){}
void TextComponent::Listener::mouseReleased(MouseEvent& e){}
void TextComponent::Listener::mouseDragged(MouseEvent& e){}
void TextComponent::Listener::mouseMoved(MouseEvent& e){}
//===========================================================
//===========================================================
void TextComponent::adjustCaretPosition(int position)
{
    if(position >=0){
        int count =0;
        int countRows =0;
        int countColumns =0;
        for(StringBuffer** s
            = _text.get();
            *s;
            ++s)
        {
            int length = (**s).length();
            if(position <= count +length){
                countColumns = position - count;
                count = position;
                break;
            }else
            if(!*(s+1)){
                countColumns = length;
                count += length;
                break;
            }else
            {
                count += length +1;
                ++countRows;
            }
        }
        _caretPosition = count;// + countRows;
        _caretRowPosition = countRows;
        _caretColumnPosition = countColumns;
    }else{
        _caretPosition =0;
        _caretRowPosition =0;
        _caretColumnPosition =0;
    }
}
void TextComponent::adjustCaretPosition(int row, int column)
{
    
    /*const_cast<int>(row) = column >0?
        row:
        row -1;*/
    const_cast<int>(row) = row >0?
        row:
        0;
    const_cast<int>(column) = column >0?
        column:
        0;
    
    
    int count =0;
    int countRows =0;
    int countColumns =0;
    //String text("");
    for(StringBuffer** s
        = _text.get();
        *s;
        ++s)
    {
        int length = (**s).length();
        if(*(s+1)){
            if(countRows < row){
                count += length +1;
                ++countRows;
                continue;
            }
        }
        
        countColumns = column < length?
            column:
            length;
        break;
    }
    _caretPosition = count +countColumns;
    _caretRowPosition = countRows;
    _caretColumnPosition = countColumns;
    
}
//===========================================================
//===========================================================
void TextComponent::insertText(
    int startRow,
    int startColumn,
    String& inserted)
{
    PointerObject<StringBuffer> poInsertedSring;
    const wchar_t* offset = inserted.toCharArray();
    const wchar_t* start = offset;
    int columnCount =0;
    
    
    while(*offset){
        //if(*offset == L'\n' || *offset == L'\r'){
        if(*offset == L'\n'){
            
            poInsertedSring.addLast(
                new StringBuffer(
                    String(start, 0, columnCount)
                )
            );
            start = offset +1;
            columnCount =0;
            //_caretRowPosition += 1;
        }else
        if(static_cast<int>(*offset) >= 0x20){
            ++columnCount;
        }
        ++offset;
    }
    StringBuffer* lastInsertedString
        = new StringBuffer(String(start, 0, columnCount));
    poInsertedSring.addLast(lastInsertedString);
    //_caretColumnPosition += columnCount;
//debug+=String("columnCount  ")+String(columnCount)+String("\n");
    
    adjustCaretPosition(startRow, startColumn);
    StringBuffer** ppText = _text.get();
    StringBuffer** ppInsertedSring = poInsertedSring.get();
    int row = _caretRowPosition;
    int column = _caretColumnPosition;
    int length = ppText[row]->length();
    if(column < length){
        lastInsertedString->append(
            ppText[row]->substring(column));
        ppText[row]->delete_(column, length);
    }
    
    ppText[row]->insert(
        column,
        ppInsertedSring[0]->substring(0));
    for(int i=1; ppInsertedSring[i]; ++i){
        _text.add(ppInsertedSring[i], _caretRowPosition +i);
    }
    
    if(_textListener){
        TextEvent e(static_cast<int>(this));
        for(TextListener** l
            = _textListener.get();
            *l;
            ++l)
        {
            (**l).textValueChanged(e);
        }
    }
}
//===========================================================
//===========================================================
void TextComponent::deleteText(
    int startRow,
    int startColumn,
    int endRow,
    int endColumn)
{
    adjustCaretPosition(endRow, endColumn);
    int supRow = _caretRowPosition;
    int supColumn = _caretColumnPosition;
    
    adjustCaretPosition(startRow, startColumn);
    int infRow = _caretRowPosition;
    int infColumn = _caretColumnPosition;
    
    if((supRow == infRow) & (supColumn == infColumn)){ return; }
    if(supRow <= infRow){
        if((supRow == infRow) & (supColumn < infColumn)
            || (supRow < infRow))
        {
            int temp;
            temp = supRow;
            supRow = infRow;
            infRow = temp;
            
            temp = supColumn;
            supColumn = infColumn;
            infColumn = temp;
        }
    }
    
    StringBuffer** text = _text.get();
    for(int i= infRow; i<= supRow; ++i){
        int start = i==infRow?
            infColumn:
            0;
        int end = i==supRow?
            supColumn:
            text[i]->length();
        
        if(start < end){
            text[i]->delete_(start, end);
        }
    }
    
    if(_textListener){
        TextEvent e(static_cast<int>(this));
        for(TextListener** l
            = _textListener.get();
            *l;
            ++l)
        {
            (**l).textValueChanged(e);
        }
    }
}
//===========================================================
//===========================================================
void TextComponent::insertText(
    StringBuffer& source,
    int index,
    String& inserted)
{
    source.insert(index, inserted);
    
    if(_textListener){
        TextEvent e(static_cast<int>(this));
        for(TextListener** l
            = _textListener.get();
            *l;
            ++l)
        {
            (**l).textValueChanged(e);
        }
    }
}
void TextComponent::deleteText(
    StringBuffer& source,
    int start,
    int end)
{
    if(end -start >0){
        source.delete_(start, end);
    }
    
    if(_textListener){
        TextEvent e(static_cast<int>(this));
        for(TextListener** l
            = _textListener.get();
            *l;
            ++l)
        {
            (**l).textValueChanged(e);
        }
    }
}
//===========================================================
//===========================================================
void TextComponent::setCaretPosition(int row, int column)
{
    adjustCaretPosition(row, column);

    String text("");
    if(_text){
        StringBuffer** s = _text.get();
        text = s[_caretRowPosition]->substring(0, _caretColumnPosition);
    }
    
    //Graphics g(_hwnd);
    //FontMetrics fm = g.getFontMetrics();
    PointerObject<FontMetrics> fm = getFontMetrics(getFont());
    _caretHeight = fm->getHeight();
    int positionX = fm->stringWidth(text);
    int positionY = _caretRowPosition * _caretHeight;
    
    HideCaret(_hwnd);
    SetCaretPos(positionX, positionY);
    repaint();
    ShowCaret(_hwnd);
}
//===========================================================
//===========================================================
TextComponent::TextComponent()
{
    _rows = 0x7FFFFFFF;
    _columns = 0x7FFFFFFF;
    setCaretPosition(0);
    setEditable(true);
    
    if(!_listener){
        _listener = new Listener();
    }
    addFocusListener(*_listener);
    addKeyListener(*_listener);
    addMouseListener(*_listener);
    addMouseMotionListener(*_listener);
}
TextComponent::~TextComponent()
{
}
//===========================================================
//===========================================================
void TextComponent::update(Graphics& g)
{
    g.setColor(getBackground());
    g.fillRect(0, 0, getWidth(), getHeight());
    paint(g);
}
void TextComponent::paint(Graphics& g)
{
    if(_text){
        g.setColor(Color::black);
        int count =0;
        for(StringBuffer** s
            = _text.get();
            *s;
            ++s)
        {
            /*
            int length = string.length();
            short* number;
            number = static_cast<short*>(string.toCharArray());
            wchar_t* wc = new wchar_t[length*6 +1];
            for(int i=0; i< length; ++i)
            {
                wsprintfW(wc +6*i, L"0x%0.4X)", number[i]);
            }
            wc[length*6]='\0';
            ExtTextOutW(_hdc, x, y, ETO_CLIPPED, NULL, wc, length*6, NULL);
            */
            g.drawString((**s).substring(0), 0, _caretHeight * count);
            ++count;
        }
    }
}
//===========================================================
//===========================================================
void TextComponent::addTextListener(TextListener& l)
{
    _textListener.add(&l);
}
void TextComponent::removeTextListener(TextListener& l)
{
    _textListener.remove(&l);
}
//===========================================================
//===========================================================
int TextComponent::getCaretPosition()
{
    return _caretPosition;
}
void TextComponent::setCaretPosition(int position)
{
    adjustCaretPosition(position);

    String text("");
    if(_text){
        StringBuffer** s = _text.get();
        text = s[_caretRowPosition]->substring(0, _caretColumnPosition);
    }
    
    //Graphics g(_hwnd);
    PointerObject<FontMetrics> fm = getFontMetrics(getFont());
    _caretHeight = fm->getHeight();
    int positionX = fm->stringWidth(text);
    int positionY = _caretRowPosition * _caretHeight;
    
    HideCaret(_hwnd);
    SetCaretPos(positionX, positionY);
    repaint();
    ShowCaret(_hwnd);
}
//===========================================================
//===========================================================
String TextComponent::getSelectedText()
{
    return _text?
        String(_text->substring(_selectionStart, _selectionEnd)):
        String("");
}
void TextComponent::select(int selectionStart, int selectionEnd)
{
}
void TextComponent::selectAll()
{
}
//===========================================================
//===========================================================
int TextComponent::getSelectionEnd()
{
    return _selectionEnd;
}
void TextComponent::setSelectionEnd(int selectionEnd)
{
    _selectionEnd = selectionEnd;
}
//===========================================================
//===========================================================
int TextComponent::getSelectionStart()
{
    return _selectionStart;
}
void TextComponent::setSelectionStart(int selectionStart)
{
    _selectionStart = selectionStart;
}
//===========================================================
//===========================================================
bool TextComponent::isEditable()
{
    return _isEditable;
}
void TextComponent::setEditable(bool b)
{
    _isEditable = b;
    setBackground(b?
        Color::white:
        SystemColor::textInactiveText);
}
//===========================================================
//===========================================================
String TextComponent::getText()
{
    StringBuffer string;
    if(_text){
        //int count =0;
        for(StringBuffer** s
            = _text.get();
            *s;
            ++s)
        {
            //g.drawString((**s).substring(0), 0, _caretHeight * count);
            string += **s;
            if(*(s+1)){
                string += String("\n");
            }
            //++count;
        }
    }
    
    return string.substring(0);
    /*
    return _text?
        String(_text->substring(0)):
        String("");
    */
}
void TextComponent::setText(String& text)
{
    _text.clear();
    const wchar_t* offset = text.toCharArray();
    const wchar_t* start = offset;
    int columnCount =0;
    
    while(*offset){
        if(*offset == L'\n'){
            
            _text.addLast(
                new StringBuffer(
                    String(start, 0, columnCount)
                )
            );
            start = offset +1;
            columnCount =0;
        }else
        {
            ++columnCount;
        }
        ++offset;
//debug+=String("columnCount  ")+String(*offset)+String("\n");
    }
    
    _text.addLast(
        new StringBuffer(
            String(start, 0, columnCount)
        )
    );
    
    
    
    //_text.clear();
    //_text.addFirst(new StringBuffer());
    //StringBuffer** string = _text.get();
    //insertText(**string, 0, text);
    
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_TextComponent_cpp

