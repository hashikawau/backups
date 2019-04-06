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

struct Vertex
{
public:
	float pos[3];
	float norm[3];
	float texc[2];
};

class Model01: public IModel
{
public:
	Model01();
	virtual ~Model01();

	void init();
	void loadGLSLProgram();
	void loadTexture();
	void loadObject();

	float* getMatrixProj();
	void setMatrixProj(float* matrixProj);
	float* getMatrixModelRot();
	void setMatrixModelRot(float* matrixModelRot);

	void drawModel();

	void incrementTime();

private:
	shared_ptr<GLSLProgram> m_glslProgram;

	shared_array<float> m_matrixProj;
	shared_array<float> m_matrixModelRot;



	//shared_array<float> m_vertexTexCoord;
	unsigned int m_idTexture;
	unsigned int m_idVBOVertex;

	unsigned int m_idVBOIndices;
	int m_numIndices;

	//shared_array<unsigned int> m_vertexIndices;

	unsigned int m_time;
};


#endif /* sampleglut02_MODEL01_H_ */
