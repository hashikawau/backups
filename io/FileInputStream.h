


#ifndef __Windows_io_FileInputStream
#define __Windows_io_FileInputStream


#include "File.h"


//===========================================================
//===========================================================
class InputStream
{
protected:
    HANDLE _hFile;
public:
    InputStream();
    virtual ~InputStream() =0;
    virtual int read() throw(IOException) =0;
    virtual void close();
};
InputStream::InputStream(){}
InputStream::~InputStream(){}
void InputStream::close()
{
    CloseHandle(_hFile);
}
//===========================================================
//===========================================================
class FileInputStream: public InputStream
{
protected:
public:
    FileInputStream(const String& name);
    FileInputStream(const File& file);
    virtual ~FileInputStream();
    virtual int read() throw(IOException);
    int read(char b[], int off, int len) throw(IOException);
};
FileInputStream::FileInputStream(const String& name)
{
    if(!File(name).exists()){ throw FileNotFoundException(); }
    _hFile = CreateFile(
        name.toCharArray(),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
}
FileInputStream::FileInputStream(const File& file)
{
    if(!file.exists()){ throw FileNotFoundException(); }
    _hFile = CreateFile(
        file.getPath().toCharArray(),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
}
FileInputStream::~FileInputStream()
{
    CloseHandle(_hFile);
}
int FileInputStream::read() throw(IOException)
{
    char byte[1];
    byte[0] = 0xFF;
    unsigned long int num;
    if(ReadFile(
        _hFile,
        byte,
        1,
        &num,
        NULL)){
        return byte[0];
    }else{
        return -1;
    }
}
int FileInputStream::read(char b[], int off, int len) throw(IOException)
{
    char* byte = b +off;
    unsigned long int num;
    if(ReadFile(
        _hFile,
        byte,
        len,
        &num,
        NULL)){
        return num;
    }else{
        return -1;
    }
}
//===========================================================
//===========================================================



#endif //ifndef __Windows_io_FileInputStream


