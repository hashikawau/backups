/*
 * GLVector.cpp
 *
 *  Created on: 2013/04/01
 *      Author: you
 */

#include "GLVector.h"
#include "GLMatrix.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

namespace glutApp {

GLVector::GLVector() {
}

GLVector::~GLVector() {
}

GLVector3::GLVector3(float x, float y, float z)
{
	m_vector[0] = x;
	m_vector[1] = y;
	m_vector[2] = z;
}
GLVector3::GLVector3(const GLVector3& ref) {
	m_vector[0] = ref.m_vector[0];
	m_vector[1] = ref.m_vector[1];
	m_vector[2] = ref.m_vector[2];
}
GLVector3& GLVector3::operator=(const GLVector3& ref) {
	m_vector[0] = ref.m_vector[0];
	m_vector[1] = ref.m_vector[1];
	m_vector[2] = ref.m_vector[2];
	return *this;
}
GLVector3::~GLVector3() {
}

void GLVector3::rotate(const GLMatrix4& rotation){
	float v[16] = {
			m_vector[0], m_vector[1], m_vector[2], 0,
			m_vector[1],1, 0, 0,
			m_vector[2]
	};
	glMatrixMode(GL_PROJECTION);
//	glLoadMatrixf(v);
//	glMultMatrixf(rotation.get());
	glLoadMatrixf(rotation.get());
	glMultMatrixf(v);
	glGetFloatv(GL_PROJECTION_MATRIX, v);
	m_vector[0] = v[0];
	m_vector[1] = v[1];
	m_vector[2] = v[2];
//	for(int i=0; i< 4; ++i){
//		for(int j=0; j< 4; ++j){
//			std::cout << v[i * 4 + j] << ", ";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;
}

} /* namespace glutApp */
