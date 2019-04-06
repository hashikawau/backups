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
		0.0, 10.0);
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
	static double delta = 0.01;

	char key = e->getKey();
	if(key == '\r'){
		m_model->loadGLSLProgram();
		glutPostRedisplay();
	}else
	if(key == 'U'){
		delta *= 2;
		std::cout << "delta = " << delta << std::endl;
	}else
	if(key == 'D'){
		delta /= 2;
		std::cout << "delta = " << delta << std::endl;
	}else
	if(key == 'u'){
		m_model->setContour(m_model->getContour() + delta);
		std::cout << "cotour = " << m_model->getContour() << std::endl;
		try{
			m_model->loadObject();
		}catch(std::string& e){
			std::cout << "caught exception - " << e << std::endl;
		}
		glutPostRedisplay();
	}else
	if(key == 'd'){
		m_model->setContour(m_model->getContour() - delta);
		std::cout << "cotour = " << m_model->getContour() << std::endl;
		try{
			m_model->loadObject();
		}catch(std::string& e){
			std::cout << "caught exception - " << e << std::endl;
		}
		glutPostRedisplay();
	}else
	if(key == ' '){
		m_model->reverseSurfaceDirection();
		try{
			m_model->loadObject();
		}catch(std::string& e){
			std::cout << "caught exception - " << e << std::endl;
		}
		glutPostRedisplay();
	}
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
	m_prevMouseX = x;
	m_prevMouseY = y;

	if(e->getButton() == GLUT_LEFT_BUTTON){
		rotateXY(dx, dy);
	}else
	if(e->getButton() == GLUT_RIGHT_BUTTON){
		rotateZ();
	}
	glutPostRedisplay();
}

void Controller01::timerCalled(){
	m_model->incrementTime();
	glutPostRedisplay();
}

void Controller01::rotateXY(double dx, double dy){
	double length = sqrt(dx *dx + dy *dy);
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

void Controller01::rotateZ(){
//	int centerX = ((UserControl)sender).Width / 2;
//	int centerY = ((UserControl)sender).Height / 2;
//	Vector3 r0 = new Vector3(
//		m_posX - centerX,
//		m_posY - centerY,
//		0.0f);
//	Vector3 r1 = new Vector3(
//		e.X - centerX,
//		e.Y - centerY,
//		0.0f);
//
//	///@note
//	///areaSquare = r0 * h0 = r1 * h1
//	/// -> (h0 * h1) / (r0 * r1) = areaSquare^2 / (r0 * r1)^2
//	///theta = R / r
//	/// ~= sqrt((h0 * h1) / (r0 * r1))
//	/// = areaSquare / (r0 * r1)
//	float areaSquare = Vector3.Cross(r0, r1).Z;
//	float rotAngle = areaSquare / (r0.Length * r1.Length);
//
//	m_cameraSceneLattice.rotate(-rotAngle, 0.0f, 0.0f, 1.0f);
}

