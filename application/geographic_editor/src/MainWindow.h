//========================================
// MainWindow.h
//
//  Created on: 2013/12/07
//      Author: you
//========================================

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtWidgets/qmainwindow.h>

/*
 *
 */
namespace geoedit {

class GeometryEditor;

class MainWindow: public QMainWindow {
Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();

private slots:
    void action_New();
    void action_Open();
    void action_SaveAs();
    void action_Undo();
    void action_Redo();

private:
    GeometryEditor* m_editor;

//    QWidget* m_color;
//    QLineEdit* m_rga[3];

};

} /* namespace geoedit */

#endif /* MAINWINDOW_H_ */
