//========================================
// GLViewer.cpp
//
//  Created on: 2014/05/10
//      Author: you
//========================================

#include "GLViewer.h"

#include <QtGui/QMouseEvent>

#include <QtGui/QMatrix4x4>
#include <QtGui/QQuaternion>
#include <QtGui/QVector2D>

//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
//#include <glm/gtx/transform2.hpp>
#include <iostream>

namespace qglwidget {

GLViewer::GLViewer(QWidget* parent)
        : QGLWidget(parent) {
}

GLViewer::~GLViewer() {
}

void GLViewer::mousePressEvent(QMouseEvent *e) {
    _mousePressPosition = e->localPos();
}

void GLViewer::mouseMoveEvent(QMouseEvent* e) {
    // Mouse release position - mouse press position
    auto diff = e->localPos() - _mousePressPosition;
    _mousePressPosition = e->localPos();

    // Rotation axis is perpendicular to the mouse position difference
    // vector
//    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
    auto axis = glm::vec3(diff.y(), diff.x(), 0.0);
    auto acc = axis.length() / 1.0f;
    axis = glm::normalize(axis);

    // Accelerate angular speed relative to the length of the mouse sweep

    // Calculate new rotation axis as weighted sum
//    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
    _rotation = glm::rotate(acc, axis) * _rotation;

    _model.setMatrix(_rotation);

    // Increase angular speed
//    angularSpeed += acc;

    updateGL();
}

void GLViewer::mouseReleaseEvent(QMouseEvent* /*e*/) {
}

void GLViewer::initializeGL() {
    initializeGLFunctions();
    qglClearColor(Qt::gray);
//    initShaders();
//    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

//    geometries.init();
    _model.init();

    // Use QBasicTimer because its faster than QTimer
//    timer.start(12, this);
}

void GLViewer::resizeGL(int w, int h) {
    // Set OpenGL viewport to cover whole widget
    glViewport(0, 0, w, h);

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
//    projection.setToIdentity();

    // Set perspective projection
//    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void GLViewer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _model.draw();
}

} //namespace qglwidget
