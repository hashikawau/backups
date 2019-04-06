//========================================
// GeometryEditor.cpp
//
//  Created on: 2013/12/07
//      Author: you
//========================================

#include "GeometryEditor.h"
#include <QtWidgets/qapplication.h>
#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>

#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>

#include "model/IShape.h"
#include "model/operation/Translator.h"
#include "util/ICommand.h"
#include "view/drawing/PickShape.h"

namespace geoedit {

CoordinateConverter::PointD GeometryEditor::m_mousePosition;
GeometryEditor::GeometryEditor(ModelRoot* modelRoot, QWidget* parent)
        : QWidget(parent),
            m_modelRoot(modelRoot),
            m_converter(1, 1)
{
    setMouseTracking(true);

    setBackgroundRole(QPalette::Window);

}

GeometryEditor::~GeometryEditor() {
}

void GeometryEditor::load(std::ifstream& fstream) {
    m_modelRoot->load(fstream);
    parentWidget()->parentWidget()->update();
}

void GeometryEditor::save(std::ofstream& fstream) {
    m_modelRoot->save(fstream);
}

void GeometryEditor::undo() {
    m_commandHistory.undo();
}

void GeometryEditor::redo() {
    m_commandHistory.redo();
    update();
}

//protected
void GeometryEditor::resizeEvent(QResizeEvent *event) {
    m_converter.setSize(event->size());
}
void GeometryEditor::paintEvent(QPaintEvent* /*event*/) {

    QPainter painter(this);
    for (auto& shape : m_modelRoot->getShapes()) {
        shape->drawShape(painter, m_converter);
    }
}

void GeometryEditor::mousePressEvent(QMouseEvent* event) {
    QPoint mousePos = event->pos();
    QPoint pos(mousePos.x(), mousePos.y());
    m_mousePosition = m_converter.convert(pos);
    m_selection.clear();

    PickShape picker(m_mousePosition.x, m_mousePosition.y);
    IShape* picked = picker.getPickedShape(m_modelRoot->getShapes());
    if (picked != nullptr) {
        std::cout << picked->toString() << std::endl;
        m_selection.push_back(picked);
        m_modelRoot->setSelection(m_selection);
    } else {
        std::cout << "nothing picked" << std::endl;
    }

}

void GeometryEditor::mouseReleaseEvent(QMouseEvent*) {
}

void GeometryEditor::mouseMoveEvent(QMouseEvent* event) {
    QPoint mousePos = event->pos();
    QPoint pos(mousePos.x(), mousePos.y());

    CoordinateConverter::PointD currentPos = m_converter.convert(pos);
//    std::cout << currentPos.x << ", " << currentPos.y << std::endl;

    if (Qt::LeftButton & event->buttons()) {
        double tx = currentPos.x - m_mousePosition.x;
        double ty = currentPos.y - m_mousePosition.y;

        for (auto it : m_selection) {
            Translator::translate(it, tx, ty);
        }
    } else
    if (Qt::RightButton & event->buttons()) {
        CoordinateConverter::PointD origin = m_converter.getOrigin();

        CoordinateConverter::PointD newPos {
            origin.x - (currentPos.x - m_mousePosition.x),
            origin.y - (currentPos.y - m_mousePosition.y) };
        m_converter.setOrigin(newPos);
    }

    m_mousePosition = m_converter.convert(pos);
//    std::cout << currentPos.x - m_mousePosition.x << ", " << currentPos.y - m_mousePosition.y << std::endl;
    update();
}

void GeometryEditor::wheelEvent(QWheelEvent* event) {
    m_converter.setRatio(
            m_converter.getRatio() * (1.0 + event->delta() / 1200.0));
    update();
}

} /* namespace geoedit */

