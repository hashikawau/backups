//========================================
// Tetrahedron.cpp
//
//  Created on: 2013/11/16
//      Author: you
//========================================

#include "Tetrahedron.h"
#include <QtGui/qevent.h>
#include <QtWidgets/qcolordialog.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/gtc/matrix_transform.hpp>
using glm::mat3;
using glm::mat4;
using glm::vec3;
using glm::vec4;

void showMat(mat3 matrix);
void showMat(mat4 matrix);
void showVec(vec4 vector);
GLuint getIndex(int i, int j, int numX, int numY) {
    return ((i % numX + numX) % numX) * numY + ((j % numY + numY) % numY);
}

void Tetrahedron::setShowNormals(int state) {
    m_showNormal = state > 0;
    updateGL();
}

Tetrahedron::Tetrahedron(QWidget* parent)
        : QGLWidget(parent) {

    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
}

Tetrahedron::~Tetrahedron() {
    glDeleteBuffers(4, m_vboHandles);
    glDeleteVertexArrays(1, &m_vaoHandle);

    glDeleteBuffers(1, m_vboHandleForNormals);
    glDeleteVertexArrays(1, &m_vaoHandleForNormals);
}

//protected
void Tetrahedron::initializeGL() {
    glewInit();

    m_modelMatrix = mat4(1.0f);
    m_viewRatio = 1.5f;
    m_cameraPos = vec3(0.0f, 0.0f, 10.0f);

    std::string vertex("phone.vert");
    std::string fragment("phone.frag");
    m_program.compileProgram(vertex, fragment);

    //--->
    m_showNormal = false;
    int numX = 50;
    int numY = 50;
    m_numVertices = numX * numY;
    GLfloat vertices[numX][numY][3];
    GLfloat normals[numX][numY][3];
    GLfloat normalVertices[numX][numY][6];
    GLfloat texCoords[numX][numY][2];
    float max = 1;
//    for (int i = 0; i < numX; ++i) {
//        for (int j = 0; j < numY; ++j) {
//            float x = i / (float) (numX - 1.0f) - 0.5f;
//            float y = j / (float) (numY - 1.0f) - 0.5f;
//            float k = 1.25f;
//            float k2 = k * k;
//            vertices[i][j][0] = k * x;
//            vertices[i][j][1] = k * y;
////            vertices[i][j][2] = (1.0f - k2 * (x * x + y * y) / max) + 0 / 2;
//            vertices[i][j][2] = 2.0f * sqrtf((1.0f - k2 * (x * x + y * y)) / max) - 1.5f;
////            vertices[i][j][2] = 0.0f;
//
////            if (i == 0 && j == 0) {
////                normals[i][j][0] = 0.0f;
////                normals[i][j][1] = 0.0f;
////                normals[i][j][2] = 1.0f;
////            } else {
////                float m = 1.0f / (2 * k2 * i);
////                float len = sqrtf(1 + m * m);
////                normals[i][j][0] = 1.0f / len;
////                normals[i][j][1] = 0.0f;
////                normals[i][j][2] = m / len;
////            }
//            float n[] = {
//                    2.0f * k2 * x / max,
//                    2.0f * k2 * y / max,
//                    // 1.0f
//                    2.0f * vertices[i][j][2]
//            };
//            float len = sqrtf(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
//            normals[i][j][0] = n[0] / len;
//            normals[i][j][1] = n[1] / len;
//            normals[i][j][2] = n[2] / len;
////            normals[i][j][0] = 0.0f;
////            normals[i][j][1] = 0.0f;
////            normals[i][j][2] = 1.0f;
////            std::cout << i * numY + j << ":\t"
////                    << vertices[i][j][0] << ",\t"
////                    << vertices[i][j][1] << ",\t"
////                    << vertices[i][j][2] << std::endl;
//            std::cout << i * numY + j << ": ["
//                    << x << ", "
//                    << y << "] = ["
//                    << normals[i][j][0] << ",\t"
//                    << normals[i][j][1] << ",\t"
//                    << normals[i][j][2] << "]"
//                    << std::endl;
//
//            normalVertices[i][j][0] = vertices[i][j][0];
//            normalVertices[i][j][1] = vertices[i][j][1];
//            normalVertices[i][j][2] = vertices[i][j][2];
//            normalVertices[i][j][3] = vertices[i][j][0] + normals[i][j][0] * 0.1;
//            normalVertices[i][j][4] = vertices[i][j][1] + normals[i][j][1] * 0.1;
//            normalVertices[i][j][5] = vertices[i][j][2] + normals[i][j][2] * 0.1;
//
//            texCoords[i][j][0] = i;
//            texCoords[i][j][1] = j;
//        }
//    }

//---> spheare
    const float RADIUS = 1.0f;
    for (int i = 0; i < numX; ++i) {
        for (int j = 0; j < numY; ++j) {
            float phy = M_PI * j / (numY - 1.0f);
            float z = RADIUS * -std::cos(phy);

            float r_z = RADIUS * std::sin(phy);
            float theta = 2.0f * M_PI * i / (numX - 1.0f);
            float x = r_z * std::cos(theta);
            float y = r_z * std::sin(theta);
            vertices[i][j][0] = x;
            vertices[i][j][1] = y;
            vertices[i][j][2] = z;

//            if (i == 0 && j == 0) {
//                normals[i][j][0] = 0.0f;
//                normals[i][j][1] = 0.0f;
//                normals[i][j][2] = 1.0f;
//            } else {
//                float m = 1.0f / (2 * k2 * i);
//                float len = sqrtf(1 + m * m);
//                normals[i][j][0] = 1.0f / len;
//                normals[i][j][1] = 0.0f;
//                normals[i][j][2] = m / len;
//            }
            float n[] = {
                    x, y, z
            };
            float len = std::sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
            normals[i][j][0] = n[0] / len;
            normals[i][j][1] = n[1] / len;
            normals[i][j][2] = n[2] / len;
//            normals[i][j][0] = 0.0f;
//            normals[i][j][1] = 0.0f;
//            normals[i][j][2] = 1.0f;
//            std::cout << i * numY + j << ":\t"
//                    << vertices[i][j][0] << ",\t"
//                    << vertices[i][j][1] << ",\t"
//                    << vertices[i][j][2] << std::endl;
            std::cout << i * numY + j << ": ["
                    << x << ", "
                    << y << "] = ["
                    << normals[i][j][0] << ",\t"
                    << normals[i][j][1] << ",\t"
                    << normals[i][j][2] << "]"
                    << std::endl;

            normalVertices[i][j][0] = vertices[i][j][0];
            normalVertices[i][j][1] = vertices[i][j][1];
            normalVertices[i][j][2] = vertices[i][j][2];
            normalVertices[i][j][3] = vertices[i][j][0] + normals[i][j][0] * 0.1;
            normalVertices[i][j][4] = vertices[i][j][1] + normals[i][j][1] * 0.1;
            normalVertices[i][j][5] = vertices[i][j][2] + normals[i][j][2] * 0.1;

            texCoords[i][j][0] = i;
            texCoords[i][j][1] = j;
        }
    }
    //<--- sphere

    std::vector<GLuint> indexList;
    indexList.push_back(0);
    for (int i = 0; i < numX - 1; ++i) {
        if (i % 2 == 0) {
            indexList.push_back(getIndex(i + 1, 0, numX, numY));
            for (int j = 1; j < numY; ++j) {
                indexList.push_back(getIndex(i + 0, j, numX, numY));
                indexList.push_back(getIndex(i + 1, j, numX, numY));
            }
        } else {
            indexList.push_back(getIndex(i + 1, -1, numX, numY));
            for (int j = numY - 2; j >= 0; --j) {
                indexList.push_back(getIndex(i + 0, j, numX, numY));
                indexList.push_back(getIndex(i + 1, j, numX, numY));
            }
        }
    }

    GLuint* indices = &indexList[0];
    m_numIndices = indexList.size();
//    for (int i = 0; i < m_numIndices; ++i) {
//        std::cout << indices[i] << std::endl;
//    }
//    std::cout << sizeof(vertices) << ", " << sizeof(indices) << std::endl;
//<---

////--->
//    int numSlices = 40;
//    float ES_PI = (float) M_PI;
//
//    int numParallels = numSlices / 2;
//    float angleStep = (2.0f * ES_PI) / ((float) numSlices);
////    int numVertices = (numParallels + 1) * (numSlices + 1);
//    m_numVertices = (numParallels + 1) * (numSlices + 1);
//    float vertices[m_numVertices * 3];
////    vertices = new GLfloat[m_numVertices * 3];
//
////    std::cout << numVertices << ", " << angleStep << std::endl;
//    for (int i = 0; i < numParallels + 1; i++) {
//        for (int j = 0; j < numSlices + 1; j++) {
//            int index = i * (numSlices + 1) + j;
//
//            vertices[3 * index + 0] = (float) (sin(angleStep * i) * sin(angleStep * j));
//            vertices[3 * index + 1] = (float) (cos(angleStep * i));
//            vertices[3 * index + 2] = (float) (sin(angleStep * i) * cos(angleStep * j));
////            std::cout << index << ": " << vertices[3 * index + 0] << ", " << vertices[3 * index + 1] << ", " << vertices[3 * index + 2] << std::endl;
//        }
//    }
//    m_numIndices = (numParallels) * (numSlices) * 6;
//    GLuint indices[m_numIndices];
//    int index = 0;
//    for (int i = 0; i < numParallels; ++i) {
//        for (int j = 0; j < numSlices; ++j) {
//            indices[index++] = (GLuint) (i * (numSlices + 1) + j);
//            indices[index++] = (GLuint) ((i + 1) * (numSlices + 1) + j);
//            indices[index++] = (GLuint) ((i + 1) * (numSlices + 1) + (j + 1));
//
//            indices[index++] = (GLuint) (i * (numSlices + 1) + j);
//            indices[index++] = (GLuint) ((i + 1) * (numSlices + 1) + (j + 1));
//            indices[index++] = (GLuint) (i * (numSlices + 1) + (j + 1));
//        }
//    }
//    //<---

//vbo
    glGenBuffers(4, m_vboHandles);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(GLfloat) * 3, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(GLfloat) * 3, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboHandles[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_numIndices, indices, GL_STATIC_DRAW);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//vao
    glGenVertexArrays(1, &m_vaoHandle);
    glBindVertexArray(m_vaoHandle);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[2]);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*) 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboHandles[3]);
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    //normal drawing ===============================
    glGenBuffers(1, m_vboHandleForNormals);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandleForNormals[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normalVertices), normalVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vaoHandleForNormals);
    glBindVertexArray(m_vaoHandleForNormals);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandleForNormals[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*) 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

