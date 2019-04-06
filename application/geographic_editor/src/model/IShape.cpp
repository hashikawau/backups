//========================================
// IShape.cpp
//
//  Created on: 2013/12/14
//      Author: you
//========================================

#include "IShape.h"

#include <iostream>
#include <typeinfo>

namespace geoedit {

IShape::IShape() {
}

IShape::~IShape() {
}

IShape::IOperation::IOperation() {
}

IShape::IOperation::~IOperation() {
}

void IShape::IOperation::operate(IShape* shape) {
    std::cout << "IOperation.operate(IShape*)" << typeid(shape).name() << std::endl;
}

} /* namespace geoedit */
