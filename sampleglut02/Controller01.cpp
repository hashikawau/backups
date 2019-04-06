/*
 * Controller01.cpp
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#include "Controller01.h"
#include "ApplicationForGLUT.h"

#include <fstream>
#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>


Controller01::Controller01(shared_ptr<Model01> model)
	:m_prevMouseX(0),
	 m_prevMouseY(0),
	 m_model(model)
{
}

Controller01::~Controller01() {
}

void Controller01::loaded(){

	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glewInit();

	m_model->init();
}
void Controller01::closed(){
}

void Controller01::componentResized(shared_ptr<ComponentEvent> e){
	int width = e->getWidth();
	int height = e->getHeight();
	glViewport(0, 0, width, height);

	double minLength = width < height?
			width:
			height;
	double w = width / minLength;
	double h = height / minLength;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-w, w,
		-h, h,
		-10.0, 10.0);
//	glFrustum(
//		-w, w,
//		-h, h,
//		100.0, 102.0);
	float matrixProj[16];
	glGetFloatv(GL_PROJECTION_MATRIX, matrixProj);
	m_model->setMatrixProj(matrixProj);

//	std::cout << "projection matrix = [";
//	for(int i=0; i< 4; ++i){
//		std::cout << std::endl;
//		for(int j=0; j< 4; ++j){
//			std::cout << g_matrixProj[4*i + j] << ", ";
//		}
//	}
//	std::cout << "]" << std::endl;
}

void Controller01::paint(shared_ptr<Graphic> e){
	m_model->drawModel();
}


void Controller01::keyTyped(shared_ptr<KeyEvent> e){
	char key = e->getKey();
	if(key == '\r'){
		m_model->loadGLSLProgram();
		glutPostRedisplay();
	}else
	if(key == 'q'){
		ApplicationForGLUT::terminate();
	}
}

void Controller01::mousePressed(shared_ptr<MouseEvent> e){
	m_prevMouseX = e->getX();
	m_prevMouseY = e->getY();
}

void Controller01::mouseDragged(shared_ptr<MouseEvent> e){
	int x = e->getX();
	int y = e->getY();
	double dx = x - m_prevMouseX;
	double dy = y - m_prevMouseY;
	double length = sqrt(dx *dx + dy *dy);
	m_prevMouseX = x;
	m_prevMouseY = y;
	double coefficient = 1.0;

	if(length > 1e-6){
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(length * coefficient, dy /length, dx /length, 0.0);
		float matrixRot[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrixRot);

		glMultMatrixf(m_model->getMatrixModelRot());
		float matrixModelRot[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrixModelRot);
		m_model->setMatrixModelRot(matrixModelRot);

//		std::cout << "rotation matrix = [";
//		for(int i=0; i< 4; ++i){
//			std::cout << std::endl;
//			for(int j=0; j< 4; ++j){
//				std::cout << matrixModelRot[4*i + j] << ", ";
//			}
//		}
//		std::cout << "]" << std::endl;

		//glutPostRedisplay();
	}
}

void Controller01::timerCalled(){
	m_model->incrementTime();
	glutPostRedisplay();
}

