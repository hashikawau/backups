//========================================
// ShowShapeEditPage.cpp
//
//  Created on: 2013/12/22
//      Author: you
//========================================

#include "ShowShapeEditPage.h"

#include <QtWidgets/qstackedlayout.h>
#include <QtWidgets/qpushbutton.h>

#include "view/edit/EditRectanglePage.h"
#include "view/edit/EditEllipsePage.h"

#include <iostream>

namespace geoedit {

ShowShapeEditPage::ShowShapeEditPage(QWidget* parent)
        : QWidget(parent),
                m_layout(new QStackedLayout())
{
    setLayout(m_layout);
    for (auto& page : m_pages) {
        page = nullptr;
    }
}

ShowShapeEditPage::~ShowShapeEditPage() {
//    std::cout << "~ShowShapeEditPage()" << std::endl;
}

void ShowShapeEditPage::operate(Rectangle* shape) {
//    std::cout << "operate(Rectangle*)" << std::endl;
    int index = static_cast<int>(SHAPES::RECTANGLE);
    auto page = static_cast<EditRectanglePage*>(m_pages[index]);
    if (page == nullptr) {
        page = new EditRectanglePage();
        m_pages[index] = page;
        m_layout->addWidget(page);
    }
    page->setModel(shape);
    m_layout->setCurrentIndex(index);
}

void ShowShapeEditPage::operate(Ellipse* shape) {
//    std::cout << "operate(Rectangle*)" << std::endl;
    int index = static_cast<int>(SHAPES::ELLIPSE);
    auto page = static_cast<EditEllipsePage*>(m_pages[index]);
    if (page == nullptr) {
        page = new EditEllipsePage();
        m_pages[index] = page;
        m_layout->addWidget(page);
    }
    page->setModel(shape);
    m_layout->setCurrentIndex(index);
}

}
/* namespace geoedit */
