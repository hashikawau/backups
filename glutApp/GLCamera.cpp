/*
 * GLCamera.cpp
 *
 *  Created on: 2013/04/01
 *      Author: you
 */

#include "GLCamera.h"
#include "GLMatrix.h"

#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

namespace glutApp {

GLCamera::GLCamera()
	:m_position(0.0f, 0.0f, 0.0f),
	 m_rotation(GLMatrix4::createIdentity()),
	 m_fovy(0.1f),
	 m_width(1.0f),
	 m_height(1.0f),
	 m_depth(2.0f),
	 m_scale(1.0f)
{
}

GLCamera::~GLCamera() {
}

void GLCamera::rotate(const GLMatrix4& rotation){
	glMatrixMode(GL_PROJECTION);
//	glLoadMatrixf(rotation.get());
//	glMultMatrixf(m_rotation.get());
	glLoadMatrixf(m_rotation.get());
	glMultMatrixf(rotation.get());
	float ret_mat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, ret_mat);
	m_rotation = ret_mat;
}

const GLMatrix4 GLCamera::getModelViewProjectionMatrix() const{
	float width = m_width / m_scale;
	float height = m_height / m_scale;
	float zNear = (float)(width / tan(m_fovy * M_PI / 360));
	float zFar = zNear + m_depth;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(
		-width, width,
		-height, height,
		zNear, zFar);
	glTranslatef(-m_position.getX(), -m_position.getY(), -m_position.getZ() - zNear);

	GLMatrix4 rot = m_rotation;
	rot.transpose();
	glMultMatrixf(rot.get());
	float ret_mat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, ret_mat);
	return GLMatrix4(ret_mat);
}
const GLMatrix4 GLCamera::getModelViewMatrix() const{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(m_position.getX(), m_position.getY(), m_position.getZ());
	GLMatrix4 rot = m_rotation;
	rot.transpose();
	glMultMatrixf(rot.get());
	float ret_mat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, ret_mat);
	return GLMatrix4(ret_mat);
}
const GLMatrix3 GLCamera::getNormalMatrix() const{
	const float* m = m_rotation.get();
	float ret_mat[] = {
			m[0], m[4], m[8],
			m[1], m[5], m[9],
			m[2], m[6], m[10]
	};
	return GLMatrix3(ret_mat);
}

} /* namespace glutApp */