//init
    qglClearColor(Qt::gray);
//    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
}

void Tetrahedron::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    GLfloat max = std::max(width, height);
    GLfloat x = width / max / m_viewRatio;
    GLfloat y = height / max / m_viewRatio;
    m_projMatrix = glm::frustum(
            -x, x,
            -y, y,
            4.0f, 15.0f);
}

void Tetrahedron::paintGL() {
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}
void Tetrahedron::mousePressEvent(QMouseEvent* event) {
    lastPos = event->pos();
}

void Tetrahedron::mouseMoveEvent(QMouseEvent* event) {
    GLfloat dx = GLfloat(event->x() - lastPos.x());
    GLfloat dy = GLfloat(event->y() - lastPos.y());

    if (event->buttons() & Qt::LeftButton) {
        float length = sqrt(dx * dx + dy * dy);
        mat4 rotation = glm::rotate(
                mat4(1.0f),
                length / 1.0f,
                vec3(dy / length, dx / length, 0.0f));
        m_modelMatrix = rotation * m_modelMatrix;
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        m_cameraPos.x += -dx / width();
        m_cameraPos.y += dy / height();
        updateGL();
    }
    lastPos = event->pos();
}

void Tetrahedron::wheelEvent(QWheelEvent* event) {
    float ratio = m_viewRatio + event->delta() / WHEEL_DELTA * 0.1;
    if (ratio > 0.0f) {
        m_viewRatio = ratio;
        int width = this->width();
        int height = this->height();
        GLfloat max = std::max(width, height);
        GLfloat x = width / max / m_viewRatio;
        GLfloat y = height / max / m_viewRatio;
        m_projMatrix = glm::frustum(
                -x, x,
                -y, y,
                4.0f, 15.0f);
    }

    updateGL();
}

