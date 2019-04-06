//========================================
// GLSLProgram.cpp
//
//  Created on: 2013/11/24
//      Author: you
//========================================

#include "GLSLProgram.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

namespace glutil {

GLSLProgram::GLSLProgram()
        : m_programID(0) {
}

GLSLProgram::~GLSLProgram() {
    if (0 != m_programID) {
        glDeleteProgram(m_programID);
        m_programID = 0;
    }
}

void GLSLProgram::compileProgram(const std::string& vertexShaderFilepath,
        const std::string& fragmentShaderFilepath) {

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    {
//        std::cout << "debug" << std::endl;
        std::string s(vertexShaderFilepath.c_str());
        std::fstream file(s.c_str(), std::ios::in);
//        std::cout << s.c_str() << std::endl;
        std::stringstream code;
        char ch;
        while (file.get(ch)) {
            code << ch;
        }
        file.close();
        const GLchar* lines[] = { &code.str()[0] };
//        std::cout << &code.str()[0] << std::endl;

        if (0 == vertexShader) {
            std::cout << "failed to create vertex shader" << std::endl;
        }
        glShaderSource(vertexShader, 1, lines, 0);
        glCompileShader(vertexShader);
        GLint result;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
        if (GL_FALSE == result) {
            std::cout << "failed to compile vertex shader." << std::endl;
            GLint len;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &len);
            if (len > 0) {
                char* log = (char*) malloc(len);
                GLsizei written;
                glGetShaderInfoLog(vertexShader, len, &written, log);
                std::cout << "vertex shader log -->" << std::endl;
                std::cout << log << std::endl;
                std::cout << "<---" << std::endl;
                free(log);
            }
        }
    }
    {
        std::ifstream file(fragmentShaderFilepath.c_str());
        std::stringstream code;
        char ch;
        while (file.get(ch)) {
            code << ch;
        }
        file.close();
        const GLchar* lines[] = { &code.str()[0] };
//        std::cout << &code.str()[0] << std::endl;

        if (0 == fragmentShader) {
            std::cout << "failed to create fragment shader" << std::endl;
        }
        glShaderSource(fragmentShader, 1, lines, 0);
        glCompileShader(fragmentShader);
        GLint result;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
        if (GL_FALSE == result) {
            std::cout << "failed to compile fragment shader." << std::endl;
            GLint len;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &len);
            if (len > 0) {
                char* log = (char*) malloc(len);
                GLsizei written;
                glGetShaderInfoLog(fragmentShader, len, &written, log);
                std::cout << "fragment shader log -->" << std::endl;
                std::cout << log << std::endl;
                std::cout << "<---" << std::endl;
                free(log);
            }
        }
    }
    {
        if (0 != m_programID) {
            glDeleteProgram(m_programID);
        }
        m_programID = glCreateProgram();
        if (0 == m_programID) {
            std::cout << "failed to create shader program" << std::endl;
        }
        glAttachShader(m_programID, vertexShader);
        glAttachShader(m_programID, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glLinkProgram(m_programID);
        GLint status;
        glGetProgramiv(m_programID, GL_LINK_STATUS, &status);
        if (GL_FALSE == status) {
            std::cout << "failed to link shader program" << std::endl;

            GLint len;
            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &len);
            if (len > 0) {
                char* log = (char*) malloc(len);
                GLsizei written;
                glGetProgramInfoLog(m_programID, len, &written, log);
                std::cout << "shader program log -->" << std::endl;
                std::cout << log << std::endl;
                std::cout << "<---" << std::endl;
                free(log);
            }
        }
    }

}

void GLSLProgram::enable() {
    glUseProgram(m_programID);
}
void GLSLProgram::disable() {
    glUseProgram(0);
}

} /* namespace glutil */
