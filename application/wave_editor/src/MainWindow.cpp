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
#include <QtWidgets/qpushbutton.h>

#include "WaveEditor.h"

#include <iostream>
#include <fstream>

namespace wavedit {

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent)
{
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
    setWindowTitle(tr("Wave Editor"));
    resize(640, 480);

//    ModelRoot* modelRoot = new ModelRoot();

//    auto central = new QSplitter(Qt::Vertical);
    auto central = new QWidget();
    setCentralWidget(central);
    auto layout_0 = new QVBoxLayout();
    central->setLayout(layout_0);
    {
        auto widget = new WaveEditor();
        layout_0->addWidget(widget, 1);

        m_editor = widget;
        m_editor->setFocus();
    }
    {
        auto widget = new QWidget();
        layout_0->addWidget(widget);

        auto layout_1 = new QHBoxLayout();
        widget->setLayout(layout_1);
        {
            auto widget = new QPushButton(tr("play"));
            layout_1->addWidget(widget);
            connect(widget, &QPushButton::clicked, m_editor, &WaveEditor::playButtonClicked);
        }
        {
            auto widget = new QPushButton(tr("stop"));
            layout_1->addWidget(widget);
            connect(widget, &QPushButton::clicked, m_editor, &WaveEditor::stopButtonClicked);
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
    QString filepath = QFileDialog::getOpenFileName(
        this,
        tr("Open Wave File"),
        ".",
        tr("Wave File (*.wav)\n"
            "All Files (*.*)"));

    if(!filepath.isEmpty()){
        setWindowTitle(filepath);

//        std::ifstream fstream(filepath.toStdString());
        m_editor->load(filepath.toStdString());
    }

}

void MainWindow::action_SaveAs() {
    QString filterString;
    QString filepath = QFileDialog::getSaveFileName(
        this,
        tr("Save Wave File"),
        ".",
        tr("Wave File (*.wav)\n"
            "All Files (*.*)"),
        &filterString);

    if(!filepath.isEmpty()){
//        std::ofstream fstream(filepath.toStdString());
        m_editor->save(filepath.toStdString());
    }
}

void MainWindow::action_Undo() {
    m_editor->undo();
}

void MainWindow::action_Redo() {
    m_editor->redo();
}

} /* namespace wavedit */
