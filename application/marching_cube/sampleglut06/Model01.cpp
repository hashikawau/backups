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

#include <GL/glew.h>
#include <GL/freeglut.h>


//===============================================
inline float linearInterpolation(float leftValue, float rightValue, float middleValue){
	return (middleValue - leftValue) / (rightValue - leftValue);
}
inline const Normal linearInterpolation(
		const Normal& leftValue,
		const Normal& rightValue,
		float interpolatedPos)
{
	float t1 = 1 - interpolatedPos;
	float t2 = interpolatedPos;
	float x = leftValue.x * t1 + rightValue.x * t2;
	float y = leftValue.y * t1 + rightValue.y * t2;
	float z = leftValue.z * t1 + rightValue.z * t2;
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
	float x = leftValue.x * t1 + rightValue.x * t2 + (subValue1.x + subValue2.x) * t3;
	float y = leftValue.y * t1 + rightValue.y * t2 + (subValue1.y + subValue2.y) * t3;
	float z = leftValue.z * t1 + rightValue.z * t2 + (subValue1.z + subValue2.z) * t3;
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
	float x = leftValue.x * t1 + rightValue.x * t2 + (subValue1.x + subValue2.x + subValue3.x) * t3 + (subValue4.x + subValue5.x + subValue6.x) * t4;
	float y = leftValue.y * t1 + rightValue.y * t2 + (subValue1.y + subValue2.y + subValue3.y) * t3 + (subValue4.y + subValue5.y + subValue6.y) * t4;
	float z = leftValue.z * t1 + rightValue.z * t2 + (subValue1.z + subValue2.z + subValue3.z) * t3 + (subValue4.z + subValue5.z + subValue6.z) * t4;
	return Normal(x, y, z);
}
inline int sign(float x){
	return x < 0.0f?
			-1:
			1;
}

//===============================================
class VertexInfo{
public:
	VertexInfo(
			int basePosX,
			int basePosY,
			int basePosZ,
			int direction,
			int index,
			float interpolatedPos,
			const Normal& normal);

	void getPosition(float out_pos[]);
	void getNormal(float out_norm[]){
		out_norm[0] = m_normal.x;
		out_norm[1] = m_normal.y;
		out_norm[2] = m_normal.z;
	}
	inline int getIndex();

private:
	int m_basePos[3];
	int m_direction;
	int m_index;
	float m_interpolatedPos;
	Normal m_normal;
};
VertexInfo::VertexInfo(
		int basePosX,
		int basePosY,
		int basePosZ,
		int direction,
		int index,
		float interpolatedPos,
		const Normal& normal)
	://m_basePos({basePosX, basePosY, basePosZ}),
	 m_direction(direction),
	 m_index(index),
	 m_interpolatedPos(interpolatedPos),
	 m_normal(normal)
{
	m_basePos[0] = basePosX;
	m_basePos[1] = basePosY;
	m_basePos[2] = basePosZ;
}
void VertexInfo::getPosition(float out_pos[]){
	int direction = abs(m_direction);
	float x = m_basePos[0];
	float y = m_basePos[1];
	float z = m_basePos[2];
	switch(direction){
	case 1:
		y += m_interpolatedPos;
		break;
	case 2:
		x += m_interpolatedPos;
		break;
	case 3:
		x += m_interpolatedPos;
		y += m_interpolatedPos;
		break;
	case 4:
		z += m_interpolatedPos;
		break;
	case 5:
		z += m_interpolatedPos;
		x += m_interpolatedPos;
		break;
	case 6:
		y += m_interpolatedPos;
		z += m_interpolatedPos;
		break;
	case 7:
		x += m_interpolatedPos;
		y += m_interpolatedPos;
		z += m_interpolatedPos;
		break;
	default:
		throw int(direction);
		break;
	}
	out_pos[0] = x;
	out_pos[1] = y;
	out_pos[2] = z;
}
int VertexInfo::getIndex(){
	return m_index;
}

//===============================================
class TetraHedronInfo{
public:
	TetraHedronInfo();

