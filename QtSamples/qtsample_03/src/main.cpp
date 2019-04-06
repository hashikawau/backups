/*
 *
 */

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "Tetrahedron.h"

#include <iostream>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow* window = new QMainWindow();

    if(!QGLFormat::hasOpenGL()){
        std::cerr << "This system has no OpenGL support" << std::endl;
        return 1;
    }
    Tetrahedron* tetrahedron = new Tetrahedron();

    window->setWindowTitle(QObject::tr("Tetrahedron"));
    window->resize(300, 300);
    window->setCentralWidget(tetrahedron);

    window->show();

    return app.exec();
}
