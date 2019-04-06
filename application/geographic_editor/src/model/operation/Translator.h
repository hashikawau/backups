//========================================
// Translator.h
//
//  Created on: 2013/12/25
//      Author: you
//========================================

#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_

#include "model/IShape.h"

namespace geoedit {

/*
 *
 */
class Translator: public IShape::IOperation {
public:
    virtual void operate(Rectangle* shape);
    virtual void operate(Ellipse* shape);

    static void translate(IShape* shape, double tx, double ty) {
        Translator translator(tx, ty);
        translator.visit(shape);
    }

private:
    Translator(double tx, double ty);
    virtual ~Translator();

    double m_tx;
    double m_ty;

};

} /* namespace geoedit */

#endif /* TRANSLATOR_H_ */
