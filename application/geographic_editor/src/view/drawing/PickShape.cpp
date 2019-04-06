//========================================
// PickShape.cpp
//
//  Created on: 2013/12/25
//      Author: you
//========================================

#include "PickShape.h"

#include "model/Rectangle.h"
#include "model/Ellipse.h"

#include <cfloat>

namespace geoedit {

PickShape::PickShape(double coordX, double coordY)
        : m_picked(nullptr),
            m_x(coordX),
            m_y(coordY)
{
}

PickShape::~PickShape() {
}

void PickShape::operate(Rectangle* shape) {
    double left = shape->eGet<Rectangle::LEFT>();
    double right = shape->eGet<Rectangle::RIGHT>();
    double bottom = shape->eGet<Rectangle::BOTTOM>();
    double top = shape->eGet<Rectangle::TOP>();
    if (m_x >= left
        && m_x <= right
        && m_y >= bottom
        && m_y <= top)
            {
        m_picked = shape;
    }
}
void PickShape::operate(Ellipse* shape) {
    double centerX = shape->eGet<Ellipse::X>();
    double centerY = shape->eGet<Ellipse::Y>();
    double radiusX = shape->eGet<Ellipse::RX>();
    double radiusY = shape->eGet<Ellipse::RY>();

    if (radiusX > DBL_EPSILON
        && radiusY > DBL_EPSILON)
    {
        double eccentricX = m_x - centerX;
        double eccentricY = m_y - centerY;
        double t = (eccentricX / radiusX) * (eccentricX / radiusX)
            + (eccentricY / radiusY) * (eccentricY / radiusY);

        if (t <= 1.0) {
            m_picked = shape;
        }
    }
}

} /* namespace geoedit */
