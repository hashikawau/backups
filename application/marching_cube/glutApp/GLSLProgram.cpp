/*
 * GLSLProgram.cpp
 *
 *  Created on: 2013/03/31
 *      Author: you
 */

#include "GLSLProgram.h"
#include "GLSLProgramShader.h"
#include "IGLSLVariable.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace glutApp {

GLSLProgram::GLSLProgram()
	:m_idProgram(glCreateProgram()),
	 m_primitive(GL_LINES)
{
}

GLSLProgram::~GLSLProgram() {
	if(m_idProgram != 0){
		//std::cout << "delete program" << std::endl;
		glDeleteProgram(m_idProgram);
	}
}

void GLSLProgram::enable(){
	glUseProgram(m_idProgram);
}
void GLSLProgram::disable(){
	for(std::vector<int>::iterator it = m_listEnabledAttribs.begin();
			it != m_listEnabledAttribs.end();
			++it)
	{
		glDisableVertexAttribArray(*it);
	}
	//glUseProgram(0);
}

void GLSLProgram::linkProgram(
		const shared_ptr<GLSLProgramShader>& vertex,
		const shared_ptr<GLSLProgramShader>& fragment)
{
//	unsigned int idProgram = m_idProgram;
	unsigned int idProgram = glCreateProgram();
	//std::cout << "create program" << std::endl;

	glAttachShader(idProgram, vertex->getID());
	//glDeleteShader(idVertexShader);

	glAttachShader(idProgram, fragment->getID());
	//glDeleteShader(idFragmentShader);

	glLinkProgram(idProgram);

	int status;
	glGetProgramiv(idProgram, GL_LINK_STATUS, &status);
	if(status == GL_FALSE){
		std::cout << "link error" << std::endl;
		int lengthInfoLog;
		glGetProgramiv(idProgram, GL_INFO_LOG_LENGTH, &lengthInfoLog);

		char infoLog[lengthInfoLog];
		glGetProgramInfoLog(idProgram, lengthInfoLog, 0, infoLog);
		std::cout << infoLog << std::endl;

		glDeleteProgram(idProgram);
	}else{
		if(m_idProgram != 0){
			//std::cout << "delete program" << std::endl;
			glDeleteProgram(m_idProgram);
		}
		m_idProgram = idProgram;

//		int lengthInfoLog;
//		glGetProgramiv(idProgram, GL_INFO_LOG_LENGTH, &lengthInfoLog);
//		char infoLog[lengthInfoLog];
//		glGetProgramInfoLog(idProgram, lengthInfoLog, 0, infoLog);
//		std::cout << infoLog << std::endl;
	}

	for(MapVariables::iterator it = m_listUniforms.begin(); it != m_listUniforms.end(); ++it){
		int location = glGetUniformLocation(m_idProgram, it->first.c_str());
		if(location == -1){
			std::cout << "no uniform. name = " << it->first << std::endl;
		}
		it->second->setLocation(location);
	}
	for(MapVariables::iterator it = m_listAttributes.begin(); it != m_listAttributes.end(); ++it){
		int location = glGetAttribLocation(m_idProgram, it->first.c_str());
		if(location == -1){
			std::cout << "no attribute. name = " << it->first << std::endl;
		}
		it->second->setLocation(location);
	}
}

void GLSLProgram::execute(){
	glUseProgram(m_idProgram);
	for(MapVariables::iterator it = m_listUniforms.begin(); it != m_listUniforms.end(); ++it){
		it->second->apply();
	}
	for(MapVariables::iterator it = m_listAttributes.begin(); it != m_listAttributes.end(); ++it){
		it->second->apply();
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexVBO);
	glDrawElements(m_primitive, m_numIndices, GL_UNSIGNED_INT, 0);
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);
}
void GLSLProgram::setUniform(const std::string& name, const shared_ptr<IGLSLVariable>& variable){
	m_listUniforms[name] = variable;
}
void GLSLProgram::setAttribute(const std::string& name, const shared_ptr<IGLSLVariable>& variable){
	m_listAttributes[name] = variable;
}




} /* namespace glutApp */
