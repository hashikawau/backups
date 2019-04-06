//========================================
// Model4.cpp
//
//  Created on: 2014/05/11
//      Author: you
//========================================

#include <model/Model4.h>

#include "util/util.hpp"

namespace qglwidget {

Model4::Model4() {
}

Model4::~Model4() {
    glDeleteBuffers(sizeof(_vboIds) / sizeof(GLuint), _vboIds);
    glDeleteTextures(sizeof(_texture) / sizeof(GLuint), _texture);
}

struct _Vertex {
    glm::vec3 _point;
    glm::vec2 _color;
};
void Model4::init() {
    initializeGLFunctions();
    {
        // Load cube.png image
//        glEnable(GL_TEXTURE_2D);
        auto glimage = QGLWidget::convertToGLFormat(QImage(":/glsl/cube.png"));
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(sizeof(_texture) / sizeof(GLuint), _texture);
        glBindTexture(GL_TEXTURE_2D, _texture[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            glimage.width(), glimage.height(),
            0, GL_RGBA, GL_UNSIGNED_BYTE, glimage.bits());
//        _texture = glBindTexture();

        // Set nearest filtering mode for texture minification
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Set bilinear filtering mode for texture magnification
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Wrap texture coordinates by repeating
        // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    {
        // Override system locale until shaders are compiled
        setlocale(LC_NUMERIC, "C");

        _program.init();
        // Compile vertex shader
        if(!_program.addShaderFromSourceFile(QGLShader::Vertex, ":/glsl/vshader_4.glsl")){
            std::cout << "error in compile vertex shader" << std::endl;
            std::cout << _program.log().toStdString() << std::endl;
        }

        // Compile fragment shader
        if(!_program.addShaderFromSourceFile(QGLShader::Fragment, ":/glsl/fshader_4.glsl")){
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
    }
    {
        glGenBuffers(sizeof(_vboIds) / sizeof(GLuint), _vboIds);

        {
            _Vertex vertices[] = {
                _Vertex { glm::vec3(-0.5, -0.5, -0.5), glm::vec2(0.0f, 0.0f) },
                _Vertex { glm::vec3(0.5, -0.5, -0.5), glm::vec2(1.0f, 0.0f) },
                _Vertex { glm::vec3(0.5, 0.5, -0.5), glm::vec2(1.0f, 1.0f) },
                _Vertex { glm::vec3(-0.5, 0.5, -0.5), glm::vec2(0.0f, 1.0f) },
                _Vertex { glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0.0f, 0.0f) },
                _Vertex { glm::vec3(0.5, -0.5, 0.5), glm::vec2(1.0f, 0.0f) },
                _Vertex { glm::vec3(0.5, 0.5, 0.5), glm::vec2(1.0f, 1.0f) },
                _Vertex { glm::vec3(-0.5, 0.5, 0.5), glm::vec2(0.0f, 1.0f) },
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
}

void Model4::draw() {
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

    {
        int loc = _program.uniformLocation("texture");
        _program.QGLShaderProgram::setUniformValue(loc, 0);
    }
    {
        int loc = _program.uniformLocation("mvp_matrix");
        _program.setUniformValue(loc, _rotation);
    }
    {
        int vertexLocation = _program.attributeLocation("a_position");
        _program.enableAttributeArray(vertexLocation);
        glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex), 0);
    }
    {
        int colorLocation = _program.attributeLocation("a_texcoord");
        _program.enableAttributeArray(colorLocation);
        glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(_Vertex),
            (const void*) sizeof(decltype(_Vertex::_point)));
    }
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, 0);

}

} //namespace qglwidget
