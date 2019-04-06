//========================================
// Model5.h
//
//  Created on: 2014/05/11
//      Author: you
//========================================

#ifndef MODEL5_H_
#define MODEL5_H_

#include "util/ShaderProgram.h"

#include <QtOpenGL/qglfunctions.h>

#include <glm/glm.hpp>

namespace qglwidget {

/*
 *
 */
class Model5: protected QGLFunctions {
public:
    Model5();
    ~Model5();

    void init();

    void setMatrix(const glm::mat4& rotation) {
        _rotation = rotation;
    }
    void draw();

private:
    glm::mat4 _rotation;

    GLuint _texture[1];
    GLuint _vboIds[2];
    ShaderProgram _program;
};

} //namespace qglwidget

#endif // MODEL5_H_