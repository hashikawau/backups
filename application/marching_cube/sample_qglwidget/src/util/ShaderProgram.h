//========================================
// ShaderProgram.h
//
//  Created on: 2014/05/11
//      Author: you
//========================================

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <QtOpenGL/qglfunctions.h>
#include <QtOpenGL/qglshaderprogram.h>

#include <glm/glm.hpp>

namespace qglwidget {

/*
 *
 */
class ShaderProgram: public QGLShaderProgram, protected QGLFunctions {
public:
    ShaderProgram();
    ~ShaderProgram();

    void init() {
        initializeGLFunctions();
    }
    void setUniformValue(const char* name, const glm::mat4& mat) {
        GLint loc = glGetUniformLocation(programId(), name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    }
    void setUniformValue(GLint loc, const glm::mat4& mat) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    }

};

} //namespace qglwidget

#endif // SHADERPROGRAM_H_