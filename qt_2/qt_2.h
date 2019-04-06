#ifndef QT_2_H
#define QT_2_H

//#include <QtGui/QMainWindow>
#include <QtWidgets/QMainWindow>
#include "ui_qt_2.h"

class qt_2 : public QMainWindow
{
    Q_OBJECT

public:
    qt_2(QWidget *parent = 0);
    ~qt_2();

private:
    Ui::qt_2Class ui;
};

#endif // QT_2_H
