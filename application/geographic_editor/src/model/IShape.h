//========================================
// IShape.h
//
//  Created on: 2013/12/14
//      Author: you
//========================================

#ifndef ISHAPE_H_
#define ISHAPE_H_

#include <iostream>
#include <sstream>

class QPainter;

namespace geoedit {

class CoordinateConverter;

/*
 *
 */
class IShape {
public:
    class IOperation;
    virtual ~IShape() =0;

    virtual void drawShape(QPainter& painter, const CoordinateConverter& converter) const =0;
    //    virtual QString toString() const =0;
//    virtual QWidget* getEditPage() const =0;
    virtual const std::string toString() =0;

protected:
    IShape();

private:
    virtual void apply(IOperation* operation) =0;
//    virtual void apply(IOperation* operation){
//        operation->operate(this);
//    }

};

class Rectangle;
class Ellipse;
class IShape::IOperation {
public:
    virtual ~IOperation() =0;

    void operate(IShape* shape);
    virtual void operate(Rectangle* shape) =0;
    virtual void operate(Ellipse* shape) =0;

protected:
    IOperation();
    void visit(IShape* shape) {
        shape->apply(this);
    }

};

#define _REFERENCE_DECLARATION_MACRO(_TYPE, _FIELD_NAME, _STRUCT_NAME)\
    private: _TYPE _FIELD_NAME;\
    public: struct _STRUCT_NAME { typedef decltype(_FIELD_NAME) Type; };

#define _EGET_IMPLEMENTATION_MACRO(_CLASS_NAME, _FIELD_NAME, _STRUCT_NAME)\
    template<>\
    const _CLASS_NAME::_STRUCT_NAME::Type&\
    _CLASS_NAME::eGet<_CLASS_NAME::_STRUCT_NAME>() const {\
        return _FIELD_NAME;\
    }

#define _ESET_IMPLEMENTATION_MACRO(_CLASS_NAME, _FIELD_NAME, _STRUCT_NAME)\
    template<>\
    void\
    _CLASS_NAME::eSet<_CLASS_NAME::_STRUCT_NAME>(const _CLASS_NAME::_STRUCT_NAME::Type& value) {\
        _FIELD_NAME = value;\
    }

} /* namespace geoedit */

#endif /* ISHAPE_H_ */
