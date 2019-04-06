//========================================
// Ellipse.h
//
//  Created on: 2013/12/23
//      Author: you
//========================================

#ifndef ELLIPSE_H_
#define ELLIPSE_H_

#include "IShape.h"

namespace geoedit {

/*
 *
 */
class Ellipse: public IShape {
public:
    Ellipse(double centerX, double centerY, double radiusX, double radiusY);
    virtual ~Ellipse();

    virtual void drawShape(QPainter& painter, const CoordinateConverter& converter) const
            override;

    virtual const std::string toString() override {
        std::stringstream ss;
        ss << "Ellipse: (" << m_x << ", " << m_y << ") - (" << m_rx << ", " << m_ry << ")";
        return ss.str();
    }

    template<class Reference>
    const typename Reference::Type& eGet() const;

    template<class Reference>
    void eSet(const typename Reference::Type& value);

private:
    virtual void apply(IOperation* operation) override;
    _REFERENCE_DECLARATION_MACRO(double, m_x, X)
    _REFERENCE_DECLARATION_MACRO(double, m_y, Y)
    _REFERENCE_DECLARATION_MACRO(double, m_rx, RX)
    _REFERENCE_DECLARATION_MACRO(double, m_ry, RY)
    };

} /* namespace geoedit */

#endif /* ELLIPSE_H_ */
