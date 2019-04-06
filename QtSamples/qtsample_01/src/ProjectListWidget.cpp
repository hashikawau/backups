//========================================
// ProjectListWidget.cpp
//
//  Created on: 2013/11/16
//      Author: you
//========================================

#include "ProjectListWidget.h"

#include <QtWidgets/QApplication>
#include <QtGui/qevent.h>
#include <QtGui/QDrag>
#include <QtCore/QMimeData>

ProjectListWidget::ProjectListWidget(QWidget* parent)
        : QListWidget(parent) {
    setAcceptDrops(true);

    addItem(tr("aaa"));
    addItem(tr("bbb"));
    addItem(tr("ccc"));
}

ProjectListWidget::~ProjectListWidget() {
}

void ProjectListWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) startPos = event->pos();
    QListWidget::mousePressEvent(event);
}

void ProjectListWidget::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()) {
            performDrag();
        }
    }
}

void ProjectListWidget::performDrag() {
    QListWidgetItem* item = currentItem();
    if (item) {
        QMimeData* mimeData = new QMimeData();
        mimeData->setText(item->text());

        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap(":/images/eclipse32.png"));
        if (drag->exec(Qt::MoveAction) == Qt::MoveAction) delete item;
    }
}

void ProjectListWidget::dragEnterEvent(QDragEnterEvent* event) {
    ProjectListWidget* source = qobject_cast<ProjectListWidget*>(
            event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::dragMoveEvent(QDragMoveEvent* event) {
    ProjectListWidget* source = qobject_cast<ProjectListWidget*>(
            event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::dropEvent(QDropEvent* event) {
    ProjectListWidget* source = qobject_cast<ProjectListWidget*>(
            event->source());
    if (source && source != this) {
        addItem(event->mimeData()->text());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

