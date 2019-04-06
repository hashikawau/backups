//========================================
// MainController.cpp
//
//  Created on: 2013/10/31
//      Author: you
//========================================

#include "MainController.h"
#include "FindDialog.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

#include <QListView>
#include <QtCore/QStringListModel>

#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QHeaderView.h>
#include <QtWidgets/QDirModel>
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

#include <iostream>
#include <typeinfo>

MainController::MainController(QWidget* window) {

    window->setWindowTitle("サンプル 00");

    QHBoxLayout* layout = new QHBoxLayout();
    window->setLayout(layout);
    {
//  QSpinBox* spinBox = new QSpinBox(window);
        QSpinBox* spinBox = new QSpinBox();
        QSlider* slider = new QSlider(Qt::Horizontal);
        spinBox->setRange(0, 130);
        slider->setRange(0, 130);

        QObject::connect(spinBox, SIGNAL(valueChanged(int)), this,
                SLOT(setValue(int)));
        QObject::connect(slider, SIGNAL(valueChanged(int)), this,
                SLOT(setValue(int)));

        QObject::connect(this, SIGNAL(valueChanged(int)), slider,
                SLOT(setValue(int)));
        QObject::connect(this, SIGNAL(valueChanged(int)), spinBox,
                SLOT(setValue(int)));

        spinBox->setValue(35);

        layout->addWidget(spinBox);
        layout->addWidget(slider);
    }

    {
//        FindDialog* dialog = new FindDialog();
//    layout->addWidget(dialog);
//    dialog->show();
    }

    {
        QStringList strings;
        strings << tr("aaa") << tr("bbb") << tr("ccc");
        QStringListModel* model = new QStringListModel(this);
        model->setStringList(strings);

        QListView* listView = new QListView();
        layout->addWidget(listView);
        listView->setModel(model);
    }

    {
        QDirModel* model = new QDirModel();
        model->setReadOnly(false);
        model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

        QTreeView* treeView = new QTreeView();
        layout->addWidget(treeView);
        treeView->setModel(model);
        treeView->header()->setStretchLastSection(true);
        treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
        treeView->header()->setSortIndicatorShown(true);
        treeView->header()->setSectionsClickable(true);
        QModelIndex index = model->index(QDir::currentPath());
        treeView->expand(index);
        treeView->scrollTo(index);
        treeView->resizeColumnToContents(0);
    }

    {
        std::cout << this << std::endl;
        m_listViewModel = new ListViewModel();
        QItemSelectionModel* selmodel = new QItemSelectionModel(m_listViewModel);
        connect(selmodel, SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_listViewModel, SLOT(selectionChanged(const QModelIndex&, const QModelIndex&)));

        QSplitter* splitter = new QSplitter(Qt::Vertical);
        layout->addWidget(splitter);
        {
            m_listView = new QListView();
            splitter->addWidget(m_listView);
            m_listView->setModel(m_listViewModel);
            m_listView->setSelectionModel(selmodel);

            QWidget* editPage = new QWidget();
            splitter->addWidget(editPage);
            {
                auto editPages = m_listViewModel->getEditPages();
                editPage->setLayout(editPages);
            }

            QPushButton* addButton = new QPushButton(tr("add"));
            splitter->addWidget(addButton);
            connect(addButton, SIGNAL(pressed()), m_listViewModel, SLOT(addItem()));

            QPushButton* delButton = new QPushButton(tr("del"));
            splitter->addWidget(delButton);
            connect(delButton, SIGNAL(pressed()), m_listViewModel, SLOT(delItem()));
        }
    }

//    m_currentSelection = 0;
}

MainController::~MainController() {
}

void MainController::setValue(int value) {
//    std::cout << "setValue()" << std::endl;
//    if (30 < value && value < 100) {
    m_value = value;
    emit valueChanged(m_value);
//    }
}

