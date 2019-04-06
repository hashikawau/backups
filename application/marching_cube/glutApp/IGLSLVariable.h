/*
 * IGLSLVariable.h
 *
 *  Created on: 2013/04/01
 *      Author: scientific
 */

#ifndef glutApp_IGLSLVARIABLE_H_
#define glutApp_IGLSLVARIABLE_H_

#include "GLMatrix.h"

namespace glutApp {

class IGLSLVariable {
public:
	IGLSLVariable();
	virtual ~IGLSLVariable() =0;

	virtual void setLocation(int location) =0;
	virtual void apply() =0;
};

class GLSLUniformMatrix4: public IGLSLVariable
{
public:
	GLSLUniformMatrix4();
	GLSLUniformMatrix4(const GLMatrix4& value);
	virtual ~GLSLUniformMatrix4();

	virtual void setLocation(int location);
	virtual void apply();

	void setValue(const GLMatrix4& value){
		m_value = value;
	}

private:
	int m_location;
	GLMatrix4 m_value;

};

class GLSLAttribPointer: public IGLSLVariable
{
public:
	GLSLAttribPointer();
	GLSLAttribPointer(unsigned int idVBO, int stride, int offset);
	virtual ~GLSLAttribPointer();

	virtual void setLocation(int location);
	virtual void apply();

	void setVBO(unsigned int idVBO){
		m_idVBO = idVBO;
	}

private:
	int m_location;
	unsigned int m_idVBO;

	int m_stride;
	int m_offset;
	int m_numCoord;
	int m_type;
};

} /* namespace glutApp */
#endif /* glutApp_IGLSLVARIABLE_H_ */
