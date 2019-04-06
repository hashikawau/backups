/*
 * GLEvent.h
 *
 *  Created on: 2013/03/30
 *      Author: you
 */

#ifndef GLEVENT_H_
#define GLEVENT_H_

namespace glutApp {

class GLEvent {
public:
	GLEvent();
	virtual ~GLEvent();
};

class GLComponentEvent: public GLEvent
{
public:
	GLComponentEvent(int width, int height);
	virtual ~GLComponentEvent();

//	Component getComponent();
	int getWidth() const{
		return m_width;
	}
	int getHeight() const{
		return m_height;
	}

private:
	int m_width;
	int m_height;
};

class GLGraphic: public GLEvent
{
public:
	GLGraphic(int width, int height);
	virtual ~GLGraphic();

	int getWidth() const{
		return m_width;
	}
	int getHeight() const{
		return m_height;
	}

private:
	int m_width;
	int m_height;
};

class GLKeyEvent: public GLEvent
{
public:
	GLKeyEvent(char key);
	virtual ~GLKeyEvent();

	char getKey() const{
		return m_key;
	}

private:
	char m_key;
};

class GLMouseEvent: public GLEvent
{
public:
	GLMouseEvent(int button, int x, int y);
	virtual ~GLMouseEvent();

	int getButton() const{
		return m_button;
	}
	int getX() const{
		return m_x;
	}
	int getY() const{
		return m_y;
	}

private:
	int m_button;
	int m_x;
	int m_y;
};


} /* namespace glutApp */
#endif /* GLEVENT_H_ */
