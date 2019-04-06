/*
 * SampleWindow.h
 *
 *  Created on: 2013/03/30
 *      Author: you
 */

#ifndef SAMPLEWINDOW_H_
#define SAMPLEWINDOW_H_


#include <glutApp/GLWindow.h>
#include <glutApp/GLMatrix.h>
#include <glutApp/GLCamera.h>
#include <glutApp/GLSLProgram.h>
#include <glutApp/IGLSLVariable.h>
using namespace glutApp;

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class SampleModelObject;

class SampleWindow: public glutApp::GLWindow {
public:
	SampleWindow(const std::string& title);
	virtual ~SampleWindow();

private:
	virtual void loaded();
	virtual void closed();
	virtual void componentResized(const GLComponentEvent& e);
	virtual void paint(const GLGraphic& e);
	virtual void keyTyped(const GLKeyEvent& e);
	virtual void mousePressed(const GLMouseEvent& e);
	virtual void mouseDragged(const GLMouseEvent& e);
	virtual void timerCalled();

private:
	void loadGLSLProgram();
	void rotateXY(double dx, double dy);
	void rotateZ();

	int m_prevMouseX;
	int m_prevMouseY;

	shared_ptr<SampleModelObject> m_modelObject;

	shared_ptr<GLSLProgram> m_glslProgram;


	unsigned int m_idVBOAttrib;
	unsigned int m_idVBOIndices;

//	shared_ptr<GLMatrix4> m_mViewMatrix;
//	shared_ptr<GLMatrix4> m_mvProjectionMatrix;
	GLMatrix4 m_mViewMatrix;
	GLMatrix4 m_mvProjectionMatrix;
	GLCamera m_camera;

	shared_ptr<GLSLUniformMatrix4> m_mvpMatrix;
};

#endif /* SAMPLEWINDOW_H_ */
