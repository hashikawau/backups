/*
 * ApplicationForGLUT.cpp
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */



#include "ApplicationForGLUT.h"

#include <iostream>
#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

shared_ptr<IController> ApplicationForGLUT::m_ptrWindow;
int ApplicationForGLUT::m_button;
int ApplicationForGLUT::m_state;

ApplicationForGLUT::ApplicationForGLUT()
{
}
ApplicationForGLUT::~ApplicationForGLUT() {
}

int ApplicationForGLUT::start(int argc, char* argv[], shared_ptr<IController> ptrWindow){

	m_ptrWindow = ptrWindow;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow(argv[0]);

	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMotion);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);

	m_ptrWindow->loaded();
//	glutTimerFunc(100, timer, 0);
	glutMainLoop();

//	terminate();
	return 0;
}
void ApplicationForGLUT::terminate(){
	m_ptrWindow->closed();
	exit(0);
}

void ApplicationForGLUT::reshape(int width, int height){
	m_ptrWindow->componentResized(shared_ptr<ComponentEvent>(new ComponentEvent(width, height)));
//	m_ptrWindow->componentMoved(shared_ptr<ComponentEvent>(new ComponentEvent(width, height)));
//	m_ptrWindow->componentHidden(shared_ptr<ComponentEvent>(new ComponentEvent(width, height)));
//	m_ptrWindow->componentShown(shared_ptr<ComponentEvent>(new ComponentEvent(width, height)));
}

void ApplicationForGLUT::mouse(int button, int state, int x, int y){
	m_button = button;
	m_state = state;

	m_ptrWindow->mousePressed(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
//	m_ptrWindow->mouseReleased(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
//	m_ptrWindow->mouseClicked(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
}

void ApplicationForGLUT::passiveMotion(int x, int y){
//	m_ptrWindow->mouseMoved(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
//	m_ptrWindow->mouseEntered(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
//	m_ptrWindow->mouseExited(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
}

void ApplicationForGLUT::motion(int x, int y){
	m_ptrWindow->mouseDragged(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
}

void ApplicationForGLUT::keyboard(unsigned char key, int x, int y){
	m_ptrWindow->keyTyped(shared_ptr<KeyEvent>(new KeyEvent(key)));
//	m_ptrWindow->keyPressed(shared_ptr<KeyEvent>(new KeyEvent(key)));
//	m_ptrWindow->keyReleased(shared_ptr<KeyEvent>(new KeyEvent(key)));
}

void ApplicationForGLUT::timer(int value){
	m_ptrWindow->timerCalled();
	glutTimerFunc(10, timer, 0);
}

void ApplicationForGLUT::display(){
	m_ptrWindow->paint(shared_ptr<Graphic>(new Graphic()));
}


