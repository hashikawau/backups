


#ifndef __Windows_io_FileWriter
#define __Windows_io_FileWriter


#include "File.h"

//===========================================================
//===========================================================
class FileWriter
{
private:
    File _file;
    String _pathname;
    //String _parent;
    //String _child;
    
public:
    FileWriter(const String& fileName, const bool append =false);
    //explicit FileWriter(const File& file);
    //File(const String& parent, const String& child);
    ~FileWriter();
};
//===========================================================
//===========================================================
FileWriter::FileWriter(const String& fileName): _file(fileName)
{
    if(!&fileName){ throw IOException(); }
}
/*
FileWriter::FileWriter(const File& file)
{
    if(!&pathname){ throw NullPointerException(); }
}
*/
FileWriter::~FileWriter()
{
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_io_FileWriter


