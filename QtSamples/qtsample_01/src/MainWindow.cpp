//========================================
// MainWindow.cpp
//
//  Created on: 2013/11/10
//      Author: you
//========================================
#include "MainWindow.h"
#include "ProjectListWidget.h"

//
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QStatusBar>

//
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtGui/QCloseEvent>

//
#include <QtWidgets/QApplication>
#include <QtGui/QClipboard>
#include <QtWidgets/QTextEdit>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtCore/QMimeData>
#include <QtWidgets/QHBoxLayout>

//
#include <iostream>

MainWindow::MainWindow() {
    setWindowIcon(QIcon(":/images/eclipse32.png"));

    createWidgets();

    createActions();
    createMenus();
    createToolBars();
    createContextMenu();
    createStatusBar();

    setupDAndD();
}

MainWindow::~MainWindow() {
}

//protected:
void MainWindow::closeEvent(QCloseEvent* event) {
//    std::cout << "closeEvent()" << std::endl;
    int r = QMessageBox::warning(this, tr("message box"),
            tr("are you sure you want to quit application?"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (r == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

//private slots:
void MainWindow::actionTriggered() {
//    std::cout << "action triggered" << std::endl;
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), ".",
            tr("All Files (*.*)\n"
                    "Text Files (*.txt)"));
    if (!filePath.isEmpty()) {
//        std::cout << filePath.toStdString() << std::endl;
        QFileInfo f(filePath);
        setWindowTitle(f.fileName());
        m_statusLabel->setText(f.absoluteDir().absolutePath());

        //
        QFile readfile(filePath);
        if (!readfile.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("read file"),
                    tr("Cannot read file %1:\n%2.").arg(readfile.fileName()).arg(
                            readfile.errorString()));
        } else {
            QDataStream in(&readfile);
            in.setVersion(QDataStream::Qt_5_1);
            QString str;
            in >> str;
            std::cout << "file data = " << str.toStdString() << std::endl;
            readfile.close();

            QFile writefile(filePath);
            if (!writefile.open(QIODevice::WriteOnly)) {
                QMessageBox::warning(this, tr("write file"),
                        tr("Cannot write file %1:\n%2.").arg(
                                writefile.fileName()).arg(
                                writefile.errorString()));
            } else {
                QDataStream out(&writefile);
                out.setVersion(QDataStream::Qt_5_1);
                str = QApplication::clipboard()->text();
                if (str.length() <= 0) {
                    str = "test line";
                }
//                str = 32;
                out << str;
                std::cout << "clipboard = " << str.toStdString() << std::endl;
                QApplication::clipboard()->setText(str);
            }
        }
    }
}

//private:
void MainWindow::createWidgets() {
    m_widget = new QWidget();
    setCentralWidget(m_widget);
}
void MainWindow::createActions() {
    m_action = new QAction(tr("&Action"), this);
    m_action->setIcon(QIcon(":/images/eclipse16.png"));
    m_action->setShortcut(QKeySequence::SelectAll);
    m_action->setStatusTip(tr("make action"));
    connect(m_action, SIGNAL(triggered(bool)), this, SLOT(actionTriggered()));
}
void MainWindow::createMenus() {
    m_menu = menuBar()->addMenu(tr("&Menu"));
    m_menu->addAction(m_action);
}
void MainWindow::createToolBars() {
    m_toolbar = addToolBar(tr("&Menu"));
    m_toolbar->addAction(m_action);
}
void MainWindow::createContextMenu() {
    m_widget->addAction(m_action);
    m_widget->setContextMenuPolicy(Qt::ActionsContextMenu);
}
void MainWindow::createStatusBar() {
    m_statusLabel = new QLabel(tr("status"));
    statusBar()->addWidget(m_statusLabel);
}

//---> for drag and drop
void MainWindow::setupDAndD() {
    m_textEdit = new QTextEdit(m_widget);

    m_textEdit->setAcceptDrops(false);
    setAcceptDrops(true);

    //
    m_lists[0] = new ProjectListWidget(m_widget);
    m_lists[1] = new ProjectListWidget(m_widget);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m_textEdit);
    layout->addWidget(m_lists[0]);
    layout->addWidget(m_lists[1]);
    m_widget->setLayout(layout);

}

void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* event) {
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) return;

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) return;

    if (readFile(fileName)) setWindowTitle(
            tr("%1 - %2").arg(fileName).arg(tr("Drag File")));
}

bool MainWindow::readFile(const QString& fileName) {
    return true;
}
//<--- for drag and drop

