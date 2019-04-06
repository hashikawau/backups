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
//#include <vector>

#include "ShowShapeEditPage.h"
#include "model/Rectangle.h"
#include "model/Ellipse.h"
#include "view/list/ExtractListViewLabelOperation.h"

namespace geoedit {

ModelEditView::ModelEditView(ModelRoot* modelRoot, QWidget* parent)
        : QWidget(parent),
            m_viewModel(new ViewModel(modelRoot))
{
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
//            listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
            listView->setDragEnabled(true);
            listView->setAcceptDrops(true);
            listView->setDropIndicatorShown(true);

            auto selModel = new QItemSelectionModel(m_viewModel);
            m_viewModel->setSelectionModel(selModel);
            connect(selModel, &QItemSelectionModel::currentChanged,
                    this,
                    &ModelEditView::selectionChanged);
            listView->setSelectionModel(selModel);

            auto layout_2 = new QHBoxLayout();
            layout_1->addLayout(layout_2);
            {
                layout_2->addStretch(0);
            }
            {
                QPushButton* addButton = new QPushButton(tr("add Rectangle"));
                layout_2->addWidget(addButton);
                connect(addButton, &QPushButton::pressed, this,
                        &ModelEditView::addRectangle);
            }
            {
                QPushButton* addButton = new QPushButton(tr("add Ellipse"));
                layout_2->addWidget(addButton);
                connect(addButton, &QPushButton::pressed, this,
                        &ModelEditView::addEllipse);
            }
            {
                QPushButton* delButton = new QPushButton(tr("delete"));
                layout_2->addWidget(delButton);
                connect(delButton, &QPushButton::pressed, this,
                        &ModelEditView::delItem);
            }
        }
    }

    m_editPage = new ShowShapeEditPage();
    splitter->addWidget(m_editPage);
}

ModelEditView::~ModelEditView() {
}

ModelEditView::ViewModel::ViewModel(ModelRoot* modelRoot)
        : m_modelRoot(modelRoot),
            m_selectionModel(nullptr)
{
    m_modelRoot->addModelChangeListner([&]() -> void {
        emit dataChanged(index(0, 0), index(m_modelRoot->size(), 0));
    });
    m_modelRoot->addSelectionChangeListner(
            [&](const std::vector<IShape*>& selection) -> void {
                for(auto key: selection) {
//        IShape* key = selection.get()[0];
                    int rowIndex = 0;
                    for(auto& it: m_modelRoot->getShapes()) {
                        if(it.get() == key) {
                            break;
                        }
                        ++rowIndex;
                    }
                    setSelectionIndex(rowIndex);
                }
            });
}

ModelEditView::ViewModel::~ViewModel() {
}

int ModelEditView::ViewModel::rowCount(const QModelIndex&) const {
    return m_modelRoot->size();
}
QVariant ModelEditView::ViewModel::data(const QModelIndex& index,
    int role) const {
    if (role == Qt::DisplayRole) {
        if (index.isValid()) {
            int i = index.row();
            if (i < size()) {
                ExtractListViewLabelOperation o;
                IShape* s = m_modelRoot->get(i);
                return QVariant(o.getString(s));
            }
        }
    }
    return QVariant();

}

void ModelEditView::selectionChanged(const QModelIndex & current,
    const QModelIndex&) {
    int index = current.row();
    std::cout << "selectionCanged(): " << index << std::endl;

    if (index >= 0) {
        auto selected = m_viewModel->get(index);

        m_editPage->changeEditPage(selected);
    }
}

void ModelEditView::addRectangle() {
//    static double d = 0.01;
    m_viewModel->add(new Rectangle(-0.5, 0.5, -0.5, 0.5));
    m_viewModel->setSelectionIndex(m_viewModel->size() - 1);
    parentWidget()->update();

//    d += 0.02;
}
void ModelEditView::addEllipse() {
    m_viewModel->add(new Ellipse(0.0, 0.0, 0.5, 0.5));
    m_viewModel->setSelectionIndex(0);
    parentWidget()->update();
}
void ModelEditView::delItem() {
    auto i = m_viewModel->getSelectionIndex();
    if (i >= 0 && i < m_viewModel->size()) {
        m_viewModel->remove(m_viewModel->get(i));
        if (i != 0) {
            m_viewModel->setSelectionIndex(i - 1);
        } else {
            m_viewModel->setSelectionIndex(-1);
            m_viewModel->setSelectionIndex(0);
        }
        parentWidget()->update();
    }
}

} /* namespace geoedit */
