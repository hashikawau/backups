//========================================
// Rectangle.cpp
//
//  Created on: 2013/12/14
//      Author: you
//========================================

#include "Rectangle.h"

#include <QtGui/qpainter.h>

#include "util/CoordinateConverter.h"

namespace geoedit {

Rectangle::Rectangle(double left, double right, double bottom, double top)
        : m_left(left),
                m_right(right),
                m_bottom(bottom),
                m_top(top)
{
}

Rectangle::~Rectangle() {
}

void Rectangle::drawShape(QPainter& painter, const CoordinateConverter& converter) const {
    painter.drawRect(QRect(
            converter.convert(CoordinateConverter::PointD { m_left, m_top }),
            converter.convert(CoordinateConverter::PointD { m_right, m_bottom })));
}

void Rectangle::apply(IOperation* operation) {
    operation->operate(this);
}

_EGET_IMPLEMENTATION_MACRO(Rectangle, m_left, LEFT)
_ESET_IMPLEMENTATION_MACRO(Rectangle, m_left, LEFT)
_EGET_IMPLEMENTATION_MACRO(Rectangle, m_right, RIGHT)
_ESET_IMPLEMENTATION_MACRO(Rectangle, m_right, RIGHT)
_EGET_IMPLEMENTATION_MACRO(Rectangle, m_bottom, BOTTOM)
_ESET_IMPLEMENTATION_MACRO(Rectangle, m_bottom, BOTTOM)
_EGET_IMPLEMENTATION_MACRO(Rectangle, m_top, TOP)
_ESET_IMPLEMENTATION_MACRO(Rectangle, m_top, TOP)

} /* namespace geoedit */

