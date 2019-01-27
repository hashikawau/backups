


#ifndef __Windows_io_FileOutputStream
#define __Windows_io_FileOutputStream


#include "File.h"


//===========================================================
//===========================================================
class OutputStream
{
protected:
    HANDLE _hFile;
    
public:
    OutputStream();
    virtual ~OutputStream() =0;
    virtual void write(int b) throw(IOException) =0;
    virtual void close();
};
//===========================================================
//===========================================================
OutputStream::OutputStream(){}
OutputStream::~OutputStream(){}
void OutputStream::close()
{
    CloseHandle(_hFile);
}
//===========================================================
//===========================================================
class FileOutputStream: public OutputStream
{
protected:
public:
    FileOutputStream(const String& name, bool append =false);
    FileOutputStream(const File& file, bool append =false);
    virtual ~FileOutputStream();
    virtual void write(int b) throw(IOException);
    void write(char b[], int off, int len) throw(IOException);
};
//===========================================================
//===========================================================
FileOutputStream::FileOutputStream(const String& name, bool append)
{
    if(!File(name).exists()){ throw FileNotFoundException(); }
    int dwDesiredAccess = append?
        FILE_APPEND_DATA:
        GENERIC_WRITE;
    _hFile = CreateFile(
        name.toCharArray(),
        dwDesiredAccess,
        FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if(append){
        long lpDistanceToMoveHigh;
        SetFilePointer(
            _hFile,
            0,
            &lpDistanceToMoveHigh,
            FILE_END);
    }
}
FileOutputStream::FileOutputStream(const File& file, bool append)
{
    if(!file.exists()){ throw FileNotFoundException(); }
    int dwDesiredAccess = append?
        FILE_APPEND_DATA:
        GENERIC_WRITE;
    _hFile = CreateFile(
        file.getPath().toCharArray(),
        dwDesiredAccess,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if(append){
        long lpDistanceToMoveHigh;
        SetFilePointer(
            _hFile,
            0,
            &lpDistanceToMoveHigh,
            FILE_END);
    }
}
FileOutputStream::~FileOutputStream()
{
    /*
    LARGE_INTEGER li1, li2;
    li1.LowPart = SetFilePointer(
        _hFile,
        0,
        &li1.HighPart,
        FILE_CURRENT);
    
    li2.LowPart = GetFileSize(
        _hFile,
        static_cast<unsigned long*>(&li2.HighPart));
    
    if(li1.HighPart > li2.HighPart){
        SetEndOfFile(_hFile);
    }else
    if(li1.HighPart == li2.HighPart && li1.LowPart > li2.LowPart){
        SetEndOfFile(_hFile);
    }
    */
    CloseHandle(_hFile);
}
void FileOutputStream::write(int b) throw(IOException)
{
    char byte[1];
    byte[0] = static_cast<char>(0xFF &b);
    unsigned long int num;
    if(WriteFile(
        _hFile,
        byte,
        1,
        &num,
        NULL)){}
}
void FileOutputStream::write(char b[], int off, int len) throw(IOException)
{
    char *byte = b +off;
    unsigned long int num;
    if(WriteFile(
        _hFile,
        byte,
        len,
        &num,
        NULL)){}
/*
LARGE_INTEGER li1, li2;
debugDisplay << (int)
SetFilePointer(
    _hFile,
    0,
    &li1.HighPart,
    FILE_CURRENT);
*/
}
//===========================================================
//===========================================================



#endif //ifndef __Windows_io_FileOutputStream


