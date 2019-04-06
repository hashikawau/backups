//========================================
// ModelEditView.h
//
//  Created on: 2013/12/20
//      Author: you
//========================================

#ifndef MODELEDITVIEW_H_
#define MODELEDITVIEW_H_

#include <qwidget.h>

#include <QtCore/qabstractitemmodel.h>

#include "IModel.h"

#include <iostream>
#include <QtCore/qmimedata.h>

class QItemSelectionModel;
class QStackedLayout;

namespace sample {

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
        int size() const {
            return m_modelRoot->size();
        }
        IModel* get(int index) const {
            return m_modelRoot->get(index);
        }
        void add(IModel* model) {
            m_modelRoot->add(model);
        }
        void remove(IModel* model) {
            m_modelRoot->remove(model);
        }

    private:
        ModelRoot* m_modelRoot;

    public:
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const
                override;
        virtual QVariant data(const QModelIndex& index, int role) const
                override;

//        virtual bool removeRows(
//            int row,
//            int count,
//            const QModelIndex& parent = QModelIndex()) override
//            {
//            std::cout << "removeRows()" << std::endl;
//            return true;
//        }
        virtual Qt::DropActions supportedDropActions() const override
        {
            return /*Qt::CopyAction |*/Qt::TargetMoveAction;
        }
        virtual Qt::ItemFlags flags(const QModelIndex &index) const override
        {
            std::cout << "flags(): " << index.row() << std::endl;
            Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

            if (index.isValid()) {
                if (index.parent().row() == -1)
                return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled
                    | defaultFlags;
                else
                return Qt::ItemIsDropEnabled | defaultFlags;
            } else {
                return Qt::ItemIsDropEnabled | defaultFlags;
            }
        }
        QStringList mimeTypes() const override
        {
            std::cout << "mimeTypes(): " << std::endl;
            QStringList types;
            types << "text/plain";
//            return types;
            return QStringList() << "text/plain";
        }
        QMimeData* mimeData(const QModelIndexList &indexes) const override
        {
            std::cout << "mimeData()" << std::endl;
            QMimeData *mimeData = new QMimeData();

//            QByteArray encodedData;
//            QDataStream stream(&encodedData, QIODevice::WriteOnly);
//
//            foreach (QModelIndex index, indexes){
//            if (index.isValid()) {
//                QString text = data(index, Qt::DisplayRole).toString();
//                stream << text;
//                }
//            }

//            mimeData->setData("text/plain", encodedData);
            mimeData->setText("");
            return mimeData;
//            return new QMimeData();
//            return nullptr;
        }
        bool dropMimeData(const QMimeData *data,
            Qt::DropAction action, int row, int column,
            const QModelIndex &parent) override
            {
            std::cout << "dropMimeData(): "
                << (data->hasText() ? data->text().toStdString() : "no text")
                << ": "
                << row << ", "
                << column << ", "
                << parent.row() << std::endl;
            return false;

            if (action == Qt::IgnoreAction)
            return true;

            if (!data->hasFormat("application/vnd.text.list"))
            return false;

            if (column > 0)
            return false;
        }
    };

public:
    ModelEditView(ModelRoot* modelRoot, QWidget* parent = 0);
    virtual ~ModelEditView();

private slots:
    void selectionChanged(const QModelIndex & current,
        const QModelIndex & previous);
    void addModelA();
    void addModelB();
    void delItem();

private:
    ViewModel* m_viewModel;
    QItemSelectionModel* m_selectionModel;
    QStackedLayout* m_editPage;
    IModel* m_selected;

};

} /* namespace sample */

#endif /* MODELEDITVIEW_H_ */
