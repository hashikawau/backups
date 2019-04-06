//========================================
// MainWindow.cpp
//
//  Created on: 2013/12/07
//      Author: you
//========================================

#include "MainWindow.h"
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qmenu.h>

#include <QtWidgets/qfiledialog.h>

#include <QtWidgets/qlayout.h>
//#include <QtWidgets/qlabel.h>
//#include <QtWidgets/qlineedit.h>

#include "IconEditor.h"
#include <iostream>

MainWindow::MainWindow() {
    {
        QMenu* menu = menuBar()->addMenu(tr("&File"));
        {
            QAction* action = new QAction(tr("&New"), this);
            menu->addAction(action);
            connect(action, SIGNAL(triggered()), this, SLOT(action_New()));
            action->setShortcut(QKeySequence::New);
        }
        {
            QAction* action = new QAction(tr("&Open"), this);
            menu->addAction(action);
            connect(action, SIGNAL(triggered()), this, SLOT(action_Open()));
            action->setShortcut(QKeySequence::Open);
        }
        {
            QAction* action = new QAction(tr("&SaveAs"), this);
            menu->addAction(action);
            connect(action, SIGNAL(triggered()), this, SLOT(action_SaveAs()));
            action->setShortcut(QKeySequence::Save);
        }
        {
            menu->addSeparator();
        }
        {
            QAction* action = new QAction(tr("&Close"), this);
            menu->addAction(action);
            connect(action, SIGNAL(triggered()), this, SLOT(close()));
            action->setShortcut(QKeySequence::Close);
        }
    }
    {
        QMenu* menu = menuBar()->addMenu(tr("&Edit"));
        {
            QAction* action = new QAction(tr("&Undo"), this);
            menu->addAction(action);
            action->setShortcut(QKeySequence::Undo);
            action->setIcon(QIcon(":images/blue.png"));
            action->setStatusTip(tr("Undo previous command"));
            connect(action, SIGNAL(triggered()), this, SLOT(action_Undo()));
        }
        {
            QAction* action = new QAction(tr("&Redo"), this);
            menu->addAction(action);
            action->setShortcut(QKeySequence::Redo);
            connect(action, SIGNAL(triggered()), this, SLOT(action_Redo()));
        }
    }
    setWindowIcon(QIcon(":images/blue.png"));
    setWindowTitle(tr("Icon Editor"));
    resize(640, 480);

    QWidget* central = new QWidget();
    setCentralWidget(central);
    {
        QBoxLayout* layout_0 = new QHBoxLayout();
        central->setLayout(layout_0);

        {
            m_editor = new IconEditor();
            layout_0->addWidget(m_editor, 1);
            m_editor->setFocus();

//            QWidget* colorView = new QWidget();
//            layout_0->addWidget(colorView);
//            {
//                QBoxLayout* layout_1 = new QVBoxLayout();
//                colorView->setLayout(layout_1);
//                {
//                    QBoxLayout* layout_2 = new QHBoxLayout();
//                    layout_1->addLayout(layout_2);
//                    QLabel* label = new QLabel(tr("Red:"));
//                    m_rga[0] = new QLineEdit(tr("128"));
//                    layout_2->addWidget(label);
//                    layout_2->addWidget(m_rga[0]);
//                }
//                {
//                    QBoxLayout* layout_2 = new QHBoxLayout();
//                    layout_1->addLayout(layout_2);
//                    QLabel* label = new QLabel(tr("Green:"));
//                    m_rga[1] = new QLineEdit(tr("128"));
//                    layout_2->addWidget(label);
//                    layout_2->addWidget(m_rga[1]);
//                }
//                {
//                    QBoxLayout* layout_2 = new QHBoxLayout();
//                    layout_1->addLayout(layout_2);
//                    QLabel* label = new QLabel(tr("Blue:"));
//                    m_rga[2] = new QLineEdit(tr("128"));
//                    layout_2->addWidget(label);
//                    layout_2->addWidget(m_rga[2]);
//                }
//                {
//                    m_color = new QWidget();
//                    layout_1->addWidget(m_color);
//                    m_color->resize(64, 64);
//                }
//            }
        }
    }

}

MainWindow::~MainWindow() {
}

//private slots
void MainWindow::action_New() {
    std::cout << "new" << std::endl;
}

void MainWindow::action_Open() {
    std::cout << "open" << std::endl;

    QString filepath = QFileDialog::getOpenFileName(
            this,
            tr("Open Image File"),
            ".",
            tr("Image File (*.ico *.png *.gif *.jpg)\n"
                    "All Files (*.*)"));

    if (!filepath.isEmpty()) {
        std::cout << filepath.toStdString() << std::endl;
        setWindowTitle(filepath);

        m_editor->load(filepath);
    }
}

void MainWindow::action_SaveAs() {
    std::cout << "save as" << std::endl;

    QString filterString;
    QString filepath = QFileDialog::getSaveFileName(
            this,
            tr("Save Image File"),
            ".",
            tr("PNG File (*.png)\n"
                    "All Files (*.*)"),
            &filterString);

    if (!filepath.isEmpty()) {
        const char* const format = QString("PNG File (*.png)\n").compare(filterString)? "PNG":
                "";
        m_editor->save(filepath, format);
    }
}

void MainWindow::action_Undo() {
    m_editor->undo();
}

void MainWindow::action_Redo() {
    m_editor->redo();
}

