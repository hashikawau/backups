/*
 * GLMatrix.cpp
 *
 *  Created on: 2013/03/31
 *      Author: you
 */

#include "GLMatrix.h"

#include <math.h>
#include <GL/freeglut.h>

namespace glutApp {

GLMatrix::GLMatrix() {
}

GLMatrix::~GLMatrix() {
}

GLMatrix3::GLMatrix3(const float* vector){
	for(int i=0; i< 9; ++i){
		m_matrix[i] = vector[i];
	}
}
GLMatrix3::GLMatrix3(const GLMatrix4& matrix4){
	const float* m = matrix4.get();
	m_matrix[0] = m[0];
	m_matrix[1] = m[1];
	m_matrix[2] = m[2];
	m_matrix[3] = m[4];
	m_matrix[4] = m[5];
	m_matrix[5] = m[6];
	m_matrix[6] = m[8];
	m_matrix[7] = m[9];
	m_matrix[8] = m[10];
}
GLMatrix3::~GLMatrix3() {
}


GLMatrix4::GLMatrix4(){
}
GLMatrix4::GLMatrix4(const float* matrix){
	for(int i=0; i< 16; ++i){
		m_matrix[i] = matrix[i];
	}
}
GLMatrix4::~GLMatrix4(){
}
GLMatrix4::GLMatrix4(const GLMatrix4& ref){
	for(int i=0; i< 16; ++i){
		m_matrix[i] = ref.m_matrix[i];
	}
}
GLMatrix4& GLMatrix4::operator=(const GLMatrix4& ref){
	for(int i=0; i< 16; ++i){
		m_matrix[i] = ref.m_matrix[i];
	}
	return *this;
}
GLMatrix4 GLMatrix4::createRotation(float angle, float x, float y, float z){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(angle, x, y, z);
	float ret_mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, ret_mat);
	return GLMatrix4(ret_mat);
}
GLMatrix4 GLMatrix4::createProjection(float fovy, float width, float height, float depth){
//	if(fovy <= 0.0f || zNear <= 0.0f || zNear >= zFar){
//		throw int(-1);
//	}

	float zNear = (float)(width / tan(fovy * M_PI / 360));
	float zFar = zNear + depth;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(
//		-100, 100,
//		-100, 100,
//		-10.0, 10.0);
	glFrustum(
		-width, width,
		-height, height,
		zNear, zFar);
	glTranslatef(0.0f, 0.0f, -zNear);
	float ret_mat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, ret_mat);
	return GLMatrix4(ret_mat);
}

} /* namespace glutApp */
