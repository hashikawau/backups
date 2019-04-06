//========================================
// ModelEditView.h
//
//  Created on: 2013/12/20
//      Author: you
//========================================

#ifndef MODELEDITVIEW_H_
#define MODELEDITVIEW_H_

#include <QtWidgets/qwidget.h>

#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qitemselectionmodel.h>

#include "model/ModelRoot.h"

namespace geoedit {

class ShowShapeEditPage;

/*
 *
 */
class ModelEditView: public QWidget {
Q_OBJECT

private:
    class ViewModel: public QAbstractListModel {
    public:
        ViewModel(ModelRoot* modelRoot);
        virtual ~ViewModel();
        //    QWidget* getEditPages() {
//        return m_selection != nullptr ? m_selection->getEditPage() : nullptr;
//    }
        void setSelectionModel(QItemSelectionModel* selModel) {
            m_selectionModel = selModel;
        }
        int getSelectionIndex() const {
            return m_selectionModel->currentIndex().row();
        }
        void setSelectionIndex(int row,
            QItemSelectionModel::SelectionFlags flag =
                QItemSelectionModel::ClearAndSelect) {
            m_selectionModel->setCurrentIndex(
                                              index(row, 0),
                                              flag);
        }

        int size() const {
            return m_modelRoot->size();
        }
        IShape* get(int index) const {
            return m_modelRoot->get(index);
        }
        void add(IShape* model) {
            m_modelRoot->add(model);
            emit dataChanged(index(0), index(size() - 1), { Qt::DisplayRole });
            emit layoutChanged();
        }
        void remove(IShape* model) {
            int row = m_modelRoot->remove(model);
//            std::cout << row << std::endl;
            if (row < size() + 1) {
//                auto indexModel = index(row, 0, QModelIndex());
                emit dataChanged(index(0), index(size() - 1),
                                 { Qt::DisplayRole });
                emit layoutChanged();
            }
        }

    private:
        ModelRoot* m_modelRoot;
        QItemSelectionModel* m_selectionModel;

    public:
        virtual int rowCount(
            const QModelIndex &parent = QModelIndex()) const override;
        virtual QVariant data(
            const QModelIndex& index, int role) const override;
        //        virtual bool insertRows(
//                int row,
//                int count,
//                const QModelIndex &parent = QModelIndex()) override;
//        virtual bool removeRows(
//                int row,
//                int count,
//                const QModelIndex &parent = QModelIndex()) override;
        virtual Qt::DropActions supportedDropActions() const override {
            return Qt::MoveAction;
        }
        virtual bool removeRows(
            int row,
            int count,
            const QModelIndex& parent = QModelIndex()) override
            {
            return true;
        }
        virtual Qt::ItemFlags flags(const QModelIndex &index) const override
        {
            Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

            if (index.isValid())
                return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
            else
                return Qt::ItemIsDropEnabled | defaultFlags;
        }

    };

public:
    ModelEditView(ModelRoot* modelRoot, QWidget* parent = 0);
    virtual ~ModelEditView();

    void updateListViewModel() {
        m_viewModel->dataChanged(
                                 m_viewModel->index(0, 0),
                                 m_viewModel->index(m_viewModel->size() - 1),
                                 { Qt::DisplayRole });
    }

private slots:
    void selectionChanged(const QModelIndex & current,
        const QModelIndex & previous);
    void addRectangle();
    void addEllipse();
    void delItem();

private:
    ViewModel* m_viewModel;
    //    QItemSelectionModel* m_selectionModel;
//    QStackedLayout* m_editPage;
//    IShape* m_selected;
    ShowShapeEditPage* m_editPage;

};

} /* namespace geoedit */

#endif /* MODELEDITVIEW_H_ */
