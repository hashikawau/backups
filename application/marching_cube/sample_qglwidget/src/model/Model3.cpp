//========================================
// Model3.cpp
//
//  Created on: 2014/05/11
//      Author: you
//========================================

#include "Model3.h"
#include "util/util.hpp"

namespace qglwidget {

Model3::Model3() {
}

Model3::~Model3() {
    glDeleteBuffers(sizeof(_vboIds) / sizeof(GLuint), _vboIds);
}

struct _Vertex {
    glm::vec3 _point;
    glm::vec3 _color;
};
void Model3::init() {
    initializeGLFunctions();

    // Override system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    _program.init();
    // Compile vertex shader
    if(!_program.addShaderFromSourceFile(QGLShader::Vertex, ":/glsl/vshader_3.glsl")){
        std::cout << "error in compile vertex shader" << std::endl;
        std::cout << _program.log().toStdString() << std::endl;
    }

    // Compile fragment shader
    if(!_program.addShaderFromSourceFile(QGLShader::Fragment, ":/glsl/fshader_3.glsl")){
        std::cout << "error in compile fragment shader" << std::endl;
        std::cout << _program.log().toStdString() << std::endl;
    }

    // Link shader pipeline
    if(!_program.link()){
        std::cout << "error in link shader" << std::endl;
        std::cout << _program.log().toStdString() << std::endl;
    }

    // Restore system locale
    setlocale(LC_ALL, "");

    glGenBuffers(sizeof(_vboIds) / sizeof(GLuint), _vboIds);

    {
        _Vertex vertices[] = {
            _Vertex { glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1.0f, 1.0f, 1.0f) },
            _Vertex { glm::vec3(0.5, -0.5, -0.5), glm::vec3(1.0f, 0.0f, 0.0f) },
            _Vertex { glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.0f, 0.0f, 0.0f) },
            _Vertex { glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.0f, 1.0f, 0.0f) },
            _Vertex { glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.0f, 0.0f, 1.0f) },
            _Vertex { glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.0f, 0.0f, 0.0f) },
            _Vertex { glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.0f, 0.0f, 0.0f) },
            _Vertex { glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.0f, 0.0f, 0.0f) },
        };
        glBindBuffer(GL_ARRAY_BUFFER, _vboIds[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }
    {
        GLushort indices[] = {
            0, 3, 1,
            0, 1, 4,
            0, 4, 3,
            4, 1, 3,
        };
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboIds[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
}

void Model3::draw() {
    struct _matLoader {
    public:
        _matLoader(ShaderProgram& program, const glm::mat4& mat)
                : _program(program)
        {
            if(!_program.bind()){
                std::cout << "error in bind shader" << std::endl;
                std::cout << _program.log().toStdString() << std::endl;
            }
        }
        ~_matLoader() {
            _program.release();
        }
        ShaderProgram& _program;
    };
    _matLoader matloader(_program, _rotation);

    glBindBuffer(GL_ARRAY_BUFFER, _vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboIds[1]);

    int loc = _program.uniformLocation("mvp_matrix");
    _program.setUniformValue(loc, _rotation);
    {
        int vertexLocation = _program.attributeLocation("a_position");
        _program.enableAttributeArray(vertexLocation);
        glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), 0);
    }
    {
        int colorLocation = _program.attributeLocation("a_color");
        _program.enableAttributeArray(colorLocation);
        glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex),
            (const void*) sizeof(decltype(_Vertex::_point)));
    }
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, 0);

}

} //namespace qglwidget
