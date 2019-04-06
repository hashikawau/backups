/*
 *
 */

#include <QApplication>
#include <QWidget>
//#include <QHBoxLayout>
//#include <QSlider>
//#include <QSpinBox>
//#include <QLabel>

#include "MainController.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget* window = new QWidget();

//    window->setWindowTitle("サンプル 00");
//
////	QSpinBox* spinBox = new QSpinBox(window);
//    QSpinBox* spinBox = new QSpinBox();
//    QSlider* slider = new QSlider(Qt::Horizontal);
//    spinBox->setRange(0, 130);
//    slider->setRange(0, 130);
//
//    QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider,
//            SLOT(setValue(int)));
//    QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox,
//            SLOT(setValue(int)));
//
//    spinBox->setValue(35);
//
//    QHBoxLayout* layout = new QHBoxLayout();
//    layout->addWidget(spinBox);
//    layout->addWidget(slider);
//    window->setLayout(layout);
//

    MainController controller(window);

    window->show();

//	QLabel* label = new QLabel("aaa");
//	label->show();

//	GLView v;

    return app.exec();
}
