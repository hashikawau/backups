/*
 * GLApplication.h
 *
 *  Created on: 2013/03/30
 *      Author: you
 */

#ifndef GLAPPLICATION_H_
#define GLAPPLICATION_H_

//#include <vector>
//#include <boost/scoped_ptr.hpp>
//using boost::scoped_ptr;

namespace glutApp {

class GLWindow;

class GLApplication {
public:
	static void init(int argc, char* argv[]);
	static void start(GLWindow* window);
	static void terminate();

private:
	static void reshape(int width, int height);
	static void mouse(int button, int state, int x, int y);
	static void passiveMotion(int x, int y);
	static void motion(int x, int y);
	static void keyboard(unsigned char key, int x, int y);
	static void display();
	static void timer(int value);

	//static scoped_ptr<GLApplication> s_application;

private:
	GLApplication();
	~GLApplication();
	GLApplication(const GLApplication& ref);
	GLApplication& operator=(const GLApplication& ref);

	//typedef	boost::scoped_ptr<GLWindow> ptrWindow;
	//std::vector<ptrWindow> m_ptrWindow;
//	static scoped_ptr<GLWindow> s_ptrWindow;
//	static int s_button;
//	static int s_state;
};

} /* namespace glutApp */
#endif /* GLAPPLICATION_H_ */