	void addVertexInfo(unsigned int indexLine, int direction, int indexVertex);
	void addVertexInfo(int indexLine, int indexVertex);
	int getIndices(unsigned int out_indices[]);

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
void TetraHedronInfo::addVertexInfo(unsigned int indexLine, int direction, int indexVertex){
//	m_vertIndices[indexLine] = indexVertex;

	int num=0;
	for(int i=0; i< 4; ++i){
		if(m_indexLine[i] == 0){
			num = i;
			break;
		}
		if(i==3){
			throw int(-1);
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
			throw int(-1);
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
			throw int(-1);
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
			throw int(-1);
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
			throw int(-1);
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
			throw int(-1);
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
			throw int(-1);
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
			throw int(-1);
		}
		break;
	}
	//
	default:
//		throw int(-1);
		break;
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
	 m_idVBOVertex(0),
	 m_time(0),
	 m_contour(0.5f)
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
}

Model01::~Model01() {
	glDeleteTextures(1, &m_idTexture);
	glDeleteBuffers(1, &m_idVBOVertex);
	glDeleteBuffers(1, &m_idVBOIndices);
}

void Model01::init(){
	loadGLSLProgram();
	loadTexture();
	loadObject();
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
	int numX = 16 *2;
	int numY = 16 *2;
	int numZ = 16 *2;
	double _d = (double)numX * (double)numY * (double)numZ;
	if(_d > 1e7){ throw int(-1); }
	bool isModeAscending = true;
//	int num = numX * numY * numZ;
	float maxLength = sqrt((numX-1)*(numX-1) + (numY-1)*(numY-1) + (numZ-1)*(numZ-1)) /2 *2;
//	float contour = 0.6045f;
//	float contour = 0.3f;
	float contour = m_contour;

//	float scalarField[numX][numY][numZ];
	float*** scalarField = new float**[numX];
	for(int i=0; i< numX; ++i){
		scalarField[i] = new float*[numY];
		for(int j=0; j< numY; ++j){
			scalarField[i][j] = new float[numZ];
		}
	}

	float t_x = (numX-1) / 2.0f;
	float t_y = (numY-1) / 2.0f;
	float t_z = (numZ-1) / 2.0f;
	int lenDiv = 8;
	for(int i=0; i< numX; ++i){
		for(int j=0; j< numY; ++j){
			for(int k=0; k< numZ ;++k){
//				scalarField[i][j][k] = sqrt(
//						(0.5*i - t_x)*(0.5*i - t_x) + (j - t_y)*(j - t_y) + (k - t_z)*(k - t_z)) /maxLength;
				scalarField[i][j][k] = sqrt(
						(i - t_x)*(i - t_x) + (j - t_y)*(j - t_y) + (k - t_z)*(k - t_z)) /maxLength * -4.0;
				scalarField[i][j][k] += sqrt(
						(i - t_x -lenDiv)*(i - t_x -lenDiv) + (j - t_y)*(j - t_y) + (k - t_z)*(k - t_z)) /maxLength;
				scalarField[i][j][k] += sqrt(
						(i - t_x +lenDiv)*(i - t_x +lenDiv) + (j - t_y)*(j - t_y) + (k - t_z)*(k - t_z)) /maxLength;
				scalarField[i][j][k] += sqrt(
						(i - t_x)*(i - t_x) + (j - t_y +lenDiv)*(j - t_y +lenDiv) + (k - t_z)*(k - t_z)) /maxLength;
				scalarField[i][j][k] += sqrt(
						(i - t_x)*(i - t_x) + (j - t_y -lenDiv)*(j - t_y -lenDiv) + (k - t_z)*(k - t_z)) /maxLength;
				scalarField[i][j][k] += sqrt(
						(i - t_x)*(i - t_x) + (j - t_y)*(j - t_y) + (k - t_z +lenDiv)*(k - t_z +lenDiv)) /maxLength;
				scalarField[i][j][k] += sqrt(
						(i - t_x)*(i - t_x) + (j - t_y)*(j - t_y) + (k - t_z -lenDiv)*(k - t_z -lenDiv)) /maxLength;
//				scalarField[i][j][k] = sqrt(i*i + j*j + k*k) /max;
//				scalarField[i][j][k] = sqrt((i-1)*(i-1) + j*j + k*k) /max;
//				scalarField[i][j][k] = sqrt(i*i + (j-1)*(j-1) + k*k) /max;
//				scalarField[i][j][k] = sqrt(i*i + j*j + (k-1)*(k-1)) /max;
//				scalarField[i][j][k] = sqrt((i-1)*(i-1) + (j-1)*(j-1) + k*k) /max;
//				scalarField[i][j][k] = sqrt(i*i + (j-1)*(j-1) + (k-1)*(k-1)) /max;
//				scalarField[i][j][k] = sqrt((i-1)*(i-1) + j*j + (k-1)*(k-1)) /max;
//				scalarField[i][j][k] = sqrt((i-1)*(i-1) + (j-1)*(j-1) + (k-1)*(k-1)) /max;
			}
		}
	}
	//0
//	scalarField[0][0][0] = 0;
//	scalarField[1][0][0] = 0;
//	scalarField[0][1][0] = 0;
//	scalarField[1][1][0] = 0;
//	scalarField[0][0][1] = 1;
//	scalarField[1][0][1] = 1;
//	scalarField[0][1][1] = 1;
//	scalarField[1][1][1] = 1;
	//
//	scalarField[0][0][0] = 0;
//	scalarField[1][0][0] = 0;
//	scalarField[0][1][0] = 1;
//	scalarField[1][1][0] = 1;
//	scalarField[0][0][1] = 0;
//	scalarField[1][0][1] = 0;
//	scalarField[0][1][1] = 1;
//	scalarField[1][1][1] = 1;
	//
//	scalarField[0][0][0] = 0;
//	scalarField[1][0][0] = 1;
//	scalarField[0][1][0] = 0;
//	scalarField[1][1][0] = 1;
//	scalarField[0][0][1] = 0;
//	scalarField[1][0][1] = 1;
//	scalarField[0][1][1] = 0;
//	scalarField[1][1][1] = 1;
	//

	//
//	scalarField[0][0][0] = 1;
//	scalarField[1][0][0] = 1;
//	scalarField[2][0][0] = 1;
//	scalarField[0][1][0] = 1;
//	scalarField[1][1][0] = 1;
//	scalarField[2][1][0] = 1;
//	scalarField[0][2][0] = 1;
//	scalarField[1][2][0] = 1;
//	scalarField[2][2][0] = 1;
//	scalarField[0][0][1] = 1;
//	scalarField[1][0][1] = 1;
//	scalarField[2][0][1] = 1;
//	scalarField[0][1][1] = 1;
//	scalarField[1][1][1] = 0;
//	scalarField[2][1][1] = 1;
//	scalarField[0][2][1] = 1;
//	scalarField[1][2][1] = 1;
//	scalarField[2][2][1] = 1;
//	scalarField[0][0][2] = 1;
//	scalarField[1][0][2] = 1;
//	scalarField[2][0][2] = 1;
//	scalarField[0][1][2] = 1;
//	scalarField[1][1][2] = 1;
//	scalarField[2][1][2] = 1;
//	scalarField[0][2][2] = 1;
//	scalarField[1][2][2] = 1;
//	scalarField[2][2][2] = 1;

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

	std::vector<VertexInfo*> vertInfos;
	typedef std::map<char, TetraHedronInfo> index_tetra;
	typedef std::map<int, index_tetra> z_index_tetra;
	typedef std::map<int, z_index_tetra> y_z_index_tetra;
	typedef std::map<int, y_z_index_tetra> x_y_z_index_tetra;
	x_y_z_index_tetra tetraInfos;
	for(int i=0; i< numX; ++i){
		for(int j=0; j< numY; ++j){
			for(int k=0; k< numZ ;++k){
				float leftV = scalarField[i][j][k];
				//line(0->2)
				if(i < numX -1){
					float rightV = scalarField[i+1][j][k];
					float intpPos = linearInterpolation(leftV, rightV, contour);
					if(intpPos >= 0.0f && intpPos <= 1.0f){
						int latticeP = 2;
						int vertIndex = vertInfos.size();
						vertInfos.push_back(new VertexInfo(
								i, j, k,
								latticeP,// * sign(leftV - rightV),
								vertIndex,
								intpPos,
								linearInterpolation(normalField[i][j][k], normalField[i+1][j][k], intpPos)));

						int direction = isModeAscending?
								sign(rightV - leftV):
								-sign(rightV - leftV);
//						direction = 1;
						tetraInfos[i][j][k][0].addVertexInfo(2, direction, vertIndex);
						tetraInfos[i][j][k][1].addVertexInfo(1, direction, vertIndex);

						if(j > 0){
							tetraInfos[i][j-1][k][3].addVertexInfo(5, direction, vertIndex);
						}
						if(k > 0){
							tetraInfos[i][j][k-1][2].addVertexInfo(5, -direction, vertIndex);
						}
						if(j > 0 && k > 0){
							tetraInfos[i][j-1][k-1][4].addVertexInfo(3, -direction, vertIndex);
							tetraInfos[i][j-1][k-1][5].addVertexInfo(4, -direction, vertIndex);
						}
					}
				}
				//line(0->1)
				if(j < numY -1){
					float rightV = scalarField[i][j+1][k];
					float intpPos = linearInterpolation(leftV, rightV, contour);
					if(intpPos >= 0.0f && intpPos <= 1.0f){
						int latticeP = 1;
						int vertIndex = vertInfos.size();
						vertInfos.push_back(new VertexInfo(
								i, j, k,
								latticeP,// * sign(leftV - rightV),
								vertIndex,
								intpPos,
								linearInterpolation(normalField[i][j][k], normalField[i][j+1][k], intpPos)));

						int direction = isModeAscending?
								sign(rightV - leftV):
								-sign(rightV - leftV);
//						direction = 1;
						tetraInfos[i][j][k][3].addVertexInfo(1, direction, vertIndex);
						tetraInfos[i][j][k][4].addVertexInfo(2, direction, vertIndex);

						if(k > 0){
							tetraInfos[i][j][k-1][5].addVertexInfo(5, direction, vertIndex);
						}
						if(i > 0){
							tetraInfos[i-1][j][k][0].addVertexInfo(5, -direction, vertIndex);
						}
						if(k > 0 && i > 0){
							tetraInfos[i-1][j][k-1][1].addVertexInfo(4, -direction, vertIndex);
							tetraInfos[i-1][j][k-1][2].addVertexInfo(3, -direction, vertIndex);
						}
					}
				}
				//line(0->4)
				if(k < numZ -1){
					float rightV = scalarField[i][j][k+1];
					float intpPos = linearInterpolation(leftV, rightV, contour);
					if(intpPos >= 0.0f && intpPos <= 1.0f){
						int latticeP = 4;
						int vertIndex = vertInfos.size();
						vertInfos.push_back(new VertexInfo(
								i, j, k,
								latticeP,// * sign(leftV - rightV),
								vertIndex,
								intpPos,
								linearInterpolation(normalField[i][j][k], normalField[i][j][k+1], intpPos)));

						int direction = isModeAscending?
								sign(rightV - leftV):
								-sign(rightV - leftV);
//						direction = 1;
						tetraInfos[i][j][k][2].addVertexInfo(2, direction, vertIndex);
						tetraInfos[i][j][k][5].addVertexInfo(1, direction, vertIndex);

						if(i > 0){
							tetraInfos[i-1][j][k][1].addVertexInfo(5, direction, vertIndex);
						}
						if(j > 0){
							tetraInfos[i][j-1][k][4].addVertexInfo(5, -direction, vertIndex);
						}
						if(i > 0 && j > 0){
							tetraInfos[i-1][j-1][k][0].addVertexInfo(3, -direction, vertIndex);
							tetraInfos[i-1][j-1][k][3].addVertexInfo(4, -direction, vertIndex);
						}
					}
				}
				//line(0->3)
				if(i < numX -1 && j < numY -1){
					float rightV = scalarField[i+1][j+1][k];
					float intpPos = linearInterpolation(leftV, rightV, contour);
					if(intpPos >= 0.0f && intpPos <= 1.0f){
						int latticeP = 3;
						int vertIndex = vertInfos.size();
						vertInfos.push_back(new VertexInfo(
								i, j, k,
								latticeP,// * sign(leftV - rightV),
								vertIndex,
								intpPos,
								linearInterpolation(normalField[i][j][k], normalField[i+1][j+1][k], normalField[i+1][j][k], normalField[i][j+1][k], intpPos)));

						int direction = isModeAscending?
								sign(rightV - leftV):
								-sign(rightV - leftV);
//						direction = 1;
						tetraInfos[i][j][k][0].addVertexInfo(1, direction, vertIndex);
						tetraInfos[i][j][k][3].addVertexInfo(2, direction, vertIndex);

						if(k > 0){
							tetraInfos[i][j][k-1][2].addVertexInfo(4, -direction, vertIndex);
							tetraInfos[i][j][k-1][5].addVertexInfo(3, -direction, vertIndex);
						}
					}
				}
				//line(0->6)
				if(j < numY -1 && k < numZ -1){
					float rightV = scalarField[i][j+1][k+1];
					float intpPos = linearInterpolation(leftV, rightV, contour);
					if(intpPos >= 0.0f && intpPos <= 1.0f){
						int latticeP = 6;
						int vertIndex = vertInfos.size();
						vertInfos.push_back(new VertexInfo(
								i, j, k,
								latticeP,// * sign(leftV - rightV),
								vertIndex,
								intpPos,
								linearInterpolation(normalField[i][j][k], normalField[i][j+1][k+1], normalField[i][j+1][k], normalField[i][j][k+1], intpPos)));

						int direction = isModeAscending?
								sign(rightV - leftV):
								-sign(rightV - leftV);
//						direction = 1;
						tetraInfos[i][j][k][4].addVertexInfo(1, direction, vertIndex);
						tetraInfos[i][j][k][5].addVertexInfo(2, direction, vertIndex);

						if(i > 0){
							tetraInfos[i-1][j][k][0].addVertexInfo(4, -direction, vertIndex);
							tetraInfos[i-1][j][k][1].addVertexInfo(3, -direction, vertIndex);
						}
					}
				}
				//line(0->5)
				if(k < numZ -1 && i < numX -1){
					float rightV = scalarField[i+1][j][k+1];
					float intpPos = linearInterpolation(leftV, rightV, contour);
					if(intpPos >= 0.0f && intpPos <= 1.0f){
						int latticeP = 5;
						int vertIndex = vertInfos.size();
						vertInfos.push_back(new VertexInfo(
								i, j, k,
								latticeP,// * sign(leftV - rightV),
								vertIndex,
								intpPos,
								linearInterpolation(normalField[i][j][k], normalField[i+1][j][k+1], normalField[i+1][j][k], normalField[i][j][k+1], intpPos)));

						int direction = isModeAscending?
								sign(rightV - leftV):
								-sign(rightV - leftV);
//						direction = 1;
						tetraInfos[i][j][k][1].addVertexInfo(2, direction, vertIndex);
						tetraInfos[i][j][k][2].addVertexInfo(1, direction, vertIndex);

						if(j > 0){
							tetraInfos[i][j-1][k][3].addVertexInfo(3, -direction, vertIndex);
							tetraInfos[i][j-1][k][4].addVertexInfo(4, -direction, vertIndex);
						}
					}
				}
				//line(0->7)
				if(i < numX -1 && j < numY -1 && k < numZ -1){
					float rightV = scalarField[i+1][j+1][k+1];
					float intpPos = linearInterpolation(leftV, rightV, contour);
					if(intpPos >= 0.0f && intpPos <= 1.0f){
						int latticeP = 7;
						int vertIndex = vertInfos.size();
						vertInfos.push_back(new VertexInfo(
								i, j, k,
								latticeP,// * sign(leftV - rightV),
								vertIndex,
								intpPos,
								linearInterpolation(normalField[i][j][k], normalField[i+1][j+1][k+1], normalField[i+1][j][k], normalField[i][j+1][k], normalField[i][j][k+1], normalField[i+1][j+1][k], normalField[i][j+1][k+1], normalField[i+1][j][k+1], intpPos)));

						int direction = isModeAscending?
								sign(rightV - leftV):
								-sign(rightV - leftV);
//						direction = 1;
						tetraInfos[i][j][k][0].addVertexInfo(0, direction, vertIndex);
						tetraInfos[i][j][k][1].addVertexInfo(0, direction, vertIndex);
						tetraInfos[i][j][k][2].addVertexInfo(0, direction, vertIndex);
						tetraInfos[i][j][k][3].addVertexInfo(0, direction, vertIndex);
						tetraInfos[i][j][k][4].addVertexInfo(0, direction, vertIndex);
						tetraInfos[i][j][k][5].addVertexInfo(0, direction, vertIndex);
					}
				}
			}
		}
	}
	for(int i=0; i< numX; ++i){
		for(int j=0; j< numY; ++j){
			delete [] scalarField[i][j];
			delete [] normalField[i][j];
		}
		delete [] scalarField[i];
		delete [] normalField[i];
	}
	delete [] scalarField;
	delete [] normalField;

	int numVertices = vertInfos.size();
	Vertex* v = new Vertex[numVertices];
	Vertex* vertIterator = v;

	int maxSize = std::max(numX, numY);
	maxSize = std::max(maxSize, numZ) - 1;
	float pos[3];
	float norm[3];
	for(std::vector<VertexInfo*>::iterator it = vertInfos.begin(); it != vertInfos.end(); ++it){
		(*it)->getPosition(pos);
		(*it)->getNormal(norm);
//		std::cout << (*it)->getIndex() << " = " << pos[0] << ", " << pos[1] << ", " << pos[2] << std::endl;

//		vertIterator->pos[0] = pos[0] / maxSize - 0.5f;
//		vertIterator->pos[1] = pos[1] / maxSize - 0.5f;
//		vertIterator->pos[2] = pos[2] / maxSize - 0.5f;
		vertIterator->pos[0] = pos[0] / (numX-1) - 0.5f;
		vertIterator->pos[1] = pos[1] / (numY-1) - 0.5f;
		vertIterator->pos[2] = pos[2] / (numZ-1) - 0.5f;
		vertIterator->norm[0] = norm[0];
		vertIterator->norm[1] = norm[1];
		vertIterator->norm[2] = norm[2];
		++vertIterator;

		delete *it;
	}

	glGenBuffers(1, &m_idVBOVertex);
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOVertex);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), v, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete v;

	//--->