void Tetrahedron::mouseDoubleClickEvent(QMouseEvent* event) {
//    int face = faceAtPosition(event->pos());
//    if (face != -1) {
//        QColor color = QColorDialog::getColor(faceColors[face], this);
//        if (color.isValid()) {
//            faceColors[face] = color;
//            updateGL();
//        }
//    }
}

//private
void Tetrahedron::draw() {

    m_program.enable();

    mat4 translation = glm::translate(mat4(1.0f), -m_cameraPos);
//    mat4 translation = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, -10.0f));
    mat4 modelViewMatrix = translation * m_modelMatrix;
    mat4 modelViewProjection = m_projMatrix * modelViewMatrix;
    GLint u_mvpMatrix = glGetUniformLocation(m_program.getID(), "u_mvpMatrix");
    if (u_mvpMatrix >= 0) {
        glUniformMatrix4fv(u_mvpMatrix, 1, GL_FALSE, &modelViewProjection[0][0]);
    } else {
        std::cout << "u_mvpMatrix does not exist" << std::endl;
    }
    glUniformMatrix4fv(glGetUniformLocation(m_program.getID(), "u_mvMatrix"), 1, GL_FALSE, &modelViewMatrix[0][0]);

    mat3 normal = mat3(modelViewMatrix[0][0], modelViewMatrix[0][1], modelViewMatrix[0][2],
            modelViewMatrix[1][0], modelViewMatrix[1][1], modelViewMatrix[1][2],
            modelViewMatrix[2][0], modelViewMatrix[2][1], modelViewMatrix[2][2]);
    glUniformMatrix3fv(glGetUniformLocation(m_program.getID(), "u_normalMatrix"), 1, GL_FALSE, &normal[0][0]);
//    std::cout << "//====================" << std::endl;
//    showMat(m_modelMatrix);
//    showMat(normal);

    glBindVertexArray(m_vaoHandle);
//    glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
//    glDrawElements(GL_TRIANGLE_STRIP, m_numIndices, GL_UNSIGNED_INT, indices);
    glDrawElements(GL_TRIANGLE_STRIP, m_numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    if (m_showNormal) {
        glBindVertexArray(m_vaoHandleForNormals);
        glDrawArrays(GL_LINES, 0, m_numVertices * 2);
        glBindVertexArray(0);
    }

    m_program.enable();
}

//===============================================
int Tetrahedron::faceAtPosition(const QPoint& pos) {
    const int MaxSize = 512;
    GLuint buffer[MaxSize];
    GLint viewport[4];

    makeCurrent();

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(MaxSize, buffer);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(GLdouble(pos.x()), GLdouble(viewport[3] - pos.y()), 5.0, 5.0,
            viewport);

    GLfloat x = GLfloat(width()) / height();
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    draw();
    glMatrixMode(GL_PROJECTION);

    glPopMatrix();
    if (!glRenderMode(GL_RENDER)) return -1;

    return buffer[3];
}
void showMat(mat4 matrix) {
    std::cout << "[" << std::endl;
    std::cout << "\t"
            << matrix[0][0]
            << ", "
            << matrix[0][1]
            << ", "
            << matrix[0][2]
            << ", "
            << matrix[0][3]
            << std::endl;
    std::cout << "\t"
            << matrix[1][0]
            << ", "
            << matrix[1][1]
            << ", "
            << matrix[1][2]
            << ", "
            << matrix[1][3]
            << std::endl;
    std::cout << "\t"
            << matrix[2][0]
            << ", "
            << matrix[2][1]
            << ", "
            << matrix[2][2]
            << ", "
            << matrix[2][3]
            << std::endl;
    std::cout << "\t"
            << matrix[3][0]
            << ", "
            << matrix[3][1]
            << ", "
            << matrix[3][2]
            << ", "
            << matrix[3][3]
            << std::endl;
    std::cout << "]" << std::endl;
}
void showMat(mat3 matrix) {
    std::cout << "[" << std::endl;
    std::cout << "\t"
            << matrix[0][0]
            << ", "
            << matrix[0][1]
            << ", "
            << matrix[0][2]
            << ", "
            << std::endl;
    std::cout << "\t"
            << matrix[1][0]
            << ", "
            << matrix[1][1]
            << ", "
            << matrix[1][2]
            << ", "
            << std::endl;
    std::cout << "\t"
            << matrix[2][0]
            << ", "
            << matrix[2][1]
            << ", "
            << matrix[2][2]
            << ", "
            << std::endl;
    std::cout << "]" << std::endl;
}
void showVec(vec4 vector) {
    std::cout << "[" << std::endl;
    std::cout << "\t" << vector[0] << std::endl;
    std::cout << "\t" << vector[1] << std::endl;
    std::cout << "\t" << vector[2] << std::endl;
    std::cout << "]" << std::endl;
}

