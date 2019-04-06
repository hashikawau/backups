/*
 * Model01.cpp
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#define GL_GLEXT_PROTOTYPES
#include "Model01.h"
#include "headerGLSL.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>
#include <boost/scoped_ptr.hpp>

#include <sys/time.h>
#include <omp.h>

#include <GL/glew.h>
#include <GL/freeglut.h>


//===============================================
inline long int getTick(){
	timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
inline float linearInterpolation(float leftValue, float rightValue, float middleValue){
	return (middleValue - leftValue) / (rightValue - leftValue);
}
inline float linearInterpolation(float leftValue, float rightValue, float subValue1, float subValue2, float middleValue){
	double temp = subValue1 + subValue2;
	double a = leftValue - temp + rightValue;
	double b = -2 * leftValue + temp;
	double c = leftValue - middleValue;

	float ret_intp = -1.0f;
	if(fabs(a) > 1e-6){
		bool hasSolv = false;
		double temp1 = b*b - 4 *a *c;
		if(temp1 >= 0.0){
			double temp2 = sqrt(temp1);
			double solvation = (-b + temp2) /a /2;
			if(solvation >= 0.0 && solvation <= 1.0){
				ret_intp = solvation;
				hasSolv = true;
			}
			solvation = (-b - temp2) /a /2;
			if(solvation >= 0.0 && solvation <= 1.0){
				if(hasSolv){
//					double temp = -c / b;
//					if(fabs(ret_intp - temp) < fabs(solvation - temp)){
//						ret_intp = solvation;
//					}
//					throw std::string("linearInterpolation() - hasSolv == true");
					ret_intp = -1.0f;
				}else{
					ret_intp = solvation;
				}
			}
		}
	}else{
		ret_intp = -c / b;
//		throw std::string("linearInterpolation() - fabs(a) == 0.0f");
//		ret_intp = (middleValue - leftValue) / (rightValue - leftValue);
	}
//	ret_intp = (middleValue - leftValue) / (rightValue - leftValue);
	return ret_intp;
}
inline const Normal linearInterpolation(
		const Normal& leftValue,
		const Normal& rightValue,
		float interpolatedPos)
{
	float t1 = 1 - interpolatedPos;
	float t2 = interpolatedPos;
	float x = leftValue.get()[0] * t1 + rightValue.get()[0] * t2;
	float y = leftValue.get()[1] * t1 + rightValue.get()[1] * t2;
	float z = leftValue.get()[2] * t1 + rightValue.get()[2] * t2;
	return Normal(x, y, z);
}
inline const Normal linearInterpolation(
		const Normal& leftValue,
		const Normal& rightValue,
		const Normal& subValue1,
		const Normal& subValue2,
		float interpolatedPos)
{
	float s_0 = interpolatedPos;
	float s_1 = 1 - interpolatedPos;
	float t1 = s_1 *s_1;
	float t2 = s_0 *s_0;
	float t3 = s_0 *s_1;
	float x = leftValue.get()[0] * t1 + rightValue.get()[0] * t2 + (subValue1.get()[0] + subValue2.get()[0]) * t3;
	float y = leftValue.get()[1] * t1 + rightValue.get()[1] * t2 + (subValue1.get()[1] + subValue2.get()[1]) * t3;
	float z = leftValue.get()[2] * t1 + rightValue.get()[2] * t2 + (subValue1.get()[2] + subValue2.get()[2]) * t3;
	return Normal(x, y, z);
}
inline const Normal linearInterpolation(
		const Normal& leftValue,
		const Normal& rightValue,
		const Normal& subValue1,
		const Normal& subValue2,
		const Normal& subValue3,
		const Normal& subValue4,
		const Normal& subValue5,
		const Normal& subValue6,
		float interpolatedPos)
{
	float s_0 = interpolatedPos;
	float s_1 = 1 - interpolatedPos;
	float t1 = s_1 *s_1 *s_1;
	float t2 = s_0 *s_0 *s_0;
	float t3 = s_0 *s_1 *s_1;
	float t4 = s_0 *s_0 *s_1;
	float x = leftValue.get()[0] * t1 + rightValue.get()[0] * t2 + (subValue1.get()[0] + subValue2.get()[0] + subValue3.get()[0]) * t3 + (subValue4.get()[0] + subValue5.get()[0] + subValue6.get()[0]) * t4;
	float y = leftValue.get()[1] * t1 + rightValue.get()[1] * t2 + (subValue1.get()[1] + subValue2.get()[1] + subValue3.get()[1]) * t3 + (subValue4.get()[1] + subValue5.get()[1] + subValue6.get()[1]) * t4;
	float z = leftValue.get()[2] * t1 + rightValue.get()[2] * t2 + (subValue1.get()[2] + subValue2.get()[2] + subValue3.get()[2]) * t3 + (subValue4.get()[2] + subValue5.get()[2] + subValue6.get()[2]) * t4;
	return Normal(x, y, z);
}
inline int sign(float x){
	return x < 0.0f?
			-1:
			1;
}

//===============================================
struct Index{
public:
	inline Index(int i, int j, int k, int m);
	inline Index(int i, int j, int k);
	inline Index(const Index& ref);
	inline Index& operator=(const Index& ref);

	inline bool operator<(const Index& operand) const;
//	inline bool operator>(const Index& operand) const;
	inline void show() const{
		std::cout << "\t" << m_i << ", " << m_j << ", " << m_k << ", " << m_m << std::endl;
	}

	short int m_i;
	short int m_j;
	short int m_k;
	short int m_m;
};
Index::Index(int i, int j, int k, int m)
	:m_i(i),
	 m_j(j),
	 m_k(k),
	 m_m(m)
{
}
Index::Index(int i, int j, int k)
	:m_i(i),
	 m_j(j),
	 m_k(k),
	 m_m(0)
{
}
Index::Index(const Index& ref)
	:m_i(ref.m_i),
	 m_j(ref.m_j),
	 m_k(ref.m_k),
	 m_m(ref.m_m)
{
}
Index& Index::operator=(const Index& ref)
{
	m_i = ref.m_i;
	m_j = ref.m_j;
	m_k = ref.m_k;
	m_m = ref.m_m;
	return *this;
}
bool Index::operator<(const Index& operand) const{
	bool ret_ = false;
	if(m_i < operand.m_i){
		ret_ = true;
	}else
	if(m_i == operand.m_i){
		if(m_j < operand.m_j){
			ret_ = true;
		}else
		if(m_j == operand.m_j){
			if(m_k < operand.m_k){
				ret_ = true;
			}else
			if(m_k == operand.m_k){
				if(m_m < operand.m_m){
					ret_ = true;
				}
			}
		}
	}
	return ret_;
}

//===============================================
class VertexInfo{
public:
	VertexInfo(){}
	VertexInfo(
			float posX,
			float posY,
			float posZ,
			int vertexIndex,
			const Normal& normal);

//	void getPosition(float out_pos[]);
//	void getNormal(float out_norm[]){
//		out_norm[0] = m_normal.x;
//		out_norm[1] = m_normal.y;
//		out_norm[2] = m_normal.z;
//	}
	const float* const getPosition() const {
		return m_pos;
	}
	const float* const getNormal() const {
		return m_normal.get();
	}
	int getVertIndex() const {
		return m_vertIndex;
	}

private:
	float m_pos[3];
//	int m_direction;
	char m_lineIndex;
	int m_vertIndex;
//	float m_interpolatedPos;
	Normal m_normal;
};
VertexInfo::VertexInfo(
		float posX,
		float posY,
		float posZ,
		int vertIndex,
		const Normal& normal)
	://m_basePos({basePosX, basePosY, basePosZ}),
	 m_vertIndex(vertIndex),
	 m_normal(normal)
{
	m_pos[0] = posX;
	m_pos[1] = posY;
	m_pos[2] = posZ;
}
//void VertexInfo::getPosition(float out_pos[]){
//	int direction = abs(m_direction);
//	float x = m_basePos[0];
//	float y = m_basePos[1];
//	float z = m_basePos[2];
//	switch(direction){
//	case 1:
//		y += m_interpolatedPos;
//		break;
//	case 2:
//		x += m_interpolatedPos;
//		break;
//	case 3:
//		x += m_interpolatedPos;
//		y += m_interpolatedPos;
//		break;
//	case 4:
//		z += m_interpolatedPos;
//		break;
//	case 5:
//		z += m_interpolatedPos;
//		x += m_interpolatedPos;
//		break;
//	case 6:
//		y += m_interpolatedPos;
//		z += m_interpolatedPos;
//		break;
//	case 7:
//		x += m_interpolatedPos;
//		y += m_interpolatedPos;
//		z += m_interpolatedPos;
//		break;
//	default:
//		throw std::string("VertexInfo::getPosition() - case default");
//		break;
//	}
//	out_pos[0] = x;
//	out_pos[1] = y;
//	out_pos[2] = z;
//}
//int VertexInfo::getIndex(){
//	return m_index;
//}

//===============================================
class TetraHedronInfo{
public:
	TetraHedronInfo();

	void addVertexInfo(unsigned int indexLine, int direction, int indexVertex);
	void addVertexInfo(int indexLine, int indexVertex);
	int getIndices(unsigned int out_indices[]);

	void setValues(float v0, float v1, float v2, float v3);
	int getVertices(float contour, bool isAscending, VertexInfo out_vertices[]);
	float m_values[4];

private:
//	std::map<unsigned char, int> m_vertIndices;

	char m_indexLine[4];
	int m_indexVertex[4];
};
TetraHedronInfo::TetraHedronInfo()
//	:m_vertIndices()
{
	m_indexLine[0] = 0;
	m_indexLine[1] = 0;
	m_indexLine[2] = 0;
	m_indexLine[3] = 0;
	m_indexVertex[0] = -1;
	m_indexVertex[1] = -1;
	m_indexVertex[2] = -1;
	m_indexVertex[3] = -1;
}
void TetraHedronInfo::setValues(float v0, float v1, float v2, float v3){
	m_values[0] = v0;
	m_values[1] = v1;
	m_values[2] = v2;
	m_values[3] = v3;
}
int TetraHedronInfo::getVertices(float contour, bool isAscending, VertexInfo out_vertices[]){
//	out_vertices[0].m_basePos[0] = 0;
//	out_vertices[0].m_basePos[1] = 0;
//	out_vertices[0].m_basePos[2] = 0;
//	out_vertices[0].m_direction = 2;
//	out_vertices[0].m_interpolatedPos = 1.0f;
//
//	out_vertices[1].m_basePos[0] = 0;
//	out_vertices[1].m_basePos[1] = 0;
//	out_vertices[1].m_basePos[2] = 0;
//	out_vertices[1].m_direction = 7;
//	out_vertices[1].m_interpolatedPos = 0.5f;
//
//	out_vertices[2].m_basePos[0] = 0;
//	out_vertices[2].m_basePos[1] = 0;
//	out_vertices[2].m_basePos[2] = 0;
//	out_vertices[2].m_direction = 3;
//	out_vertices[2].m_interpolatedPos = 0.5f;

	return 3;
}
void TetraHedronInfo::addVertexInfo(unsigned int indexLine, int direction, int indexVertex){
//	m_vertIndices[indexLine] = indexVertex;

	int num=0;
	for(int i=0; i< 4; ++i){
		if(m_indexLine[i] == 0){
			num = i;
			break;
		}
		if(i==3){
//			return;
			throw std::string("TetraHedronInfo::addVertexInfo - if(i == 3)");
		}
	}

	if(direction > 0){
		m_indexLine[num] = 0x01 << indexLine;
	}else{
		m_indexLine[num] = (0x01 << indexLine) | 0x80;
	}
	m_indexVertex[num] = indexVertex;
}
int TetraHedronInfo::getIndices(unsigned int out_indices[]){
	char patternForShape = 0;
	char patternForSurface = 0;
//	int count = 0;
	for(int i=0; i< 4; ++i){
		patternForShape |= m_indexLine[i];
		if(m_indexLine[i] & 0x80){
			patternForSurface |= m_indexLine[i];
//			++count;
		}
	}
	patternForShape &= 0x3F;
	patternForSurface &= 0x3F;

	int ret_numIndices = 0;
	char temp_indices[6] = {0};
	switch(patternForShape){
	//
	case 0x07:{
		ret_numIndices = 3;
		if(patternForSurface == 0x00){
			temp_indices[0] = 0;
			temp_indices[1] = 2;
			temp_indices[2] = 1;
		}else
		if(patternForSurface == 0x07){
			temp_indices[0] = 0;
			temp_indices[1] = 1;
			temp_indices[2] = 2;
		}else{
			throw std::string("TetraHedronInfo::getIndices() - case 0x07");
		}
		break;
	}
	case 0x19:{
		ret_numIndices = 3;
		if(patternForSurface == 0x01){
			temp_indices[0] = 0;
			temp_indices[1] = 3;
			temp_indices[2] = 4;
		}else
		if(patternForSurface == 0x18){
			temp_indices[0] = 0;
			temp_indices[1] = 4;
			temp_indices[2] = 3;
		}else{
			throw std::string("TetraHedronInfo::getIndices() - case 0x19");
		}
		break;
	}
	case 0x2A:{
		ret_numIndices = 3;
		if(patternForSurface == 0x0A){
			temp_indices[0] = 1;
			temp_indices[1] = 5;
			temp_indices[2] = 3;
		}else
		if(patternForSurface == 0x20){
			temp_indices[0] = 1;
			temp_indices[1] = 3;
			temp_indices[2] = 5;
		}else{
			throw std::string("TetraHedronInfo::getIndices() - case 0x2A");
		}
		break;
	}
	case 0x34:{
		ret_numIndices = 3;
		if(patternForSurface == 0x34){
			temp_indices[0] = 2;
			temp_indices[1] = 4;
			temp_indices[2] = 5;
		}else
		if(patternForSurface == 0){
			temp_indices[0] = 2;
			temp_indices[1] = 5;
			temp_indices[2] = 4;
		}else{
			throw std::string("TetraHedronInfo::getIndices() - case 0x34");
		}
		break;
	}
	//
	case 0x1E:{
		ret_numIndices = 6;
		if(patternForSurface == 0x00){
			temp_indices[0] = 1;
			temp_indices[1] = 3;
			temp_indices[2] = 2;
			temp_indices[3] = 4;
			temp_indices[4] = 2;
			temp_indices[5] = 3;
		}else
		if(patternForSurface == 0x1E){
			temp_indices[0] = 1;
			temp_indices[1] = 2;
			temp_indices[2] = 3;
			temp_indices[3] = 4;
			temp_indices[4] = 3;
			temp_indices[5] = 2;
		}else{
			throw std::string("TetraHedronInfo::getIndices() - case 0x1E");
		}
		break;
	}
	case 0x2D:{
		ret_numIndices = 6;
		if(patternForSurface == 0x08){
			temp_indices[0] = 0;
			temp_indices[1] = 2;
			temp_indices[2] = 3;
			temp_indices[3] = 5;
			temp_indices[4] = 3;
			temp_indices[5] = 2;
		}else
		if(patternForSurface == 0x25){
			temp_indices[0] = 0;
			temp_indices[1] = 3;
			temp_indices[2] = 2;
			temp_indices[3] = 5;
			temp_indices[4] = 2;
			temp_indices[5] = 3;
		}else{
			throw std::string("TetraHedronInfo::getIndices() - case 0x2D");
		}
		break;
	}
	case 0x33:{
		ret_numIndices = 6;
		if(patternForSurface == 0x30){
			temp_indices[0] = 0;
			temp_indices[1] = 4;
			temp_indices[2] = 1;
			temp_indices[3] = 5;
			temp_indices[4] = 1;
			temp_indices[5] = 4;
		}else
		if(patternForSurface == 0x03){
			temp_indices[0] = 0;
			temp_indices[1] = 1;
			temp_indices[2] = 4;
			temp_indices[3] = 5;
			temp_indices[4] = 4;
			temp_indices[5] = 1;
		}else{
			throw std::string("TetraHedronInfo::getIndices() - case 0x33");
		}
		break;
	}
	//
	default:
		return 0;
//		throw std::string("TetraHedronInfo::getIndices() - case default");
//		break;
	}

//	std::cout << "\t";
	for(int i=0; i< ret_numIndices; ++i){
//		std::cout << (int)temp_indices[i] << ", ";
		temp_indices[i] = 0x01 << temp_indices[i];
	}
//	std::cout << std::endl;

	for(int i=0; i< ret_numIndices; ++i){
		for(int index =0; index< 4; ++index){
			if((m_indexLine[index] & 0x3F) == temp_indices[i]){
				out_indices[i] = m_indexVertex[index];
				break;
			}
		}
//		out_indices[i] = m_vertIndices[temp_indices[i]];
	}
	return ret_numIndices;
}

//===============================================
Model01::Model01()
	:m_glslProgram(shared_ptr<GLSLProgram>(new GLSLProgram())),
	 m_matrixProj(shared_array<float>(new float[16])),
	 m_matrixModelRot(shared_array<float>(new float[16])),
	 m_idTexture(0),
	 m_idVBOVertex(0),
	 m_idVBOIndices(0),
	 m_numIndices(0),
	 m_numVertices(0),
	 m_time(0),
	 m_contour(0.5f),
	 m_surfaceDirection(true)
{
	float identity[] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
	};
	for(int i=0; i< 16; ++i){
		m_matrixProj[i] = identity[i];
		m_matrixModelRot[i] = identity[i];
	}

	int numX = 2 *64;
	int numY = 2 *64;
	int numZ = 2 *64;
	double _d = (double)numX * (double)numY * (double)numZ;
	if(_d > 1e7){ throw std::string("Model01::loadObject() - _d > 1e7"); }
//	bool isModeAscending = m_surfaceDirection;
//	int num = numX * numY * numZ;
//	float maxLength = sqrt((numX-1)*(numX-1) + (numY-1)*(numY-1) + (numZ-1)*(numZ-1)) /2 *2;
//	float contour = 0.6045f;
//	float contour = 0.3f;
//	float contour = m_contour;

//	float scalarField[numX][numY][numZ];
	float*** scalarField = new float**[numX];
	for(int i=0; i< numX; ++i){
		scalarField[i] = new float*[numY];
		for(int j=0; j< numY; ++j){
			scalarField[i][j] = new float[numZ];
		}
	}

//	float t_x = (numX-1) / 2.0f;
//	float t_y = (numY-1) / 2.0f;
//	float t_z = (numZ-1) / 2.0f;
//	int lenDiv = 8;

#pragma omp parallel
{
#pragma omp for
	for(int i=0; i< numX; ++i){
		for(int j=0; j< numY; ++j){
			for(int k=0; k< numZ ;++k){
				//======================================
//				scalarField[i][j][k] = fabs(i - t_x);

				//======================================
//				scalarField[i][j][k] = sqrt(
//						0.5*(i - t_x)*(i - t_x) + (j - t_y)*(j - t_y) + (k - t_z)*(k - t_z));

				//============================
//				scalarField[i][j][k] = sqrt(
//						(i - t_x)*(i - t_x) + (j - t_y)*(j - t_y) + (k - t_z)*(k - t_z)) * -4.0;
//				scalarField[i][j][k] += sqrt(
//						(i - t_x -lenDiv)*(i - t_x -lenDiv) + (j - t_y)*(j - t_y) + (k - t_z)*(k - t_z));
//				scalarField[i][j][k] += sqrt(
//						(i - t_x +lenDiv)*(i - t_x +lenDiv) + (j - t_y)*(j - t_y) + (k - t_z)*(k - t_z));
//				scalarField[i][j][k] += sqrt(
//						(i - t_x)*(i - t_x) + (j - t_y +lenDiv)*(j - t_y +lenDiv) + (k - t_z)*(k - t_z));
//				scalarField[i][j][k] += sqrt(
//						(i - t_x)*(i - t_x) + (j - t_y -lenDiv)*(j - t_y -lenDiv) + (k - t_z)*(k - t_z));
//				scalarField[i][j][k] += sqrt(
//						(i - t_x)*(i - t_x) + (j - t_y)*(j - t_y) + (k - t_z +lenDiv)*(k - t_z +lenDiv));
//				scalarField[i][j][k] += sqrt(
//						(i - t_x)*(i - t_x) + (j - t_y)*(j - t_y) + (k - t_z -lenDiv)*(k - t_z -lenDiv));

				//=====================================
				scalarField[i][j][k] = sqrt(i*i + j*j + k*k);
//				scalarField[i][j][k] = sqrt((i-1)*(i-1) + j*j + k*k);
//				scalarField[i][j][k] = sqrt(i*i + (j-1)*(j-1) + k*k);
//				scalarField[i][j][k] = sqrt(i*i + j*j + (k-1)*(k-1));
//				scalarField[i][j][k] = sqrt((i-1)*(i-1) + (j-1)*(j-1) + k*k);
//				scalarField[i][j][k] = sqrt(i*i + (j-1)*(j-1) + (k-1)*(k-1));
//				scalarField[i][j][k] = sqrt((i-1)*(i-1) + j*j + (k-1)*(k-1));
//				scalarField[i][j][k] = sqrt((i-1)*(i-1) + (j-1)*(j-1) + (k-1)*(k-1));

				//===================================
//				scalarField[i][j][k] = std::max(std::max(
//						fabs(i-(numX-1)/2.0),
//						fabs(j-(numY-1)/2.0)),
//						fabs(k-(numZ-1)/2.0));
			}
		}
	}
} //#pragma omp parallel
	float maxScalar = scalarField[0][0][0];
	float minScalar = scalarField[0][0][0];

#pragma omp parallel
{
#pragma omp for reduction(max: maxScalar) reduction(min: minScalar)
	for(int i=0; i< numX; ++i){
		for(int j=0; j< numY; ++j){
			for(int k=0; k< numZ; ++k){
				float temp = scalarField[i][j][k];
				if(temp > maxScalar){
					maxScalar = temp;
				}
				if(temp < minScalar){
					minScalar = temp;
				}
			}
		}
	}

} //#pragma omp parallel
//	std::cout << "max = " << maxScalar << ", min = " << minScalar << std::endl;
	maxScalar = maxScalar - minScalar;

#pragma omp parallel for
	for(int i=0; i< numX; ++i){
		for(int j=0; j< numY; ++j){
			for(int k=0; k< numZ; ++k){
				scalarField[i][j][k] = (scalarField[i][j][k] - minScalar) / maxScalar;
			}
		}
	}

	//
//	scalarField[0][0][0] = 0;
//	scalarField[1][0][0] = 0;
//	scalarField[0][1][0] = 0;
//	scalarField[1][1][0] = 0;
//	scalarField[0][0][1] = 1;
//	scalarField[1][0][1] = 1;
//	scalarField[0][1][1] = 1;
//	scalarField[1][1][1] = 1;

//	std::cout << "scalarField = " << std::endl;
//	for(int i=0; i< numX; ++i){
//		std::cout << "i= " << i << std::endl;
//		for(int j=0; j< numY; ++j){
//			std::cout << "\t j= " << j << std::endl;
//			for(int k=0; k< numZ ;++k){
//				std::cout << "\t\t k = " << k << std::endl;
//				std::cout << "\t\t\t value = " << scalarField[i][j][k] << std::endl;
//			}
//		}
//	}

	Normal*** normalField = new Normal**[numX];
	for(int i=0; i< numX; ++i){
		normalField[i] = new Normal*[numY];
		for(int j=0; j< numY; ++j){
			normalField[i][j] = new Normal[numZ];
		}
	}
#pragma omp parallel
{
#pragma omp for
	for(int i=1; i< numX -1; ++i){
		for(int j=1; j< numY -1; ++j){
			for(int k=1; k< numZ -1; ++k){
				normalField[i][j][k].set(
						scalarField[i+1][j][k] - scalarField[i-1][j][k],
						scalarField[i][j+1][k] - scalarField[i][j-1][k],
						scalarField[i][j][k+1] - scalarField[i][j][k-1]);
			}
		}
	}
} //#pragma omp parallel

	m_scalarField = scalarField;
	m_normalField = normalField;
	m_numX = numX;
	m_numY = numY;
	m_numZ = numZ;
}

Model01::~Model01() {
	glDeleteTextures(1, &m_idTexture);
	glDeleteBuffers(1, &m_idVBOVertex);
	glDeleteBuffers(1, &m_idVBOIndices);

	for(int i=0; i< m_numX; ++i){
		for(int j=0; j< m_numY; ++j){
			delete [] m_scalarField[i][j];
			delete [] m_normalField[i][j];
		}
		delete [] m_scalarField[i];
		delete [] m_normalField[i];
	}
	delete [] m_scalarField;
	delete [] m_normalField;
}

void Model01::init(){
	loadGLSLProgram();
	loadTexture();
	try{
		loadObject();
	}catch(std::string& e){
		std::cout << "caught exception - " << e << std::endl;
	}
}

void Model01::loadGLSLProgram(){
	std::cout << "---> compile program" << std::endl;

	shared_ptr<GLSLShader> vertexShader(new GLSLShader(VERTEX, "shader00.vert"));
	//shared_ptr<GLSLShader> vertexShader(new GLSLShader(VERTEX, "shader03-Gouraud.vert"));
	if(vertexShader->compileProgramFromFile()){
		vertexShader->compileProgram("void main(){ gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; gl_FrontColor = gl_Color; }");
	}

	shared_ptr<GLSLShader> fragmentShader = shared_ptr<GLSLShader>(new GLSLShader(FRAGMENT, "shader00.frag"));
	//shared_ptr<GLSLShader> fragmentShader = shared_ptr<GLSLShader>(new GLSLShader(FRAGMENT, "shader03-Gouraud.frag"));
	if(fragmentShader->compileProgramFromFile()){
		fragmentShader->compileProgram("void main(){ gl_FragColor = gl_Color; }");
	}

	m_glslProgram->linkProgram(vertexShader, fragmentShader);

	std::cout << "<--- compile program" << std::endl;
	std::cout << std::endl;
}

void Model01::loadTexture(){
	int width = 64;
	int height = 64;
//	unsigned char texture[] = {
//			0, 63,
//			127, 255
//	};
//	unsigned char texture[] = {
//			64, 196,
//			64, 196
//	};
//	unsigned char texture[width * height];
//	for(int i=0; i< width; ++i){
//		for(int j=0; j< height; ++j){
//			texture[width * i + j] = width * i + j;
//		}
//	}
//	unsigned char texture[width * height];
//	for(int i=0; i< width; ++i){
//		for(int j=0; j< height; ++j){
//			texture[width * i + j] = (int)(i / 8) *32;
//		}
//	}
	unsigned char texture[width * height];
	for(int i=0; i< width; ++i){
		for(int j=0; j< height; ++j){
			//texture[width * i + j] = (int)(i / 16) * 8 + 64;
			texture[width * i + j] = 128;
		}
		//texture[width * 0 + i] = 0;
	}
//	for(int i=0; i< width; ++i){
//		texture[width * 0 + i] = 0;
//		texture[width * 1 + i] = 0;
//	}
//	unsigned char texture[width * height];
//	for(int i=0; i< width; ++i){
//		for(int j=0; j< height; ++j){
//			texture[width * i + j] = (int)(sqrt(i*i + j*j) / 8) * 16;
//		}
//	}

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_idTexture);
	glBindTexture(GL_TEXTURE_2D, m_idTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
//	glPixelStorei(GL_PACK_ALIGNMENT, 1);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Model01::loadObject(){
	float*** scalarField = m_scalarField;
	Normal*** normalField = m_normalField;
	float contour = m_contour;
	int numLatticeX = m_numX;
	int numLatticeY = m_numY;
	int numLatticeZ = m_numZ;
	int numVoxelX = numLatticeX -1;
	int numVoxelY = numLatticeY -1;
	int numVoxelZ = numLatticeZ -1;
	bool isModeAscending = m_surfaceDirection;

	long int time = getTick();
	long int prevtime = time;

//#pragma omp parallel
//	{
//		unsigned char*** pattern;;
//#pragma omp single
//		{
//			pattern = new unsigned char**[numVoxelX];
//		}
//#pragma omp for
//		for(int i=0; i< numVoxelX; ++i){
//			pattern[i] = new unsigned char*[numVoxelY];
//			for(int j=0; j< numVoxelY; ++j){
//				pattern[i][j] = new unsigned char[numVoxelZ];
//				for(int k=0; k< numVoxelZ; ++k){
//					pattern[i][j][k] = 0x00;
//				}
//			}
//		}
//
//#pragma omp for
//		for(int i=0; i< numVoxelX; ++i){
//			for(int j=0; j< numVoxelY; ++j){
//				for(int k=0; k< numVoxelZ; ++k){
//					if(scalarField[i][j][k] < contour){
//
//					}
//				}
//			}
//		}
//	}

//	std::vector<int*> basePosisions(numX*numY*numZ/2);
	time = getTick();
	std::cout << "\ttime 00 = " << time - prevtime << std::endl;
	prevtime = time;

//	typedef std::map<char, VertexInfo> map_index_vertex;
//	typedef std::map<Index, map_index_vertex> map_coord_vertInfo;
//	map_coord_vertInfo vertInfos;
	typedef std::map<Index, VertexInfo> map_index_vertex;
//	map_index_vertex vertInfos;
	map_index_vertex* vertInfos;
//	typedef std::map<char, VertexInfo> index_vert;
//	typedef std::map<int, index_vert> z_index_vert;
//	typedef std::map<int, z_index_vert> y_z_index_vert;
//	typedef std::map<int, y_z_index_vert> x_y_z_index_vert;
//	x_y_z_index_vert vertInfos0;
//
//	VertexInfo***** vertInfos = new VertexInfo****[numLatticeX];
//	for(int i=0; i< numLatticeX; ++i){
//		vertInfos[i] = new VertexInfo***[numLatticeY];
//		for(int j=0; j< numLatticeY; ++j){
//			vertInfos[i][j] = new VertexInfo**[numLatticeZ];
//			for(int k=0; k< numLatticeZ; ++k){
//				vertInfos[i][j][k] = new VertexInfo*[7];
//			}
//		}
//	}

//	std::vector<VertexInfo*> vertices;

	int numThreads = 1;
#pragma omp parallel
	{
#pragma omp single
		{
			numThreads = omp_get_num_threads();
			std::cout << numThreads << std::endl;
		//	map_index_vertex voxel;

			vertInfos = new map_index_vertex[numThreads];
//		}//#pragma omp single

		int thredNum = omp_get_thread_num();
//#pragma omp for
		for(int i=0; i< numLatticeX; ++i){
			for(int j=0; j< numLatticeY; ++j){
				for(int k=0; k< numLatticeZ ;++k){
					float leftV = scalarField[i][j][k];
					//line(0->2)
					if(i < numLatticeX -1){
						float rightV = scalarField[i+1][j][k];
						float intpPos = linearInterpolation(leftV, rightV, contour);
						if(intpPos >= 0.0f && intpPos <= 1.0f){
							int latticeP = 2;
							vertInfos[thredNum][Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k)][latticeP] = VertexInfo(
	//						voxel[latticeP] = VertexInfo(
									i + intpPos,
									j,
									k,
									-1,
									linearInterpolation(normalField[i][j][k], normalField[i+1][j][k], intpPos));
						}
					}
					//line(0->1)
					if(j < numLatticeY -1){
						float rightV = scalarField[i][j+1][k];
						float intpPos = linearInterpolation(leftV, rightV, contour);
						if(intpPos >= 0.0f && intpPos <= 1.0f){
							int latticeP = 1;
							vertInfos[thredNum][Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k)][latticeP] = VertexInfo(
	//						voxel[latticeP] = VertexInfo(
									i,
									j + intpPos,
									k,
									-1,
									linearInterpolation(normalField[i][j][k], normalField[i][j+1][k], intpPos));
						}
					}
					//line(0->4)
					if(k < numLatticeZ -1){
						float rightV = scalarField[i][j][k+1];
						float intpPos = linearInterpolation(leftV, rightV, contour);
						if(intpPos >= 0.0f && intpPos <= 1.0f){
							int latticeP = 4;
							vertInfos[thredNum][Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k)][latticeP] = VertexInfo(
	//						voxel[latticeP] = VertexInfo(
									i,
									j,
									k + intpPos,
									-1,
									linearInterpolation(normalField[i][j][k], normalField[i][j][k+1], intpPos));
						}
					}
					//line(0->3)
					if(i < numLatticeX -1 && j < numLatticeY -1){
						float rightV = scalarField[i+1][j+1][k];
	//					float intpPos = linearInterpolation(leftV, rightV, contour);
						float intpPos = linearInterpolation(leftV, rightV, scalarField[i+1][j][k], scalarField[i][j+1][k], contour);
						if(intpPos >= 0.0f && intpPos <= 1.0f){
							int latticeP = 3;
							vertInfos[thredNum][Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k)][latticeP] = VertexInfo(
	//						voxel[latticeP] = VertexInfo(
									i + intpPos,
									j + intpPos,
									k,
									-1,
									linearInterpolation(normalField[i][j][k], normalField[i+1][j+1][k], normalField[i+1][j][k], normalField[i][j+1][k], intpPos));
						}
					}
					//line(0->6)
					if(j < numLatticeY -1 && k < numLatticeZ -1){
						float rightV = scalarField[i][j+1][k+1];
	//					float intpPos = linearInterpolation(leftV, rightV, contour);
						float intpPos = linearInterpolation(leftV, rightV, scalarField[i][j+1][k], scalarField[i][j][k+1], contour);
						if(intpPos >= 0.0f && intpPos <= 1.0f){
							int latticeP = 6;
							vertInfos[thredNum][Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k)][latticeP] = VertexInfo(
	//						voxel[latticeP] = VertexInfo(
									i,
									j + intpPos,
									k + intpPos,
									-1,
									linearInterpolation(normalField[i][j][k], normalField[i][j+1][k+1], normalField[i][j+1][k], normalField[i][j][k+1], intpPos));
						}
					}
					//line(0->5)
					if(k < numLatticeZ -1 && i < numLatticeX -1){
						float rightV = scalarField[i+1][j][k+1];
	//					float intpPos = linearInterpolation(leftV, rightV, contour);
						float intpPos = linearInterpolation(leftV, rightV, scalarField[i+1][j][k], scalarField[i][j][k+1], contour);
						if(intpPos >= 0.0f && intpPos <= 1.0f){
							int latticeP = 5;
							vertInfos[thredNum][Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k)][latticeP] = VertexInfo(
	//						voxel[latticeP] = VertexInfo(
									i,
									j + intpPos,
									k + intpPos,
									-1,
									linearInterpolation(normalField[i][j][k], normalField[i+1][j][k+1], normalField[i+1][j][k], normalField[i][j][k+1], intpPos));
						}
					}
					//line(0->7)
					if(i < numLatticeX -1 && j < numLatticeY -1 && k < numLatticeZ -1){
						float rightV = scalarField[i+1][j+1][k+1];
						float intpPos = linearInterpolation(leftV, rightV, contour);
						if(intpPos >= 0.0f && intpPos <= 1.0f){
							int latticeP = 7;
							vertInfos[thredNum][Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k, latticeP)] = VertexInfo(
	//						vertInfos[Index(i, j, k)][latticeP] = VertexInfo(
	//						voxel[latticeP] = VertexInfo(
									i,
									j + intpPos,
									k + intpPos,
									-1,
									linearInterpolation(normalField[i][j][k], normalField[i+1][j+1][k+1], normalField[i+1][j][k], normalField[i][j+1][k], normalField[i][j][k+1], normalField[i+1][j+1][k], normalField[i][j+1][k+1], normalField[i+1][j][k+1], intpPos));
						}
					}
	//				if(!voxel.empty()){
	//					vertInfos[Index(i, j, k)] = voxel;
	//				}
	//				voxel.clear();
				} //for k
			} //for j
		} //for i, #pragma omp for







		}
	} //#pragma omp parallel

	time = getTick();
	std::cout << "\ttime 01 = " << time - prevtime << std::endl;
	prevtime = time;


	int numVertices0 = 0;
//	for(x_y_z_index_vert::iterator it_X = vertInfos0.begin(); it_X != vertInfos0.end(); ++it_X){
//		for(y_z_index_vert::iterator it_Y = it_X->second.begin(); it_Y != it_X->second.end(); ++it_Y){
//			for(z_index_vert::iterator it_Z = it_Y->second.begin(); it_Z != it_Y->second.end(); ++it_Z){
//				for(index_vert::iterator it = it_Z->second.begin(); it != it_Z->second.end(); ++it){
//					const float* const p = it->second.getPosition();
////					std::cout << "[" << p[0] << ", " << p[1] << ", " << p[2] << "]" << std::endl;
//					++numVertices0;
//				}
//			}
//		}
//	}
//	numVertices0 = vertInfos.size();
	numVertices0 = vertInfos[0].size() + vertInfos[1].size();
//	for(map_coord_vertInfo::iterator it = vertInfos.begin(); it != vertInfos.end(); ++it){
//		numVertices0 += it->second.size();
//	}
	std::cout << "number of vertices = " << numVertices0 << std::endl;

	TetraHedronInfo tetra;
	tetra.setValues(0.0, 1.0, 1.0, 1.0);
//	int numVertices = vertInfos.size();
	VertexInfo vertices1[6];
	int numVertices = tetra.getVertices(contour, isModeAscending, vertices1);
	Vertex* v = new Vertex[numVertices];
	for(int i=0; i< numVertices; ++i){
		const float* const p = vertices1[i].getPosition();
		v[i].pos[0] = p[0] -0.5;
		v[i].pos[1] = p[1] -0.5;
		v[i].pos[2] = p[2] -0.5;
	}
//
//#pragma omp parallel for
//	for(int i=0; i< numVertices; ++i){
//		float pos[3];
//		float norm[3];
//		vertInfos[i].getPosition(pos);
//		vertInfos[i].getNormal(norm);
//
//		v[i].pos[0] = pos[0] / (numX-1) - 0.5f;
//		v[i].pos[1] = pos[1] / (numY-1) - 0.5f;
//		v[i].pos[2] = pos[2] / (numZ-1) - 0.5f;
//		v[i].norm[0] = norm[0];
//		v[i].norm[1] = norm[1];
//		v[i].norm[2] = norm[2];
////		++vertIterator;
//
////		delete vertInfos[i];
//	}
//	time = getTick();
//	std::cout << "\ttime 02 = " << time - prevtime << std::endl;
//	prevtime = time;

	m_numVertices = numVertices;
	glGenBuffers(1, &m_idVBOVertex);
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOVertex);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), v, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete v;

//	unsigned int temp_array[6];
//	std::vector<unsigned int> temp_vector;
//	for(x_y_z_index_tetra::iterator it_X = tetraInfos.begin(); it_X != tetraInfos.end(); ++it_X){
//		for(y_z_index_tetra::iterator it_Y = it_X->second.begin(); it_Y != it_X->second.end(); ++it_Y){
//			for(z_index_tetra::iterator it_Z = it_Y->second.begin(); it_Z != it_Y->second.end(); ++it_Z){
//				for(index_tetra::iterator it = it_Z->second.begin(); it != it_Z->second.end(); ++it){
//					int numIndices = it->second.getIndices(temp_array);
//
////					std::cout << "\t";
//					for(int i=0; i< numIndices; ++i){
//						temp_vector.push_back(temp_array[i]);
////						std::cout << temp_array[i] << ", ";
//					}
////					std::cout << std::endl;
//				}
//			}
//		}
//	}
//	time = getTick();
//	std::cout << "\ttime 03 = " << time - prevtime << std::endl;
//	prevtime = time;

//	m_numIndices = temp_vector.size();
//	unsigned int* indices = new unsigned int[m_numIndices];
//	for(int i=0; i< m_numIndices; ++i){
//		indices[i] = temp_vector[i];
//	}
//	time = getTick();
//	std::cout << "\ttime 04 = " << time - prevtime << std::endl;
//	prevtime = time;

//	glGenBuffers(1, &m_idVBOIndices);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idVBOIndices);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//<---

//	delete indices;

//	for(int i=0; i< numLatticeX; ++i){
//		for(int j=0; j< numLatticeY; ++j){
//			for(int k=0; k< numLatticeZ; ++k){
//				delete [] vertInfos[i][j][k];
//			}
//			delete [] vertInfos[i][j];
//		}
//		delete [] vertInfos[i];
//	}
	delete [] vertInfos;
}

float* Model01::getMatrixProj(){
	return m_matrixProj.get();
}
void Model01::setMatrixProj(float* matrixProj){
	for(int i=0; i< 16; ++i){
		m_matrixProj[i] = matrixProj[i];
	}
}
float* Model01::getMatrixModelRot(){
	return m_matrixModelRot.get();
}
void Model01::setMatrixModelRot(float* matrixModelRot){
	for(int i=0; i< 16; ++i){
		m_matrixModelRot[i] = matrixModelRot[i];
	}
}

void Model01::drawModel(){
	glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//	glFrontFace(GL_CW);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_matrixModelRot.get());
	float mvMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mvMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_matrixProj.get());
	glMultMatrixf(mvMatrix);
	float mvpMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mvpMatrix);

	float* mrotMat = m_matrixModelRot.get();
	float nMatrix[9] = {
			mrotMat[0], mrotMat[1], mrotMat[2],
			mrotMat[4], mrotMat[5], mrotMat[6],
			mrotMat[8], mrotMat[9], mrotMat[10]
	};

	//--->
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(m_matrixProj.get());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(mvMatrix);
	glScalef(1.0f, 1.0f, 10.0f);
	//<---

	m_time = m_time % 200;
	float timeRatio = m_time / 200.0;

	m_glslProgram->enable();
	m_glslProgram->uniform1("u_timeRatio", timeRatio);

	m_glslProgram->uniformMatrix4("u_mvMatrix", mvMatrix);
	m_glslProgram->uniformMatrix4("u_mvpMatrix", mvpMatrix);
	m_glslProgram->uniformMatrix3("u_nMatrix", nMatrix);
	m_glslProgram->uniform1("u_texture0", 0);
	//---> vbo setup
	int locationV = glGetAttribLocation(m_glslProgram->getID(), "a_vertex");
	int locationN = glGetAttribLocation(m_glslProgram->getID(), "a_normal");
	int locationTC = glGetAttribLocation(m_glslProgram->getID(), "a_texCoord");

	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOVertex);
	glVertexAttribPointer(locationV, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 0));
	glVertexAttribPointer(locationN, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 3));
	glVertexAttribPointer(locationTC, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 6));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(locationV);
	glEnableVertexAttribArray(locationN);
	glEnableVertexAttribArray(locationTC);

	//<--- vbo setup

	glBindTexture(GL_TEXTURE_2D, m_idTexture);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idVBOIndices);
	//glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, m_vertexIndices.get());
//	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
	glBindTexture(GL_TEXTURE_2D, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(locationV);
	glDisableVertexAttribArray(locationN);
	glDisableVertexAttribArray(locationTC);

	glBegin(GL_LINES);{
		glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f);

		glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f);
	}glEnd();

	m_glslProgram->disable();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glutSwapBuffers();
}

void Model01::incrementTime(){
	++m_time;
}