//	unsigned int indices[] = {
//			6, 0, 3,
//			6, 5, 0,
//			6, 2, 5,
//			6, 3, 1,
//			6, 1, 4,
//			6, 4, 2
//	};

	unsigned int temp_array[6];
	std::vector<unsigned int> temp_vector;
	for(x_y_z_index_tetra::iterator it_X = tetraInfos.begin(); it_X != tetraInfos.end(); ++it_X){
		for(y_z_index_tetra::iterator it_Y = it_X->second.begin(); it_Y != it_X->second.end(); ++it_Y){
			for(z_index_tetra::iterator it_Z = it_Y->second.begin(); it_Z != it_Y->second.end(); ++it_Z){
				for(index_tetra::iterator it = it_Z->second.begin(); it != it_Z->second.end(); ++it){
					int numIndices = it->second.getIndices(temp_array);

//					std::cout << "\t";
					for(int i=0; i< numIndices; ++i){
						temp_vector.push_back(temp_array[i]);
//						std::cout << temp_array[i] << ", ";
					}
//					std::cout << std::endl;
				}
			}
		}
	}

//	m_numIndices = sizeof(indices) / sizeof(int);
	m_numIndices = temp_vector.size();
	unsigned int* indices = new unsigned int[m_numIndices];
	for(int i=0; i< m_numIndices; ++i){
		indices[i] = temp_vector[i];
	}

	glGenBuffers(1, &m_idVBOIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idVBOIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//<---

	delete indices;
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idVBOIndices);
	//glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, m_vertexIndices.get());
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(locationV);
	glDisableVertexAttribArray(locationN);
	glDisableVertexAttribArray(locationTC);

	m_glslProgram->disable();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glutSwapBuffers();
}

void Model01::incrementTime(){
	++m_time;
}

