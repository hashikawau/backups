//========================================
// EditEllipsePage.cpp
//
//  Created on: 2013/12/23
//      Author: you
//========================================

#include "EditEllipsePage.h"

#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>

#include "model/Ellipse.h"

#include "view/ModelEditView.h"

namespace geoedit {

EditEllipsePage::EditEllipsePage(QWidget* parent)
        : QWidget(parent),
                m_shape(nullptr)
{
    auto layout_0 = new QVBoxLayout();
    setLayout(layout_0);
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto widget = new QLabel(tr("Ellipse"));
            layout_1->addWidget(widget);
        }
    }
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto widget = new QLabel(tr("Center X: "));
            layout_1->addWidget(widget);
        }
        {
            auto widget = new QLineEdit();
            layout_1->addWidget(widget);
            connect(widget, &QLineEdit::textChanged,
                    this, &EditEllipsePage::setValue);
            m_centerX = widget;
        }
    }
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto widget = new QLabel(tr("Center Y: "));
            layout_1->addWidget(widget);
        }
        {
            auto widget = new QLineEdit();
            layout_1->addWidget(widget);
            connect(widget, &QLineEdit::textChanged,
                    this, &EditEllipsePage::setValue);
            m_centerY = widget;
        }
    }
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto widget = new QLabel(tr("Radius X: "));
            layout_1->addWidget(widget);
        }
        {
            auto widget = new QLineEdit();
            layout_1->addWidget(widget);
            connect(widget, &QLineEdit::textChanged,
                    this, &EditEllipsePage::setValue);
            m_radiusX = widget;
        }
    }
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto widget = new QLabel(tr("Radius Y: "));
            layout_1->addWidget(widget);
        }
        {
            auto widget = new QLineEdit();
            layout_1->addWidget(widget);
            connect(widget, &QLineEdit::textChanged,
                    this, &EditEllipsePage::setValue);
            m_radiusY = widget;
        }
    }
    {
        layout_0->addStretch();
    }
}

EditEllipsePage::~EditEllipsePage() {
}

void EditEllipsePage::setModel(Ellipse* shape) {
    m_shape = shape;
    m_centerX->setText(QString::number(m_shape->eGet<Ellipse::X>()));
    m_centerY->setText(QString::number(m_shape->eGet<Ellipse::Y>()));
    m_radiusX->setText(QString::number(m_shape->eGet<Ellipse::RX>()));
    m_radiusY->setText(QString::number(m_shape->eGet<Ellipse::RY>()));
}

//private slots
void EditEllipsePage::setValue(const QString& text) {
    if (m_shape != nullptr) {
        bool ok;
        double value = text.toDouble(&ok);
        if (ok) {
            auto widget = sender();
            if (widget == m_centerX) {
                m_shape->eSet<Ellipse::X>(value);
            } else
            if (widget == m_centerY) {
                m_shape->eSet<Ellipse::Y>(value);
            } else
            if (widget == m_radiusX) {
                m_shape->eSet<Ellipse::RX>(value);
            } else
            if (widget == m_radiusY) {
                m_shape->eSet<Ellipse::RY>(value);
            }

            parentWidget()->parentWidget()->parentWidget()->parentWidget()->update();
            static_cast<ModelEditView*>(parentWidget()->parentWidget()->parentWidget())->updateListViewModel();
        }
    }
}

} /* namespace geoedit */
