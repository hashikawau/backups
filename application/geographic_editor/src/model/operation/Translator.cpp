//========================================
// Translator.cpp
//
//  Created on: 2013/12/25
//      Author: you
//========================================

#include "Translator.h"

#include "model/Rectangle.h"
#include "model/Ellipse.h"

namespace geoedit {

Translator::Translator(double tx, double ty)
        : m_tx(tx),
            m_ty(ty)
{
}

Translator::~Translator() {
}

void Translator::operate(Rectangle* shape) {
    double left = shape->eGet<Rectangle::LEFT>();
    double right = shape->eGet<Rectangle::RIGHT>();
    double bottom = shape->eGet<Rectangle::BOTTOM>();
    double top = shape->eGet<Rectangle::TOP>();

    shape->eSet<Rectangle::LEFT>(left + m_tx);
    shape->eSet<Rectangle::RIGHT>(right + m_tx);
    shape->eSet<Rectangle::BOTTOM>(bottom + m_ty);
    shape->eSet<Rectangle::TOP>(top + m_ty);
}
void Translator::operate(Ellipse* shape) {
    double cx = shape->eGet<Ellipse::X>();
    double cy = shape->eGet<Ellipse::Y>();
    shape->eSet<Ellipse::X>(cx + m_tx);
    shape->eSet<Ellipse::Y>(cy + m_ty);
}

} /* namespace geoedit */
