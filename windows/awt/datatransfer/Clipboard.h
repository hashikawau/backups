

#ifndef __Windows_awt_datatransfer_Clipboard
#define __Windows_awt_datatransfer_Clipboard


//===========================================================
//===========================================================
#include <string>
//===========================================================
//===========================================================
template<class T> class PointerObject;
//===========================================================
//===========================================================
class DataFlavor
{
public:
    static DataFlavor stringFlavor; 
    
public:
    int _flavor;
    DataFlavor(int flavor);
    virtual ~DataFlavor();
};
//===========================================================
//===========================================================
class Transferable
{
public:
    Transferable();
    virtual ~Transferable() =0;
};
//===========================================================
//===========================================================
class StringSelection: public Transferable
{
private:
    friend class Clipboard;
    
    String _data;
    
public:
    StringSelection(const String& data);
    virtual ~StringSelection();
};
//===========================================================
//===========================================================
class Clipboard
{
private:
    HWND _hwnd;
    //static Transferable* 
public:
    Clipboard(HWND hwnd);
    ~Clipboard();
    void setContents(const StringSelection& contents);
    PointerObject<wchar_t> getData(const DataFlavor& flavor);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_datatransfer_Clipboard

