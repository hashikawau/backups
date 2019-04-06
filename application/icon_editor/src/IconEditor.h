//========================================
// IconEditor.h
//
//  Created on: 2013/12/07
//      Author: you
//========================================

#ifndef ICONEDITOR_H_
#define ICONEDITOR_H_

#include <QtWidgets/qwidget.h>
#include <QtGui/qimage.h>

#include <vector>

#include "OperationHistory.h"

//class QScrollArea;
class QSpinBox;

/*
 *
 */
class IconEditor: public QWidget {
Q_OBJECT

public:
    IconEditor(QWidget* parent = 0);
    virtual ~IconEditor();

    void load(const QString& filepath);
    void save(const QString &fileName, const char* format = 0, int quality = -1);
    void undo();
    void redo();

public slots:
    void setColor(int value);

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    //virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);

private:
    QString m_filepath;
    QImage m_image;
    int m_zoom;

    QColor m_color[2];
    QSpinBox* m_rgbs[2][3];

    OperationHistory m_commandHistory;

};

#endif /* ICONEDITOR_H_ */
