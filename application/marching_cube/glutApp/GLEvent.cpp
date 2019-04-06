/*
 * GLEvent.cpp
 *
 *  Created on: 2013/03/30
 *      Author: you
 */

#include "GLEvent.h"

namespace glutApp {

GLEvent::GLEvent() {
}
GLEvent::~GLEvent() {
}

GLComponentEvent::GLComponentEvent(int width, int height)
	:m_width(width),
	 m_height(height)
{
}
GLComponentEvent::~GLComponentEvent(){
}

GLGraphic::GLGraphic(int width, int height)
	:m_width(width),
	 m_height(height)
{
}
GLGraphic::~GLGraphic(){
}

GLKeyEvent::GLKeyEvent(char key)
	:m_key(key)
{
}
GLKeyEvent::~GLKeyEvent(){
}

GLMouseEvent::GLMouseEvent(int button, int x, int y)
	:m_button(button),
	 m_x(x),
	 m_y(y)
{
}
GLMouseEvent::~GLMouseEvent(){
}

} /* namespace glutApp */
