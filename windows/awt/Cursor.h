

#ifndef __Windows_awt_Cursor
#define __Windows_awt_Cursor


//===========================================================
//===========================================================
class Cursor
{
public:
    static const int CUSTOM_CURSOR;
    static const int DEFAULT_CURSOR;
    static const int CROSSHAIR_CURSOR;
    static const int TEXT_CURSOR;
    static const int WAIT_CURSOR;
    static const int SW_RESIZE_CURSOR;
    static const int SE_RESIZE_CURSOR;
    static const int NW_RESIZE_CURSOR;
    static const int NE_RESIZE_CURSOR;
    static const int N_RESIZE_CURSOR;
    static const int S_RESIZE_CURSOR;
    static const int W_RESIZE_CURSOR;
    static const int E_RESIZE_CURSOR;
    static const int HAND_CURSOR;
    static const int MOVE_CURSOR;
    
private:
    int _type;
    HCURSOR _hcursor;
    //friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    friend class Component;
    
public:
    Cursor(int type);
    virtual ~Cursor();
    int getType();
};
//===========================================================
//===========================================================
const int Cursor::CUSTOM_CURSOR    =-1;
const int Cursor::DEFAULT_CURSOR   = 0;
const int Cursor::CROSSHAIR_CURSOR = 1;
const int Cursor::TEXT_CURSOR      = 2;
const int Cursor::WAIT_CURSOR      = 3;
const int Cursor::SW_RESIZE_CURSOR = 4;
const int Cursor::SE_RESIZE_CURSOR = 5;
const int Cursor::NW_RESIZE_CURSOR = 6;
const int Cursor::NE_RESIZE_CURSOR = 7;
const int Cursor::N_RESIZE_CURSOR  = 8;
const int Cursor::S_RESIZE_CURSOR  = 9;
const int Cursor::W_RESIZE_CURSOR  =10;
const int Cursor::E_RESIZE_CURSOR  =11;
const int Cursor::HAND_CURSOR      =12;
const int Cursor::MOVE_CURSOR      =13;
//===========================================================
//===========================================================
Cursor::Cursor(int type): _type(type)
{
    switch(_type){
        case Cursor::CUSTOM_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_NO);
            //SetCursor(LoadCursor(NULL, IDC_NO));
            break;
        
        case Cursor::DEFAULT_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_ARROW);
            //SetCursor(LoadCursor(NULL, IDC_ARROW));
            break;
        
        case Cursor::CROSSHAIR_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_CROSS);
            //SetCursor(LoadCursor(NULL, IDC_CROSS));
            break;
        
        case Cursor::TEXT_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_IBEAM);
            //SetCursor(LoadCursor(NULL, IDC_IBEAM));
            break;
        
        case Cursor::WAIT_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_WAIT);
            //SetCursor(LoadCursor(NULL, IDC_WAIT));
            break;
        
        case Cursor::SW_RESIZE_CURSOR:
        case Cursor::NE_RESIZE_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_SIZENESW);
            //SetCursor(LoadCursor(NULL, IDC_SIZENESW));
            break;
        
        case Cursor::SE_RESIZE_CURSOR:
        case Cursor::NW_RESIZE_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_SIZENWSE);
            //SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
            break;
        
        case Cursor::N_RESIZE_CURSOR:
        case Cursor::S_RESIZE_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_SIZENS);
            //SetCursor(LoadCursor(NULL, IDC_SIZENS));
            break;
        
        case Cursor::W_RESIZE_CURSOR:
        case Cursor::E_RESIZE_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_SIZEWE);
            //SetCursor(LoadCursor(NULL, IDC_SIZEWE));
            break;
        
        case Cursor::HAND_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_APPSTARTING);
            //SetCursor(LoadCursor(NULL, IDC_APPSTARTING));
            break;
        
        case Cursor::MOVE_CURSOR:
            _hcursor = LoadCursor(NULL, IDC_SIZEALL);
            //SetCursor(LoadCursor(NULL, IDC_SIZEALL));
            break;
        
        default:
            _hcursor = 0;
            break;
    }
}
Cursor::~Cursor()
{
    DestroyCursor(_hcursor);
}
//===========================================================
//===========================================================
int Cursor::getType()
{
    return _type;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Cursor

