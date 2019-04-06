/*
 * _main.cpp
 *
 *  Created on: 2013/03/25
 *      Author: scientific
 */



#include <iostream>
#include <fstream>
#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

//#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>

#include <windows.h>
//using namespace std;
//using namespace boost;


//glsl
static unsigned int g_idGLSLProgram = 0;
static unsigned int g_idTexture = 0;

//matrices
static float g_matrixProj[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
};
static float g_matrixModelRot[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
};
//static float g_vectorViewPos[3] = {
//		0.0f, 0.0f, 1.0f
//};
//static float g_vectorViewDir[3] = {
//		0.0f, 0.0f, -1.0f
//};

//mouse
static int g_mouseButton = 0;
static int g_mouseState = 0;
static int g_mousePosX = 0;
static int g_mousePosY = 0;

//functions
void init();
void destruct();
void loadGLSLProgram();

//callback functions
void reshape(int width, int height);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void display();

//classes
struct Vertex;

//definitions
int main(int argc, char* argv[]){
	std::cout << "main started" << std::endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);

	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	destruct();

	std::cout << "main terminated" << std::endl;
	return 0;
}

void init(){

	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glewInit();
	loadGLSLProgram();

	float lightPosition[] = {0.0f, 2.0f, 0.0f};
	float lightAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	int width = 8;
	int height = 8;
	unsigned char texture[width * height];
	for(int i=0; i< width; ++i){
		for(int j=0; j< height; ++j){
			texture[width * i + j] = 200;
		}
	}

	glGenTextures(1, &g_idTexture);
	glBindTexture(GL_TEXTURE_2D, g_idTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texture);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void destruct(){
	if(g_idGLSLProgram){
		std::cout << "delete GLSL program" << std::endl;
		glDeleteProgram(g_idGLSLProgram);
	}
}

void loadGLSLProgram(){


	std::string fileNameVertexShader = "test01.vert";
	unsigned int idVertexShader = glCreateShader(GL_VERTEX_SHADER);
	{
		std::cout << "compile vertex shader" << std::endl;
		unsigned int idShader = idVertexShader;

		std::fstream file(fileNameVertexShader.c_str(), std::ios::in);
		std::istreambuf_iterator<char> fileBegin(file);
		std::istreambuf_iterator<char> fileEnd;
		std::string sourceString(fileBegin, fileEnd);
		const char* sourceChars = sourceString.c_str();
		glShaderSource(idShader, 1, &sourceChars, 0);
		glCompileShader(idShader);

		int status;
		glGetShaderiv(idShader, GL_COMPILE_STATUS, &status);
		if(status == GL_FALSE){
			std::cout << "compile error in vertex shader" << std::endl;
			int lengthInfoLog;
			glGetShaderiv(idShader, GL_INFO_LOG_LENGTH, &lengthInfoLog);
			if(lengthInfoLog > 0){
				char infoLog[lengthInfoLog];
				glGetShaderInfoLog(idShader, lengthInfoLog, 0, infoLog);
				std::cout << infoLog << std::endl;
			}

			std::string sourceString = "void main(){ gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; gl_FrontColor = gl_Color; }";
			const char* sourceChars = sourceString.c_str();
			glShaderSource(idShader, 1, &sourceChars, 0);
			glCompileShader(idShader);
		}
	}

	std::string fileNameFragmentShader = "test01.frag";
	unsigned int idFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	{
		std::cout << "compile fragment shader" << std::endl;
		unsigned int idShader = idFragmentShader;
		std::fstream file(fileNameFragmentShader.c_str(), std::ios::in);
		std::istreambuf_iterator<char> fileBegin(file);
		std::istreambuf_iterator<char> fileEnd;
		std::string sourceString(fileBegin, fileEnd);
		const char* sourceChars = sourceString.c_str();
		glShaderSource(idShader, 1, &sourceChars, 0);
		glCompileShader(idShader);

		int status;
		glGetShaderiv(idShader, GL_COMPILE_STATUS, &status);
		if(status == GL_FALSE){
			std::cout << "compile error in fragment shader" << std::endl;
			int lengthInfoLog;
			glGetShaderiv(idShader, GL_INFO_LOG_LENGTH, &lengthInfoLog);
			if(lengthInfoLog > 0){
				char infoLog[lengthInfoLog];
				glGetShaderInfoLog(idShader, lengthInfoLog, 0, infoLog);
				std::cout << infoLog << std::endl;
			}

			std::string sourceString = "void main(){ gl_FragColor = gl_Color; }";
			const char* sourceChars = sourceString.c_str();
			glShaderSource(idShader, 1, &sourceChars, 0);
			glCompileShader(idShader);
		}
	}

	if(g_idGLSLProgram != 0){
		std::cout << "delete program" << std::endl;
		glDeleteProgram(g_idGLSLProgram);
	}
	{
		std::cout << "create program" << std::endl;
		g_idGLSLProgram = glCreateProgram();
		unsigned int idProgram = g_idGLSLProgram;

		glAttachShader(idProgram, idVertexShader);
		glDeleteShader(idVertexShader);

		glAttachShader(idProgram, idFragmentShader);
		glDeleteShader(idFragmentShader);

		std::cout << "link program" << std::endl;
		glLinkProgram(idProgram);

		int status;
		glGetProgramiv(idProgram, GL_LINK_STATUS, &status);
		if(status == GL_FALSE){
			std::cout << "link error in GLSL program" << std::endl;
			int lengthInfoLog;
			glGetProgramiv(idProgram, GL_INFO_LOG_LENGTH, &lengthInfoLog);
			if(lengthInfoLog > 0){
				char infoLog[lengthInfoLog];
				glGetProgramInfoLog(idProgram, lengthInfoLog, 0, infoLog);
				std::cout << infoLog << std::endl;
			}

			std::cout << "program terminated" << std::endl;
			throw new int(-1);
		}
	}
}

void reshape(int width, int height){
	glViewport(0, 0, width, height);

	double minLength = width < height?
			width:
			height;
	double w = width / minLength;
	double h = height / minLength;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-w, w,
		-h, h,
		-10.0, 10.0);
//	glFrustum(
//		-w, w,
//		-h, h,
//		100.0, 102.0);
	glGetFloatv(GL_PROJECTION_MATRIX, g_matrixProj);

//	std::cout << "projection matrix = [";
//	for(int i=0; i< 4; ++i){
//		std::cout << std::endl;
//		for(int j=0; j< 4; ++j){
//			std::cout << g_matrixProj[4*i + j] << ", ";
//		}
//	}
//	std::cout << "]" << std::endl;
}

