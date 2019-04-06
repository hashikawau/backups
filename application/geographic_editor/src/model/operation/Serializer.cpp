//========================================
// Serializer.cpp
//
//  Created on: 2013/12/24
//      Author: you
//========================================

#include "Serializer.h"

namespace geoedit {

Serializer::Serializer()
        : m_serialized(nullptr)
{
}

Serializer::~Serializer() {
}

void Serializer::operate(Rectangle* shape) {
    m_serialized = new Rectangle_Serializable(shape);
}
void Serializer::operate(Ellipse* shape) {
    m_serialized = new Ellipse_Serializable(shape);
}
IShape_Serializable::~IShape_Serializable() {
}

} /* namespace geoedit */

