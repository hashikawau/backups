//========================================
// MainWindow.cpp
//
//  Created on: 2014/05/10
//      Author: you
//========================================

#include "MainWindow.h"
#include "GLViewer.h"

#include <QtWidgets/qlayout.h>

namespace qglwidget {

struct Layout {
public:
    enum EType
        : int{
            VERTICAL,
            HORIZONTAL,
    };
    Layout(EType type) {
        switch(type){
        case EType::VERTICAL:
            _layout = new QVBoxLayout();
            break;
        case EType::HORIZONTAL:
            _layout = new QHBoxLayout();
            break;
        default:
            break;
        }
    }
    ~Layout() {
        if(_layout->parent() == nullptr){
            delete _layout;
        }
    }
    Layout(Layout&&) = default;
    Layout& operator=(Layout&&) = default;

    operator QBoxLayout*() {
        return _layout;
    }

    Layout& add(QBoxLayout* child) {
        _layout->addLayout(child);
        return *this;
    }
    Layout& add(QWidget* child) {
        _layout->addWidget(child);
        return *this;
    }

private:
    Layout(const Layout&) = delete;
    Layout& operator=(const Layout&) = delete;

    QBoxLayout* _layout;

};

MainWindow::MainWindow() {

    setWindowTitle(tr("OpenGL Viewer"));
    resize(640, 480);

    auto central = new QWidget();
    setCentralWidget(central);
    central->setLayout(
        Layout(Layout::VERTICAL)
            .add(new GLViewer()));

}

MainWindow::~MainWindow() {
}

} //namespace qglwidget