void mouse(int button, int state, int x, int y){
	g_mouseButton = button;
	g_mouseState = state;
	g_mousePosX = x;
	g_mousePosY = y;
}

void motion(int x, int y){
	double dx = x - g_mousePosX;
	double dy = y - g_mousePosY;
	double length = sqrt(dx *dx + dy *dy);
	g_mousePosX = x;
	g_mousePosY = y;
	double coefficient = 1.0;

	if(length > 1e-6){

	//	std::cout << g_mousePosX << ", " << g_mousePosY << std::endl;
	//	std::cout << dx << ", " << dy << std::endl;
//		std::cout << length << ", " << dx /length << ", " << dy /length << std::endl;

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(length * coefficient, dy /length, dx /length, 0.0);
		float matrixRot[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrixRot);

//		glLoadMatrixf(g_matrixModelRot);
//		glMultMatrixf(matrixRot);
		glMultMatrixf(g_matrixModelRot);
		glGetFloatv(GL_MODELVIEW_MATRIX, g_matrixModelRot);

//		std::cout << "rotation matrix = [";
//		for(int i=0; i< 4; ++i){
//			std::cout << std::endl;
//			for(int j=0; j< 4; ++j){
//	//			std::cout << g_matrixModelRot[4*i + j] << ", ";
//				std::cout << matrixRot[4*i + j] << ", ";
//			}
//		}
//		std::cout << "]" << std::endl;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
	if(key == '\r'){
		loadGLSLProgram();
		glutPostRedisplay();
	}else
	if(key == 'q'){
		exit(0);
	}
}

void display(){
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
//	glCullFace(GL_FRONT_AND_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float cr = pow(1.0, 0.3333333);



	float vertexPosition[] = {
			 0.0,  0.0, -0.5,
			 0.0,  0.0,  0.5,
			 0.0, -0.5,  0.0,
			 0.0,  0.5,  0.0,
			-0.5,  0.0,  0.0,
			 0.5,  0.0,  0.0,

			-0.5, -0.5, -0.5,
			 0.5, -0.5, -0.5,
			 0.5,  0.5, -0.5,
			-0.5,  0.5, -0.5,

			-0.5, -0.5,  0.5,
			 0.5, -0.5,  0.5,
			 0.5,  0.5,  0.5,
			-0.5,  0.5,  0.5
	};
	float vertexNormal[] = {
			 0.0,  0.0, -1.0,
			 0.0,  0.0,  1.0,
			 0.0, -1.0,  0.0,
			 0.0,  1.0,  0.0,
			-1.0,  0.0,  0.0,
			 1.0,  0.0,  0.0,

			-cr, -cr, -cr,
			 cr, -cr, -cr,
			 cr,  cr, -cr,
			-cr,  cr, -cr,

			-cr, -cr,  cr,
			 cr, -cr,  cr,
			 cr,  cr,  cr,
			-cr,  cr,  cr
	};
	float vertexTexCoord[] = {
			0.5, 0.5,
			0.5, 0.5,
			0.5, 0.5,
			0.5, 0.5,
			0.5, 0.5,
			0.5, 0.5,

			1.0, 0.0,
			0.0, 0.0,
			0.0, 1.0,
			1.0, 1.0,

			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0,
			0.0, 1.0
	};
	unsigned int vertexIndices[] = {
			//z= -0.5
			0, 6, 9,
			0, 9, 8,
			0, 8, 7,
			0, 7, 6,
			//z= 0.5
			1, 10, 11,
			1, 11, 12,
			1, 12, 13,
			1, 13, 10,
			//y= -0.5
			2, 6, 7,
			2, 7, 11,
			2, 11, 10,
			2, 10, 6,
			//y= 0.5
			3, 8, 9,
			3, 9, 13,
			3, 13, 12,
			3, 12, 8,
			//x= -0.5
			4, 6, 10,
			4, 10, 13,
			4, 13, 9,
			4, 9, 6,
			//x= 0.5
			5, 7, 8,
			5, 8, 12,
			5, 12, 11,
			5, 11, 7
	};

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(g_matrixProj);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(g_matrixModelRot);

	glActiveTexture(GL_TEXTURE0);
	glUseProgram(g_idGLSLProgram);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexPosition);
	glNormalPointer(GL_FLOAT, 0, vertexNormal);
	glTexCoordPointer(2, GL_FLOAT, 0, vertexTexCoord);

	glEnable(GL_TEXTURE_2D);
	glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, vertexIndices);
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glutSwapBuffers();
}


//--->
struct Vertex
{
public:

private:

};
//<---

