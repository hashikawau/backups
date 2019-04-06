/*
 * GLSLProgramShader.cpp
 *
 *  Created on: 2013/03/31
 *      Author: you
 */

#include "GLSLProgramShader.h"

#include <iostream>
#include <fstream>
#include <GL/glew.h>

namespace glutApp {

GLSLProgramShader::GLSLProgramShader(SHADER_TYPE type, std::string fileName)
	:m_idShader(0),
	 m_type(type),
	 m_fileName(fileName)
{
}

GLSLProgramShader::~GLSLProgramShader() {
	if(m_idShader != 0){
		//std::cout << "delete shader" << std::endl;
		glDeleteShader(m_idShader);
	}
}

bool GLSLProgramShader::compileProgramFromFile(){
	std::fstream file(m_fileName.c_str(), std::ios::in);
	if(file.is_open()){
		std::istreambuf_iterator<char> fileBegin(file);
		std::istreambuf_iterator<char> fileEnd;
		std::string sourceString(fileBegin, fileEnd);

		return compileProgram(sourceString);
	}
	return false;
}
bool GLSLProgramShader::compileProgram(std::string sourceString){
	int type =
			m_type == VERTEX? GL_VERTEX_SHADER:
			m_type == FRAGMENT? GL_FRAGMENT_SHADER:
			m_type == GEOMETRY? GL_GEOMETRY_SHADER:
			0;
	unsigned int idShader = glCreateShader(type);

	const char* sourceChars = sourceString.c_str();
	glShaderSource(idShader, 1, &sourceChars, 0);
	glCompileShader(idShader);

	bool ret_noShader = false;
	int status;
	glGetShaderiv(idShader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE){
		std::cout << "compile error in ";
		std::cout << (m_type == VERTEX? "vertex shader": "fragment shader");
		std::cout << std::endl;
		int lengthInfoLog;
		glGetShaderiv(idShader, GL_INFO_LOG_LENGTH, &lengthInfoLog);

		char infoLog[lengthInfoLog];
		glGetShaderInfoLog(idShader, lengthInfoLog, 0, infoLog);
		std::cout << infoLog << std::endl;

		ret_noShader = true;
		glDeleteShader(idShader);
	}else{
		if(m_idShader != 0){
			glDeleteShader(m_idShader);
		}
		m_idShader = idShader;

//		int lengthInfoLog;
//		glGetShaderiv(idShader, GL_INFO_LOG_LENGTH, &lengthInfoLog);
//		char infoLog[lengthInfoLog];
//		glGetShaderInfoLog(idShader, lengthInfoLog, 0, infoLog);
//		std::cout << infoLog << std::endl;
	}

	return ret_noShader;
}

} /* namespace glutApp */
