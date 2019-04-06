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
#include <QtWidgets/qsplitter.h>
#include <QtWidgets/qscrollarea.h>
#include <QtWidgets/qlistview.h>
//#include <QtWidgets/qlabel.h>
//#include <QtWidgets/qlineedit.h>

#include "GeometryEditor.h"
#include "model/ModelRoot.h"
#include "view/ModelEditView.h"
//#include <iostream>

#include <fstream>

namespace geoedit {

MainWindow::MainWindow() {
    {
        QMenu* menu = menuBar()->addMenu(tr("&File"));
        {
            QAction* action = new QAction(tr("&New"), this);
            menu->addAction(action);
            connect(action, &QAction::triggered, this, &MainWindow::action_New);
            action->setShortcut(QKeySequence::New);
        }
        {
            QAction* action = new QAction(tr("&Open"), this);
            menu->addAction(action);
            connect(action, &QAction::triggered, this, &MainWindow::action_Open);
            action->setShortcut(QKeySequence::Open);
        }
        {
            QAction* action = new QAction(tr("&SaveAs"), this);
            menu->addAction(action);
            connect(action, &QAction::triggered, this, &MainWindow::action_SaveAs);
            action->setShortcut(QKeySequence::Save);
        }
        {
            menu->addSeparator();
        }
        {
            QAction* action = new QAction(tr("&Close"), this);
            menu->addAction(action);
            connect(action, &QAction::triggered, this, &MainWindow::close);
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
            connect(action, &QAction::triggered, this, &MainWindow::action_Undo);
        }
        {
            QAction* action = new QAction(tr("&Redo"), this);
            menu->addAction(action);
            action->setShortcut(QKeySequence::Redo);
            connect(action, &QAction::triggered, this, &MainWindow::action_Redo);
        }
    }
    setWindowIcon(QIcon(":images/blue.png"));
    setWindowTitle(tr("Geometry Editor"));
    resize(640, 480);

    ModelRoot* modelRoot = new ModelRoot();

    auto central = new QSplitter(Qt::Horizontal);
    setCentralWidget(central);
    {
        m_editor = new GeometryEditor(modelRoot);
        auto scrollArea = new QScrollArea();
        scrollArea->setBackgroundRole(QPalette::Dark);
//        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget(m_editor);
        central->addWidget(scrollArea);
        m_editor->resize(500, 500);

        m_editor->setFocus();
    }
    {
        auto editArea = new ModelEditView(modelRoot);
        central->addWidget(editArea);
    }

}

MainWindow::~MainWindow() {
}

//private slots
void MainWindow::action_New() {
    std::cout << "new" << std::endl;
}

void MainWindow::action_Open() {
    QString filepath = QFileDialog::getOpenFileName(
            this,
            tr("Open GeoGraphical File"),
            ".",
            tr("GeoGraphical File (*.geo)\n"
                    "All Files (*.*)"));

    if (!filepath.isEmpty()) {
        setWindowTitle(filepath);

        std::ifstream fstream(filepath.toStdString());
        m_editor->load(fstream);
    }

}

void MainWindow::action_SaveAs() {
    QString filterString;
    QString filepath = QFileDialog::getSaveFileName(
            this,
            tr("Save GeoGraphical File"),
            ".",
            tr("GeoGraphical File (*.geo)\n"
                    "All Files (*.*)"),
            &filterString);

    if (!filepath.isEmpty()) {
        std::ofstream fstream(filepath.toStdString());
        m_editor->save(fstream);
    }
}

void MainWindow::action_Undo() {
    m_editor->undo();
}

void MainWindow::action_Redo() {
    m_editor->redo();
}

} /* namespace geoedit */
