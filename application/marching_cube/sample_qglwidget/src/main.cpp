//========================================
// main.cpp
//
//  Created on: 2013/12/07
//      Author: you
//========================================

#include <QtWidgets/qapplication.h>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    qglwidget::MainWindow window;

    window.show();

    return app.exec();
}

