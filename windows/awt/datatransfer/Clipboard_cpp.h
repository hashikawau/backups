

#ifndef __Windows_awt_datatransfer_Clipboard_cpp
#define __Windows_awt_datatransfer_Clipboard_cpp


//===========================================================
//===========================================================
#include "Clipboard.h"
#include "../../_windows.h"
#include "../../cpp/PointerObject.h"
#include "../../lang/String.h"
#include "../../cpp/PointerObject_cpp.h"
#include "../../lang/String_cpp.h"
//===========================================================
//===========================================================
DataFlavor DataFlavor::stringFlavor(CF_UNICODETEXT);
//===========================================================
//===========================================================
DataFlavor::DataFlavor(int flavor): _flavor(flavor){}
DataFlavor::~DataFlavor(){}
//===========================================================
//===========================================================
Transferable::Transferable(){}
Transferable::~Transferable(){}
//===========================================================
//===========================================================
StringSelection::StringSelection(const String& data):
    _data(const_cast<String&>(data))
{}
StringSelection::~StringSelection(){}
//===========================================================
//===========================================================
Clipboard::Clipboard(HWND hwnd): _hwnd(hwnd){}
Clipboard::~Clipboard(){}
//===========================================================
//===========================================================
void Clipboard::setContents(const StringSelection& contents)
{
    const wchar_t* const data = contents._data.toCharArray();
    if(
        data
        && OpenClipboard(_hwnd)
    ){
        EmptyClipboard();
        int size = (::strlen(data) +1) *sizeof(*data);
        HGLOBAL hg = GlobalAlloc(GHND | GMEM_SHARE , size);
        wchar_t* c = static_cast<wchar_t*>(GlobalLock(hg));
        ::strcpy(c , data);
        GlobalUnlock(hg);
        
        SetClipboardData(CF_UNICODETEXT , hg);
        CloseClipboard();
    }
}
PointerObject<wchar_t> Clipboard::getData(const DataFlavor& flavor)
{
    wchar_t* data =0;
    if(
        (IsClipboardFormatAvailable(flavor._flavor))
        && OpenClipboard(_hwnd)
    ){
        HGLOBAL hg = GetClipboardData(flavor._flavor);
        int size = GlobalSize(hg);
        data = new wchar_t[size +1];
        wchar_t* c = static_cast<wchar_t*>(GlobalLock(hg));
        for(int i=0; i< size; ++i)
        {
            data[i] = c[i];
        }
        GlobalUnlock(hg);
        CloseClipboard();
        data[size] = 0;
    }
    
    return PointerObject<wchar_t>(data);
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_datatransfer_Clipboard_cpp

