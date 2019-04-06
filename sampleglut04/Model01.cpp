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

#include <GL/glew.h>
#include <GL/freeglut.h>

Model01::Model01()
	:m_glslProgram(shared_ptr<GLSLProgram>(new GLSLProgram())),
	 m_matrixProj(shared_array<float>(new float[16])),
	 m_matrixModelRot(shared_array<float>(new float[16])),
	 m_idVBOVertex(0),
	 m_time(0)
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
}

void Model01::init(){
	loadGLSLProgram();
	loadTexture();
	loadObject();
}

void Model01::loadGLSLProgram(){
	std::cout << "---> compile program" << std::endl;

	shared_ptr<GLSLShader> vertexShader(new GLSLShader(VERTEX, "shader00.vert"));
	if(vertexShader->compileProgramFromFile()){
		vertexShader->compileProgram("void main(){ gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; gl_FrontColor = gl_Color; }");
	}

	shared_ptr<GLSLShader> fragmentShader = shared_ptr<GLSLShader>(new GLSLShader(FRAGMENT, "shader00.frag"));
	if(fragmentShader->compileProgramFromFile()){
		fragmentShader->compileProgram("void main(){ gl_FragColor = gl_Color; }");
	}

	m_glslProgram->linkProgram(vertexShader, fragmentShader);

	std::cout << "<--- compile program" << std::endl;
	std::cout << std::endl;
}

