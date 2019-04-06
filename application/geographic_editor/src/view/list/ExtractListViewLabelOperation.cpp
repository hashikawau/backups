//========================================
// ExtractListViewLabelOperation.cpp
//
//  Created on: 2013/12/21
//      Author: you
//========================================

#include "ExtractListViewLabelOperation.h"

#include "model/Rectangle.h"
#include "model/Ellipse.h"
#include <sstream>

namespace geoedit {

ExtractListViewLabelOperation::ExtractListViewLabelOperation() {
}

ExtractListViewLabelOperation::~ExtractListViewLabelOperation() {
}

void ExtractListViewLabelOperation::operate(Rectangle* shape) {
//    m_string = QString::number(shape->ege)
    std::stringstream ss;
    ss << "Rectangle: ("
            << shape->eGet<Rectangle::LEFT>()
            << ", "
            << shape->eGet<Rectangle::TOP>()
            << ") -> ("
            << shape->eGet<Rectangle::RIGHT>()
            << ", "
            << shape->eGet<Rectangle::BOTTOM>()
            << ")";
//    m_string = QString("Rectangle: ")
//            + QString::number(shape->eGet<Rectangle::LEFT>());
    m_string = QString::fromStdString(ss.str());
}


void ExtractListViewLabelOperation::operate(Ellipse* shape) {
//    m_string = QString::number(shape->ege)
    std::stringstream ss;
    ss << "Ellipse: ("
            << shape->eGet<Ellipse::X>()
            << ", "
            << shape->eGet<Ellipse::Y>()
            << ") -> ("
            << shape->eGet<Ellipse::RX>()
            << ", "
            << shape->eGet<Ellipse::RY>()
            << ")";
//    m_string = QString("Rectangle: ")
//            + QString::number(shape->eGet<Rectangle::LEFT>());
    m_string = QString::fromStdString(ss.str());
}

} /* namespace geoedit */
