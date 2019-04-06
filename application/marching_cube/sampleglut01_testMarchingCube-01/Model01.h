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

#include <math.h>
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

struct Normal
{
public:
	Normal(float x, float y, float z){
		double len = sqrt(x*x + y*y + z*z);
		m_norm[0] = x /len;
		m_norm[0] = y /len;
		m_norm[0] = z /len;
	}
	Normal(){
		m_norm[0] = 0.0f;
		m_norm[1] = 0.0f;
		m_norm[2] = 1.0f;
	}
	void set(float x, float y, float z){
		double len = sqrt(x*x + y*y + z*z);
		m_norm[0] = x /len;
		m_norm[0] = y /len;
		m_norm[0] = z /len;
	}
	const float* const get() const {
		return m_norm;
	}
private:
	float m_norm[3];
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
	void setContour(float value){
		m_contour = value;
	}
	float getContour(){
		return m_contour;
	}
	void reverseSurfaceDirection(){
		m_surfaceDirection = !m_surfaceDirection;
	}

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
	int m_numVertices;

	//shared_array<unsigned int> m_vertexIndices;

	unsigned int m_time;

	float m_contour;
	bool m_surfaceDirection;

	float*** m_scalarField;
	Normal*** m_normalField;
	int m_numX;
	int m_numY;
	int m_numZ;
};


#endif /* sampleglut02_MODEL01_H_ */
