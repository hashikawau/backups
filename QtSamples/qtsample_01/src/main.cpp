/*
 *
 */

#include <QtWidgets/QApplication>
#include <QtWidgets/QSplashScreen>

#include "MainWindow.h"
#include <windows.h>


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QSplashScreen* splash = new QSplashScreen();
    splash->setPixmap(QPixmap(":/images/eclipse256.png"));
    splash->show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::white);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    Sleep(2000);
    QApplication::restoreOverrideCursor();

    MainWindow* window = new MainWindow();
    window->show();

    splash->finish(window);
    delete splash;

    return app.exec();
}
