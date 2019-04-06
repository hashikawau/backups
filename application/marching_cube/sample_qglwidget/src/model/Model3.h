//========================================
// Model3.h
//
//  Created on: 2014/05/11
//      Author: you
//========================================

#ifndef MODEL3_H_
#define MODEL3_H_

#include "util/ShaderProgram.h"

#include <QtOpenGL/qglfunctions.h>

#include <glm/glm.hpp>

namespace qglwidget {

/*
 *
 */
class Model3: protected QGLFunctions {
public:
    Model3();
    ~Model3();

    void init();

    void setMatrix(const glm::mat4& rotation) {
        _rotation = rotation;
    }
    void draw();

private:
    glm::mat4 _rotation;

    GLuint _vboIds[2];
    ShaderProgram _program;

};

} //namespace qglwidget

#endif // MODEL3_H_