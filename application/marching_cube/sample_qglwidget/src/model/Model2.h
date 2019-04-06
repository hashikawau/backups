//========================================
// Model2.h
//
//  Created on: 2014/05/11
//      Author: you
//========================================

#ifndef MODEL2_H_
#define MODEL2_H_

#include <QtOpenGL/QGLFunctions>
#include <QtOpenGL/QGLShaderProgram>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace qglwidget {

/*
 *
 */
class Model2: protected QGLFunctions {
public:
    Model2();
    ~Model2();

    void init();

    void setMatrix(const glm::mat4& rotation) {
        _rotation = rotation;
    }
    void draw();

private:
    glm::mat4 _rotation;

    GLuint _vboIds[2];

};

} //namespace qglwidget

#endif // MODEL2_H_