void Model01::loadTexture(){
	int width = 16;
	int height = 16;
//	unsigned char texture[] = {
//			255, 255, 0, 0,
//			255, 255, 0, 0,
//			255, 255, 0, 0,
//			255, 255, 0, 0
//	};
//	unsigned char texture[width * height];
//	for(int i=0; i< width; ++i){
//		for(int j=0; j< height; ++j){
//			texture[width * i + j] = width * i + j;
//		}
//	}
	unsigned char texture[width * height * 4];
	for(int i=0; i< width * height * 4; ++i){
		texture[i] = (i / width) * 4;
	}

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_idTexture);
	glBindTexture(GL_TEXTURE_2D, m_idTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_R8, GL_UNSIGNED_BYTE, texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Model01::loadObject(){
	float root2 = 1 / sqrt(2);
	Vertex v[] = {
			//
			{{-0.5,  0.0,  0.5}, { 0.0,   root2,  root2}, {0.0, 0.0}},
			{{ 0.5,  0.0,  0.5}, { 0.0,   root2,  root2}, {1.0, 0.0}},
			{{-0.5,  0.5,  0.0}, { 0.0,   root2,  root2}, {0.0, 1.0}},
			{{ 0.5,  0.5,  0.0}, { 0.0,   root2,  root2}, {1.0, 1.0}},
			{{-0.5,  0.0, -0.5}, { 0.0,  -root2, -root2}, {0.0, 0.0}},
			{{ 0.5,  0.0, -0.5}, { 0.0,  -root2, -root2}, {1.0, 0.0}},
			{{-0.5, -0.5,  0.0}, { 0.0,  -root2, -root2}, {0.0, 1.0}},
			{{ 0.5, -0.5,  0.0}, { 0.0,  -root2, -root2}, {1.0, 1.0}},
			//
			{{-0.5, -0.5,  0.0}, { 0.0,  -root2,  root2}, {0.0, 0.0}},
			{{ 0.5, -0.5,  0.0}, { 0.0,  -root2,  root2}, {1.0, 0.0}},
			{{-0.5,  0.0,  0.5}, { 0.0,  -root2,  root2}, {0.0, 1.0}},
			{{ 0.5,  0.0,  0.5}, { 0.0,  -root2,  root2}, {1.0, 1.0}},
			{{-0.5,  0.5,  0.0}, { 0.0,   root2, -root2}, {0.0, 0.0}},
			{{ 0.5,  0.5,  0.0}, { 0.0,   root2, -root2}, {1.0, 0.0}},
			{{-0.5,  0.0, -0.5}, { 0.0,   root2, -root2}, {0.0, 1.0}},
			{{ 0.5,  0.0, -0.5}, { 0.0,   root2, -root2}, {1.0, 1.0}},
			//
			{{-0.5,  0.5,  0.0}, {-1.0,  0.0,  0.0}, {0.0, 0.0}},
			{{-0.5,  0.0, -0.5}, {-1.0,  0.0,  0.0}, {1.0, 0.0}},
			{{-0.5,  0.0,  0.5}, {-1.0,  0.0,  0.0}, {0.0, 1.0}},
			{{-0.5, -0.5,  0.0}, {-1.0,  0.0,  0.0}, {1.0, 1.0}},
			{{ 0.5,  0.5,  0.0}, { 1.0,  0.0,  0.0}, {0.0, 0.0}},
			{{ 0.5,  0.0,  0.5}, { 1.0,  0.0,  0.0}, {1.0, 0.0}},
			{{ 0.5,  0.0, -0.5}, { 1.0,  0.0,  0.0}, {0.0, 1.0}},
			{{ 0.5, -0.5,  0.0}, { 1.0,  0.0,  0.0}, {1.0, 1.0}}
	};

	glGenBuffers(1, &m_idVBOVertex);
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

//	int num = 4 * 6;
//	m_vertexTexCoord = shared_array<float>(new float[num * 2]);
//	for(int i=0; i< num; ++i){
//		m_vertexTexCoord[2 * i + 0] = v[i].texc[0];
//		m_vertexTexCoord[2 * i + 1] = v[i].texc[1];
//	}

	unsigned int vertexIndices[] = {
			//z= -0.5
			 0,  1,  2,
			 3,  2,  1,
			//z= 0.5
			 4,  5,  6,
			 7,  6,  5,
			//y= -0.5
			 8,  9, 10,
			11, 10,  9,
			//y= 0.5
			12, 13, 14,
			15, 14, 13,
			//x= -0.5
			16, 17, 18,
			19, 18, 17,
			//x= 0.5
			20, 21, 22,
			23, 22, 21
	};
	m_numIndices = 2 * 6 * 3;
	m_vertexIndices = shared_array<unsigned int>(new unsigned int[m_numIndices]);
	for(int i=0; i< m_numIndices; ++i){
		m_vertexIndices[i] = vertexIndices[i];
	}
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
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_matrixModelRot.get());
	glScalef(1.0f, 1.0f, 10.0f);
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
	//<---

	m_time = m_time % 200;
	float timeRatio = m_time / 200.0;

	m_glslProgram->enable();
	m_glslProgram->uniform1("u_timeRatio", timeRatio);

	m_glslProgram->uniformMatrix4("u_mvMatrix", mvMatrix);
	m_glslProgram->uniformMatrix4("u_mvpMatrix", mvpMatrix);
	m_glslProgram->uniformMatrix3("u_nMatrix", nMatrix);
	m_glslProgram->uniform1("u_texture0", 0);
	//---> vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOVertex);
	int locationV = glGetAttribLocation(m_glslProgram->getID(), "a_vertex");
	glVertexAttribPointer(locationV, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 0));
	int locationN = glGetAttribLocation(m_glslProgram->getID(), "a_normal");
	glVertexAttribPointer(locationN, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 3));
	int locationTC = glGetAttribLocation(m_glslProgram->getID(), "a_texCoord");
	glVertexAttribPointer(locationTC, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 5));
	glEnableVertexAttribArray(locationV);
	glEnableVertexAttribArray(locationN);
	glEnableVertexAttribArray(locationTC);
	//<--- vbo

	glBindTexture(GL_TEXTURE_2D, m_idTexture);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glTexCoordPointer(2, GL_FLOAT, 0, m_vertexTexCoord.get());


	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, m_vertexIndices.get());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	m_glslProgram->disable();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glutSwapBuffers();
}

void Model01::incrementTime(){
	++m_time;
}

