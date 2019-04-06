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
	float x;
	float y;
	float z;
	Normal(float x, float y, float z){
		double len = sqrt(x*x + y*y + z*z);
		this->x = x /len;
		this->y = y /len;
		this->z = z /len;
//		this->x = 1;
//		this->y = 0;
//		this->z = 0;
	}
	Normal(): x(0), y(0), z(1){}
	void set(float x, float y, float z){
		double len = sqrt(x*x + y*y + z*z);
		this->x = x /len;
		this->y = y /len;
		this->z = z /len;
	}
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
