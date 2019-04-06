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

namespace sample {

class MainController: public QObject {
Q_OBJECT

public:
    MainController(QWidget* window);
    virtual ~MainController();

private slots:
    void clicked(const QModelIndex& index);

private:
    ModelRoot m_modelRoot;
    std::unique_ptr<ModelRoot> p;

};

} /* namespace sample */

#endif /* qtsample_00_MAINCONTROLLER_H_ */
