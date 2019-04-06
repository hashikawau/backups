//========================================
// Ellipse.cpp
//
//  Created on: 2013/12/23
//      Author: you
//========================================

#include "Ellipse.h"

#include <QtGui/qpainter.h>

#include "util/CoordinateConverter.h"

namespace geoedit {

Ellipse::Ellipse(double centerX, double centerY, double radiusX, double radiusY)
        : m_x(centerX),
                m_y(centerY),
                m_rx(radiusX),
                m_ry(radiusY)
{
}

Ellipse::~Ellipse() {
}

void Ellipse::drawShape(QPainter& painter, const CoordinateConverter& converter) const {
    painter.drawEllipse(
            converter.convert(CoordinateConverter::PointD { m_x, m_y }),
            converter.convert(m_rx),
            converter.convert(m_ry));
}

void Ellipse::apply(IOperation* operation) {
    operation->operate(this);
}

_EGET_IMPLEMENTATION_MACRO(Ellipse, m_x, X)
_ESET_IMPLEMENTATION_MACRO(Ellipse, m_x, X)
_EGET_IMPLEMENTATION_MACRO(Ellipse, m_y, Y)
_ESET_IMPLEMENTATION_MACRO(Ellipse, m_y, Y)
_EGET_IMPLEMENTATION_MACRO(Ellipse, m_rx, RX)
_ESET_IMPLEMENTATION_MACRO(Ellipse, m_rx, RX)
_EGET_IMPLEMENTATION_MACRO(Ellipse, m_ry, RY)
_ESET_IMPLEMENTATION_MACRO(Ellipse, m_ry, RY)

} /* namespace geoedit */
