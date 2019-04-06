//========================================
// MainController.cpp
//
//  Created on: 2013/10/31
//      Author: you
//========================================

#include "MainController.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QSplitter>
#include <QScrollArea>

#include <iostream>

#include "ModelEditView.h"

namespace sample {

MainController::MainController(QWidget* window) {

    window->setWindowTitle("qt list view sample");

    QHBoxLayout* layout = new QHBoxLayout();
    window->setLayout(layout);
    {
        QSplitter* splitter = new QSplitter(Qt::Horizontal);
        layout->addWidget(splitter);
        {
            QScrollArea* area = new QScrollArea();
            splitter->addWidget(area);
        }
        {
            QWidget* widget = new ModelEditView(&m_modelRoot);
            splitter->addWidget(widget);
        }
    }
}

MainController::~MainController() {
}

void MainController::clicked(const QModelIndex& index) {
//    std::cout << index.model()->parent() << std::endl;
//    std::cout << static_cast<const QStandardItemModel*>(index.model())->item(index.row(), 0)->text().toStdString().c_str() << std::endl;
//    std::cout << index.data(Qt::DisplayRole).toString().toStdString().c_str() << std::endl;
//    std::cout << index.row() << ", " << index.column() << std::endl;
}

} /* namespace sample */

