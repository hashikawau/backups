//========================================
// MainController.h
//
//  Created on: 2013/10/31
//      Author: you
//========================================

#ifndef qtsample_00_MAINCONTROLLER_H_
#define qtsample_00_MAINCONTROLLER_H_

#include <QtCore/qobject.h>
#include <QWidget>

#include <QListView>
#include <QtCore/qabstractitemmodel.h>

#include <memory>

#include "IModel.h"

class QWidget;
class QLabel;
class QStackedLayout;

//--->
class ListViewModel: public QAbstractListModel {
Q_OBJECT

public:
    ListViewModel();
    //    std::vector<IModel*> m_data;
//    IModel* get(int index) {
//        return m_modelRoot.get(index);
//    }
//
//    IModel* getSelection() {
//        return m_selection;
//    }
//    void add(IModel* model) {
//        m_modelRoot.add(model);
//    }
//    void remove(IModel* model) {
//        m_modelRoot.remove(model);
//    }
    QStackedLayout* getEditPages() {
        return m_editPages;
    }

private:
    QStackedLayout* m_editPages;
    ModelRoot m_modelRoot;
    IModel* m_selection;

public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const
            override;
    virtual QVariant data(const QModelIndex& index, int role) const
            override;

private slots:
    void selectionChanged(const QModelIndex & current, const QModelIndex & previous);
    void setX(const QString& text);
    void setY(const QString& text);
    void addItem();
    void delItem();

};
//<---

class MainController: public QObject {
Q_OBJECT

public:
    MainController(QWidget* window);
    virtual ~MainController();

signals:
    void valueChanged(int value);

private slots:
    void setValue(int value);
    void clicked(const QModelIndex& index);

private:
    int m_value;

//    class ViewModel01: public QAbstractListModel {
//    public:
//        ViewModel01();
//        std::vector<IModel*> m_data;
//
//    public:
//        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const
//                override;
//        virtual QVariant data(const QModelIndex& index, int role) const
//                override;
//
//    };
//    ViewModel01* m_model;
    ListViewModel* m_listViewModel;

    QListView* m_listView;

//    IModel* m_currentSelection;
};

#endif /* qtsample_00_MAINCONTROLLER_H_ */
