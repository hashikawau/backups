/*
 * IGLSLVariable.cpp
 *
 *  Created on: 2013/04/01
 *      Author: scientific
 */

#include "IGLSLVariable.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
//#include <iostream>

namespace glutApp {

IGLSLVariable::IGLSLVariable() {
}

IGLSLVariable::~IGLSLVariable() {
}

//--->
GLSLUniformMatrix4::GLSLUniformMatrix4()
	:m_location(0),
	 m_value()
{
}
GLSLUniformMatrix4::GLSLUniformMatrix4(const GLMatrix4& value)
	:m_location(0),
	 m_value(value)
{
}
GLSLUniformMatrix4::~GLSLUniformMatrix4(){
}

void GLSLUniformMatrix4::setLocation(int location){
	m_location = location;
}

void GLSLUniformMatrix4::apply(){
	glUniformMatrix4fv(m_location, 1, GL_FALSE, m_value.get());
}
//<---

//--->
GLSLAttribPointer::GLSLAttribPointer()
	:m_location(0),
	 m_idVBO(0),
	 m_stride(0),
	 m_offset(0),
	 m_numCoord(3),
	 m_type(GL_FLOAT)
{
}
GLSLAttribPointer::GLSLAttribPointer(unsigned int idVBO, int stride, int offset)
	:m_location(0),
	 m_idVBO(idVBO),
	 m_stride(stride),
	 m_offset(offset),
	 m_numCoord(3),
	 m_type(GL_FLOAT)
{
}
GLSLAttribPointer::~GLSLAttribPointer(){
}

void GLSLAttribPointer::setLocation(int location){
	m_location = location;
}

void GLSLAttribPointer::apply(){
//	glUniformMatrix4fv(m_location, 1, GL_FALSE, m_value.get());
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBO);
	glVertexAttribPointer(m_location, m_numCoord, m_type, GL_FALSE, m_stride, (const void*)(sizeof(float) * m_offset));
//	glVertexAttribPointer(m_location, 3, GL_FLOAT, GL_FALSE, 32, (const void*)(sizeof(float) * 0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(m_location);
//	m_listEnabledAttrib.push_back(location);
}
//<---

} /* namespace glutApp */
