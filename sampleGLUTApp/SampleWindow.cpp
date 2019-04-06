/*
 * SampleWindow.cpp
 *
 *  Created on: 2013/03/30
 *      Author: you
 */

#include "SampleWindow.h"
#include <glutApp/GLApplication.h>
#include <glutApp/GLEvent.h>
#include <glutApp/GLSLProgram.h>
#include <glutApp/GLSLProgramShader.h>
#include <glutApp/IGLSLVariable.h>

#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
//#include <boost/shared_ptr.hpp>
//using boost::shared_ptr;

#include "SampleModelObject.h"

SampleWindow::SampleWindow(const std::string& title)
	:GLWindow(title),
	 m_prevMouseX(0),
	 m_prevMouseY(0),
	 m_modelObject(new SampleModelObject()),
//	 m_idVBOAttrib(0),
//	 m_idVBOIndices(0),
	 m_glslProgram(new GLSLProgram()),
	 m_mViewMatrix(GLMatrix4::createIdentity()),
	 m_mvProjectionMatrix(GLMatrix4::createIdentity()),
	 m_mvpMatrix(shared_ptr<GLSLUniformMatrix4>(new GLSLUniformMatrix4(GLMatrix4::createIdentity())))
{
	glGenBuffers(1, &m_idVBOAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOAttrib);
	glBufferData(GL_ARRAY_BUFFER, m_modelObject->getNumVertices() * sizeof(float), m_modelObject->getVertices().get(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_idVBOIndices);
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOIndices);
	glBufferData(GL_ARRAY_BUFFER, m_modelObject->getNumIndices() * sizeof(unsigned int), m_modelObject->getIndices().get(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	loadGLSLProgram();
}

SampleWindow::~SampleWindow() {
	glDeleteBuffers(1, &m_idVBOAttrib);
	glDeleteBuffers(1, &m_idVBOIndices);
}

void SampleWindow::loadGLSLProgram(){
	std::cout << "---> compile program" << std::endl;

	shared_ptr<GLSLProgramShader> vertexShader(new GLSLProgramShader(VERTEX, "shader00.vert"));
	if(vertexShader->compileProgramFromFile()){
		vertexShader->compileProgram("void main(){ gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; gl_FrontColor = gl_Color; }");
	}

	shared_ptr<GLSLProgramShader> fragmentShader(new GLSLProgramShader(FRAGMENT, "shader00.frag"));
	if(fragmentShader->compileProgramFromFile()){
		fragmentShader->compileProgram("void main(){ gl_FragColor = gl_Color; }");
	}

	m_glslProgram->setUniform("u_mvpMatrix", m_mvpMatrix);

	m_glslProgram->linkProgram(vertexShader, fragmentShader);

	std::cout << "<--- compile program" << std::endl;
	std::cout << std::endl;
}

//private virtual
void SampleWindow::loaded(){

}
void SampleWindow::closed(){
}

void SampleWindow::componentResized(const GLComponentEvent& e){
	int width = e.getWidth();
	int height = e.getHeight();
	glViewport(0, 0, width, height);

	double minLength = width < height?
			width:
			height;
	double w = width / minLength;
	double h = height / minLength;

	m_camera.setFovy(10.0f);
	m_camera.setPosition(GLVector3(0.0f, 0.0f, 1.0f));
	m_camera.setVolume(w, h, 5);
	m_mvProjectionMatrix = m_camera.getModelViewProjectionMatrix();

//	std::cout << "projection matrix = [";
//	for(int i=0; i< 4; ++i){
//		std::cout << std::endl;
//		for(int j=0; j< 4; ++j){
//			std::cout << g_matrixProj[4*i + j] << ", ";
//		}
//	}
//	std::cout << "]" << std::endl;
}

void SampleWindow::paint(const GLGraphic& e){
	//m_model->drawModel();
	glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(m_mvProjectionMatrix.get());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glLoadMatrixf(m_mViewMatrix.get());
//	glScalef(1.0f, 1.0f, 10.0f);

	m_glslProgram->execute();

	//m_glslProgram->enable();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);

	//---> vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_idVBOAttrib);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idVBOIndices);
	glDrawElements(GL_LINE_STRIP, m_modelObject->getNumIndices(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//<--- vbo

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);

	m_glslProgram->disable();

	glutSwapBuffers();
}


void SampleWindow::keyTyped(const GLKeyEvent& e){
	char key = e.getKey();
	if(key == '\r'){
		loadGLSLProgram();
		glutPostRedisplay();
	}else
	if(key == 'q'){
		glutApp::GLApplication::terminate();
	}
}

void SampleWindow::mousePressed(const GLMouseEvent& e){
	m_prevMouseX = e.getX();
	m_prevMouseY = e.getY();
}

void SampleWindow::mouseDragged(const GLMouseEvent& e){
	int x = e.getX();
	int y = e.getY();
	double dx = x - m_prevMouseX;
	double dy = y - m_prevMouseY;
	m_prevMouseX = x;
	m_prevMouseY = y;

	if(e.getButton() == GLUT_LEFT_BUTTON){
		rotateXY(dx, dy);
	}else
	if(e.getButton() == GLUT_RIGHT_BUTTON){
		rotateZ();
	}
}

void SampleWindow::timerCalled(){
	//m_model->incrementTime();
	glutPostRedisplay();
}

void SampleWindow::rotateXY(double dx, double dy){
	double length = sqrt(dx *dx + dy *dy);
	double coefficient = 1.0;

	if(length > 1e-6){
		GLMatrix4 rotation = GLMatrix4::createRotation(length * coefficient, dy /length, dx /length, 0.0);
		//rotation.transpose();
		m_camera.rotate(rotation);
//		GLVector3 position =
		//m_camera.getPosition().rotate(rotation);
//		position.rotate(rotation);
//		m_camera.setPosition(position);
//		std::cout << m_camera.getPosition().getX() << ", ";
//		std::cout << m_camera.getPosition().getY() << ", ";
//		std::cout << m_camera.getPosition().getZ() << std::endl;
		m_mvProjectionMatrix = m_camera.getModelViewProjectionMatrix();
		m_mvpMatrix->setValue(m_camera.getModelViewProjectionMatrix());
		//m_mViewMatrix = m_camera.getModelViewProjectionMatrix();

//		std::cout << "rotation matrix = [";
//		for(int i=0; i< 4; ++i){
//			std::cout << std::endl;
//			for(int j=0; j< 4; ++j){
//				std::cout << matrixModelRot[4*i + j] << ", ";
//			}
//		}
//		std::cout << "]" << std::endl;

		//glutPostRedisplay();
	}
}

void SampleWindow::rotateZ(){
//	int centerX = ((UserControl)sender).Width / 2;
//	int centerY = ((UserControl)sender).Height / 2;
//	Vector3 r0 = new Vector3(
//		m_posX - centerX,
//		m_posY - centerY,
//		0.0f);
//	Vector3 r1 = new Vector3(
//		e.X - centerX,
//		e.Y - centerY,
//		0.0f);
//
//	///@note
//	///areaSquare = r0 * h0 = r1 * h1
//	/// -> (h0 * h1) / (r0 * r1) = areaSquare^2 / (r0 * r1)^2
//	///theta = R / r
//	/// ~= sqrt((h0 * h1) / (r0 * r1))
//	/// = areaSquare / (r0 * r1)
//	float areaSquare = Vector3.Cross(r0, r1).Z;
//	float rotAngle = areaSquare / (r0.Length * r1.Length);
//
//	m_cameraSceneLattice.rotate(-rotAngle, 0.0f, 0.0f, 1.0f);
}

