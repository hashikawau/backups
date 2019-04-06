/*
 * GLSLShader.cpp
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#include "GLSLShader.h"

#include <iostream>
#include <fstream>
#include <GL/glew.h>

GLSLShader::GLSLShader(SHADER_TYPE type, std::string fileName)
	:m_idShader(0),
	 m_type(type),
	 m_fileName(fileName)
{
}

GLSLShader::~GLSLShader() {
	if(m_idShader != 0){
		//std::cout << "delete shader" << std::endl;
		glDeleteShader(m_idShader);
	}
}

bool GLSLShader::compileProgramFromFile(){
	std::fstream file(m_fileName.c_str(), std::ios::in);
	std::istreambuf_iterator<char> fileBegin(file);
	std::istreambuf_iterator<char> fileEnd;
	std::string sourceString(fileBegin, fileEnd);

	return compileProgram(sourceString);
}
bool GLSLShader::compileProgram(std::string sourceString){
	unsigned int idShader = glCreateShader(m_type);

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

