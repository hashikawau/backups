//============================================================================
// Name        : hello.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <stdio.h>
#include <iostream>
#include <GL/freeglut.h>
using namespace std;


//#include <GL/freeglut.h>

//----------- �v���g�^�C�v�錾 --------------//
void display();
void reshape(int w, int h);
void timer(int value);


//------------- OpenGL�̏����ݒ� ------------------//
void GLUT_INIT()
{
        glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH); //�_�u���o�b�t�@�AZ�o�b�t�@
        glutInitWindowSize(640,480);
        glutCreateWindow("free glut Primitive");
}

void GLUT_CALL_FUNC()
{
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutTimerFunc(0,timer,17);
}

void MY_INIT()
{
        glClearColor(1.0, 1.0, 1.0, 1.0);

        glEnable(GL_DEPTH_TEST);//Z�o�b�t�@ON
}



//------------- ���C���֐� ----------------//
int main(int argc, char **argv)
{
    glutInit(&argc,argv);

    GLUT_INIT();
    GLUT_CALL_FUNC();
    MY_INIT();

    glutMainLoop();

    return 0;
}

//------------ ��������R�[���o�b�N�֐� ------------------//
void display()
{
        static int r = 0;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glColor3f(0,0,1);
        glPushMatrix(); //�s��ޔ�
        glRotated(double(r), 0.0, 1.0, 0.0); //[2].��]
        static double data[]={0,0,0};
        glutWireSierpinskiSponge(2,data,1);//�V�F���s���X�L�[�̎l�ʑ�

        glPopMatrix(); //�s���߂�
        glColor3f(1,1,1);

        glutSwapBuffers();

        if(++r > 360){
                r= 0;
        }
}

void reshape(int w, int h)
{
        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION); //�s�񃂁[�h�ؑ�
        glLoadIdentity();  //�s�񏉊���
        gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

        glMatrixMode(GL_MODELVIEW); //�s�񃂁[�h�ؑ�
        glLoadIdentity();
        gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void timer(int t)
{
        glutPostRedisplay();
        glutTimerFunc(t,timer,17); //�^�C�}�[�֐�
}
