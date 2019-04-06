//========================================
// ModelEditView.cpp
//
//  Created on: 2013/12/20
//      Author: you
//========================================

#include "ModelEditView.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qstackedlayout.h>
#include <QtWidgets/qsplitter.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qpushbutton.h>

#include <QtWidgets/qlabel.h>
#include <iostream>

namespace sample {

ModelEditView::ModelEditView(ModelRoot* modelRoot, QWidget* parent)
        : QWidget(parent),
                m_viewModel(new ViewModel(modelRoot)),
                m_selectionModel(new QItemSelectionModel(m_viewModel)),
                m_selected(nullptr)
{
//    std::cout << this << std::endl;
//    m_viewModel = new ViewModel(modelRoot);

    auto layout_0 = new QVBoxLayout();
    setLayout(layout_0);

    auto splitter = new QSplitter(Qt::Vertical);
    layout_0->addWidget(splitter);
    {
        auto listPage = new QWidget();
        splitter->addWidget(listPage);

        auto layout_1 = new QVBoxLayout();
        listPage->setLayout(layout_1);

        {
            auto listView = new QListView();
            layout_1->addWidget(listView);
            listView->setModel(m_viewModel);
            listView->setDragEnabled(true);
            listView->setAcceptDrops(true);
            listView->setDropIndicatorShown(true);
            listView->setDragDropMode(QAbstractItemView::InternalMove);
            listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

//            QItemSelectionModel* selmodel = new QItemSelectionModel(m_viewModel);
            connect(m_selectionModel, &QItemSelectionModel::currentChanged,
                    this, &ModelEditView::selectionChanged);
            listView->setSelectionModel(m_selectionModel);

            auto layout_2 = new QHBoxLayout();
            layout_1->addLayout(layout_2);
            {
                layout_2->addStretch(0);
            }
            {
                QPushButton* addButton = new QPushButton(tr("add A"));
                layout_2->addWidget(addButton);
                connect(addButton, &QPushButton::pressed, this, &ModelEditView::addModelA);
            }
            {
                QPushButton* addButton = new QPushButton(tr("add B"));
                layout_2->addWidget(addButton);
                connect(addButton, &QPushButton::pressed, this, &ModelEditView::addModelB);
            }
            {
                QPushButton* delButton = new QPushButton(tr("del"));
                layout_2->addWidget(delButton);
                connect(delButton, &QPushButton::pressed, this, &ModelEditView::delItem);
            }
        }
    }

    auto editPageWidget = new QWidget();
    splitter->addWidget(editPageWidget);
    {
        m_editPage = new QStackedLayout();
        editPageWidget->setLayout(m_editPage);
//            auto editPages = m_listViewModel->getEditPages();
//            editPage->setLayout(editPages);
    }
}

ModelEditView::~ModelEditView() {
}

ModelEditView::ViewModel::ViewModel(ModelRoot* modelRoot)
        : m_modelRoot(modelRoot)
{
}

ModelEditView::ViewModel::~ViewModel() {
}

int ModelEditView::ViewModel::rowCount(const QModelIndex&) const {
    return m_modelRoot->size();
}
QVariant ModelEditView::ViewModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        return QVariant(QString::fromStdString(m_modelRoot->get(index.row())->toString()));
    } else {
        return QVariant();
    }
}

void ModelEditView::selectionChanged(const QModelIndex & current, const QModelIndex&) {
    int index = current.row();
//    m_currentSelection = m_model->get(index);
    m_selected = m_viewModel->get(index);
//    std::cout << index << ", " << m_selected->toString() << std::endl;

    if(m_selected){
        m_editPage->removeWidget(m_editPage->currentWidget());
        QWidget* widget = m_selected->getEditPage();
        m_editPage->addWidget(widget);
        m_editPage->setCurrentWidget(widget);
//        m_editPage->parentWidget()->update();
    }
}

void ModelEditView::addModelA() {
//    std::cout << "add" << std::endl;
    m_viewModel->add(new ModelA(0));
    emit m_viewModel->dataChanged(QModelIndex(), QModelIndex(), { Qt::DisplayRole });
    m_selectionModel->select(QModelIndex(), QItemSelectionModel::NoUpdate);
}
void ModelEditView::addModelB() {
//    std::cout << "add" << std::endl;
    m_viewModel->add(new ModelB(0, 0));
    emit m_viewModel->dataChanged(QModelIndex(), QModelIndex(), { Qt::DisplayRole });
}
void ModelEditView::delItem() {
//    std::cout << "delete" << std::endl;
    if (m_selected) {
        m_viewModel->remove(m_selected);
        emit m_viewModel->dataChanged(QModelIndex(), QModelIndex(), { Qt::DisplayRole });
    }
}

} /* namespace sample */
