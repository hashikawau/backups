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
//	unsigned char texture[width * height];
//	for(int i=0; i< width; ++i){
//		for(int j=0; j< height; ++j){
//			//texture[width * i + j] = (int)(i / 16) * 8 + 64;
//			texture[width * i + j] = 128;
//		}
//		//texture[width * 0 + i] = 0;
//	}
//	for(int i=0; i< width; ++i){
//		texture[width * 0 + i] = 0;
//		texture[width * 1 + i] = 0;
//	}
	unsigned char texture[width * height];
	for(int i=0; i< width; ++i){
		for(int j=0; j< height; ++j){
			texture[width * i + j] = (int)(sqrt(i*i + j*j) / 8) * 16;
		}
	}

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
	float root2 = sqrt(2) / 2;
	Vertex v[] = {
			//
			{{-0.5,  0.0,  0.5}, { 0.0,   root2,  root2}, {0.0, 0.0}},
			{{ 0.5,  0.0,  0.5}, { 0.0,   root2,  root2}, {1.0, 0.0}},
			{{-0.5,  0.5,  0.0}, { 0.0,   root2,  root2}, {0.0, 1.0}},
			{{ 0.5,  0.5,  0.0}, { 0.0,   root2,  root2}, {1.0, 1.0}},
			{{-0.5,  0.0, -0.5}, { 0.0,  -root2, -root2}, {1.0, 0.0}},
			{{ 0.5,  0.0, -0.5}, { 0.0,  -root2, -root2}, {0.0, 0.0}},
			{{-0.5, -0.5,  0.0}, { 0.0,  -root2, -root2}, {1.0, 1.0}},
			{{ 0.5, -0.5,  0.0}, { 0.0,  -root2, -root2}, {0.0, 1.0}},
			//
			{{-0.5, -0.5,  0.0}, { 0.0,  -root2,  root2}, {1.0, 0.0}},
			{{ 0.5, -0.5,  0.0}, { 0.0,  -root2,  root2}, {1.0, 1.0}},
			{{-0.5,  0.0,  0.5}, { 0.0,  -root2,  root2}, {0.0, 0.0}},
			{{ 0.5,  0.0,  0.5}, { 0.0,  -root2,  root2}, {0.0, 1.0}},
			{{-0.5,  0.5,  0.0}, { 0.0,   root2, -root2}, {1.0, 1.0}},
			{{ 0.5,  0.5,  0.0}, { 0.0,   root2, -root2}, {1.0, 0.0}},
			{{-0.5,  0.0, -0.5}, { 0.0,   root2, -root2}, {0.0, 1.0}},
			{{ 0.5,  0.0, -0.5}, { 0.0,   root2, -root2}, {0.0, 0.0}},
			//
			{{-0.5,  0.5,  0.0}, {-1.0,  0.0,  0.0}, {1.0, 0.0}},
			{{-0.5,  0.0, -0.5}, {-1.0,  0.0,  0.0}, {1.0, 1.0}},
			{{-0.5,  0.0,  0.5}, {-1.0,  0.0,  0.0}, {0.0, 0.0}},
			{{-0.5, -0.5,  0.0}, {-1.0,  0.0,  0.0}, {0.0, 1.0}},
			{{ 0.5,  0.5,  0.0}, { 1.0,  0.0,  0.0}, {1.0, 0.0}},
			{{ 0.5,  0.0,  0.5}, { 1.0,  0.0,  0.0}, {1.0, 1.0}},
			{{ 0.5,  0.0, -0.5}, { 1.0,  0.0,  0.0}, {0.0, 0.0}},
			{{ 0.5, -0.5,  0.0}, { 1.0,  0.0,  0.0}, {0.0, 1.0}}
	};

	glGenBuffers(1, &m_idVBOVertex);
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//--->
	unsigned int indices[] = {
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

//	m_numIndices = 2 * 6 * 3;
//	m_vertexIndices = shared_array<unsigned int>(new unsigned int[m_numIndices]);
//	for(int i=0; i< m_numIndices; ++i){
//		m_vertexIndices[i] = indices[i];
//	}

	m_numIndices = sizeof(indices) / sizeof(int);
	glGenBuffers(1, &m_idVBOIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idVBOIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//<---
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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

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
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOVertex);
	int locationV = glGetAttribLocation(m_glslProgram->getID(), "a_vertex");
	glVertexAttribPointer(locationV, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 0));
	int locationN = glGetAttribLocation(m_glslProgram->getID(), "a_normal");
	glVertexAttribPointer(locationN, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 3));
	int locationTC = glGetAttribLocation(m_glslProgram->getID(), "a_texCoord");
	glVertexAttribPointer(locationTC, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 6));
	glEnableVertexAttribArray(locationV);
	glEnableVertexAttribArray(locationN);
	glEnableVertexAttribArray(locationTC);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idVBOIndices);
	//<--- vbo setup

	glBindTexture(GL_TEXTURE_2D, m_idTexture);

	//glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, m_vertexIndices.get());
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	//---> vbo teardown
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//<--- vbo teardown

	m_glslProgram->disable();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glutSwapBuffers();
}

void Model01::incrementTime(){
	++m_time;
}

