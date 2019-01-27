

#ifndef __Windows_awt_FileDialog
#define __Windows_awt_FileDialog


//===========================================================
//===========================================================
#include "Dialog.h"
#include "../_windows.h"
#include "../lang/String.h"
class Frame;
//===========================================================
//===========================================================
class FileDialog//: public Dialog
{
private:
    String _directory;
    String _file;
    OPENFILENAMEW _ofn;
    int _mode;
    wchar_t _str[MAX_PATH];
    
public:
    static const int SAVE;
    static const int LOAD;
    
    FileDialog(Frame& parent, String& title, int mode =LOAD);
    FileDialog(FileDialog& fd);
    FileDialog& operator=(const FileDialog&);
    virtual ~FileDialog();
    String& getDirectory();
    String& getFile();
    void setVisible(bool b);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_FileDialog

