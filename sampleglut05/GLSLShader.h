/*
 * GLSLShader.h
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#ifndef sampleglut02_GLSLSHADER_H_
#define sampleglut02_GLSLSHADER_H_

#include "headerGLSL.h"
#include <iostream>

class GLSLShader {
public:
	GLSLShader(SHADER_TYPE type, std::string fileName ="");
	~GLSLShader();

	unsigned int getID(){
		return m_idShader;
	}
	bool compileProgramFromFile();
	bool compileProgram(std::string sourceString);

private:
	unsigned int m_idShader;
	SHADER_TYPE m_type;
	std::string m_fileName;
};

#endif /* sampleglut02_GLSLSHADER_H_ */
