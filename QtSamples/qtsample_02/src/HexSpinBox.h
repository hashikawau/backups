//========================================
// HexSpinBox.h
//
//  Created on: 2013/11/13
//      Author: you
//========================================

#ifndef qtsample_02_HEXSPINBOX_H_
#define qtsample_02_HEXSPINBOX_H_

#include <QtWidgets/qspinbox.h>

class QRegExpValidator;

class HexSpinBox: public QSpinBox {
Q_OBJECT

public:
    HexSpinBox(QWidget* parent = 0);
    virtual ~HexSpinBox();

protected:
    virtual QValidator::State validate(QString& text, int& pos) const;
    virtual int valueFromText(const QString& text) const;
    virtual QString textFromValue(int value) const;

private:
    QRegExpValidator* validator;

};

#endif /* qtsample_02_HEXSPINBOX_H_ */
