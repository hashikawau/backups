/*
 * IController.cpp
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#include "IController.h"


IController::IController() {
}

IController::~IController() {
}

ComponentEvent::ComponentEvent(int width, int height)
	:m_width(width),
	 m_height(height)
{
}
ComponentEvent::~ComponentEvent(){
}
int ComponentEvent::getWidth(){
	return m_width;
}
int ComponentEvent::getHeight(){
	return m_height;
}

Graphic::Graphic(){
}
Graphic::~Graphic(){
}

int Graphic::getWidth(){
	return 0;
}
int Graphic::getHeight(){
	return 0;
}

KeyEvent::KeyEvent(char key)
	:m_key(key)
{
}
KeyEvent::~KeyEvent(){
}

char KeyEvent::getKey(){
	return m_key;
}


MouseEvent::MouseEvent(int button, int x, int y)
	:m_button(button),
	 m_x(x),
	 m_y(y)
{
}
MouseEvent::~MouseEvent(){
}

int MouseEvent::getButton(){
	return m_button;
}
int MouseEvent::getX(){
	return m_x;
}
int MouseEvent::getY(){
	return m_y;
}


