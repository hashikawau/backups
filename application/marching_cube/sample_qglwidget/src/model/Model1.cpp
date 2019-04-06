//========================================
// Model1.cpp
//
//  Created on: 2014/05/11
//      Author: you
//========================================

#include "Model1.h"

namespace qglwidget {

Model1::Model1() {
    _vertices = {
        _Vertex{glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1.0f, 1.0f, 1.0f)},
        _Vertex{glm::vec3( 0.5, -0.5, -0.5), glm::vec3(1.0f, 0.0f, 0.0f)},
        _Vertex{glm::vec3( 0.5,  0.5, -0.5), glm::vec3(0.0f, 0.0f, 0.0f)},
        _Vertex{glm::vec3(-0.5,  0.5, -0.5), glm::vec3(0.0f, 1.0f, 0.0f)},
        _Vertex{glm::vec3(-0.5, -0.5,  0.5), glm::vec3(0.0f, 0.0f, 1.0f)},
        _Vertex{glm::vec3( 0.5, -0.5,  0.5), glm::vec3(0.0f, 0.0f, 0.0f)},
        _Vertex{glm::vec3( 0.5,  0.5,  0.5), glm::vec3(0.0f, 0.0f, 0.0f)},
        _Vertex{glm::vec3(-0.5,  0.5,  0.5), glm::vec3(0.0f, 0.0f, 0.0f)},
    };
}

Model1::~Model1() {
}

} //namespace qglwidget
