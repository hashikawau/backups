/*
 * ApplicationForGLUT.h
 *
 *  Created on: 2013/03/27
 *      Author: scientific
 */

#ifndef sampleglut02_APPLICATIONFORGLUT_H_
#define sampleglut02_APPLICATIONFORGLUT_H_

#include "IController.h"
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class ApplicationForGLUT {
public:
	static int start(int argc, char* argv[], shared_ptr<IController> ptrWindow);
	static void terminate();

protected:
	ApplicationForGLUT();
	~ApplicationForGLUT();

private:
	static void reshape(int width, int height);
	static void mouse(int button, int state, int x, int y);
	static void passiveMotion(int x, int y);
	static void motion(int x, int y);
	static void keyboard(unsigned char key, int x, int y);
	static void display();

	static void timer(int value);

	static shared_ptr<IController> m_ptrWindow;
	static int m_button;
	static int m_state;
};

#endif /* sampleglut02_APPLICATIONFORGLUT_H_ */
