/*
 * GLWindow.cpp
 *
 *  Created on: 2013/03/30
 *      Author: you
 */

#include "GLWindow.h"

//#include <boost/shared_ptr.hpp>
//using boost::shared_ptr;

namespace glutApp {

GLWindow::GLWindow(const std::string& title)
	:m_title(title),
	 m_width(640),
	 m_height(480)
{
}

GLWindow::~GLWindow() {
}

void GLWindow::setSize(int width, int height) {
	m_width = width;
	m_height = height;
}

//private virtual
void GLWindow::loaded(){}
void GLWindow::closed(){}
void GLWindow::componentResized(const GLComponentEvent& e){}
void GLWindow::paint(const GLGraphic& e){}
void GLWindow::keyTyped(const GLKeyEvent& e){}
void GLWindow::mousePressed(const GLMouseEvent& e){}
void GLWindow::mouseDragged(const GLMouseEvent& e){}
void GLWindow::timerCalled(){}


} /* namespace glutApp */
