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
namespace wavedit {

class WaveEditor;

class MainWindow: public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent =0);
    virtual ~MainWindow();

private slots:
    void action_New();
    void action_Open();
    void action_SaveAs();
    void action_Undo();
    void action_Redo();

private:
    WaveEditor* m_editor;

//    QWidget* m_color;
//    QLineEdit* m_rga[3];

};

} /* namespace wavedit */

#endif /* MAINWINDOW_H_ */
