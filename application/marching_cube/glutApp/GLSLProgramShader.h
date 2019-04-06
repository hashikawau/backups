/*
 * GLSLProgramShader.h
 *
 *  Created on: 2013/03/31
 *      Author: you
 */

#ifndef GLSLPROGRAMSHADER_H_
#define GLSLPROGRAMSHADER_H_

#include <string>

namespace glutApp {

enum SHADER_TYPE{
	VERTEX,
	FRAGMENT,
	GEOMETRY
};

class GLSLProgramShader {
public:
	GLSLProgramShader(SHADER_TYPE type, std::string fileName ="");
	~GLSLProgramShader();

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

} /* namespace glutApp */
#endif /* GLSLPROGRAMSHADER_H_ */
