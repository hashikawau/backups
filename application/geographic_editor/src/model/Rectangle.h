//========================================
// Rectangle.h
//
//  Created on: 2013/12/14
//      Author: you
//========================================

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "IShape.h"

namespace geoedit {

/*
 *
 */
class Rectangle: public IShape {
public:
    Rectangle(double left, double right, double bottom, double top);
    virtual ~Rectangle();

    virtual void drawShape(QPainter& painter, const CoordinateConverter& converter) const
            override;

    virtual const std::string toString() override {
        std::stringstream ss;
        ss << "Rectangle: (" << m_left << ", " << m_top << ") -> (" << m_right << ", " << m_bottom << ")";
        return ss.str();
    }

    template<class Reference>
    const typename Reference::Type& eGet() const;

    template<class Reference>
    void eSet(const typename Reference::Type& value);

private:
    virtual void apply(IOperation* operation) override;
    _REFERENCE_DECLARATION_MACRO(double, m_left, LEFT)
    _REFERENCE_DECLARATION_MACRO(double, m_right, RIGHT)
    _REFERENCE_DECLARATION_MACRO(double, m_bottom, BOTTOM)
    _REFERENCE_DECLARATION_MACRO(double, m_top, TOP)

//    double m_left;
//    double m_right;
//    double m_bottom;
//    double m_top;

};

} /* namespace geoedit */

#endif /* RECTANGLE_H_ */
