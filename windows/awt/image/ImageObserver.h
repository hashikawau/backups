

#ifndef __Windows_awt_image_ImageObserver
#define __Windows_awt_image_ImageObserver


//===========================================================
//===========================================================
class Image;
//===========================================================
//===========================================================
class ImageObserver
{
public:
    static const int ABORT;
    static const int ALLBITS;
    //static const int ERROR;
    static const int FRAMEBITS;
    static const int HEIGHT;
    static const int PROPERTIES;
    static const int SOMEBITS;
    static const int WIDTH;
    
public:
    ImageObserver();
    virtual ~ImageObserver() =0;
    virtual bool imageUpdate(
        Image& img,
        int infoflags,
        int x,
        int y,
        int width,
        int height) =0;
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_image_ImageObserver

