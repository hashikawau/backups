//========================================
// MainWindow.h
//
//  Created on: 2013/11/10
//      Author: you
//========================================

#ifndef qtsample_01_MAINWINDOW_H_
#define qtsample_01_MAINWINDOW_H_

#include <QtWidgets/QMainWindow>

class QAction;
class QLabel;
class QTextEdit;

class ProjectListWidget;

class MainWindow: public QMainWindow {
Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();

protected:
    virtual void closeEvent(QCloseEvent* event);
    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dropEvent(QDropEvent* evnet);

private:
    void createWidgets();
    void createActions();
    void createMenus();
    void createToolBars();
    void createContextMenu();
    void createStatusBar();

public slots:
    void actionTriggered();

private:
    QWidget* m_widget;
    QAction* m_action;
    QMenu* m_menu;
    QToolBar* m_toolbar;
    QLabel* m_statusLabel;

    //for drag and drop
    void setupDAndD();
    bool readFile(const QString& fileName);
    QTextEdit* m_textEdit;

    ProjectListWidget* m_lists[2];
};

#endif /* qtsample_01_MAINWINDOW_H_ */
