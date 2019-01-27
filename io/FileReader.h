


#ifndef __Windows_io_FileReader
#define __Windows_io_FileReader


//#include "InputStream.h"
#include "FileInputStream.h"


//===========================================================
//===========================================================
class Reader
{
protected:
    Reader();
    
public:
    virtual ~Reader() =0;
    virtual int read(wchar_t cbuf[], int off, int len) throw(IOException) =0;
    virtual void close() =0;
};
Reader::~Reader(){}
//===========================================================
//===========================================================
class InputStreamReader: public Reader
{
protected:
public:
    InputStreamReaderReader();
    virtual ~InputStreamReader();
};
InputStreamReader::InputStreamReaderReader(){}
InputStreamReader::~InputStreamReader(){}
//===========================================================
//===========================================================
class FileReader: public InputStreamReader
{
private:
    //HANDLE _file;
    String _pathname;
    //String _parent;
    //String _child;
    
public:
    explicit FileReader(const File& file);
    //File(const String& parent, const String& child);
    virtual ~FileReader();
};
//===========================================================
//===========================================================
FileReader::FileReader(const File& file)
{
    if(!&file){ throw NullPointerException(); }
    if(!file.exists()){ throw FileNotFoundException(); }
    _pathname = file.getPath();
}

FileReader::~FileReader()
{
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_io_FileReader


