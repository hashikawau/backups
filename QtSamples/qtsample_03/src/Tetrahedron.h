//========================================
// Tetrahedron.h
//
//  Created on: 2013/11/16
//      Author: you
//========================================

#ifndef qtsample_03_TETRAHEDRON_H_
#define qtsample_03_TETRAHEDRON_H_

#include <QtOpenGL/QGLWidget>

class QGLShaderProgram;

/*
 *
 */
class Tetrahedron: public QGLWidget {
    Q_OBJECT

public:
    Tetrahedron(QWidget* parent = 0);
    virtual ~Tetrahedron();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);

private:
    void draw();
    int faceAtPosition(const QPoint& pos);
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[4];
    QPoint lastPos;

    QGLShaderProgram* m_program;
};

#endif /* qtsample_03_TETRAHEDRON_H_ */
