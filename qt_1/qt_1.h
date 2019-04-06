#ifndef QT_1_H
#define QT_1_H

#include <QtWidgets/QWidget>
#include "ui_qt_1.h"

class qt_1 : public QMainWindow
{
    Q_OBJECT

public:
    qt_1(QMainWindow *parent = 0);
    ~qt_1();

private:
    Ui::qt_1Class ui;
};

#endif // QT_1_H
