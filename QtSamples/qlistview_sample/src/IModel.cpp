//========================================
// IModel.cpp
//
//  Created on: 2013/12/19
//      Author: you
//========================================

#include "IModel.h"

#include <iostream>
#include <sstream>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>

namespace sample {

//--->
EditPage4ModelA* EditPage4ModelA::s_instance = nullptr;
EditPage4ModelA::EditPage4ModelA(QWidget* parent)
        : QWidget(parent),
                m_model(nullptr),
                m_textX(new QLineEdit())
{
    auto layout_0 = new QVBoxLayout();
    setLayout(layout_0);
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto label = new QLabel(tr("x: "));
            layout_1->addWidget(label);
        }
        {
            layout_1->addWidget(m_textX);
            connect(m_textX, &QLineEdit::textChanged, this, &EditPage4ModelA::setX);
        }
    }
}
EditPage4ModelA::~EditPage4ModelA() {
}
EditPage4ModelA* EditPage4ModelA::getInstance(ModelA* model) {
    if (s_instance == nullptr) {
        s_instance = new EditPage4ModelA();
    }
    s_instance->setModel(model);
    return s_instance;
}
void EditPage4ModelA::setModel(ModelA* model) {
    m_model = model;
    m_textX->setText(QString::number(m_model->x()));
}
void EditPage4ModelA::setX(const QString& text) {
//    IModel* selection = m_model->getSelection();
    if (m_model != nullptr) {
        bool ok;
        double value = text.toDouble(&ok);
        if (ok) {
            m_model->setX(value);
//            emit dataChanged(QModelIndex(), QModelIndex(), {Qt::DisplayRole});
        }
    }
}
//<---

//--->
EditPage4ModelB* EditPage4ModelB::s_instance = nullptr;
EditPage4ModelB::EditPage4ModelB(QWidget* parent)
        : QWidget(parent),
                m_model(nullptr),
                m_textX(new QLineEdit()),
                m_textY(new QLineEdit())
{
    auto layout_0 = new QVBoxLayout();
    setLayout(layout_0);
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto label = new QLabel(tr("x: "));
            layout_1->addWidget(label);
        }
        {
            layout_1->addWidget(m_textX);
            connect(m_textX, &QLineEdit::textChanged, this, &EditPage4ModelB::setX);
        }
    }
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto label = new QLabel(tr("y: "));
            layout_1->addWidget(label);
        }
        {
            layout_1->addWidget(m_textY);
            connect(m_textY, &QLineEdit::textChanged, this, &EditPage4ModelB::setY);
        }
    }
}
EditPage4ModelB::~EditPage4ModelB() {
}
EditPage4ModelB* EditPage4ModelB::getInstance(ModelB* model) {
    if (s_instance == nullptr) {
        s_instance = new EditPage4ModelB();
    }
    s_instance->setModel(model);
    return s_instance;
}
void EditPage4ModelB::setModel(ModelB* model) {
    m_model = model;
    m_textX->setText(QString::number(m_model->x()));
    m_textY->setText(QString::number(m_model->y()));
}
void EditPage4ModelB::setX(const QString& text) {
    if (m_model != nullptr) {
        bool ok;
        double value = text.toDouble(&ok);
        if (ok) {
            m_model->setX(value);
//            emit dataChanged(QModelIndex(), QModelIndex(), {Qt::DisplayRole});
        }
    }
}
void EditPage4ModelB::setY(const QString& text) {
    if (m_model != nullptr) {
        bool ok;
        double value = text.toDouble(&ok);
        if (ok) {
            m_model->setY(value);
//            emit dataChanged(QModelIndex(), QModelIndex(), {Qt::DisplayRole});
        }
    }
}
//<---

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
    result << "ModelA: [x] = [" << m_x << "]";
    return result.str();
}
QWidget* ModelA::getEditPage() {
    return EditPage4ModelA::getInstance(this);
//    return new QPushButton("aaaa");
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
    result << "ModelB: [x, y] = [" << m_x << ", " << m_y << "]";
    return result.str();
}
QWidget* ModelB::getEditPage() {
//    return new QLabel(QString::fromStdString(toString()));
    return EditPage4ModelB::getInstance(this);
}
//<---

} /* namespace sample */
