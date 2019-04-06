/*
 * IController.h
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#ifndef sampleglut02_ICONTROLLER_H_
#define sampleglut02_ICONTROLLER_H_

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class Graphic
{
public:
	Graphic();
	~Graphic();

	int getWidth();
	int getHeight();
};

class KeyEvent
{
public:
	KeyEvent(char key);
	~KeyEvent();

	char getKey();

private:
	char m_key;
};

class MouseEvent
{
public:
	MouseEvent(int button, int x, int y);
	~MouseEvent();

	int getButton();
	int getX();
	int getY();

private:
	int m_button;
	int m_x;
	int m_y;
};


class ComponentEvent
{
public:
	ComponentEvent(int width, int height);
	~ComponentEvent();

//	Component getComponent();
	int getWidth();
	int getHeight();

private:
	int m_width;
	int m_height;
};

class IController {
public:
	IController();
	virtual ~IController() =0;

	virtual void loaded() =0;
	virtual void closed() =0;
	virtual void componentResized(shared_ptr<ComponentEvent> e) =0;
	virtual void paint(shared_ptr<Graphic> e) =0;
	virtual void keyTyped(shared_ptr<KeyEvent> e) =0;
	virtual void mousePressed(shared_ptr<MouseEvent> e) =0;
	virtual void mouseDragged(shared_ptr<MouseEvent> e) =0;
	virtual void timerCalled() =0;
};

#endif /* sampleglut02_ICONTROLLER_H_ */
