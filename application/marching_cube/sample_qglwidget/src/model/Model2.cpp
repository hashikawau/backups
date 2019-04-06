//========================================
// Model2.cpp
//
//  Created on: 2014/05/11
//      Author: you
//========================================

#include "Model2.h"

namespace qglwidget {

Model2::Model2() {
}

Model2::~Model2() {
    glDeleteBuffers(sizeof(_vboIds) / sizeof(GLuint), _vboIds);
}

struct _Vertex {
    glm::vec3 _point;
    glm::vec3 _color;
};
void Model2::init() {
    initializeGLFunctions();
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

void Model2::draw() {
    struct _matLoader {
    public:
        _matLoader(const glm::mat4& mat) {
            glPushMatrix();
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf(&mat[0][0]);
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);

            glVertexPointer(3, GL_FLOAT, sizeof(_Vertex), 0);
            glColorPointer(3, GL_FLOAT, sizeof(_Vertex), (const void*) sizeof(_Vertex()._point));
        }
        ~_matLoader() {
            glPopMatrix();
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
        }
    };
    _matLoader matloader(_rotation);

    glBindBuffer(GL_ARRAY_BUFFER, _vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboIds[1]);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, 0);

}

} //namespace qglwidget
