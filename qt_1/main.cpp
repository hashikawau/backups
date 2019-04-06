#include "qt_1.h"

#include <QtGui>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt_1 w;
    w.show();
    return a.exec();
}
