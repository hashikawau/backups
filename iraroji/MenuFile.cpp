



//#include "../windows/awt/Frame.h"
//#include "../windows/awt/Label.h"
//#include "../windows/awt/Button.h"
//#include "../windows/awt/Canvas.h"
//#include "../windows/awt/ScrollPane.h"
//#include "../windows/awt/TextField.h"
//#include "../windows/awt/FileDialog.h"
//#include "../windows/lang/String.h"
//#include "../windows/lang/Math.h"
//#include "../windows/lang/Number.h"
//#include "../windows/util/LinkedList.h"
//#include "../windows/awt/FileDialog_cpp.h"

#include "MenuFile.h"

void MenuFile::MenuOpen::Listener::actionPerformed(ActionEvent& e)
{
    MenuOpen& m
        = *static_cast<MenuOpen*>(e.getSource());
    MenuComponent* mc
        = dynamic_cast<MenuComponent*>(&m.getParent());
    MenuBar* mb
        = dynamic_cast<MenuBar*>(&mc->getParent());

    Frame* f
        = static_cast<Frame*>(&mb->getParent());

    FileDialog fd(*f, L"Open File");
    fd.setVisible(true);
    static_cast<IllustrationLogicSolver*>(f)->setFile(
        String(fd.getDirectory())
        +String(fd.getFile()));
}

