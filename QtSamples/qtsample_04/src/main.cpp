/*
 *
 */

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QVBoxLayout>
#include "Tetrahedron.h"

#include <iostream>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow* window = new QMainWindow();

    if(!QGLFormat::hasOpenGL()){
        std::cerr << "This system has no OpenGL support" << std::endl;
        return 1;
    }
    QGLFormat format;
    format.setVersion(4, 0);
    format.setProfile(QGLFormat::CoreProfile);

    Tetrahedron* tetrahedron = new Tetrahedron();
    QCheckBox* showNormals = new QCheckBox(QObject::tr("show Normal Vectors"));

    QObject::connect(showNormals, SIGNAL(stateChanged(int)), tetrahedron, SLOT(setShowNormals(int)));

    //
    QWidget* central = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(tetrahedron);
    layout->addWidget(showNormals);
    central->setLayout(layout);

    window->setWindowTitle(QObject::tr("Tetrahedron"));
    window->resize(640, 480);
    window->setCentralWidget(central);


    window->show();

    return app.exec();
}
