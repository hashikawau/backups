//========================================
// ProjectListWidget.h
//
//  Created on: 2013/11/16
//      Author: you
//========================================

#ifndef qtsample_01_PROJECTLISTWIDGET_H_
#define qtsample_01_PROJECTLISTWIDGET_H_

#include <QtWidgets/QListWidget>

/*
 *
 */
class ProjectListWidget: public QListWidget {
Q_OBJECT

public:
    ProjectListWidget(QWidget* parent = 0);
    virtual ~ProjectListWidget();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dragMoveEvent(QDragMoveEvent* event);
    virtual void dropEvent(QDropEvent* event);

private:
    void performDrag();
    QPoint startPos;

};

#endif /* qtsample_01_PROJECTLISTWIDGET_H_ */
