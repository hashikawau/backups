//========================================
// GLViewer.h
//
//  Created on: 2014/05/10
//      Author: you
//========================================

#ifndef GLVIEWER_H_
#define GLVIEWER_H_

#include "model/Model1.h"
#include "model/Model2.h"
#include "model/Model3.h"
#include "model/Model4.h"
#include "model/Model5.h"

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLfunctions.h>

#include <QtOpenGL/QGLShaderProgram>
#include <QtCore/QBasicTimer>

#include <glm/glm.hpp>

namespace qglwidget {

/*
 *
 */
class GLViewer: public QGLWidget, protected QGLFunctions {
Q_OBJECT

public:
    explicit GLViewer(QWidget* parent =0);
    virtual ~GLViewer();

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    QPointF _mousePressPosition;

    glm::mat4 _rotation;

//    Model1 _model;
//    Model2 _model;
//    Model3 _model;
//    Model4 _model;
    Model5 _model;

};

} //namespace qglwidget

#endif // GLVIEWER_H_