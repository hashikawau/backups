//========================================
// Tetrahedron.h
//
//  Created on: 2013/11/16
//      Author: you
//========================================

#ifndef qtsample_03_TETRAHEDRON_H_
#define qtsample_03_TETRAHEDRON_H_

//#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include <QtOpenGL/QGLWidget>
#include <glm/glm.hpp>
#include "GLSLProgram.h"


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
    virtual void wheelEvent(QWheelEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);

private slots:
    void setShowNormals(int state);


private:
    void draw();
    int faceAtPosition(const QPoint& pos);
    QPoint lastPos;

    glutil::GLSLProgram m_program;
    GLuint m_vboHandles[4];
    GLuint m_vaoHandle;

    //
    bool m_showNormal;
    GLuint m_vboHandleForNormals[1];
    GLuint m_vaoHandleForNormals;

    int m_numVertices;
//    GLfloat* vertices;
    int m_numIndices;
//    GLuint* indices;

    glm::mat4 m_projMatrix;
    glm::mat4 m_modelMatrix;
    float m_viewRatio;
    glm::vec3 m_cameraPos;
};

#endif /* qtsample_03_TETRAHEDRON_H_ */
