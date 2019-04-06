//========================================
// FindDialog.h
//
//  Created on: 2013/10/31
//      Author: you
//========================================

#ifndef qtsample_00_FINDDIALOG_H_
#define qtsample_00_FINDDIALOG_H_

#include <QDialog>

class QLabel;
class QCheckBox;
class QLineEdit;
class QPushButton;

class FindDialog: public QDialog {

Q_OBJECT

public:
    FindDialog(QWidget* parent = 0);
    virtual ~FindDialog();

signals:
    void findNet(const QString& str, Qt::CaseSensitivity cs);
    void findPrevious(const QString& str, Qt::CaseSensitivity cs);

private slots:
    void findClicked();
    void enableFindButton(const QString& text);

private:
    QLabel* label;
    QLineEdit* lineEdit;
    QCheckBox* caseCheckBox;
    QCheckBox* backwardCheckBox;
    QPushButton* findButton;
    QPushButton* closeButton;

};

#endif /* qtsample_00_FINDDIALOG_H_ */
