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
	 m_idVBOIndices(0),
	 m_numVertices(0),
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

	float lightPosition[] = {0.0f, 2.0f, 0.0f};
	float lightAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	int width = 8;
	int height = 8;
	unsigned char texture[width * height];
	for(int i=0; i< width; ++i){
		for(int j=0; j< height; ++j){
			texture[width * i + j] = 32 * i;
		}
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texture);

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
	glLoadMatrixf(m_matrixProj.get());
	glMultMatrixf(m_matrixModelRot.get());
	//glScalef(1.0f, 1.0f, 2.0f);
	float* mvMatrix = m_matrixModelRot.get();
	float mvpMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mvpMatrix);
	float nMatrix[9] = {
			mvMatrix[0], mvMatrix[1], mvMatrix[2],
			mvMatrix[4], mvMatrix[5], mvMatrix[6],
			mvMatrix[8], mvMatrix[9], mvMatrix[10]
	};

	//--->
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glLoadMatrixf(m_matrixProj.get());
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glLoadMatrixf(m_matrixModelRot.get());
	//<---

//	float lightPosition[] = {0.0f, 1.0f, 1.0f};
	m_time = m_time % 200;
	float timeRatio = m_time / 200.0;

	m_glslProgram->enable();
//	m_glslProgram->uniform3("u_lightPosition", lightPosition);
//	m_glslProgram->uniform1("u_time", s_time);
	m_glslProgram->uniform1("u_timeRatio", timeRatio);

	m_glslProgram->uniformMatrix4("u_mvMatrix", mvMatrix);
	m_glslProgram->uniformMatrix4("u_mvpMatrix", mvpMatrix);
	m_glslProgram->uniformMatrix3("u_nMatrix", nMatrix);
	//---> va
//	m_glslProgram->vertexAttribPointer3("a_vertex", 0, m_vertexPosition.get());
//	m_glslProgram->vertexAttribPointer3("a_normal", 0, m_vertexNormal.get());
	//<--- va
	//---> vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOVertex);
	int locationV = glGetAttribLocation(m_glslProgram->getID(), "a_vertex");
	glVertexAttribPointer(locationV, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 0));
	int locationN = glGetAttribLocation(m_glslProgram->getID(), "a_normal");
	glVertexAttribPointer(locationN, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 3));
	int locationTC = glGetAttribLocation(m_glslProgram->getID(), "a_texture");
	glVertexAttribPointer(locationTC, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GL_FLOAT) * 5));
	glEnableVertexAttribArray(locationV);
	glEnableVertexAttribArray(locationN);
	glEnableVertexAttribArray(locationTC);
	//<--- vbo

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, m_vertexTexCoord.get());

	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, m_vertexIndices.get());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	m_glslProgram->disable();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glutSwapBuffers();
}

void Model01::loadObject(){
	Vertex v[] = {
			//z= -0.5
			{{-0.5, -0.5, -0.5}, { 0.0,  0.0, -1.0}, {0.0, 0.0}},
			{{-0.5,  0.5, -0.5}, { 0.0,  0.0, -1.0}, {1.0, 0.0}},
			{{ 0.5, -0.5, -0.5}, { 0.0,  0.0, -1.0}, {0.0, 1.0}},
			{{ 0.5,  0.5, -0.5}, { 0.0,  0.0, -1.0}, {1.0, 1.0}},
			//z= 0.5
			{{-0.5, -0.5,  0.5}, { 0.0,  0.0,  1.0}, {0.0, 0.0}},
			{{ 0.5, -0.5,  0.5}, { 0.0,  0.0,  1.0}, {1.0, 0.0}},
			{{-0.5,  0.5,  0.5}, { 0.0,  0.0,  1.0}, {0.0, 1.0}},
			{{ 0.5,  0.5,  0.5}, { 0.0,  0.0,  1.0}, {1.0, 1.0}},
			//y= -0.5
			{{-0.5, -0.5, -0.5}, { 0.0, -1.0,  0.0}, {0.0, 0.0}},
			{{ 0.5, -0.5, -0.5}, { 0.0, -1.0,  0.0}, {1.0, 0.0}},
			{{-0.5, -0.5,  0.5}, { 0.0, -1.0,  0.0}, {0.0, 1.0}},
			{{ 0.5, -0.5,  0.5}, { 0.0, -1.0,  0.0}, {1.0, 1.0}},
			//y= 0.5
			{{-0.5,  0.5, -0.5}, { 0.0,  1.0,  0.0}, {0.0, 0.0}},
			{{-0.5,  0.5,  0.5}, { 0.0,  1.0,  0.0}, {1.0, 0.0}},
			{{ 0.5,  0.5, -0.5}, { 0.0,  1.0,  0.0}, {0.0, 1.0}},
			{{ 0.5,  0.5,  0.5}, { 0.0,  1.0,  0.0}, {1.0, 1.0}},
			//x= -0.5
			{{-0.5, -0.5, -0.5}, {-1.0,  0.0,  0.0}, {0.0, 0.0}},
			{{-0.5, -0.5,  0.5}, {-1.0,  0.0,  0.0}, {1.0, 0.0}},
			{{-0.5,  0.5, -0.5}, {-1.0,  0.0,  0.0}, {0.0, 1.0}},
			{{-0.5,  0.5,  0.5}, {-1.0,  0.0,  0.0}, {1.0, 1.0}},
			//x= 0.5
			{{ 0.5, -0.5, -0.5}, { 1.0,  0.0,  0.0}, {0.0, 0.0}},
			{{ 0.5,  0.5, -0.5}, { 1.0,  0.0,  0.0}, {1.0, 0.0}},
			{{ 0.5, -0.5,  0.5}, { 1.0,  0.0,  0.0}, {0.0, 1.0}},
			{{ 0.5,  0.5,  0.5}, { 1.0,  0.0,  0.0}, {1.0, 1.0}}
	};

	glGenBuffers(1, &m_idVBOVertex);
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	m_numVertices = 4 * 6;
	m_vertexPosition = shared_array<float>(new float[m_numVertices * 3]);
	m_vertexNormal = shared_array<float>(new float[m_numVertices * 3]);
	m_vertexTexCoord = shared_array<float>(new float[m_numVertices * 2]);
	for(int i=0; i< m_numVertices; ++i){
		m_vertexPosition.get()[3 * i + 0] = v[i].pos[0];
		m_vertexPosition.get()[3 * i + 1] = v[i].pos[1];
		m_vertexPosition.get()[3 * i + 2] = v[i].pos[2];
		m_vertexNormal.get()[3 * i + 0] = v[i].norm[0];
		m_vertexNormal.get()[3 * i + 1] = v[i].norm[1];
		m_vertexNormal.get()[3 * i + 2] = v[i].norm[2];
		m_vertexTexCoord.get()[2 * i + 0] = v[i].texc[0];
		m_vertexTexCoord.get()[2 * i + 1] = v[i].texc[1];
	}

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

void Model01::incrementTime(){
	++m_time;
}

