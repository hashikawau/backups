

#ifndef __Windows_cpp_MathGraphics
#define __Windows_cpp_MathGraphics


//#include "windows\cpp\MathFunction.h"

#include "windows\_windows.h"
#include "windows\lang\Math.h"
#include "windows\awt\Component.h"

#include "windows\util\LinkedList.h"


//===========================================================
//===========================================================
class MathGraphics
{
public:
    MathGraphics();
    ~MathGraphics();
    
    static PointerObject<Image> drawContents(
        const Component& comp,
        const double* vector,
        int size);
    static PointerObject<Image> drawContents(
        const Component& comp,
        const int* vector,
        int size);
};
MathGraphics::MathGraphics(){}
MathGraphics::~MathGraphics(){}
//===========================================================
//===========================================================
PointerObject<Image> MathGraphics::drawContents(
    const Component& comp,
    const double* vector,
    int size)
{
    String* number = new String[size];
    int maxlen = 0;
    for(int i=0; i< size; ++i){
        number[i] = String(vector[i]);
        int length = number[i].length();
        maxlen = length > maxlen?
            length:
            maxlen;
    }
    
    const FontMetrics& fm = comp.getGraphics().getFontMetrics();
    int width = fm.getWidth() *maxlen +4;
    int charHeight = fm.getHeight();
    int height = charHeight *size +4;
    
    PointerObject<Image> image = comp.createImage(width, height);
    const Graphics& graphics = image->getGraphics();
    
    graphics.setColor(Color(0xFFFFFF));
    graphics.fillRect(0, 0, width, height);
    graphics.setColor(Color(0x00));
    for(int i=0; i< size; ++i){
        //graphics.drawString(number[i], 2, charHeight *i +2);
    }
    
    return image;
}
PointerObject<Image> MathGraphics::drawContents(
    const Component& comp,
    const int* vector,
    int size)
{
    String* number = new String[size];
    int maxlen = 0;
    for(int i=0; i< size; ++i){
        number[i] = String(vector[i]);
        int length = number[i].length();
        maxlen = length > maxlen?
            length:
            maxlen;
    }
    
    const FontMetrics& fm = comp.getGraphics().getFontMetrics();
    int width = fm.getWidth() *maxlen +4;
    int charHeight = fm.getHeight();
    int height = charHeight *size +4;
    
    PointerObject<Image> image = comp.createImage(width, height);
    const Graphics& graphics = image->getGraphics();
    
    for(int i=0; i< size; ++i){
        graphics.drawString(number[i], 2, charHeight *i +2);
    }
    
    return image;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_cpp_MathGraphics


