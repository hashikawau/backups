/*
 *
 */

#include <QApplication>
#include <QWidget>

#include "MainController.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget* window = new QWidget();

    sample::MainController controller(window);

    window->show();

    return app.exec();
}
