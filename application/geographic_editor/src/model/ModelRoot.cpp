//========================================
// ModelRoot.cpp
//
//  Created on: 2013/12/14
//      Author: you
//========================================

#include "ModelRoot.h"

#include <fstream>

//#include <boost/serialization/serialization.hpp>
//#include <boost/serialization/base_object.hpp>
//#include <boost/serialization/export.hpp>
//#include <boost/serialization/string.hpp>
//#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "model/operation/Serializer.h"

namespace geoedit {

ModelRoot::ModelRoot() {
}

ModelRoot::~ModelRoot() {
}

class ModelRoot_Serializable {
public:
    ModelRoot_Serializable() {
    }

    ModelRoot_Serializable(ModelRoot* modelRoot) {
        Serializer serializer;
        for (auto& shape : modelRoot->getShapes()) {
            list.push_back(serializer.getSerialized(shape.get()));
        }
    }
    ~ModelRoot_Serializable() {
        for (auto serialized : list) {
            delete serialized;
        }
    }
    const std::vector<IShape*>& getShapes() {
        m_shapes.clear();
        for (auto& serialized : list) {
            m_shapes.push_back(serialized->getShape());
        }
        return m_shapes;
    }

private:
    std::vector<IShape_Serializable*> list;
    std::vector<IShape*> m_shapes;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/) {
        ar & list;
    }
};
//==============================================<---
void ModelRoot::load(std::ifstream& fstream) {
    boost::archive::text_iarchive archive(fstream);
    ModelRoot_Serializable r;
    archive >> r;

    m_shapes.clear();
    for (auto& it : r.getShapes()) {
        m_shapes.push_back(std::unique_ptr<IShape>(it));
    }

    modelChanged();
}

void ModelRoot::save(std::ofstream& fstream) {
    boost::archive::text_oarchive archive(fstream);
    ModelRoot_Serializable r(this);
    archive << r;

}

} /* namespace geoedit */

BOOST_CLASS_EXPORT_GUID(geoedit::IShape_Serializable, "IShape")
BOOST_CLASS_EXPORT_GUID(geoedit::Rectangle_Serializable, "Rectangle")
BOOST_CLASS_EXPORT_GUID(geoedit::Ellipse_Serializable, "Ellipse")
