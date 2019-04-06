/*
 * Controller01.h
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#ifndef sampleglut02_CONTROLLER01_H_
#define sampleglut02_CONTROLLER01_H_

#include "IController.h"
#include "Model01.h"

class Controller01: public IController
{
public:
	Controller01(shared_ptr<Model01> model);
	virtual ~Controller01();

	virtual void loaded();
	virtual void closed();
	virtual void componentResized(shared_ptr<ComponentEvent> e);
	virtual void paint(shared_ptr<Graphic> e);
	virtual void keyTyped(shared_ptr<KeyEvent> e);
	virtual void mousePressed(shared_ptr<MouseEvent> e);
	virtual void mouseDragged(shared_ptr<MouseEvent> e);
	virtual void timerCalled();

private:
	void loadGLSLProgram();
	void rotateXY();
	void ratateZ();

	int m_prevMouseX;
	int m_prevMouseY;

	shared_ptr<Model01> m_model;
};

#endif /* sampleglut02_CONTROLLER01_H_ */
