//========================================
// Serializer.h
//
//  Created on: 2013/12/24
//      Author: you
//========================================

#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include "model/IShape.h"

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>

#include "model/Rectangle.h"
#include "model/Ellipse.h"

namespace geoedit {

/*
 *
 */
class IShape_Serializable;
class Serializer: public IShape::IOperation {
public:
    Serializer();
    virtual ~Serializer();

    virtual void operate(Rectangle* shape);
    virtual void operate(Ellipse* shape);

    IShape_Serializable* getSerialized(IShape* shape) {
        visit(shape);
        return m_serialized;
    }
private:
    IShape_Serializable* m_serialized;

};

//==============================================--->
class IShape_Serializable {
public:
    virtual ~IShape_Serializable() =0;
    virtual IShape* getShape() =0;

protected:
    IShape_Serializable() {
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& /*ar*/, const unsigned int /*version*/) {
    }
};
class Rectangle_Serializable: public IShape_Serializable {
public:
    Rectangle_Serializable()
            : m_left(0.0), m_right(0.0), m_bottom(0.0), m_top(0.0)
    {
    }
    Rectangle_Serializable(Rectangle* shape)
            : m_left(shape->eGet<Rectangle::LEFT>()),
                m_right(shape->eGet<Rectangle::RIGHT>()),
                m_bottom(shape->eGet<Rectangle::BOTTOM>()),
                m_top(shape->eGet<Rectangle::TOP>())
    {
    }
    virtual ~Rectangle_Serializable() {
    }

    virtual IShape* getShape() override {
        return new Rectangle(m_left, m_right, m_bottom, m_top);
    }

private:
    double m_left;
    double m_right;
    double m_bottom;
    double m_top;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/) {
        ar & boost::serialization::base_object<IShape_Serializable>(*this);
        ar & m_left;
        ar & m_right;
        ar & m_bottom;
        ar & m_top;
    }
};

class Ellipse_Serializable: public IShape_Serializable {
public:
    Ellipse_Serializable()
            : m_x(0.0), m_y(0.0), m_rx(0.0), m_ry(0.0)
    {
    }
    Ellipse_Serializable(Ellipse* shape)
            : m_x(shape->eGet<Ellipse::X>()),
                m_y(shape->eGet<Ellipse::Y>()),
                m_rx(shape->eGet<Ellipse::RX>()),
                m_ry(shape->eGet<Ellipse::RY>())
    {
    }
    virtual ~Ellipse_Serializable() {
    }

    virtual IShape* getShape() override {
        return new Ellipse(m_x, m_y, m_rx, m_ry);
    }

private:
    double m_x;
    double m_y;
    double m_rx;
    double m_ry;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/) {
        ar & boost::serialization::base_object<IShape_Serializable>(*this);
        ar & m_x;
        ar & m_y;
        ar & m_rx;
        ar & m_ry;
    }
};

} /* namespace geoedit */

#endif /* SERIALIZER_H_ */
