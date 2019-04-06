/*
 * GLSLProgram.cpp
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#include "GLSLProgram.h"

GLSLProgram::GLSLProgram()
	:m_idProgram(0)
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
	for(std::vector<int>::iterator it = m_listEnabledAttrib.begin();
			it != m_listEnabledAttrib.end();
			++it)
	{
		glDisableVertexAttribArray(*it);
	}
	glUseProgram(0);
}

void GLSLProgram::linkProgram(
		shared_ptr<GLSLShader> vertex,
		shared_ptr<GLSLShader> fragment)
{
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
}

void GLSLProgram::uniform1(std::string name, int value){
	int location = glGetUniformLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no uniform variable, name = " << name << std::endl;
		return;
	}
	glUniform1i(location, value);
}
void GLSLProgram::uniform2(std::string name, int* value){
	int location = glGetUniformLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no uniform variable, name = " << name << std::endl;
		return;
	}
	glUniform2iv(location, 1, value);
}
void GLSLProgram::uniform3(std::string name, int* value){
	int location = glGetUniformLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no uniform variable, name = " << name << std::endl;
		return;
	}
	glUniform3iv(location, 1, value);
}
void GLSLProgram::uniform4(std::string name, int* value){
	int location = glGetUniformLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no uniform variable, name = " << name << std::endl;
		return;
	}
	glUniform4iv(location, 1, value);
}

void GLSLProgram::uniform1(std::string name, float value){
	int location = glGetUniformLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no uniform variable, name = " << name << std::endl;
		return;
	}
	glUniform1f(location, value);
}
void GLSLProgram::uniform2(std::string name, float* value){
	int location = glGetUniformLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no uniform variable, name = " << name << std::endl;
		return;
	}
	glUniform2fv(location, 1, value);
}
void GLSLProgram::uniform3(std::string name, float* value){
	int location = glGetUniformLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no uniform variable, name = " << name << std::endl;
		return;
	}
	glUniform3fv(location, 1, value);
}
void GLSLProgram::uniform4(std::string name, float* value){
	int location = glGetUniformLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no uniform variable, name = " << name << std::endl;
		return;
	}
	glUniform4fv(location, 1, value);
}
void GLSLProgram::uniformMatrix3(std::string name, float* value){
	int location = glGetUniformLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no uniform variable, name = " << name << std::endl;
		return;
	}
	glUniformMatrix3fv(location, 1, GL_FALSE, value);
}
void GLSLProgram::uniformMatrix4(std::string name, float* value){
	int location = glGetUniformLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no uniform variable, name = " << name << std::endl;
		return;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void GLSLProgram::vertexAttribPointer3(std::string name, int stride, float* value){
	int location = glGetAttribLocation(m_idProgram, name.c_str());
	if(location == -1){
		//std::cout << "no attribute variable. name = " << name << std::endl;
		return;
	}
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, stride, value);
	glEnableVertexAttribArray(location);
	m_listEnabledAttrib.push_back(location);
}





