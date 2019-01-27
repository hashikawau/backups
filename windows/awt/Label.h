

#ifndef __Windows_awt_Label
#define __Windows_awt_Label


//===========================================================
//===========================================================
#include "Component.h"
#include "../lang/String.h"
class Graphics;
//===========================================================
//===========================================================
class Label: public Component
{
private:
protected:
    String _label;
    
public:
    explicit Label(String& label =String(L""));
    virtual ~Label();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
    
    void setText(String& label);
    String getText();
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Label

