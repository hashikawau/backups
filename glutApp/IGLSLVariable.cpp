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
//	std::cout << "setLocation() location = " << m_location << std::endl;
}

void GLSLUniformMatrix4::apply(){
//	for(int i=0; i< 4; ++i){
//		for(int j=0; j< 4; ++j){
//			std::cout << m_value.get()[i * 4 + j] << ", ";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;
	glUniformMatrix4fv(m_location, 1, GL_FALSE, m_value.get());
}
//<---

} /* namespace glutApp */
