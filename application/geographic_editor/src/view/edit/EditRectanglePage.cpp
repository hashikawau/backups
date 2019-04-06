//========================================
// EditRectanglePage.cpp
//
//  Created on: 2013/12/23
//      Author: you
//========================================

#include "EditRectanglePage.h"

#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>

#include "model/Rectangle.h"

#include "view/ModelEditView.h"

namespace geoedit {

EditRectanglePage::EditRectanglePage(QWidget* parent)
        : QWidget(parent),
                m_shape(nullptr)
{
    auto layout_0 = new QVBoxLayout();
    setLayout(layout_0);
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto widget = new QLabel(tr("Rectangle"));
            layout_1->addWidget(widget);
        }
    }
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto widget = new QLabel(tr("Left: "));
            layout_1->addWidget(widget);
        }
        {
            auto widget = new QLineEdit();
            layout_1->addWidget(widget);
            connect(widget, &QLineEdit::textChanged,
                    this, &EditRectanglePage::setValue);
            m_left = widget;
        }
    }
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto widget = new QLabel(tr("Right: "));
            layout_1->addWidget(widget);
        }
        {
            auto widget = new QLineEdit();
            layout_1->addWidget(widget);
            connect(widget, &QLineEdit::textChanged,
                    this, &EditRectanglePage::setValue);
            m_right = widget;
        }
    }
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto widget = new QLabel(tr("Bottom: "));
            layout_1->addWidget(widget);
        }
        {
            auto widget = new QLineEdit();
            layout_1->addWidget(widget);
            connect(widget, &QLineEdit::textChanged,
                    this, &EditRectanglePage::setValue);
            m_bottom = widget;
        }
    }
    {
        auto layout_1 = new QHBoxLayout();
        layout_0->addLayout(layout_1);
        {
            auto widget = new QLabel(tr("Top: "));
            layout_1->addWidget(widget);
        }
        {
            auto widget = new QLineEdit();
            layout_1->addWidget(widget);
            connect(widget, &QLineEdit::textChanged,
                    this, &EditRectanglePage::setValue);
            m_top = widget;
        }
    }
    {
        layout_0->addStretch();
    }
}
EditRectanglePage::~EditRectanglePage() {
//    std::cout << "~EditRectanglePage()" << std::endl;
}

void EditRectanglePage::setModel(Rectangle* shape) {
    m_shape = shape;
    m_left->setText(QString::number(m_shape->eGet<Rectangle::LEFT>()));
    m_right->setText(QString::number(m_shape->eGet<Rectangle::RIGHT>()));
    m_bottom->setText(QString::number(m_shape->eGet<Rectangle::BOTTOM>()));
    m_top->setText(QString::number(m_shape->eGet<Rectangle::TOP>()));
}

//private slots
void EditRectanglePage::setValue(const QString& text) {
    if (m_shape != nullptr) {
        bool ok;
        double value = text.toDouble(&ok);
        if (ok) {
            auto widget = sender();
            if (widget == m_left) {
                m_shape->eSet<Rectangle::LEFT>(value);
            } else
            if (widget == m_right) {
                m_shape->eSet<Rectangle::RIGHT>(value);
            } else
            if (widget == m_bottom) {
                m_shape->eSet<Rectangle::BOTTOM>(value);
            } else
            if (widget == m_top) {
                m_shape->eSet<Rectangle::TOP>(value);
            }

            parentWidget()->parentWidget()->parentWidget()->parentWidget()->update();
            static_cast<ModelEditView*>(parentWidget()->parentWidget()->parentWidget())->updateListViewModel();
        }
    }
}

} /* namespace geoedit */
