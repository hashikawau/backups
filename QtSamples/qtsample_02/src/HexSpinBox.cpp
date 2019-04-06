//========================================
// HexSpinBox.cpp
//
//  Created on: 2013/11/13
//      Author: you
//========================================
#include "HexSpinBox.h"

#include <iostream>

HexSpinBox::HexSpinBox(QWidget* parent)
        : QSpinBox(parent) {
    setRange(0, 255);
    validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
}

HexSpinBox::~HexSpinBox() {
}

QValidator::State HexSpinBox::validate(QString& text, int& pos) const {
    std::cout << "validate(): " << text.toStdString() << ", " << pos << std::endl;
    return validator->validate(text, pos);
}

QString HexSpinBox::textFromValue(int value) const{
    std::cout << "textFromValue(): " << value << std::endl;
    return QString::number(value, 16).toUpper();
}

int HexSpinBox::valueFromText(const QString& text) const{
    std::cout << "valueFromText(): " << text.toStdString() << std::endl;
    bool ok;
    return text.toInt(&ok, 16);
}

