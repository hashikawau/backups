//========================================
// Model1.h
//
//  Created on: 2014/05/11
//      Author: you
//========================================

#ifndef MODEL1_H_
#define MODEL1_H_

#include <vector>
#include <QtOpenGL/qglfunctions.h>
#include <glm/glm.hpp>

namespace qglwidget {

/*
 *
 */
class Model1: protected QGLFunctions {
public:
    Model1();
    ~Model1();

    void init(){
        initializeGLFunctions();
    }

    void setMatrix(const glm::mat4& rotation) {
        _rotation = rotation;
    }
    void draw(){

        _matLoader load(_rotation);
        //    util::print(
        //        glm::rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f)));

        glBegin(GL_TRIANGLES);
        {
            {
                glColor3fv(&_vertices[0]._color[0]);
                glVertex3fv(&_vertices[0]._point[0]);

                glColor3fv(&_vertices[3]._color[0]);
                glVertex3fv(&_vertices[3]._point[0]);

                glColor3fv(&_vertices[1]._color[0]);
                glVertex3fv(&_vertices[1]._point[0]);
            }
            {
                glColor3fv(&_vertices[0]._color[0]);
                glVertex3fv(&_vertices[0]._point[0]);

                glColor3fv(&_vertices[1]._color[0]);
                glVertex3fv(&_vertices[1]._point[0]);

                glColor3fv(&_vertices[4]._color[0]);
                glVertex3fv(&_vertices[4]._point[0]);
            }
            {
                glColor3fv(&_vertices[0]._color[0]);
                glVertex3fv(&_vertices[0]._point[0]);

                glColor3fv(&_vertices[4]._color[0]);
                glVertex3fv(&_vertices[4]._point[0]);

                glColor3fv(&_vertices[3]._color[0]);
                glVertex3fv(&_vertices[3]._point[0]);
            }
            {
                glColor3fv(&_vertices[4]._color[0]);
                glVertex3fv(&_vertices[4]._point[0]);

                glColor3fv(&_vertices[1]._color[0]);
                glVertex3fv(&_vertices[1]._point[0]);

                glColor3fv(&_vertices[3]._color[0]);
                glVertex3fv(&_vertices[3]._point[0]);
            }
        }
        glEnd();
    }

private:
    struct _matLoader {
    public:
        _matLoader(const glm::mat4& mat) {
            glPushMatrix();
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf(&mat[0][0]);
        }
        ~_matLoader() {
            glPopMatrix();
        }
    };
    struct _Vertex {
        glm::vec3 _point;
        glm::vec3 _color;
    };

    glm::mat4 _rotation;
    std::vector<_Vertex> _vertices;

};

} //namespace qglwidget

#endif // MODEL1_H_