void MainController::clicked(const QModelIndex& index) {
    std::cout << index.model()->parent() << std::endl;
    std::cout << static_cast<const QStandardItemModel*>(index.model())->item(index.row(), 0)->text().toStdString().c_str() << std::endl;
    std::cout << index.data(Qt::DisplayRole).toString().toStdString().c_str() << std::endl;
//    std::cout << index.row() << ", " << index.column() << std::endl;
}

void ListViewModel::setX(const QString& text) {
//    IModel* selection = m_model->getSelection();
    if (m_selection != 0) {
//        bool ok;
//        double value = text.toDouble(&ok);
//        if (ok) {
//            m_selection->x = value;
//            emit dataChanged(QModelIndex(), QModelIndex(), {Qt::DisplayRole});
//        }
    }
}
void ListViewModel::setY(const QString& text) {
//    IModel* selection = m_model->getSelection();
    if (m_selection != 0) {
//        bool ok;
//        double value = text.toDouble(&ok);
//        if (ok) {
//            m_selection->y = value;
//            emit dataChanged(QModelIndex(), QModelIndex(), {Qt::DisplayRole});
//        }
    }
}

ListViewModel::ListViewModel()
        : m_editPages(new QStackedLayout()),
                m_selection(nullptr)
{

//    m_data.push_back(new ModelB(1, 2));
//    m_data.push_back(new ModelB(2, 1));
//    m_data.push_back(new ModelA(3));
}

int ListViewModel::rowCount(const QModelIndex&) const {
//    std::cout << m_data.size() << std::endl;
    return m_modelRoot.size();
}
QVariant ListViewModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        return QVariant(
                tr("x, y = ") + QString(m_modelRoot.get(index.row())->toString().c_str()));
    } else {
        return QVariant();
    }
}

void ListViewModel::selectionChanged(const QModelIndex & current, const QModelIndex&) {
    int index = current.row();
//    m_currentSelection = m_model->get(index);
    m_selection = m_modelRoot.get(index);
//    std::cout << index << ", " << m_currentSelection->toString() << std::endl;

    QWidget* edit = m_editPages->parent()->findChild<QWidget*>(QString::number(index));
    if (edit == 0) {
        edit = new QWidget();
        edit->setObjectName(QString::number(index));
        m_editPages->addWidget(edit);
        std::cout << "not created: " << edit->objectName().toStdString() << std::endl;
        {
            {
                QVBoxLayout* layout_0 = new QVBoxLayout();
                edit->setLayout(layout_0);
                {
                    QHBoxLayout* layout_0_1 = new QHBoxLayout();
                    layout_0->addLayout(layout_0_1);

                    QLabel *label = new QLabel(tr("x_") + QString::number(index) + tr(": "));
                    layout_0_1->addWidget(label);

                    QLineEdit* lineEdit = new QLineEdit(QString(m_selection->toString().c_str()));
                    layout_0_1->addWidget(lineEdit);
                    connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setX(const QString&)));
                }
                {
                    QHBoxLayout* layout_0_2 = new QHBoxLayout();
                    layout_0->addLayout(layout_0_2);

                    QLabel *label = new QLabel(tr("y_") + QString::number(index) + tr(": "));
                    layout_0_2->addWidget(label);

                    QLineEdit* lineEdit = new QLineEdit(QString(m_selection->toString().c_str()));
                    layout_0_2->addWidget(lineEdit);
                    connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setY(const QString&)));
                }
            }
        }
    }
    m_editPages->setCurrentWidget(edit);
}

void ListViewModel::addItem() {
//    std::cout << "add" << std::endl;
    m_modelRoot.add(new ModelB(0, 0));
    emit dataChanged(QModelIndex(), QModelIndex(), { Qt::DisplayRole });
}
void ListViewModel::delItem() {
//    std::cout << "delete" << std::endl;
    if (m_selection) {
        m_modelRoot.remove(m_selection);
        emit dataChanged(QModelIndex(), QModelIndex(), { Qt::DisplayRole });
    }
}

