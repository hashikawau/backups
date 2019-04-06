

#include <iostream>

#include <QtGui>

#include "common.h"


class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();

};
MainWindow::MainWindow()
{
    std::cout << "constructor: MainWindow" << std::endl;
}
MainWindow::~MainWindow()
{
    std::cout << "destructor: MainWindow" << std::endl;
}
#include "main.moc"

#include <QtCore>

int main(int argc, char* argv[])
{
    std::cout << "hello world" << std::endl;

    //Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}


