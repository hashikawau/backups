/*
 * GLSLProgram.h
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#ifndef sampleglut02_GLSLPROGRAM_H_
#define sampleglut02_GLSLPROGRAM_H_

#include "headerGLSL.h"
#include "GLSLShader.h"
#include <GL/glew.h>

#include <vector>
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	unsigned int getID(){
		return m_idProgram;
	}
	void enable();
	void disable();

	void linkProgram(shared_ptr<GLSLShader> vertex, shared_ptr<GLSLShader> fragment);

	void uniform1(std::string name, int value);
	void uniform2(std::string name, int* value);
	void uniform3(std::string name, int* value);
	void uniform4(std::string name, int* value);

	void uniform1(std::string name, float value);
	void uniform2(std::string name, float* value);
	void uniform3(std::string name, float* value);
	void uniform4(std::string name, float* value);

	void uniformMatrix3(std::string name, float* value);
	void uniformMatrix4(std::string name, float* value);
	void vertexAttribPointer3(std::string name, int stride, float* value);

private:
	unsigned int m_idProgram;
	std::vector<int> m_listEnabledAttrib;
};

#endif /* sampleglut02_GLSLPROGRAM_H_ */
