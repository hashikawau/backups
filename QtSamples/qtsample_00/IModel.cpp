//========================================
// IModel.cpp
//
//  Created on: 2013/12/19
//      Author: you
//========================================

#include "IModel.h"

#include <iostream>
#include <sstream>

//IModel::IModel() {
//}

IModel::~IModel() {
}

//--->
ModelRoot::ModelRoot() {
    m_models.push_back(new ModelA(1));
    m_models.push_back(new ModelB(1, 2));
    m_models.push_back(new ModelB(2, 1));
    m_models.push_back(new ModelA(3));
}
ModelRoot::~ModelRoot() {
//    for (auto it = m_models.begin(); it != m_models.end();) {
//        delete *it;
//        it = m_models.erase(it);
//    }
}

int ModelRoot::size() const {
    return m_models.size();
}
IModel* ModelRoot::get(int index) const {
    return m_models[index];
}
void ModelRoot::add(IModel* model) {
    m_models.push_back(model);
}
void ModelRoot::remove(IModel* model) {
    for (auto it = m_models.begin(); it != m_models.end(); ++it) {
        if (*it == model) {
            delete *it;
            m_models.erase(it);
            break;
        }
    }
}
//<---

//--->
ModelA::ModelA(double x)
        : m_x(x) {
}
ModelA::~ModelA() {
}

void ModelA::process() {
    std::cout << "ModelA.process(): " << m_x << std::endl;
}
const std::string ModelA::toString() {
    std::stringstream result;
    result << m_x;
    return result.str();
}
QWidget* ModelA::getEditPage(){

}
//<---

//--->
ModelB::ModelB(double x, double y)
        : m_x(x), m_y(y) {
}
ModelB::~ModelB() {
}
void ModelB::process() {
    std::cout << "ModelB.process(): " << m_x << ", " << m_y << std::endl;
}
const std::string ModelB::toString() {
    std::stringstream result;
    result << m_x << ", " << m_y;
    return result.str();
}
QWidget* ModelB::getEditPage(){

}
//<---

