/*
 * GLApplication.cpp
 *
 *  Created on: 2013/03/30
 *      Author: you
 */

#include "GLApplication.h"
#include "GLEvent.h"
#include "GLWindow.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <boost/scoped_ptr.hpp>
using boost::scoped_ptr;

namespace glutApp {

//---> private static
//scoped_ptr<GLWindow> GLApplication::s_ptrWindow(0);
//int GLApplication::s_button =0;
//int GLApplication::s_state =0;
//<--- private static
static scoped_ptr<GLWindow> g_ptrWindow(0);
static int g_button =0;
static int g_state =0;

//private
//GLApplication::GLApplication() {
//}
//GLApplication::~GLApplication() {
//}

//---> public static
void GLApplication::init(int argc, char* argv[]){
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow(argv[0]);

	glewInit();

	std::cout << "glut initialized" << std::endl;
	std::cout << "glew initialized" << std::endl;
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}
void GLApplication::start(GLWindow* window) {
	g_ptrWindow.reset(window);

	glutSetWindowTitle(g_ptrWindow->getTitle().c_str());
	glutReshapeWindow(g_ptrWindow->getWidth(), g_ptrWindow->getHeight());

	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMotion);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);

	g_ptrWindow->loaded();
	glutTimerFunc(100, timer, 0);
	glutMainLoop();

//	terminate();
	return;
}

void GLApplication::terminate(){
	g_ptrWindow->closed();
	exit(0);
}
//<--- public static

//---> private static
void GLApplication::reshape(int width, int height){
	//scoped_ptr<GLComponentEvent> e(new GLComponentEvent(width, height));
	g_ptrWindow->componentResized(GLComponentEvent(width, height));
//	s_ptrWindow->componentMoved(shared_ptr<ComponentEvent>(new ComponentEvent(width, height)));
//	s_ptrWindow->componentHidden(shared_ptr<ComponentEvent>(new ComponentEvent(width, height)));
//	s_ptrWindow->componentShown(shared_ptr<ComponentEvent>(new ComponentEvent(width, height)));
}

void GLApplication::mouse(int button, int state, int x, int y){
	g_button = button;
	g_state = state;
	//scoped_ptr<GLMouseEvent> e(new GLMouseEvent(g_button, x, y));
	g_ptrWindow->mousePressed(GLMouseEvent(g_button, x, y));
//	s_ptrWindow->mouseReleased(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
//	s_ptrWindow->mouseClicked(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
}

void GLApplication::passiveMotion(int x, int y){
//	s_ptrWindow->mouseMoved(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
//	s_ptrWindow->mouseEntered(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
//	s_ptrWindow->mouseExited(shared_ptr<MouseEvent>(new MouseEvent(m_button, x, y)));
}

void GLApplication::motion(int x, int y){
	//scoped_ptr<GLMouseEvent> e(new GLMouseEvent(g_button, x, y));
	g_ptrWindow->mouseDragged(GLMouseEvent(g_button, x, y));
}

void GLApplication::keyboard(unsigned char key, int x, int y){
	//scoped_ptr<GLKeyEvent> e(new GLKeyEvent(key));
	g_ptrWindow->keyTyped(GLKeyEvent(key));
//	s_ptrWindow->keyPressed(shared_ptr<KeyEvent>(new KeyEvent(key)));
//	s_ptrWindow->keyReleased(shared_ptr<KeyEvent>(new KeyEvent(key)));
}

void GLApplication::timer(int value){
	g_ptrWindow->timerCalled();
	glutTimerFunc(10, timer, 0);
}

void GLApplication::display(){
	//scoped_ptr<GLGraphic> e(new GLGraphic(g_ptrWindow->getWidth(), g_ptrWindow->getHeight()));
	g_ptrWindow->paint(GLGraphic(g_ptrWindow->getWidth(), g_ptrWindow->getHeight()));
}
//<--- private static

} /* namespace glutApp */
