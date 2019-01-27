


#ifndef __Windows_io_File
#define __Windows_io_File


#include "windows\_windows.h"
#include "windows\lang\Exception.h"


//===========================================================
//===========================================================
class IOException: public Exception
{
public:
    IOException();
    virtual ~IOException();
};
IOException::IOException(){}
IOException::~IOException(){}
//===========================================================
//===========================================================
class FileNotFoundException: public IOException
{
public:
    FileNotFoundException();
    virtual ~FileNotFoundException();
};
FileNotFoundException::FileNotFoundException(){}
FileNotFoundException::~FileNotFoundException(){}
//===========================================================
//===========================================================
class File
{
private:
    //HANDLE _file;
    String _pathname;
    WIN32_FILE_ATTRIBUTE_DATA wfad;
    
public:
    explicit File(const String& pathname);
    //File(const String& parent, const String& child);
    ~File();
    operator HANDLE() const;
    
    const bool exists() const;
    const bool isDirectory() const;
    const bool isFile() const;
    const bool isHidden() const;
    const FILETIME lastModified() const;
    const unsigned int length() const;
    const bool createNewFile();
    const bool mkdir() const;
    const bool delete_() const;
    const String getPath() const;
    const String getName() const;
    const String getParent() const;
    
};
//===========================================================
//===========================================================
/*
File::operator HANDLE() const
{
    return _file;
}
*/
//===========================================================
//===========================================================
File::File(const String& pathname)
{
    if(!&pathname){ throw NullPointerException(); }
    
    _pathname = pathname;
    if(!GetFileAttributesEx(
        _pathname.toCharArray(),
        GetFileExInfoStandard,
        &wfad))
    {
        wfad.dwFileAttributes = 0;
    }
    //debugDisplay.setformat(DebugDisplay::BIN);
    //debugDisplay << (int)wfad.dwFileAttributes << String(L"    \n");
    /*
    WIN32_FIND_DATA wfd;
    _file = FindFirstFileW(
        _pathname.toCharArray(),
        &wfd);
    CloseHandle(_file);
    debugDisplay << String(wfd.cFileName) + String(L"    ");
    debugDisplay << String(wfd.cAlternateFileName) + String(L"    \n");
    */
}

File::~File()
{
    //CloseHandle(_file);
}
//===========================================================
//===========================================================
const bool File::exists() const
{
    if(wfad.dwFileAttributes)
    {
        return true;
    }
    return false;
}
const bool File::isDirectory() const
{
    if(wfad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return true;
    }
    return false;
}
const bool File::isFile() const
{
    if(
        wfad.dwFileAttributes &&
        !(wfad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
        return true;
    }
    return false;
}
const bool File::isHidden() const
{
    if(wfad.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
    {
        return true;
    }
    return false;
}
//===========================================================
//===========================================================
const FILETIME File::lastModified() const
{
    FILETIME ft;
    ft.dwLowDateTime = 0;
    ft.dwHighDateTime = 0;
    return isFile()?
        wfad.ftLastWriteTime:
        _FILETIME(ft);
}
//===========================================================
//===========================================================
const unsigned int File::length() const
{
    return isFile()?
        wfad.nFileSizeHigh * (MAXDWORD+1) + wfad.nFileSizeLow:
        0;
}
//===========================================================
//===========================================================
const bool File::createNewFile()
{
    if(exists() || _pathname.length() == 0){
        return false;
    }else
    if(CloseHandle(
        CreateFile(
            _pathname.toCharArray(),
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            CREATE_NEW,//CREATE_ALWAYS,// | OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL))){
        return true;
    }else{
        throw IOException();
        return false;
    }
}
const bool File::mkdir() const
{
    return CreateDirectory(
        _pathname.toCharArray(),
        NULL);
}
const bool File::delete_() const
{
    return isFile()?
        DeleteFile(_pathname.toCharArray()):
        isDirectory()?
            RemoveDirectory(_pathname.toCharArray()):
            false;
}
//===========================================================
//===========================================================
const String File::getName() const
{
    int index = _pathname.length();
    wchar_t* pathname = const_cast<wchar_t*>(_pathname.toCharArray());
    for( ; index>= 0 && pathname[index]!=L'\\'; --index){}
    return String(&pathname[index +1]);
}
const String File::getParent() const
{
    int index = _pathname.length();
    wchar_t* pathname = const_cast<wchar_t*>(_pathname.toCharArray());
    for( ; index>= 0 && pathname[index]!=L'\\'; --index){}
    return String(pathname, 0, index +1);
}
const String File::getPath() const
{
    return String(_pathname);
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_io_File

