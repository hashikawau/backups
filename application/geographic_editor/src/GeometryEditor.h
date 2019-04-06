//========================================
// GeometryEditor.h
//
//  Created on: 2013/12/07
//      Author: you
//========================================

#ifndef GEOMETRYEDITOR_H_
#define GEOMETRYEDITOR_H_

#include <QtWidgets/qwidget.h>
//#include <QtGui/qimage.h>

#include <fstream>

#include "model/ModelRoot.h"
#include "util/CoordinateConverter.h"
#include "util/OperationHistory.h"

namespace geoedit {

/*
 *
 */
class GeometryEditor: public QWidget {
Q_OBJECT

public:
    GeometryEditor(ModelRoot* modelRoot, QWidget* parent = 0);
    virtual ~GeometryEditor();

    void load(std::ifstream& fstream);
    void save(std::ofstream& fstream);
    void undo();
    void redo();

public slots:

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    //virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;

private:
    static CoordinateConverter::PointD m_mousePosition;

    ModelRoot* m_modelRoot;
    CoordinateConverter m_converter;
    std::vector<IShape*> m_selection;

    util::OperationHistory m_commandHistory;

};

} /* namespace geoedit */

#endif /* GEOMETRYEDITOR_H_ */
