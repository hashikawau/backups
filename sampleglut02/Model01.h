/*
 * Model01.h
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#ifndef sampleglut02_MODEL01_H_
#define sampleglut02_MODEL01_H_

#include "IModel.h"
#include "GLSLProgram.h"

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
using boost::shared_ptr;
using boost::shared_array;

class Model01: public IModel
{
public:
	Model01();
	virtual ~Model01();

	void init();
	void loadGLSLProgram();

	float* getMatrixProj();
	void setMatrixProj(float* matrixProj);
	float* getMatrixModelRot();
	void setMatrixModelRot(float* matrixModelRot);

	void drawModel();
	void loadVertices();
	void loadNormals();
	void loadTexCoord();
	void loadIndices();

	void incrementTime();

private:
	shared_ptr<GLSLProgram> m_glslProgram;

	//unsigned int m_idGLSLProgram;
	shared_array<float> m_matrixProj;
	shared_array<float> m_matrixModelRot;

	int m_numVertices;
	int m_numIndices;
	int m_numTexCoords;
	shared_array<float> m_vertexPosition;
	shared_array<float> m_vertexNormal;
	shared_array<float> m_vertexTexCoord;
	shared_array<unsigned int> m_vertexIndices;

	unsigned int m_time;
};

#endif /* sampleglut02_MODEL01_H_ */
