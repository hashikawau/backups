/*
 * GLSLProgram.h
 *
 *  Created on: 2013/03/31
 *      Author: you
 */

#ifndef GLSLPROGRAM_H_
#define GLSLPROGRAM_H_

#include <string>
#include <vector>
#include <map>

namespace boost{
template<typename T> class shared_ptr;
}
using boost::shared_ptr;

namespace glutApp {

class GLSLProgramShader;
class IGLSLVariable;

class GLSLProgram {
public:
	GLSLProgram();
	~GLSLProgram();

	unsigned int getID(){
		return m_idProgram;
	}
	void enable();
	void disable();

	void linkProgram(const shared_ptr<GLSLProgramShader>& vertex, const shared_ptr<GLSLProgramShader>& fragment);

	void execute();
	void setUniform(const std::string& name, const shared_ptr<IGLSLVariable>& variable);
	void setAttribute(const std::string& name, const shared_ptr<IGLSLVariable>& variable);

	void setIndexVBO(unsigned int idVBO){
		m_IndexVBO = idVBO;
	}
	void setPrimitive(int primitive){
		m_primitive = primitive;
	}
	void setNumIndex(int num){
		m_numIndices = num;
	}

private:
	unsigned int m_idProgram;
	std::vector<int> m_listEnabledAttribs;

	typedef std::map<std::string, shared_ptr<IGLSLVariable> > MapVariables;
	MapVariables m_listUniforms;
	MapVariables m_listAttributes;

	unsigned int m_IndexVBO;
	int m_primitive;
	int m_numIndices;
};

} /* namespace glutApp */
#endif /* GLSLPROGRAM_H_ */
