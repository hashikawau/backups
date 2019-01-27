

#ifndef __Windows_awt_FileDialog_cpp
#define __Windows_awt_FileDialog_cpp


//===========================================================
//===========================================================
#include "FileDialog.h"
#include "../_windows.h"
#include "Frame.h"
#include "FileDialog.h"
#include "../lang/String.h"
//===========================================================
//===========================================================
const int FileDialog::SAVE = 1;
const int FileDialog::LOAD = 0;
//===========================================================
//===========================================================
FileDialog::FileDialog(Frame& parent, String& title, int mode )
{
    _directory = String(L"");
    _file = String(L"");
    _mode = mode;
    _str[0] = L'\0';
    //ZeroMemory(&_ofn, sizeof(_ofn));
    _ofn.lStructSize       = sizeof(_ofn);
    _ofn.hwndOwner         = parent._hwnd;
    _ofn.hInstance         = NULL;
    _ofn.lpstrFilter       = L"All files (*.*)\0*.*\0"
                             L"Text files (*.txt)\0*.txt\0\0";
    _ofn.lpstrCustomFilter = NULL;
    _ofn.nMaxCustFilter    = 40;
    _ofn.nFilterIndex      = 0;
    _ofn.lpstrFile         = _str;
    _ofn.nMaxFile          = MAX_PATH;
    _ofn.lpstrFileTitle    = NULL;
    _ofn.nMaxFileTitle     = MAX_PATH;
    _ofn.lpstrInitialDir   = NULL;
    _ofn.lpstrTitle        = title.toCharArray();
    _ofn.Flags             = 0//OFN_ALLOWMULTISELECT
                           | OFN_CREATEPROMPT
                           //| OFN_EXPLORER
                           | OFN_OVERWRITEPROMPT
                           | OFN_LONGNAMES;
    _ofn.nFileOffset       = 0;    //return value
    _ofn.nFileExtension    = 0;    //return value
    _ofn.lpstrDefExt       = NULL;
    _ofn.lCustData         = 0;
    _ofn.lpfnHook          = NULL;
    _ofn.lpTemplateName    = NULL;
}
void FileDialog::setVisible(bool b)
{
    if(!b){ return; }
    
    if(_mode == FileDialog::SAVE)
    {
        if(GetSaveFileNameW(&_ofn))
        {
            _directory = String(_str, 0, _ofn.nFileOffset);
            _file = String(_str, _ofn.nFileOffset, String(_str).length() -_ofn.nFileOffset);
        }
    }
    else    //if(_mode == FileDialog::LOAD)
    {
        if(GetOpenFileNameW(&_ofn))
        {
            _directory = String(_str, 0, _ofn.nFileOffset);
            _file = String(_str, _ofn.nFileOffset, String(_str).length() -_ofn.nFileOffset);
        }
    }
}
FileDialog::~FileDialog()
{
}
//===========================================================
//===========================================================
String& FileDialog::getDirectory()
{
    return _directory;
}
String& FileDialog::getFile()
{
    return _file;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_FileDialog_cpp

