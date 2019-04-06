/*
 * GLWindow.h
 *
 *  Created on: 2013/03/30
 *      Author: you
 */

#ifndef GLWINDOW_H_
#define GLWINDOW_H_

#include <string>

namespace glutApp {

class GLComponentEvent;
class GLGraphic;
class GLKeyEvent;
class GLMouseEvent;

class GLWindow {
public:
	GLWindow(const std::string& title);
	virtual ~GLWindow();

	const std::string& getTitle(){
		return m_title;
	}
	int getWidth(){
		return m_width;
	}
	int getHeight(){
		return m_height;
	}
	void setSize(int width, int height);

protected:

private:
friend class GLApplication;
	virtual void loaded();
	virtual void closed();
	virtual void componentResized(const GLComponentEvent& e);
	virtual void paint(const GLGraphic& e);
	virtual void keyTyped(const GLKeyEvent& e);
	virtual void mousePressed(const GLMouseEvent& e);
	virtual void mouseDragged(const GLMouseEvent& e);
	virtual void timerCalled();

private:
	std::string m_title;
	int m_width;
	int m_height;
};

} /* namespace glutApp */
#endif /* GLWINDOW_H_ */
