//========================================
// PickShape.h
//
//  Created on: 2013/12/25
//      Author: you
//========================================

#ifndef PICKSHAPE_H_
#define PICKSHAPE_H_

#include "model/IShape.h"

namespace geoedit {

/*
 *
 */
class PickShape: public IShape::IOperation {
public:
    PickShape(double coordX, double coordY);
    virtual ~PickShape();

    virtual void operate(Rectangle* shape);
    virtual void operate(Ellipse* shape);

    template<class List>
    IShape* getPickedShape(List& list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            visit((*it).get());
            if (m_picked != nullptr) {
                break;
            }
        }
        return m_picked;
    }

private:
    IShape* m_picked;
    const double m_x;
    const double m_y;

};

} /* namespace geoedit */

#endif /* PICKSHAPE_H_ */
