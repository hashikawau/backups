//========================================
// GLSLProgram.h
//
//  Created on: 2013/11/24
//      Author: you
//========================================

#ifndef GLUTIL_GLSLPROGRAM_H_
#define GLUTIL_GLSLPROGRAM_H_

#include <GL/glew.h>
#include <string>


namespace glutil {

/*
 *
 */
class GLSLProgram {
public:
    GLSLProgram();
    ~GLSLProgram();

    GLuint getID(){
        return m_programID;
    }
    void compileProgram(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath);
//    void linkProgram();

    void enable();
    void disable();

private:
    GLuint m_programID;
};

} /* namespace glutil */

#endif /* GLUTIL_GLSLPROGRAM_H_ */
